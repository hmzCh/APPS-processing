const int potentiometer1 = A0;
const int potentiometer2 = A1;
const int outputPin = 9;
unsigned long timeStart = 0;

void setup() { // put your setup code here, to run once:
  pinMode(potentiometer1, INPUT);
  pinMode(potentiometer2, INPUT);
  pinMode(outputPin, OUTPUT);
  timeStart = millis(); //starts the timer
}

void loop() { // put your main code here, to run repeatedly:
  
  int voltage1 = analogRead(potentiometer1);
  int voltage2 = analogRead(potentiometer2);

  // Convert the 10-bit analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage1Converted = voltage1 * (5.0 / 1023.0);
  float voltage2Converted = voltage2 * (5.0 / 1023.0);

  if (voltage1Converted <= (voltage2Converted * 1.1) && voltage1Converted >= (voltage2Converted * 0.9)) {
    
    float averageVoltage = (voltage1Converted + voltage2Converted) / 2.0;   
    
    // Map the average voltage (0 - 5V) to a PWM value (0 - 255):
    int outputValue = averageVoltage * (255.0 / 5.0);   
    
    analogWrite(outputPin, outputValue);

    timeStart = millis(); //resets the timer if an implausability hasn't happened
  
  } else if (millis() - timeStart > 100) { //implausability
    
    //Shut down power to the motor
    analogWrite(outputPin, 0); //[don't know if this is correct]
 
  }

}
