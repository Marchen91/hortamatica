void verificarUmidadeAr(){

  Serial.println("Executando função DHT");


  // Leitura dos valores de umidades e temperaturas do DHT11
  double umidadeDHT = dht.readHumidity();
  double temperaturaDHT = dht.readTemperature();

  //Função apra identificar falhas na leitura do DHT11
  if (isnan(umidadeDHT) || isnan(temperaturaDHT)) 
  {
    Serial.println("Falha na leitura do DHT");
  } 
  else
  {
    Serial.print("Umidade: ");
    Serial.print(umidadeDHT);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(temperaturaDHT);
    Serial.println(" °C");
  }

  //Acionar ou não a Solenóide de acordo com o % de umidade
  if (umidadeDHT <= 30.0) {
    ligarSolenoide();
  } else if (umidadeDHT >= 68.0) {
    desligarSolenoide();
  }


  //Cálculo indicador Umidade Média Acumulada do Ar
  umidadeAcumuladaAr += umidadeDHT;
  contUmidadeAcumAr++;

 

  //Verificação estado da solenoide
  String statusSolenoide = (digitalRead(pino_Trilha1_Solenoide) == HIGH) ? "Status: Solenóide Ligada." : "Status: Solenóide Desligada.";
  Serial.println(statusSolenoide);
  



}
