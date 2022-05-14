#include "BluetoothSerial.h"

// Aqui é checado se o Bluetooth do esp está devidamente ativo
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Cria um objeto de BluetoothSerial chamada SerialBT
BluetoothSerial SerialBT;

void setup() 
{
    // Inicializa a comunicação serial em 115200 bytes/s
    Serial.begin(115200);

    // Inicializa comunicação serial via Bluetooth, nomeia o dispositivo
    SerialBT.begin("ESP32");
    Serial.println("Iniciando comunicação bluetooth, agora é possível parear o esp com seu dispositivo");
}

void loop() 
{   
    // Se houver dados no monitor serial, eles serão enviados ao outro dispositivo
    if (Serial.available()) 
    {
        SerialBT.write(Serial.read());
    }
    
    // Se o dispositivo enviar dados, eles aparecerão no monitor serial
    if (SerialBT.available()) 
    {
        Serial.write(SerialBT.read());
    }
    delay(20);
}