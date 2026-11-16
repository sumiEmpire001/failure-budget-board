#include "../../cpp/core.hpp"
using namespace embedded_budget;
Budget budget(10,2);
const unsigned long samplePeriodMs=1000;
unsigned long lastSample=0;
void setup(){pinMode(LED_BUILTIN,OUTPUT);digitalWrite(LED_BUILTIN,LOW);Serial.begin(115200);}
void loop(){
 const unsigned long now=millis();
 if((unsigned long)(now-lastSample)<samplePeriodMs)return;
 lastSample=now;
 // Replace this synthetic input with a validated, electrically safe sensor reading.
 const bool success=(digitalRead(2)==HIGH);
 if(!budget.record(success)){digitalWrite(LED_BUILTIN,LOW);Serial.println(F("FAULT: manual reset required"));return;}
 const Snapshot s=budget.snapshot();
 // LED is a diagnostic only, not a safety-rated actuator interlock.
 digitalWrite(LED_BUILTIN,s.state==Healthy?HIGH:LOW);
 Serial.print(F("failures="));Serial.println(s.failures);
 if(s.total==10){digitalWrite(LED_BUILTIN,LOW);Serial.println(F("Window complete: stop until explicit reset"));}
}
