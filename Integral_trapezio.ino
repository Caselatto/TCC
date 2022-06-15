float integral_1[m];

float integral_trapezio_1(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_1[m + 1 - i] = integral_1[m - i];
  }
  integral_1[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_1[i];
    }
    else {
      resultado = resultado + 2 * integral_1[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}

float integral_2[m];

float integral_trapezio_2(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_2[m + 1 - i] = integral_2[m - i];
  }
  integral_2[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_2[i];
    }
    else {
      resultado = resultado + 2 * integral_2[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}

float integral_3[m];

float integral_trapezio_3(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_3[m + 1 - i] = integral_3[m - i];
  }
  integral_3[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_3[i];
    }
    else {
      resultado = resultado + 2 * integral_3[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}

float integral_4[m];

float integral_trapezio_4(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_4[m + 1 - i] = integral_4[m - i];
  }
  integral_4[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_4[i];
    }
    else {
      resultado = resultado + 2 * integral_4[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}

float integral_5[m];

float integral_trapezio_5(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_5[m + 1 - i] = integral_5[m - i];
  }
  integral_5[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_5[i];
    }
    else {
      resultado = resultado + 2 * integral_5[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}

float integral_6[m];

float integral_trapezio_6(float entrada) {
  int i;
  float resultado = 0;
  for (i = m - 1; i > 0 ; i--) {
    integral_6[m + 1 - i] = integral_6[m - i];
  }
  integral_6[0] = entrada;

  for (i = m - 1; i >= 0 ; i--) {
    if ((i == 1) || (i == m)) {
      resultado = resultado + integral_6[i];
    }
    else {
      resultado = resultado + 2 * integral_6[i];
    }
  }
  resultado =  resultado * (dt / 2);
  return (resultado);
}
