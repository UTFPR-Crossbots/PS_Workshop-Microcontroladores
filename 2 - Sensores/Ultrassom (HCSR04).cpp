/*------------------------------------------------*/
//     CÓDIGO PARA LEITURA HC-SR04
//     NO ARDUINO
/*------------------------------------------------*/

/* 
    PINOUT (LED EMBUTIDOS NA PLACA)
    LED Arduino Uno/Nano -> 13  
    LED ESP32 -> 2

    PINOUT SENSOR HC-SR04 (Arduino)
    VCC -> 5V 
    GND -> GND 
    TRIG -> 3
    ECHO -> 4

    * O sensor HC-SR04 só pode ser alimentado em 5V, portando sua tensão lógica é de 5V, por conta disso o 
    ultrassom não pode ser alimentado pelo ESP e este microcontrolador não pode receber os dados do echo sem um divisor
    de tensão ou um conversor analógico para baixar o nível de tensão do echo. 

*/

#include "Arduino.h"

#define trig 4
#define echo 3 

long tempo = 0;
long distancia = 0;  

void setup()
{
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);

  Serial.begin(9600);  

}

void loop()
{
  // Começa com 0 no trigger, para garantir que o pulso seja mandado de forma limpa
  digitalWrite(trig, LOW); 
  delayMicroseconds(5); 

  // Manda sinal ALTO para o trigger que assim manda o impulso de onda
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 

  // Desativa o trigger 
  digitalWrite(trig, LOW); 

  // Esta função mede o tempo que um pulso demorou para chegar em pino 
  tempo = pulseIn(echo, HIGH);  

  // Sabendo a velocidade do som e o tempo que pulso demorou para chegar no receptor, é possível calcular a distância
  // em que o objeto se encontra (o tempo é dividido por 2, porque dessa forma é o tempo de ida e volta do sinal)
  distancia = (tempo/2)*0.0343; 

  Serial.print("A distancia em cm e:");
  Serial.println(distancia);
  Serial.println("\n"); 
}



/*
//Leitura de distância com o sensor HC-SR04
#include <Ultrasonic.h>
 Ultrasonic ultrassom(8,7); // define o nome do sensor(ultrassom)
//e onde esta ligado o trig(8) e o echo(7) respectivamente
long distancia;
 void setup() {
 Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
 
 }

 void loop()
 {
   distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
                                     // centímetros(CM) ou polegadas(INC)
   Serial.print(distancia); //imprime o valor da variável distancia
   Serial.println("cm");
   delay(100);
 }
*/