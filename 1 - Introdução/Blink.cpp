/*------------------------------------------------*/
//     CÓDIGO PARA COMUNICAÇÃO SERIAL
//     NO ARDUINO E ESP
/*------------------------------------------------*/

/* 
    PINOUT (LED EMBUTIDOS NA PLACA)
    LED Arduino Uno/Nano -> 13  
    LED ESP32 -> 2
*/

// Caso esteja utilizando o PlataformIO, descomente esta linha
//#include <Arduino.h>

// Escolha qual pino você quer que o LED esteja ligado
#define LED_PIN 13

// a função setup roda apenas uma vez ao inicializar a placa
void setup() 
{
    // inicializa o pino LED_PIN e o configura como saída de sinal.
    pinMode(LED_PIN, OUTPUT);

    // Inicia com o LED apagado
    digitalWrite(LED_PIN, LOW);
}

// A função loop, como diz o nome, roda em loop enquanto a placa estiver ligada
void loop() 
{
    // Faz com que a saída do pino LED_PIN seja ALTA (5V) 
    digitalWrite(LED_PIN, HIGH);

    // A função delay para o código por um determinado tempo em milisegundos, nesse caso, vai parar o código por 1 segundo
    delay(1000);

    // Faz com que a saída do pino LED_PIN seja BAIXA (0V)
    digitalWrite(LED_PIN, LOW);

    // Para o código por 1 segundo
    delay(1000);                      
}