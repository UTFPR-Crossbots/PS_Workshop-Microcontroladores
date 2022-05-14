/*------------------------------------------------*/
//     CÓDIGO PARA CONTROLE PONTE-H 
//     COM ARDUINO
/*------------------------------------------------*/

/* 
    PINOUT PONTE-H TB6612
    VM  -> 12V
    AO1 -> SAIDA MOTOR A
    AO2 -> SAIDA MOTOR A
    BO1 -> SAIDA MOTOR B
    BO2 -> SAIDA MOTOR B
    GND -> GND

    VCC  -> 5V
    PWMA -> 3   controla velocidade
    AIN1 -> 4   controla sentido
    AIN2 -> 5   controla sentido
    PWMB -> 6   controla velocidade
    BIN1 -> 7   controla sentido
    BIN2 -> 8   controla sentido

    STBY -> 5V
   
*/

// Se estiver utilianzando a IDE do Arduino, comente a linha abaixo
#include <Arduino.h>

// Declaração pinos digitais da ponte-h
#define PWM1 3
#define AIN1 4
#define AIN2 5
#define PWM2 6
#define BIN1 7
#define BIN2 8

#define motorA 1 
#define motorB 2 

void setup() 
{
  // Inicialização e configuração dos pinos
  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);

  pinMode(PWM2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
}

// Função para mover os motores para frente
void foward(int motor, int velocidade)
{
  if (motor == 1)
  {
    //define o sentido pelos pinos AIN1 e AIN2 e a velocidade pelo PWM1
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW); 

    analogWrite(PWM1, velocidade); 
  }
  else
  {
    //define o sentido pelos pinos BIN1 e BIN2 e a velocidade pelo PWM2
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW); 

    analogWrite(PWM2, velocidade); 
  }
}

// Função para mover os motores para trás
void reverse(int motor, int velocidade)
{
  if (motor == 1)
  {
    //define o sentido pelos pinos AIN1 e AIN2 e a velocidade pelo PWM1
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH); 

    analogWrite(PWM1, velocidade); 
  }
  else
  {
    //define o sentido pelos pinos BIN1 e BIN2 e a velocidade pelo PWM2
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); 

    analogWrite(PWM2, velocidade); 
  }
}

// Função para parar os motores
void stop(int motor)
{
    if (motor == 1)
  {
    analogWrite(PWM1, 0); 
  }
  else
  {
    analogWrite(PWM2, 0); 
  }
}

 
void loop() 
{
  // A ideia é aumentar a velocidade aos poucos nos dois motores e depois mudar sentido
  for(int vel = 0; vel<=255; vel++)
  {
    foward(motorA, vel);
    foward(motorB, vel);
    delay(500); 
  }

  stop(motorA);
  stop(motorB);
  delay(1000);

  for(int vel = 0; vel<=255; vel++)
  {
    reverse(motorA, vel);
    reverse(motorB, vel);
    delay(500); 
  }
  stop(motorA);
  stop(motorB);
  delay(1000); 

}