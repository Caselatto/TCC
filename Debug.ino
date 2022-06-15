void mostraRAW()
{
  salva("AX", AX);
  salva("AY", AY);
  salva("AZ", AZ);
  salva("GX", GX);
  salva("GY", GY);
  salva("GZ", GZ);
}

void mostraOFF()
{
  //  Serial.print("\toffAX = "); Serial.print(offAX, 5);
  //  Serial.print("\toffAY = "); Serial.print(offAY, 5);
  //  Serial.print("\toffAZ = "); Serial.print(offAZ, 5);
  //  Serial.print("\toffGX = "); Serial.print(offGX, 5);
  //  Serial.print("\toffGY = "); Serial.print(offGY, 5);
  //  Serial.print("\toffGZ = "); Serial.print(offGZ, 5);
  //  Serial.print("\toffRol = "); Serial.print(offRoll, 5);
  //  Serial.print("\toffPit = "); Serial.print(offPitch, 5);
  //  Serial.print("\toffYaw = "); Serial.print(offYaw, 5);
  Serial.print("\tCorrigidoX = "); Serial.print(CorrigidoX, 5);
  Serial.print("\tCorrigidoY = "); Serial.print(CorrigidoY, 5);
  Serial.print("\tCorrigidoZ = "); Serial.print(CorrigidoZ, 5);
}

void mostraCON()
{
  //  salva("AcX", AcX - offAX);
  //  salva("AcY", AcY - offAY);
  //  salva("AcZ", AcZ - offAZ);

  salva("AcX", AcX);
  salva("AcY", AcY);
  salva("AcZ", AcZ);

  //  salva("AcX", AcX - CorrigidoX);
  //  salva("AcY", AcY - CorrigidoY);
  //  salva("AcZ", AcZ - CorrigidoZ);

  salva("GyX", GyX);
  salva("GyY", GyY);
  salva("GyZ", GyZ);

  //  salva("GyX", GyX - offGX);
  //  salva("GyY", GyY - offGY);
  //  salva("GyZ", GyZ - offGZ);
}

void mostraANG()
{
  //  salva("Roll", Roll);
  //  salva("Pitch", Pitch);
  //  salva("Yaw", Yaw);

  salva("Roll", Roll * RAD_TO_DEG);
  salva("Pitch", Pitch * RAD_TO_DEG);
  salva("Yaw", Yaw * RAD_TO_DEG);
}

void mostraVEL()
{
  salva("VelX", VelX);
  salva("VelY", VelY);
  salva("VelZ", VelZ);
}

void mostraCOR()
{
  salva("CorX", CorrigidoX);
  salva("CorY", CorrigidoY);
  salva("CorZ", CorrigidoZ);
}
