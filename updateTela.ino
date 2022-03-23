void updateTelaAppMovel() {

  //Serial.println("*******************************************************");
  //Serial.println("Executando a função: updateTelaAppMovel()");
  //Atualização de dados do App é independente
  //do restante dos controles do sistema.
  atualizarDadosRemoteXY();

  //Rotina de manipulação do aplicativo móvel
  RemoteXY_Handler();

  //Serial.println("*******************************************************");
}
