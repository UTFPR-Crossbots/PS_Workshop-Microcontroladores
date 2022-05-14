/*------------------------------------------------*/
//     CÓDIGO PARA LEITURA VL53L0X
//     NO ARDUINO E ESP
/*------------------------------------------------*/

/* 
    PINOUT (LED EMBUTIDOS NA PLACA)
    LED Arduino Uno/Nano -> 13  
    LED ESP32 -> 2

    PINOUT SENSOR VL53L0X (para o ESP32)
    VCC -> 3,3V 
    GND -> GND 
    SCL -> 22
    SDA -> 21

    PINOUT SENSOR VL53L0X (para o Arduino Uno)
    VCC -> 5V 
    GND -> GND 
    SDA -> 18 
    SCL -> 19

    PINOUT SENSOR VL53L0X (para o Arduino Nano)
    VCC -> 5V 
    GND -> GND 
    SDA -> A4 
    SCL -> A5
*/

// Caso esteja utilizando a IDE do Arduino, comente a linha abaixo
#include "Arduino.h"

// Biblioteca do sensor
#include "Adafruit_VL53L0X.h"

// Declara o sensor como o objeto "laser"
Adafruit_VL53L0X laser = Adafruit_VL53L0X();

// Variável para armazenar as medidas dos sensores
VL53L0X_RangingMeasurementData_t measure;

void setup() 
{
  // Inicializa a comunicação serial e configura a velocidade bits/s
  Serial.begin(115200);
  
  Serial.println("Teste de conexao com sensor VL53L0X");
  
  // Essa função testa se o sensor está conectado neste endereço e se a comunicação esta ok, em caso de falha
  // retorna falso 
  if (!laser.begin(0x29)) 
  {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  
  Serial.println("Conexao bem-sucedida\n"); 
}


void loop() 
{
  
  //laser.rangingTest(&measure, false);

  // Mostra a leitura do sensor se a medição estiver dentro de alcance e for bem sucedida
  if (measure.RangeStatus != 4) 
  {
    Serial.print("Distancia (mm): "); 
    Serial.println(measure.RangeMilliMeter);
  } 
  else 
  {
    Serial.println(" Fora de alcance "); // Alcance do sensor é 2m 
  }
    
  delay(100);
}