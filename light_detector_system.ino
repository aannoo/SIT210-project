SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler;

//buzzer
const pin_t BUZZER_PIN = D6; 

//phototransistor
const pin_t SENSOR_PIN = A0; 

//value of phototransistor
int analogvalue; 

int count = 0;

//average value of phototransistor
int averageAnalogValue = 0;

//all values
int analogValues = 0;


void setup() {
	//buzzer is output
	pinMode(BUZZER_PIN, OUTPUT);

	//declare particle variable
	Particle.variable("analogvalue", analogvalue);
}

void loop() {
	//get value from sensor
	analogvalue = analogRead(SENSOR_PIN);

	// Print value to USB debugging serial port for debugging
	Log.info("analogvalue=%d", analogvalue);

	delay(1000ms);
	
	count++;
	
	analogValues = analogValues + analogvalue;
	
	//calculate if light is on or off, log average, reset values
	if (count == 10) {
	    averageAnalogValue = analogValues / count;
	    checkForLight();
	    Log.info("averageAnalogValue=%d", averageAnalogValue);
	    count = 0;
	    averageAnalogValue = 0;
	    analogValues = 0;
	}
}


void checkForLight() {
	if (averageAnalogValue > 6) {
        // light is on, sound the alarm and send a notification!
        analogWrite(BUZZER_PIN, 100);
        Particle.publish("light_value", String("1"), PUBLIC);
    }
    else {
        // light is off, nice!
        analogWrite(BUZZER_PIN, 0);
    }
}
