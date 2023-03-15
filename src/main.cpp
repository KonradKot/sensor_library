//Example of use library
#include "temp_DS18B20/Conv_Ds18B20.h"
#define XCOLD 4
#define HOT 5
#define NN 6
#define COLD 7
DS18 sensor1;  // declaration library

void setup()
{
    Serial.begin(9600); 
    sensor1.begin(A0);
}

void loop()
{
    sensor1.connect(300); // time of connect
    sensor1.calibrate(700); // time to calibrate
    sensor1.convert_to_celcius(); // function convert to celcius
    float temp=sensor1.get_celcius();
    Serial.println(temp); // print result
   
}














