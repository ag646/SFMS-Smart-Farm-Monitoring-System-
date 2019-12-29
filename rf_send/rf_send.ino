#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
float a=1.0;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
}
 
void loop()
{
    char msg[10];
    dtostrf(a,0,0,msg);
    rf_driver.send(msg,0);
    rf_driver.waitPacketSent();
    
    delay(100);
}
