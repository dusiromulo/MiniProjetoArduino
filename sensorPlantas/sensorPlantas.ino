#include "DHT.h"

/*
 * Módulo de implementação do arduino com sensor de temperatura e umidade para
 * controle de plantas em estufas.
 * 
 * Quando ocorre do ambiente estar fora dos padrões "aceitáveis" para
 * a sobrevivência da planta, o arduino emite um sinal acendendo o LED.
 */

// Output pin
#define LEDPIN 13

// Input pin
#define DHTPIN 2

// Tipo de sensor
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float minTempLimit, maxTempLimit;
float minHumLimit, maxHumLimit;
float currTemp, currHum;
int currTime;

bool isTempWithinLimits, isHumWithinLimits;

void setup() {
  Serial.begin(9600);

  pinMode(LEDPIN, OUTPUT);

  // Configura limites de temperatura da planta
  minTempLimit = 15;
  maxTempLimit = 35;

  minHumLimit = 20;
  maxHumLimit = 60;
  
  dht.begin();
  currTime = millis();
}

void loop() {
  // Lê do sensor os dados de temperatura e umidade a cada segundo.
  if (millis() - currTime >= 1000) {
    currTime = millis();
    
    currHum = dht.readHumidity();
    currTemp = dht.readTemperature();
  
    if (isnan(currHum) || isnan(currTemp)) {
      Serial.println("Leitura do sensor falhou!");
      return;
    }
  
    Serial.print("Humidity: ");
    Serial.print(currHum);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(currTemp);
    Serial.print(" *C \n");

    // Se está fora dos limites de temperatura
    isTempWithinLimits = (currTemp >= minTempLimit && currTemp <= maxTempLimit);
  
    // Se está fora dos limites de umidade
    isHumWithinLimits = (currHum >= minHumLimit && currHum <= maxHumLimit);
    if (!(isTempWithinLimits && isHumWithinLimits)) {
      digitalWrite(LEDPIN, HIGH);
    }
    else {      
      digitalWrite(LEDPIN, LOW);
    }
  }
}
