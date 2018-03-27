const int buttonPin = 11; 

int redPin= 4;
int greenPin = 7;
int bluePin = 2 ;

int motorPin= 12;

int buttonState = 0; 

int weight = 200;
float hrsDay = .1;
float water;
float drink;
const int temperaturePin = 0;

void setup() {
  Serial.begin(9600);

  pinMode(motorPin, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonPin, INPUT);

  water = getWaterIntake();
  
}
void loop() {
   float voltage, degreesC, degreesF;
   buttonState = digitalRead(buttonPin);
    Serial.println(temperaturePin);
  if (buttonState == HIGH) {
     voltage = getVoltage(temperaturePin);
     degreesC = (voltage - 0.5) * 100.0;
     degreesF = degreesC * (9.0/5.0) + 32.0;

     Serial.print("deg F:");
     Serial.println(degreesF);

      drink = notificationDelay(water, degreesF);
      Serial.println(drink);
      setColor(255, 0, 0); // Blue Color
      digitalWrite(motorPin, HIGH);
      delay(1000);
      setColor(0, 0, 0);
      digitalWrite(motorPin, LOW);
      delay(drink); 
  }
  else{
    setColor(0, 0, 0);
  }
}

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

float notificationDelay(float water, float degreesF){
  float timeToDrink = (hrsDay * 60)/water;
  float dTime;
  Serial.println(timeToDrink);
  if(degreesF > 80 && degreesF < 88){
   timeToDrink * 50000;
  }
  else if(degreesF > 70){
     dTime = timeToDrink * 40000;
  }
  else if(degreesF > 98){
     dTime = timeToDrink * 30000;
  }
  else
     dTime = timeToDrink * 60000;
  Serial.println(dTime);
  return dTime;
}

float getWaterIntake(){
  float ounces = weight * 0.5;
  float cups = ounces / 8;
  Serial.println(cups);
  return cups;
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

/*  if(degreesF > 80 && degreesF < 88){
   cups = cups + 1
  }
  if(degreesF > 88 && degreesF < 98){
   cups = cups + 2
  }
  if(degreesF > 98){
   cups = cups + 4
  }*/
