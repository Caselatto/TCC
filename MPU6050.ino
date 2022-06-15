/*
   Definições de alguns endereços mais comuns do MPU6050
   os registros podem ser facilmente encontrados no mapa de registros do MPU6050
*/
const int MPU_ADDR =      0x68; // definição do endereço do sensor MPU6050 (0x68)
const int WHO_AM_I =      0x75; // registro de identificação do dispositivo
const int PWR_MGMT_1 =    0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG =   0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG =  0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT =    0x3B; // registro de leitura do eixo X do acelerômetro

/*
   função que configura a I2C com os pinos desejados
   sda_pin -> D5
   scl_pin -> D6
*/
void initI2C()
{
  Serial.println("---inside initI2C");
  Wire.begin(sda_pin, scl_pin);
}

/*
   função que escreve um dado valor em um dado registro
*/
void writeRegMPU(int reg, int val)      //aceita um registro e um valor como parâmetro
{
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.write(val);                      // escreve o valor no registro
  Wire.endTransmission(true);           // termina a transmissão
}

/*
   função que lê de um dado registro
*/
uint8_t readRegMPU(uint8_t reg)        // aceita um registro como parâmetro
{
  uint8_t data;
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.endTransmission(false);          // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 1);        // configura para receber 1 byte do registro escolhido acima
  data = Wire.read();                   // lê o byte e guarda em 'data'
  return data;                          //retorna 'data'
}

/*
   função que procura pelo sensor no endereço 0x68
*/
void findMPU(int mpu_addr)
{
  Wire.beginTransmission(mpu_addr);
  int data = Wire.endTransmission(true);

  if (data == 0)
  {
    Serial.print("Dispositivo encontrado no endereço: 0x\n");
    Serial.println(mpu_addr, HEX);
  }
  else
  {
    Serial.println("Dispositivo não encontrado!");
    delay(100);
    findMPU(mpu_addr);
  }
}

/*
   função que verifica se o sensor responde e se está ativo
*/
void checkMPU(int mpu_addr)
{
  findMPU(MPU_ADDR);

  int data = readRegMPU(WHO_AM_I); // Register 117 – Who Am I - 0x75

  if (data == 104)
  {
    Serial.println("MPU6050 Dispositivo respondeu OK! (104)");

    data = readRegMPU(PWR_MGMT_1); // Register 107 – Power Management 1-0x6B

    if (data == 64)
    {
      Serial.println("MPU6050 em modo SLEEP! (64)");
    }
    else
    {
      Serial.println("MPU6050 em modo ACTIVE!");
    }
  }
  else
  {
    Serial.println("Verifique dispositivo - MPU6050 NÃO disponível!");
    delay(100);
    checkMPU(mpu_addr);
  }
}

/*
   função de inicialização do sensor
*/
void initMPU()
{
  setSleepOff();
  setGyroScale();
  setAccelScale();
}

/*
    função para configurar o sleep bit
*/
void setSleepOff()
{
  writeRegMPU(PWR_MGMT_1, 0); // escreve 0 no registro de gerenciamento de energia(0x68), colocando o sensor em o modo ACTIVE
}

/* função para configurar as escalas do giroscópio
   registro da escala do giroscópio: 0x1B[4:3]
   0 é 250°/s

    FS_SEL  Full Scale Range                  Conversão
      0        ± 250 °/s      0b00000000      131         ok
      1        ± 500 °/s      0b00001000      65.5        ??
      2        ± 1000 °/s     0b00010000      32.8        ??
      3        ± 2000 °/s     0b00011000      16.4        ??
*/
void setGyroScale()
{
  writeRegMPU(GYRO_CONFIG, 0);
  convGYRO = 131.00;
}

/* função para configurar as escalas do acelerômetro
   registro da escala do acelerômetro: 0x1C[4:3]
   0 é 250°/s

    AFS_SEL   Full Scale Range                    Conversão
      0           ± 2g            0b00000000      1638.4      ok
      1           ± 4g            0b00001000      8192        ??
      2           ± 8g            0b00010000      4096        ??
      3           ± 16g           0b00011000      2048        ??
*/
void setAccelScale()
{
  writeRegMPU(ACCEL_CONFIG, 0);
  convACEL  = 1638.40;
}

/* função que lê os dados 'crus'(raw data) do sensor
   são 14 bytes no total sendo eles 2 bytes para cada eixo e 2 bytes para temperatura:

  0x3B 59 ACCEL_XOUT[15:8]
  0x3C 60 ACCEL_XOUT[7:0]
  0x3D 61 ACCEL_YOUT[15:8]
  0x3E 62 ACCEL_YOUT[7:0]
  0x3F 63 ACCEL_ZOUT[15:8]
  0x40 64 ACCEL_ZOUT[7:0]

  0x41 65 TEMP_OUT[15:8]
  0x42 66 TEMP_OUT[7:0]

  0x43 67 GYRO_XOUT[15:8]
  0x44 68 GYRO_XOUT[7:0]
  0x45 69 GYRO_YOUT[15:8]
  0x46 70 GYRO_YOUT[7:0]
  0x47 71 GYRO_ZOUT[15:8]
  0x48 72 GYRO_ZOUT[7:0]

*/

void Read_MPU()
{
  Wire.beginTransmission(MPU_ADDR);       // inicia comunicação com endereço do MPU6050
  Wire.write(ACCEL_XOUT);                       // envia o registro com o qual se deseja trabalhar, começando com registro 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);            // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 14);         // configura para receber 14 bytes começando do registro escolhido acima (0x3B)

  AX = Wire.read() << 8;                 // lê primeiro o byte mais significativo
  AX |= Wire.read();                     // depois lê o bit menos significativo
  AY = Wire.read() << 8;
  AY |= Wire.read();
  AZ = Wire.read() << 8;
  AZ |= Wire.read();

  Tp = Wire.read() << 8;
  Tp |= Wire.read();

  GX = Wire.read() << 8;
  GX |= Wire.read();
  GY = Wire.read() << 8;
  GY |= Wire.read();
  GZ = Wire.read() << 8;
  GZ |= Wire.read();
}

void Setup_MPU()
{
  Serial.println("Iniciando configuração do MPU6050");
  initI2C();
  initMPU();
  checkMPU(MPU_ADDR);
  Serial.println("Configuração finalizada, iniciando loop");
}
