#ifdef CARTAO

char filename[11] = "Tcc00.csv";    // Nome do arquivo inicial
int i = 0;

void Setup_Cartao()
{
  pinMode(CS_PIN, OUTPUT);   // Inicia cartão SD
  while (!SD.begin(CS_PIN))
  {
    Serial.println(F("SD falhou"));   // Em caso de falha na inicialização
    Serial.println(F("Esperando SD"));   // Em caso de falha na inicialização
    while (!SD.begin(CS_PIN))
    {
      delay (500);
    }
  }
  Serial.println(F("Tudo certo"));    // Inicialização certa

  while (SD.exists(filename))         // Função para gerar arquivo com nome seguinte
  {
    if (i < 10)
    {
      sprintf(filename, "Tcc0%d.csv", i);
    }
    else
    {
      sprintf(filename, "Tcc%2d.csv", i);
    }
    i++;
  }
  sdFile = SD.open(filename, FILE_WRITE);
  Serial.print("Arquivo: ");
  Serial.println(filename);
  Serial.println("SD ok");
}

#endif

void salva(char nome[9], float valor)
{
  Serial.print(nome);
  Serial.print("\t");
  Serial.print(valor, 3);
  Serial.print("\t");
#ifdef CARTAO
  if (!OFFSET)
  {
    sdFile.print(valor, 5);
    sdFile.print(";\t");
  }
#endif
}
