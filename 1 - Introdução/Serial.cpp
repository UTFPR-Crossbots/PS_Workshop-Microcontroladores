
/*------------------------------------------------*/
//     CÓDIGO PARA FAZER A FUNÇÃO BLINK
//     NO ARDUINO E ESP
/*------------------------------------------------*/

/* 
    PINOUT (LED EMBUTIDOS NA PLACA)
    LED Arduino Uno/Nano -> 13  
    LED ESP32 -> 2
*/

// Caso esteja utilizando o PlataformIO, descomente esta linha
#include <Arduino.h>

// Escolha qual pino você quer que o LED esteja ligado
#define LED_PIN 13
int LED_status; 

// A função setup roda apenas uma vez ao inicializar a placa
void setup() 
{
    // Inicializa o pino LED_PIN e o configura como saída de sinal.
    pinMode(LED_PIN, OUTPUT);

    // Inicializa e define a frequência da comunicação serial
    Serial.begin(9600); 

    // Imprime essa mensagem no monitor serial
    Serial.println("A função deste código é controlar o led por meio da serial"); 

    // Espera por 2 segundos
    delay(2000); 
}

// A função loop, como diz o nome, roda em loop enquanto a placa estiver ligada
void loop() 
{
    // Imprime essa mensagem no monitor serial
    Serial.println("Digite 0 desligar ou 1 para ligar o LED");

    // Verifica se há dados na serial para leitura
    if (!Serial.available())
    {
        // Le os dados disponíveis na serial e armazena na variável LED_status
        LED_status = Serial.read(); 

        switch (LED_status)
        {   
            // Entra nessa condição caso o usuário tenha digitado 0
            case 0:
                // Faz com que a saída do pino LED_PIN seja BAIXA (0V)
                digitalWrite(LED_PIN, LED_status); 

                // Imprime essa mensagem no monitor serial
                Serial.println("LED esta desligado");
                
                // Espera por 2 segundos
                delay(2000); 
            break;

            // Entra nessa condição caso o usuário tenha digitado 1
            case 1:
                // Faz com que a saída do pino LED_PIN seja ALTA (5V)
                digitalWrite(LED_PIN, LED_status); 

                // Imprime essa mensagem no monitor serial
                Serial.println("LED esta desligado");

                // Espera por 2 segundos
                delay(2000);
            break;
    
            // Entra nessa condição caso o usuário tenha digitado qualquer número diferente de 0 e 1
            default:
                // Imprime essa mensagem no monitor serial
                Serial.println("Opçao invalida"); 

                // Espera por 2 segundos
                delay(2000); 
            break;
        }
    }            
}