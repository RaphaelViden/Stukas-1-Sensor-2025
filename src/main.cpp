#include <DHT.h>

#define DHTPIN 2          
#define LDRPIN A0         
#define DHTTYPE DHT11     

DHT dht(DHTPIN, DHTTYPE);

#define LED_GREEN 3
#define LED_ORANGE 4
#define LED_RED 5

const float minHumidity = 40.0;  
const float maxHumidity = 60.0;  
const int ldrThreshold = 100;    

float readHumidity() {
  return dht.readHumidity();
}

int readLight() {
  return analogRead(LDRPIN);
}

void setIndicators(int green, int orange, int red) {
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_ORANGE, orange);
  digitalWrite(LED_RED, red);
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  dht.begin();
  setIndicators(HIGH, LOW, LOW);
  Serial.begin(9600);
}

void loop() {
  float humidity = readHumidity();
  int light = readLight();

  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.print("%, Pencahayaan: ");
  Serial.println(light);

  if (humidity < minHumidity || humidity > maxHumidity || light < ldrThreshold) {
    if (humidity < minHumidity || humidity > maxHumidity) {
      setIndicators(LOW, HIGH, LOW);
    }
    if (light < ldrThreshold) {
      setIndicators(LOW, HIGH, LOW);
    }
  } else {
    setIndicators(HIGH, LOW, LOW);
  }

  if (humidity < minHumidity || humidity > maxHumidity && light < ldrThreshold) {
    setIndicators(LOW, LOW, HIGH);
  }

  delay(500);
}
