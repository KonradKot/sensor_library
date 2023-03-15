
#include "Conv_Ds18B20.h"

DS18::DS18()
{
    data[0]={0};
    addr[0]={0};
    celcius=0.0;
    pin=0;
    model=0;
    status=false;
    t=nullptr;
    h=nullptr;
}
void DS18::begin(uint8_t p)
{
    pin=p;
    t=new OneWire(pin);
    h=t;
}
void DS18::connect(uint16_t time=300)//time to calibrate
{
    //if(h==nullptr){return;}
    if(!(h->search(addr))){
    h->reset_search();
    delay(time);

    //if((h->crc8(addr,7)) != addr[7]){return;}

    switch (addr[0]) {
    case 0x10:
      model = 1;
      break;
    default:model=0;
    }
    return;
    }
}
void DS18::calibrate(uint16_t time=700)//time co calibrate
{
    //if(h==nullptr){return;}
    h->reset();
    h->select(addr);
    h->write(0x44,1); // convertion parasite
    h->reset();
    h->select(addr);
    h->write(0xBE); // convertion 
    delay(time);
}
uint16_t DS18::write_raw_data(bool sh=false)
{
    //if(h==nullptr){return 0;}
    for(int i=0;i<9;i++){data[i]=h->read();}
    int16_t r=((data[1]<<8)|data[0]);
    if(model){
        r=r<<3; //8 bit resolution
        if(data[7]==0x10){r=((r&0xFFF0)+12 - data[6]);}
        } //12 bit resolution
    //else{
        //byte c = (data[4]&0x60);
        //r=r&~7; // 9 bit resolution
    //}
    if(sh==true){
        Serial.println(r);
        for(int i=0;i<9;i++){Serial.println(data[i]);}
        }
    return (uint16_t)r;
}

void DS18::convert_to_celcius()
{
    celcius=((float)write_raw_data()/16.0);
}


void DS18::show_data()
{
    Serial.println(pin);
    Serial.println(model);
    Serial.println(addr[1]);
}

float DS18::get_celcius()
{
    return celcius;
}


