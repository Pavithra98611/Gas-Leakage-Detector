#include <IRremote.h>

int pin = 8;
int MQ2sensor = A0;
int sensorValue = 0;
int recpin = 11;
bool on = true;

IRrecv irrecv(recpin);
decode_results results;

void setup() 
{
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() 
{
  sensorValue = analogRead(MQ2sensor);
  if(sensorValue>750) 
  {
  	Serial.print("SENSOR VALUE : ");
    Serial.print(sensorValue, DEC);
    Serial.println(" ==>> SMOKE DETECTED");
    if(on)
    {	
    	digitalWrite(pin, HIGH);
    }
    if(irrecv.decode(&results))
    {
    	Serial.println(results.value, HEX);
    	irrecv.resume();
      	if(results.value == 0xFD30CF)
        {
         	digitalWrite(pin, LOW);
           	on = false;
        } 
		else if(results.value == 0xFD08F7)
        {
			digitalWrite(pin, HIGH);
			on = true;
        }
	}
  }
  else 
  {
    digitalWrite(pin, LOW);
	Serial.print("SENSOR VALUE : ");
    on = true;
    Serial.println(sensorValue, DEC);
  }
  delay(500);
}