
#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0
//#define DEBUG //Выводить в порт текущие показания
#define DETECT 3 //Порог срабатывания
#define START_PIN 12
HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library
bool Detected=false, Started=false;
void setup() {
  pinMode(START_PIN, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  scale.set_scale(10000.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale.tare();				        // reset the scale to 0

}

void loop() {
bool start;
start=digitalRead(START_PIN);
if(start)
  {
    if(!Started)
    {
      Started=true;
      scale.tare(10); 
      Serial.println("Start"); 
    }
  float value=scale.get_units(5);
  #ifdef DEBUG
  Serial.println(value);
  #endif
  if(value<-DETECT || value>DETECT)
  {
    digitalWrite(LED_BUILTIN, HIGH); 
     if(!Detected)
     {
      Serial.print("Touched ");
      Serial.println(value);
      Detected=true;
     }
    
  }else
  {
    digitalWrite(LED_BUILTIN, LOW); 
    if(Detected)
     {
      Serial.print("Released ");
      Serial.println(value);
      Detected=false;
     }
  }
  }else //end
  {
    if(Started)
    {
      Started=false;
      Detected=false;
      digitalWrite(LED_BUILTIN, LOW); 
      Serial.println("Stop"); 
    }
  }
  //scale.power_up();
}
