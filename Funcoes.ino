
void finaliza()
{
  led_state = !led_state;
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, !led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();

#ifdef CARTAO
  if (!OFFSET)
  {
    sdFile.println();
    sdFile.flush();
  }
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void converterRAW()
{
  //  AcX = ArredondaAcc(media_movel_1(float(AX) / convACEL));
  //  AcY = ArredondaAcc(media_movel_2(float(AY) / convACEL));
  //  AcZ = ArredondaAcc(media_movel_3(float(AZ) / convACEL));
  //  AcX = ((int(10000 * ((media_movel_1(float(AX) / convACEL)) - offAX))) / 10000);
  //  AcY = ((int(10000 * ((media_movel_2(float(AY) / convACEL)) - offAX))) / 10000);
  //  AcZ = ((int(10000 * ((media_movel_3(float(AZ) / convACEL)) - offAX))) / 10000);
  //  GyX = ArredondaGyr(media_movel_4(float(GX) / convGYRO));
  //  GyY = ArredondaGyr(media_movel_5(float(GY) / convGYRO));
  //  GyZ = ArredondaGyr(media_movel_6(float(GZ) / convGYRO));
  Tmp = (float(Tp) + 12412.0) / 340.0;

  AcX = media_movel_1(float(AX) / convACEL);
  AcY = media_movel_2(float(AY) / convACEL);
  AcZ = media_movel_3(float(AZ) / convACEL);
  GyX = media_movel_4(float(GX) / convGYRO);
  GyY = media_movel_5(float(GY) / convGYRO);
  GyZ = media_movel_6(float(GZ) / convGYRO);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PitchRollYaw(float aX, float aY, float aZ, float gX, float gY, float gZ)
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  //  Acc[1] = atan(aX / sqrt(pow(aY, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  //  Acc[0] = atan(aY / sqrt(pow(aX, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  //Aplicar el Filtro Complementario
  //  Pitch = 0.98 * (Pitch + gX * dt) + 0.02 * Acc[0];
  dRoll = integral_trapezio_1(gX) / RAD_TO_DEG;
  //  Roll = 0.98 * (Roll + gY * dt) + 0.02 * Acc[1];
  dPitch = integral_trapezio_2(gY) / RAD_TO_DEG;
  //Integración respecto del tiempo paras calcular el YAW
  dYaw = integral_trapezio_3(gZ) / RAD_TO_DEG;

  Roll = confANG(Roll + dRoll);
  Pitch = confANG(Pitch + dPitch);
  Yaw = confANG(Yaw + dYaw);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float confANG(float valor)
{
  //    if (valor > 3.14159)
  //    {
  //      valor = valor - 2 * 3.14159;
  //    }
  //    else if (valor < -3.14159)
  //    {
  //      valor = valor + 2 * 3.14159;
  //    }
  return (valor);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void velocidade(float aX, float aY, float aZ, float oX, float oY, float oZ)
{
  VelX = VelX + (integral_trapezio_4(aX - CorrigidoX) * 3.6);
  VelY = VelY + (integral_trapezio_5(aY - CorrigidoY) * 3.6);
  VelZ = VelZ + (integral_trapezio_6(aZ - CorrigidoZ) * 3.6);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float ArredondaAcc(float valor)
{
  valor = (round(valor * RoundAcc)) / RoundAcc;
  return (valor);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float ArredondaGyr(float valor)
{
  valor = (round(valor * RoundGyr)) / RoundGyr;
  return (valor);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CorrigeOff()
{
  //  CorrigidoX = aX * (cos(int(Pitch)) * cos(int(Yaw))) + aY * (cos(int(Roll)) * sin(int(Yaw)) + sin(int(Pitch)) * cos(int(Yaw)) * sin(int(Roll))) + aZ * (sin(int(Roll)) * sin(int(Yaw)) - cos(int(Roll)) * sin(int(Pitch)) * cos(int(Yaw)));
  //  CorrigidoY = aX * (-cos(int(Pitch)) * sin(int(Yaw))) + aY * (cos(int(Roll)) * cos(int(Yaw)) - sin(int(Pitch)) * sin(int(Roll)) * sin(int(Yaw))) + aZ * (cos(int(Yaw)) * sin(int(Roll)) + cos(int(Roll)) * sin(int(Pitch)) * sin(int(Yaw)));
  //  CorrigidoZ = aX * sin(int(Pitch)) + aY * (-cos(int(Pitch)) * sin(int(Roll))) + aZ * (cos(int(Pitch)) * cos(int(Roll)));
  CorrigidoX = ArredondaAcc(offAX * (cos(Pitch) * cos(Yaw)) + offAY * (cos(Roll) * sin(Yaw) + sin(Pitch) * cos(Yaw) * sin(Roll)) + offAZ * (sin(Roll) * sin(Yaw) - cos(Roll) * sin(Pitch) * cos(Yaw)));
  CorrigidoY = -(ArredondaAcc(offAX * (-cos(Pitch) * sin(Yaw)) + offAY * (cos(Roll) * cos(Yaw) - sin(Pitch) * sin(Roll) * sin(Yaw)) + offAZ * (cos(Yaw) * sin(Roll) + cos(Roll) * sin(Pitch) * sin(Yaw))));
  CorrigidoZ = ArredondaAcc(offAX * sin(Pitch) + offAY * (-cos(Pitch) * sin(Roll)) + offAZ * (cos(Pitch) * cos(Roll)));
}
