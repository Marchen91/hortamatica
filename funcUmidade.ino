void verificarUmidadeSolo()
{
  //Serial.println("#############################################");
  Serial.println("Executando função: verificarUmidadeSolo()");
  //Sensor antigo -------------------------------------------------
  //Range analógico de leitura - 0 (mínimo) até 4095 (máximo)
  //Range de porcentagem de umidade: 550 -> 0% e 4095 -> 100%
  //---------------------------------------------------------------
  //Novo sensor HD-38
  //Range analógico de leitura - 0 (máximo) até 4095 (mínimo)
  //Range de porcentagem de umidade: 1326 (100% úmido) e 4095 (0% seco) 
  
  valorUmidade_Trilha1 = analogRead(pino_Trilha1_SensorUmidade);
  Serial.printf("Analog Read - Sensor Umidade:  %d \n", valorUmidade_Trilha1);

  //Verificação Porcentagem de Umidade
  if (valorUmidade_Trilha1 >= 1800 && valorUmidade_Trilha1 <= 4095 ) {
    porcentUmidade_Trilha1 = map(valorUmidade_Trilha1, 4095, 1800, 0, 100);
  } else {
    porcentUmidade_Trilha1 = 100.0;
  }
  Serial.printf("Porcentagem de Umidade: %d \n ", porcentUmidade_Trilha1);
  
  //Verificação do estado do solo de plantio
  if (porcentUmidade_Trilha1 <= 50.0) {
    
    ligarSolenoide();
    irrigacaoAuto = true;
    
  } else if (porcentUmidade_Trilha1 >= 85.0) {
    desligarSolenoide();
    irrigacaoAuto = false;
  }

  

  //  if (valorUmidade_Trilha1 >= 550) {
  //    Serial.println("Estado da Terra: Solo úmido.");
  //    desligarSolenoide();
  //  }
  //  else
  //  {
  //    Serial.println("Estado da Terra: Solo seco.");
  //    ligarSolenoide();
  //  }

  //Cálculo indicador Umidade Média Acumulada do Solo
  umidadeAcumulada += porcentUmidade_Trilha1;
  contUmidadeAcum++;

  //Verificação estado da solenoide
  String statusSolenoide = (digitalRead(pino_Trilha1_Solenoide) == HIGH) ? "Status: Solenóide Ligada." : "Status: Solenóide Desligada.";
  Serial.println(statusSolenoide);
  //Serial.println("#############################################");
}
