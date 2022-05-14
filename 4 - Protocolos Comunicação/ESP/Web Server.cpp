/*--------------------------------------------------------------------*/
//     CÓDIGO PARA CONTROLE ESP32 COM SERVIDOR WEB
/*--------------------------------------------------------------------*/

// Caso esteja utilizando a IDE do Arduino, comente a linha abaixo
#include <Arduino.h>

// Biblioteca para conexão wi-fi
#include <WiFi.h>

// Substitua pelas credenciais da sua rede de internet 
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// Configura o servidor web para porta 80
WiFiServer server(80);

// Variável para armazenar as requisições HTTP
String header;

// Variável auxiliar para armazenar o estado atual do LED
String output2State = "off";

// Pino de saída de sinal 
const int output2 = 2;

// Medição de tempo atual
unsigned long currentTime = millis();

// Medição de tempo anterior
unsigned long previousTime = 0; 

// Define período do código em milisegundos
const long timeoutTime = 2000;

void setup() 
{
  // Inicializa a serial
  Serial.begin(115200);

  // Inicializa e configura o pino como saída de sinal 
  pinMode(output2, OUTPUT);

  // Define a saída do pino output2 como LOW
  digitalWrite(output2, LOW);

  // Conexão com a rede Wi-Fi, utlilizando SSID e senha
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Espera até que a conexão com o wi-fi seja realizada
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  // Mostra no monitor serial o endereço IP
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Inicializa o servidor web 
  server.begin();
}

void loop()
{
  // Código espera até que o cliente se conecte a rede, quando isto acontecer a função loop pode prosseguir
  WiFiClient client = server.available();

  // Se um cliente se conectar a rede
  if (client) 
  {                             
    currentTime = millis();
    previousTime = currentTime;

    // Avisa da conexão pelo monitor serial
    Serial.println("New Client.");          
    
    // Variável auxiliar para armazenar eventuais informações enviadas pelo cliente 
    String currentLine = "";

    // Este loop se manterá ativo enquanto o cliente estiver conectado a rede
    while (client.connected() && currentTime - previousTime <= timeoutTime) 
    { 
      currentTime = millis();

      // Caso haja qualquer bytes enviados pelo cliente a ser lido
      if (client.available()) 
      {  
        // Lê a informação enviada           
        char c = client.read();

        // Mostra essa informação no monitor serial
        Serial.write(c);                  
        header += c;

        // Verifica se byte é caractere de nova linha, caso a linha atual esteja em branco, significa que há 2 caracteretes seguidos de nova linha
        // com isso é o fim da requisição http, com isso é possível enviar a resposta
        if (c == '\n') 
        {                    
          if (currentLine.length() == 0) 
          {

            // A requisição HTTP sempre irá começar com um código de resposta (e.g. HTTP/1.1 200 OK)
            // e um tipo da informação para que o cliente saiba o que está por vir, então uma linha em branco 
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Liga e desliga LEDs
            if (header.indexOf("GET /2/on") >= 0) 
            {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } 
            else if (header.indexOf("GET /2/off") >= 0) 
            {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
            
            // Mostra a página HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // Atributos de estilo da página web
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Título da página
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Mostra o estado atual do LED da placa
            client.println("<p>GPIO 26 - State " + output2State + "</p>");
            
            // Caso o LED esteja desligado, a página irá mostra o botão ON       
            if (output2State=="off") 
            {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } 
            
            // Caso o LED esteja ligado, a página irá mostra o botão OFF
            else 
            {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("</body></html>");
            
            // A resposta HTTP termina com uma linha em branco
            client.println();

            // Encerra o loop
            break;
          }
          // Caso haja uma nova linha, é preciso apagar a anterior
          else 
          { 
            currentLine = "";
          }
        } 
        // Caso tenha algo além de uma quebra de linha
        else if (c != '\r') 
        { 
          // Byte é adicionado ao final de currentLine
          currentLine += c; 
        }
      }
    }

    // Limpa a variável
    header = "";

    // Encerra a conexão
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}