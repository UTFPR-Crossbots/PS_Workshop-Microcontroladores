/*------------------------------------------------*/
//     CÓDIGO PARA CONTROLE PONTE-H 
//     COM ESP32
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
    PWMA -> 32   controla velocidade
    AIN1 -> 25   controla sentido
    AIN2 -> 26   controla sentido
    PWMB -> 33   controla velocidade
    BIN1 -> 27   controla sentido
    BIN2 -> 14   controla sentido

    STBY -> 5V
   
*/

// Se estiver utilianzando a IDE do Arduino, comente a linha abaixo
#include <Arduino.h>

// Declaração pinos digitais da ponte-h
#define PWM1 32
#define AIN1 25
#define AIN2 26
#define PWM2 33
#define BIN1 27
#define BIN2 14

#define motorA 1 
#define motorB 2 

// Definindo propriedades sinal PWM ESP
const int freq = 30000;
const int pwmChannel_A = 0;
const int pwmChannel_B = 1;
const int resolution = 8;

void setup() 
{
  // Inicialização e configuração dos pinos
  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);

  pinMode(PWM2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);

  // Configura funcionalidades LED PWM 
  ledcSetup(pwmChannel_A, freq, resolution);
  ledcSetup(pwmChannel_B, freq, resolution);

  // anexa o canal ao GPIO a ser controlado
  ledcAttachPin(PWM1, pwmChannel_A);
  ledcAttachPin(PWM2, pwmChannel_B);
}

// Função para mover os motores para frente
void foward(int motor, int velocidade)
{
  if (motor == 1)
  {
    //define o sentido pelos pinos AIN1 e AIN2 e a velocidade pelo PWM1
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW); 

    ledcWrite(pwmChannel_A, velocidade); 
  }
  else
  {
    //define o sentido pelos pinos BIN1 e BIN2 e a velocidade pelo PWM2
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW); 

    ledcWrite(pwmChannel_B, velocidade); 
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

    ledcWrite(pwmChannel_A, velocidade); 
  }
  else
  {
    //define o sentido pelos pinos BIN1 e BIN2 e a velocidade pelo PWM2
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); 

    ledcWrite(pwmChannel_B, velocidade); 
  }
}

// Função para parar os motores
void stop(int motor)
{
    if (motor == 1)
  {
    ledcWrite(pwmChannel_A, 0); 
  }
  else
  {
    ledcWrite(pwmChannel_B, 0); 
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