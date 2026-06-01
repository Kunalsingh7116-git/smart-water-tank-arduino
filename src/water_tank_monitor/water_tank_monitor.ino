#define trigPin 9
#define echoPin 10
#define relayPin 7

const float emptyDistance = 11.7;
const float fullDistance = 2.0;

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // Pump OFF
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if(duration == 0)
  {
    Serial.println("Sensor Error!");
    delay(1000);
    return;
  }

  float distance = duration * 0.0343 / 2;

  float waterLevel =
   ((emptyDistance - distance) /
   (emptyDistance - fullDistance)) * 100;

  if(waterLevel < 0)
    waterLevel = 0;

  if(waterLevel > 100)
    waterLevel = 100;

  // Active LOW relay
  if(waterLevel <= 10)
  {
    digitalWrite(relayPin, LOW); // Pump ON
  }

  if(waterLevel >= 90)
  {
    digitalWrite(relayPin, HIGH); // Pump OFF
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");

  Serial.print(" | Water Level: ");
  Serial.print(waterLevel);
  Serial.print("%");

  Serial.print(" | Pump: ");

  if(digitalRead(relayPin) == LOW)
    Serial.println("ON");
  else
    Serial.println("OFF");

  delay(1000);
}