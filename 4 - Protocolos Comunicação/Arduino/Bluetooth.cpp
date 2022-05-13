/*--------------------------------------------------------*/
//     CÓDIGO PARA COMUNICAÇÃO COM MÓDULO BLUETOOTH HC-05
//     NO ARDUINO
/*--------------------------------------------------------*/

/* 

    PINOUT MÓDULO HC-05 (Arduino)
    VCC -> 5V 
    GND -> GND 
    TRIG -> 3
    ECHO -> 4

*/

#include "Arduino.h"

// Biblioteca para comunicação serial (não precisa baixar é padrão do arduino)
#include <SoftwareSerial.h>

// Pinos para comunicação serial 
// Lembre que RX do arduino conecta no TX do módulo; e o TX do arduino conecta no RX do módulo
#define RX 2
#define TX 4

String command = ""; 

SoftwareSerial bluetooth(RX, TX); 

void setup()
{
  Serial.begin(9600); 
  bluetooth.begin(9600); 
}

void loop()
{
  // Verifica se o módulo está disponível  
  if (bluetooth.available()) 
  {  
    while(bluetooth.available()) 
    { // Lê enquanto houver caracteres na serial  
      command += (char)bluetooth.read();  
    }  
   Serial.println(command); 
   // Limpa a variável para evitar repetições 
   command = ""; 
  }  
   
  // Verifica se a serial do arduino está disponível  
  if (Serial.available())
  {  
    delay(10);

    // Manda as informações que estiverem no monitor serial para o módulo bluetooth  
    bluetooth.write(Serial.read());  
  }

}
