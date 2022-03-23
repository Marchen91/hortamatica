 boolean conectarRedeWiFi() {
  //http://kio4.com/arduino/112_Wemos_WebServer_IPestatica.htm
  //https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/

  //-------------------------------------
  //Dados de acesso à rede Wi-Fi

  // char ssid[]     = "MHPNet";
  // char password[] = "mhpnet2021";
  //-------------------------------------
  //Serial.println("SSID: " + (String)ssid);
  //Serial.println("pwd: " + (String)password);

  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }
  //Configuração do modo de operação - Station Mode
  WiFi.mode(WIFI_STA);

  //Configurando nome de host da conexão
  WiFi.setHostname("Hortamatica");

  //Desconectar e deletar as configurações de conexão anteriores...
  WiFi.disconnect(true);
  //delay(1000);

  //Tentativa de conexão na rede WiFi
  WiFi.begin(REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD);
  Serial.println("Executando função conectarRedeWiFi...Tentativa de conexão!");
  Serial.println("SSID: " + (String)REMOTEXY_WIFI_SSID);

  /*if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Falha na conexão WiFi.");
    

  }*/
  



  while (WiFi.status() != WL_CONNECTED) {
    timeoutWiFi = millis() + 60000;
    Serial.print("Conexão Falhou.");
    delay(500);
    if(millis()>= timeoutWiFi){
      return false;}

    }
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;

  }


  //else {

  return false;
  //}

}
