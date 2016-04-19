/*
 * Módulo de implementação do arduino com sensor de temperatura e umidade para
 * controle de plantas em estufas.
 * 
 * Quando ocorre do ambiente estar fora dos padrões "aceitáveis" para
 * a sobrevivência da planta, o arduino emite um sinal acendendo o LED.
 */

#include "DHT.h"

// Output pin
#define LEDPIN 13

// Input pin
#define DHTPIN 2

// Tipo de sensor
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

double minTempLimit, maxTempLimit;
double minHumLimit, maxHumLimit;
double currTemp, currHum;
int currTime;

bool isTempWithinLimits, isHumWithinLimits;

void setup() {
  pinMode(LEDPIN, OUTPUT);

  // Configura limites de temperatura da planta
  minTempLimit = 15.0;
  maxTempLimit = 35.0;

  minHumLimit = 20.0;
  maxHumLimit = 90.0;
  
  dht.begin();
  currTime = millis();
}

void loop() {
  // Lê do sensor os dados de temperatura e umidade a cada segundo.
  if (millis() - currTime >= 1000) {
    currTime = millis();

    // Lê os valores do sensor
    currHum = dht.readHumidity();
    currTemp = dht.readTemperature();

    // Caso a leitura falhe
    if (isnan(currHum) || isnan(currTemp)) {
      return;
    }

    // Se está fora dos limites de temperatura
    isTempWithinLimits = (currTemp >= minTempLimit && currTemp <= maxTempLimit);
  
    // Se está fora dos limites de umidade
    isHumWithinLimits = (currHum >= minHumLimit && currHum <= maxHumLimit);

    // Acende o LED caso esteja algo fora dos limites
    if (!(isTempWithinLimits && isHumWithinLimits)) {
      digitalWrite(LEDPIN, HIGH);
    }
    else {      
      digitalWrite(LEDPIN, LOW);
    }
  }
}