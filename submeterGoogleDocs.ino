void submeterDadosGoogleDocs() {


  //Submete dados ao Google Docs se houver conexão de rede WiFi...
  //Serial.println("----------------------------------------------");
  Serial.println("Função envio de dados no Google Docs.");

  if (conectarRedeWiFi() == true) {
    Serial.println("Conexão estabelecida.");
    WiFiClient client;
    const char *host = "api.pushingbox.com";
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("Falha na conexão WiFi!");
      return;
    }
    //else {
    //ip = WiFi.localIP();
    //Serial.println(ip);
    //}

    //Coluna de informação da solenóide
    String t1solenoide = "";
    if (digitalRead(pino_Trilha1_Solenoide) == HIGH) {
      t1solenoide = "LIGADA";
    } else {
      t1solenoide = "DESLIGADA";
    }
    //*****

    int mediaFluxoT1 = (int)(fluxoAcumulado / contFluxoAcum);
    int mediaUmidadeT1 = (int)(umidadeAcumulada / contUmidadeAcum);
    Serial.println("Fluxo Acumulado : ");
    Serial.println(fluxoAcumulado);
    Serial.println("Média Fluxo : ");
    Serial.println(mediaFluxoT1);

    Serial.println("Umidade Acumulado : ");
    Serial.println(umidadeAcumulada);
    Serial.println("Média Umidade : ");
    Serial.println(mediaUmidadeT1);

    //int mediaUmidadeArT1 = (int)(umidadeAcumuladaAr / contUmidadeAcumAr);
    //litrosPorMinuto_Trilha1

    //Composição de partes da URL para enviar
    String url = "/pushingbox?";
    url += "devid=";
    url += "v45CDDC2B798C5CF";
    url += "&t1umidade=" + (String)mediaUmidadeT1;
    url += "&t1solenoide=" + (String)t1solenoide;
    url += "&t1fluxo=" + (String)litrosPorMinuto_Trilha1;
    url += "&t1volAcumulado=" + (String)volumeAcumulado;
    //litrosPorMinuto_Trilha1 = 0.0;
    Serial.println("Requisitanto URL ao servidor...");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 4000) {
        Serial.println(">>> Client Timeout!");
        client.stop();
        return;
      }
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.print("Data Sent!");
      timeoutDadosGoogleDocs = millis() + 3600000;
      umidadeAcumulada =0;
      contUmidadeAcum =0;

    }
    Serial.println();
    Serial.println("closing client connection");
  }
  else {
    timeoutDadosGoogleDocs = millis() + 5000;
    Serial.println("Tentativa de envio Google falhou.");

    return;




    /*
      // Serial.println("ERRO AO VERIFICAR A CONEXÃO.");
      Serial.println("Sem conexão, reconectando...");
      unsigned long timereconnection = millis();
      WiFi.disconnect();
      WiFi.begin(REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD);

      while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if (millis() - timereconnection > 4000) {
        Serial.println("Falha na reconexão.");
        return;
      }
      }*/
  }
}
