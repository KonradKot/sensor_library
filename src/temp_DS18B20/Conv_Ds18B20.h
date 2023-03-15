#include <OneWire.h>
#include <Arduino.h>


class DS18
{
private:
    byte data[9]; // bus data
    byte addr[8]; // addres sensor
    byte model; // model sensor
    bool status; // status
    float celcius;
    uint8_t pin; // 4.7k resistor
    OneWire *h; 
    OneWire *t;
public:
    DS18(); // konstrutor domyślny
    //.....
    void begin(uint8_t);
    void connect(uint16_t);
    //......
    void calibrate(uint16_t);
    uint16_t write_raw_data(bool);
    void convert_to_celcius();
    float auto_convert_to_celcius();
    //.....
    void show_data();
    float get_celcius();
};