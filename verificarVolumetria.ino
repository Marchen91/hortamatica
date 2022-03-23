void verificarVolumetriaAgua() {
  //http://kio4.com/arduino/220_Wemos_Interrupcion.htm
  //https://www.arduino.cc/reference/pt/language/functions/external-interrupts/attachinterrupt/
  //https://how2electronics.com/iot-water-flow-meter-using-esp8266-water-flow-sensor/
  //https://community.blynk.cc/t/solved-flow-meter-intergration-with-wemos-d1/13918
  //https://www.robocore.net/tutoriais/usando-sensor-fluxo-de-agua

  //Range analógico de leitura Placa Wemos ==> 0 (mínimo) até 4095 (máximo)
  //Range de Litros/Minuto do Sensor de Fluxo de Água 1/2" ==> De 1 a 30 L/min
  //Serial.println("----------------------------------------------");
  Serial.println("Executando função: verificarVolumetriaAgua()");

  //executa a contagem de pulsos uma vez por segundo
  //if () {
  if ((millis() - tempo_antes) > 1000 && digitalRead(pino_Trilha1_Solenoide) == HIGH) {

    //desabilita a interrupcao para realizar a conversao do valor de pulsos
    //MODELO DE SINTAXE: detachInterrupt(digitalPinToInterrupt(pin));
    detachInterrupt(digitalPinToInterrupt(pino_Trilha1_SensorVolumetriaAgua));

    //conversao do valor de pulsos para L/min
    fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;
    //exibicao do valor de fluxo
    Serial.print("Fluxo de: ");
    Serial.print(fluxo);
    Serial.println(" L/min");
    litrosPorMinuto_Trilha1 = fluxo;

    //calculo do volume em L passado pelo sensor
    volume = fluxo / 60;

    //armazenamento do volume
    volume_total += volume;
    //exibicao do valor de volume
    Serial.print("Volume: ");
    Serial.print(volume_total);
    Serial.println(" L");
    Serial.println();

    //reinicializacao do contador de pulsos
    contador = 0;

    //atualizacao da variavel tempo_antes
    tempo_antes = millis();

    attachInterrupt(digitalPinToInterrupt(pino_Trilha1_SensorVolumetriaAgua), contador_pulso, FALLING);
    //******************************************

    //Armazenamento de Valores: KPI Fluxo Médio L/Min
    fluxoAcumulado += fluxo;
    contFluxoAcum++;

    //Armazenamento de Valores KPI Volume Acumulado L
    volumeAcumulado += volume;

  }
}
