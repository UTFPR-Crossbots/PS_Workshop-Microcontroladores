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
//#include <Arduino.h>

// Escolha qual pino você quer que o LED esteja ligado
#define LED_BUILTIN 13

// a função setup roda apenas uma vez ao inicializar a placa
void setup() 
{
    // inicializa o pino LED_BUILTIN e o configura como saída de sinal.
    pinMode(LED_BUILTIN, OUTPUT);
}

// A função loop, como diz o nome, roda em loop enquanto a placa estiver ligada
void loop() 
{
    // Faz com que a saída do pino LED_BUILTIN seja ALTA (5V) 
    digitalWrite(LED_BUILTIN, HIGH);

    // A função delay para o código por um determinado tempo em milisegundos, nesse caso, vai parar o código por 1 segundo
    delay(1000);

    // Faz com que a saída do pino LED_BUILTIN seja BAIXA (0V)
    digitalWrite(LED_BUILTIN, LOW);

    // Para o código por 1 segundo
    delay(1000);                      
}