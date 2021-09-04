#include "../../serialib/lib/serialib.h"

int main( int argc, char** argv)
{
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

    char read[256];
    
    // Loop forever
    while (1) {
        serial.readString(read, '\n', 256);
        
        float num_float = atof(read);
        printf("%f\n", num_float);
    }
    
    // Close the serial device
    serial.closeDevice();

    return 0 ;
}
