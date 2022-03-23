void atualizarDadosRemoteXY() {

  //Serial.println("Atualizando dados para o App Movel...");

  //1. Porcentagem de Umidade (%)
  if (porcentUmidade_Trilha1 >= 0.0 && porcentUmidade_Trilha1 <= 100.0) {
    RemoteXY.levelUmid = (int)porcentUmidade_Trilha1;
    RemoteXY.graphUmid = (int)porcentUmidade_Trilha1;
  } else {
    RemoteXY.levelUmid = 0;
    RemoteXY.graphUmid = 0;
  }

  //2. Solenoide (Aberta/Fechada)
  if (digitalRead(pino_Trilha1_Solenoide) == HIGH) {
    //Solenoide LIGADA
    RemoteXY.ledVerde_b = 255; //Aceso == 255
    RemoteXY.ledVermelho_r = 0; //Apagado == 0
  } else {
    //Solenoide DESLIGADA
    RemoteXY.ledVermelho_r = 255;
    RemoteXY.ledVerde_b = 0;

  }

  //3. Modo do Sistema (Ligado/Desligado)
  if (RemoteXY.switchOnOff == 1) {
    sysStatus = true;
    //Serial.println("Sistema automatizado LIGADO manualmente...");
  } else if (RemoteXY.switchOnOff == 0) {
    sysStatus = false;
    //Serial.println("Sistema automatizado DESLIGADO manualmente...");
  }
  RemoteXY_Handler();
}
