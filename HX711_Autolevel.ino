
#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0
#define START_PIN 12
HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library
bool Detected=false, Started=false;
void setup() {
  pinMode(START_PIN, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  scale.set_scale(10000.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale.tare();				        // reset the scale to 0

  //delay(2000);
  //scale.tare();  
}

void loop() {
bool start;
start=digitalRead(START_PIN);
if(start)
  {
    if(!Started)
    {
      //scale.power_up();		
      //delay(400);	        
      Started=true;
      scale.tare(10); 
      Serial.println("Start"); 
    }
  float value=scale.get_units(5);
  //Serial.println(value);
  if(value<-3)
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
      //delay(500);
      //scale.tare();  
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
      //scale.power_down();  // put the ADC in sleep mode
    }
    //float value=scale.get_units(5);
    //Serial.println(value);
  }
  //scale.power_up();
}
