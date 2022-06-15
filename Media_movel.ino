float media_1[n];

float media_movel_1(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_1[i] = media_1[i - 1];
    //    Serial.print(media_1[i]);
    //    Serial.print(",");
  }
  media_1[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_1[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_1[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

float media_2[n];

float media_movel_2(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_2[i] = media_2[i - 1];
    //    Serial.print(media_2[i]);
    //    Serial.print(",");
  }
  media_2[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_2[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_2[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

float media_3[n];

float media_movel_3(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_3[i] = media_3[i - 1];
    //    Serial.print(media_3[i]);
    //    Serial.print(",");
  }
  media_3[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_3[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_3[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

float media_4[n];

float media_movel_4(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_4[i] = media_4[i - 1];
    //    Serial.print(media_4[i]);
    //    Serial.print(",");
  }
  media_4[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_3[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_4[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

float media_5[n];

float media_movel_5(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_5[i] = media_5[i - 1];
    //    Serial.print(media_4[i]);
    //    Serial.print(",");
  }
  media_5[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_3[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_5[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

float media_6[n];

float media_movel_6(float entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    media_6[i] = media_6[i - 1];
    //    Serial.print(media_4[i]);
    //    Serial.print(",");
  }
  media_6[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(media_3[0]);
  //  Serial.print("\t");
  float acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += media_6[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}
