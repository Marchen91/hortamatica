//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP32CORE_WIFI_POINT

#include <WiFi.h>
#include <RemoteXY.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>


// RemoteXY connection settings
//#define REMOTEXY_WIFI_SSID "Fatec Lab_IoT"
//#define REMOTEXY_WIFI_PASSWORD "%fatecrp!"
#define REMOTEXY_WIFI_SSID "CheapVegarden"
#define REMOTEXY_WIFI_PASSWORD "@123Cheap"
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 2, 0, 7, 0, 225, 0, 11, 13, 1,
  66, 0, 6, 3, 9, 20, 179, 26, 129, 0,
  1, 25, 24, 4, 16, 85, 109, 105, 100, 97,
  100, 101, 32, 40, 37, 41, 0, 65, 4, 47,
  4, 9, 9, 65, 1, 47, 14, 9, 9, 129,
  0, 41, 25, 19, 4, 16, 83, 111, 108, 101,
  110, 195, 179, 105, 100, 101, 0, 129, 0, 29,
  7, 16, 4, 16, 70, 101, 99, 104, 97, 100,
  97, 0, 129, 0, 33, 17, 13, 4, 16, 65,
  98, 101, 114, 116, 97, 0, 1, 0, 5, 33,
  12, 12, 179, 8, 72, 50, 79, 0, 129, 0,
  5, 47, 12, 4, 16, 73, 114, 114, 105, 103,
  97, 114, 0, 68, 49, 2, 60, 60, 39, 8,
  192, 86, 97, 114, 105, 97, 195, 167, 195, 163,
  111, 32, 85, 109, 105, 100, 97, 100, 101, 32,
  40, 37, 41, 0, 2, 0, 33, 34, 22, 11,
  2, 26, 31, 31, 76, 73, 71, 0, 68, 69,
  83, 76, 0, 129, 0, 1, 56, 61, 4, 16,
  72, 105, 115, 116, 195, 179, 114, 105, 99, 111,
  32, 84, 82, 32, 85, 109, 105, 100, 97, 100,
  101, 32, 83, 111, 108, 111, 0, 129, 0, 26,
  47, 35, 4, 16, 68, 101, 115, 97, 116, 105,
  118, 97, 114, 32, 83, 105, 115, 116, 101, 109,
  97, 0
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  uint8_t btnIrrigar; // =1 if button pressed, else =0
  uint8_t switchOnOff; // =1 if switch ON and =0 if OFF

  // output variables
  int8_t levelUmid; // =0..100 level position
  uint8_t ledVermelho_r; // =0..255 LED Red brightness
  uint8_t ledVerde_b; // =0..255 LED Blue brightness
  float graphUmid;

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


//***************************************************
//* * Variáveis de Pinagem da placa Wemos D1 R32 * *
#define pino_Trilha1_SensorUmidade 36
#define pino_Trilha1_Solenoide 14
#define pino_Trilha1_SensorVolumetriaAgua 39
#define DHTPIN 13
#define DHTTYPE DHT22
//***************************************************

//* * Variáveis de Configuração das Trilhas de Irrigação da Horta Automatizada * *

//Observação: Cada trilha será equivalente a um canteiro de plantio.
int valorUmidade_Trilha1 = 0;
int porcentUmidade_Trilha1 = 0.0; //Valores em porcentagem de 0% a 100%
float litrosPorMinuto_Trilha1 = 0.0;
boolean estadoIrrigacao_Trilha1 = false;
float fluxoAcumulado = 0.0;
float volumeAcumulado = 0.0;
float contFluxoAcum = 0;
float umidadeAcumulada = 0.0;
float contUmidadeAcum = 0;
float umidadeAcumuladaAr = 0.0;
float contUmidadeAcumAr = 0;
boolean irrigacaoManual = false;
boolean irrigacaoAuto = false;
unsigned long leituraIrrigando = 0;
unsigned long timeoutIrrigacaoManual = 0;
unsigned long timeoutLeituraUmidade = 0;
unsigned long timeoutLeituraVolumetriaAgua = 0;
//unsigned long timeoutTelaRemoteXY = 0;

//definicao do pino do sensor e de interrupcao
//const int INTERRUPCAO_SENSOR = 0; //interrupt = 0 equivale ao pino digital 2
//const int PINO_SENSOR = 2;

//definicao da variavel de contagem de voltas
unsigned long contador = 0;

//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 4.5;

//definicao das variaveis de fluxo e volume
float fluxo = 0;
float volume = 0;
float volume_total = 0;

//definicao da variavel de intervalo de tempo
unsigned long tempo_antes = 0;

// * * Variáveis Globais do Sistema de Controle
boolean sysStatus = false;
//***************************************************

//***************************************************
//Variáveis de Controle de Comunicação de Dados em REDE/INTERNET
unsigned long timeoutDadosGoogleDocs = 0;
unsigned long timeoutWiFi = 0;
//***************************************************

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  //Inicialização Biblioteca do Aplicativo Móvel
  RemoteXY_Init ();

  //Configuração para uso do Monitor Serial
  Serial.begin(115200);
  Serial.println("Energizando Arduino");
  //inicializando a conexão da Rede WiFi
  conectarRedeWiFi();

  //Configuração dos pinos da placa Wemos_D1_R32
  pinMode(pino_Trilha1_SensorUmidade, INPUT);
  pinMode(pino_Trilha1_Solenoide, OUTPUT);
  pinMode(pino_Trilha1_SensorVolumetriaAgua, INPUT_PULLUP);

  //Configuração - Estado inicial das portas dos componentes
  desligarSolenoide();

  //O sistema inicia no estado de LIGADO (sysStatus==true)
  sysStatus = true;
  RemoteXY.switchOnOff = 1;

  //TIMEOUTS - Configuração
  //timeoutDadosGoogleDocs = millis() + 3600000; //1 hora em milissegundos ==> 3600000
  //timeoutLeituraUmidade = millis() + 300000;  //a cada 5 minutos

  dht.begin();
  //Mensagem de OK do Sistema
  Serial.println("Sistema de Controle Horta Automatizada FATECRP iniciado...");
  //Serial.end();
}

//############################################################################

void loop() {

  //Atualização de dados na tela do App RemoteXY
  updateTelaAppMovel();
  //delay(100);

  //Verificando o Status do sistema da horta automática
  if (sysStatus == true) {

    
    leituraIrrigando = lerTempoIrrigacao(); 
    if (millis() > timeoutLeituraUmidade) {
      verificarUmidadeSolo();
      verificarUmidadeAr();
      //timeoutLeituraUmidade = millis() + 300000; //5 minutos
      timeoutLeituraUmidade = millis() + 5000; //1 seg
    }
    //delay(100);
    //Serial.println(millis());
    if ((millis() > timeoutLeituraVolumetriaAgua)) {
      verificarVolumetriaAgua();
      timeoutLeituraVolumetriaAgua = millis() + 5000; //1 segundo
    }
    //delay(100);

    if (millis() > timeoutIrrigacaoManual) {
      irrigarManual();
      timeoutIrrigacaoManual = millis() + 300000; //5 minutos
    }

    //delay(100);

    //Envio de dados para planilha em nuvem de 1 em 1 hora
    if (millis() > timeoutDadosGoogleDocs) {
      submeterDadosGoogleDocs();
      
      //timeoutDadosGoogleDocs = millis() + 30000;
    }
    //delay(100);
  } else {
    desligarSolenoide();
    Serial.println("Sistema hortamática desativado manualmente...");
  }
} //end-loop
