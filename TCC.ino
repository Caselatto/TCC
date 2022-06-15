#include "Arduino.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C
#include "SD.h"       //biblioteca responsável pela comunicação com o Cartão SD

/*
  ================================================================
  ===                        DEFINIÇÕES                        ===
  ================================================================
*/

#define CARTAO

/*
  ================================================================
  ===                          PINOUT                          ===
  ================================================================
*/

//MPU
/*VCC       3v
  GND       GND
*/
#define scl_pin  4  //D2
#define sda_pin  5  //D1

//Botão
//uint8_t botOffset = D4;

//Leds6y
#define LED1 2  //D4
#define LED2 16  //D3

#ifdef CARTAO
//Cartão
/* VCC        vUSB
   GND        GND
   MISO       D6
   MOSI       D7
   SCK        D5
*/
#define CS_PIN  15  //D8 pino ligado ao CS do módulo SD Card
File sdFile;
#endif

/*
  ===============================================================
  ===                        VARIÁVEIS                        ===
  ===============================================================
*/

// Tempo
float dt, tempo_prev = 0.00;

// Armazenamento dos dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

// Variavel do offset
float offAX = 0, offAY = 0, offAZ = 0, offGX = 0, offGY = 0, offGZ = 0, offRoll = 0, offPitch = 0, offYaw = 0, offTempo;
bool OFFSET = true;

// Armazenamento dos dados após conversão
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long convGYRO, convACEL;     // Datasheet do sensor

// Calculo ângulos
float Pitch = 0, Roll = 0, Yaw = 0;
float dPitch = 0, dRoll = 0, dYaw = 0;
float Acc[2];
#define RAD_TO_DEG 57.2957795  // Radianos para graus (180/PI)

// Calculo velocidade
float VelX = 0, VelY = 0, VelZ = 0;
float CorrigidoX = 0, CorrigidoY = 0, CorrigidoZ = 0;

// Media movel
#define n 100
int MM = 1.5 * n;

// Integral
#define m 1

// Truncamento
float RoundAcc = 1.25;
float RoundGyr = 0.2;

// Leds piscando alternado a cada ciclo do loop
bool led_state = false;

//float ErroRoll = 0.00009, ErroPitch = 0, ErroYaw = -0.00071, ErroVelX = -0.02271, ErroVelY = -0.00745, ErroVelZ = -0.14214;
float ErroRoll = 0, ErroPitch = 0, ErroYaw = 0, ErroVelX = 0, ErroVelY = 0, ErroVelZ = 0;

/*
  ===============================================================
  ===                      SETUP INICIAL                      ===
  ===============================================================
*/

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n\n\n\nComeçou\n\n");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, !led_state);
  digitalWrite(LED2, !led_state);
  delay(100);
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, led_state);
  delay(100);
  digitalWrite(LED1, !led_state);
  digitalWrite(LED2, !led_state);
  delay(100);
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, led_state);
  delay(100);

  Setup_MPU();
#ifdef CARTAO
  Setup_Cartao();

  sdFile.print("Tempo;\t");
  sdFile.print("Dt;\t");

  //  sdFile.print("AX;\t");
  //  sdFile.print("AY;\t");
  //  sdFile.print("AZ;\t");
  //  sdFile.print("GX;\t");
  //  sdFile.print("GY;\t");
  //  sdFile.print("GZ;\t");

  sdFile.print("AcX;\t");
  sdFile.print("AcY;\t");
  sdFile.print("AcZ;\t");
  sdFile.print("GyX;\t");
  sdFile.print("GyY;\t");
  sdFile.print("GyZ;\t");

  sdFile.print("Roll;\t");
  sdFile.print("Pitch;\t");
  sdFile.print("Yaw;\t");

  //  sdFile.print("CorX;\t");
  //  sdFile.print("CorY;\t");
  //  sdFile.print("CorZ;\t");

  //  sdFile.print("VelX;\t");
  //  sdFile.print("VelY;\t");
  //  sdFile.print("VelZ;\t");

  sdFile.println();
  sdFile.flush();
  delay(500);
  Serial.end();
#endif
}

/*
  ================================================================
  ===                       MAIN PROGRAM                       ===
  ================================================================
*/

void loop ()
{
  if (OFFSET) {
    if (MM > 0) {
      MM = MM - 1;
    }
    else {
      offAX = AcX;
      offAY = AcY;
      offAZ = AcZ;

      offGX = GyX;
      offGY = GyY;
      offGZ = GyZ;

      offRoll = Roll;
      offPitch = Pitch;
      offYaw = Yaw;
      Roll = 0;
      Pitch = 0;
      Yaw = 0;

      VelX = 0;
      VelY = 0;
      VelZ = 0;

      offTempo = millis();

      OFFSET = false;
    }
  }

  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();

  // lê os dados do sensor
  Read_MPU();

  // Converte os dados do sensor
  converterRAW();

  // Calcula os ângulos em função dos eixos do sensor
  //  PitchRollYaw(AcX - offAX, AcY - offAY, AcZ - offAZ, GyX - offGX, GyY - offGY, GyZ - offGZ);
  PitchRollYaw(AcX, AcY, AcZ, GyX - offGX, GyY - offGY, GyZ - offGZ);
  //  PitchRollYaw(AcX - (99 * offAX / 100), AcY - (99 * offAY / 100), AcZ - (99 * offAZ / 100), GyX - offGX, GyY - offGY, GyZ - offGZ);

  // Corrigir Offsets devido ao angulos
  //  CorrigeOff();

  // Calculo da velocidade
  //  velocidade(AcX, AcY, AcZ, offAX, offAY, offAZ);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Mostra os valores
  salva("Tempo", (millis() - offTempo) / 1000.0);
  salva("Dt", dt);
  //  mostraRAW();
  //  mostraOFF();

  mostraCON();
  mostraANG();
  //  mostraCOR();
  //  mostraVEL();
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //  Serial.print(GyX - offGX,5);
  //  Serial.print("\t");
  //  Serial.print(Pitch,5);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  finaliza();
}
