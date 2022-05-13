/*------------------------------------------------*/
//     CÓDIGO PARA LEITURA SENSOR TCRT 5000
//     NO ARDUINO E ESP
/*------------------------------------------------*/

/* 
    PINOUT (LED EMBUTIDOS NA PLACA)
    LED Arduino Uno/Nano -> 13  
    LED ESP32 -> 2

    PINOUT SENSOR TCRT 5000 (para o ESP32)
    VCC -> 3,3V 
    GND -> GND 
    D0  -> 5
    A0  -> 4

    PINOUT SENSOR TCRT 5000 (para o Arduino)
    VCC -> 5V 
    GND -> GND 
    D0  -> 5
    A0  -> A0
*/

// Caso esteja utilizando o PlataformIO, descomente esta linha
#include <Arduino.h>

// LED do microcontrolador
#define LED_PIN 13

// Saida analógica e digital do sensor 
#define SENSOR_DIGITAL 5

// Comente esta linha caso esteja utilizando o Arduino
#define SENSOR_ANALOGICO 4

// Descomente esta linha caso esteja utilizando o Arduino 
//#define SENSOR_ANALOGICO A0 

bool deteccao; 

void setup()
{   
    // Inicializa e configura o pino LED_PIN como saída de sinal
    pinMode(LED_PIN, OUTPUT); 

    // Inicializa e configura os pinos SENSOR_ANALOGICO e SENSOR_DIGITAL como entrada de sinal 
    pinMode(SENSOR_DIGITAL, INPUT); 
    pinMode(SENSOR_ANALOGICO, INPUT); 

    // Inicializa com o LED apagado
    digitalWrite(LED_PIN, LOW); 

    // Inicializa e configura a velocidade da comunicação serial 
    Serial.begin(9600); 

}

void loop()
{
    // Imprime a mensagem no monitor serial
    Serial.print("A leitura analogica do sensor e:");

    // Mostra o valor da leitura no monitor serial e pula uma linha
    Serial.println(analogRead(SENSOR_ANALOGICO)); 

    // Le a saida digital do sensor
    deteccao = digitalRead(SENSOR_DIGITAL); 
    if(deteccao == 1)
    {   
        // Se saida do sensor for HIGH, significa que este detectou branco, com isso avisa no monitor serial e acende o LED
        Serial.println("Cor branca detectada"); 
        digitalWrite(LED_PIN, HIGH); 

    }
    else
    {
        // Se saida do sensor for LOW, significa que este detectou preto, com isso avisa no monitor serial e apaga o LED
        Serial.println("Cor preta detectada"); 
        digitalWrite(LED_PIN, LOW); 
    }
}