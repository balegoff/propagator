#include <stdio.h>
#include <vector>

#include "serialib.h"

#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

void errorcb(int error, const char* desc)
{
    printf("GLFW error %d: %s\n", error, desc);
}

static void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    NVG_NOTUSED(scancode);
    NVG_NOTUSED(mods);
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        printf("Space key pressed \n");
    }
}

int main() {
    
    GLFWwindow* window;
    NVGcontext* vg = NULL;
    double prevt = 0;

    if (!glfwInit()) {
        printf("Failed to init GLFW.");
        return -1;
    }

    // Serial connection init -----
    
    const std::string SERIAL_PORT = "/dev/tty.usbmodem1464301";
    
    // Serial object
    serialib serial;
    
    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT.c_str(), 9600);
    
    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1) {
        return errorOpening;
    }
    
    printf ("Successful connection to %s\n",SERIAL_PORT.c_str());
        
    // -----

    glfwSetErrorCallback(errorcb);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1000, 600, "Propagator", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key);
    glfwMakeContextCurrent(window);
    
#ifdef NANOVG_GLEW
    if(glewInit() != GLEW_OK) {
        printf("Could not init glew.\n");
        return -1;
    }
#endif

    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

    if (vg == NULL) {
        printf("Could not init nanovg.\n");
        return -1;
    }

    glfwSwapInterval(0);

    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    
    std::vector<float> voltages(winWidth, 0);
    uint32_t current_pos = 0;
    char read[256];
    
    while (!glfwWindowShouldClose(window))
    {
        double mx, my, t, dt;
        int fbWidth, fbHeight;
        float pxRatio;

        glfwGetCursorPos(window, &mx, &my);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        // Calculate pixel ration for hi-dpi devices.
        pxRatio = (float)fbWidth / (float)winWidth;
        
        // Update data -----
        
        float val = 0.f;
        
        for(uint32_t i=0; i < 4 ; ++i) { // Get peak point between 4 measurements
            serial.readString(read, '\n', 256);
            float num_float = atof(read);
            val = std::max(val, num_float);
        }

        voltages[current_pos] = val;
        current_pos = (current_pos + 1) % voltages.size();
        //printf("%f\n", val);
    
        // Update and render -----
        
        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        nvgBeginPath(vg);
        nvgMoveTo(vg, 0, winHeight*(1.f - voltages[0]*2));
        
        for(uint32_t i=0; i < voltages.size(); ++i) {
            nvgLineTo(vg, i, winHeight*(1.f - voltages[i]*2)); // considering max is 0.5V for now
        }

        nvgStrokeColor(vg, nvgRGB(255, 255, 255));
        nvgStrokeWidth(vg, 2);
        nvgStroke(vg);

        nvgEndFrame(vg);
        
        // -----
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    nvgDeleteGL2(vg);

    glfwTerminate();
    return 0;
}
