void irrigarManual () {
  //Irrigar manualmente ao clicar no botão [Irrigar]
  //Tempo padrão de 30 segundos de irrigação.
  if (RemoteXY.btnIrrigar == 1) {
    //Botão foi pressionado na interface
    Serial.println("Botao irrigar PRESSIONADO...");
    RemoteXY_Handler();
    irrigacaoManual = true;
  }

  if (irrigacaoManual == true && (millis() < timeoutIrrigacaoManual)) {
    ligarSolenoide();
  } else {
    desligarSolenoide();
  }
}
