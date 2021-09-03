#include "../../serialib/lib/serialib.h"

int main( int argc, char** argv)
{
    const std::string SERIAL_PORT = "/dev/tty.usbmodem1464301";
    
    // Serial object
    serialib serial;

    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT.c_str(), 9600);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening!=1) return errorOpening;
    
    printf ("Successful connection to %s\n",SERIAL_PORT.c_str());

    char read;
    
    // Display ASCII characters (from 32 to 128)
//    for(int c=32;c<128;c++) {
        // Loop forever
            while (1)
            {
        
        serial.readChar(&read);
        usleep(10000);
            }
//    }

    // Close the serial device
    serial.closeDevice();

    return 0 ;
}
