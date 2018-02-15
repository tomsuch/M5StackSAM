String getWiFiMac() {
  uint8_t baseMac[6];
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  char baseMacChr[18] = {0};
  sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
  return String(baseMacChr);
}

//void appTEMPLATE(){
//  MyMenu.drawAppMenu(F("APP_TITTLE"),F("BTN_A_TITTLE"),F("BTN_B_TITTLE"),F("BTN_C_TITTLE"));
//
//  while(M5.BtnB.wasPressed()){
//    M5.update();
//  }
//    
//  while(!M5.BtnB.wasPressed()){
//    M5.update();
//  }
//
//  MyMenu.show();
//}

void appListDemo(){
  MyMenu.drawAppMenu(F("LIST DEMO"),F("SELECT"),F("ESC"),F("LIST"));

  while(M5.BtnB.wasPressed()){
    M5.update();
  }

  MyMenu.clearList();
  MyMenu.setListCaption("DEMO LIST");
  MyMenu.addList("AHOOJ");  
  MyMenu.addList("VOLE");  
  MyMenu.addList("JAK");  
  MyMenu.addList("SE");
  MyMenu.addList("MAS");
  MyMenu.addList("TY");
  MyMenu.addList("VOLE");
  MyMenu.addList("JEDEN");
  MyMenu.addList("SKAREDEJ");
  MyMenu.addList("PLESNIVEJ");
  MyMenu.addList("JAK");  
  MyMenu.addList("SE");
  MyMenu.addList("MAS");
  MyMenu.addList("TY");
  MyMenu.addList("VOLE");
  MyMenu.addList("JEDEN");
  MyMenu.addList("SKAREDEJ");
  MyMenu.addList("PLESNIVEJ");
  MyMenu.addList("SKAREDEJ");
  MyMenu.addList("PLESNIVEJ");
  MyMenu.showList();  

  while(!M5.BtnB.wasPressed()){
    if(M5.BtnC.wasPressed()){
      MyMenu.nextList();
    }
    if(M5.BtnA.wasPressed()){
      MyMenu.windowClr();
      M5.Lcd.drawCentreString("ID: "+String(MyMenu.getListID()),M5.Lcd.width()/2,(M5.Lcd.height()/2)-10,2);
      M5.Lcd.drawCentreString("TEXT: "+MyMenu.getListString(),M5.Lcd.width()/2,(M5.Lcd.height()/2)+10,2);
    }
    M5.update();
  }
  
  MyMenu.show();
}


void appFacesGetString(){
  String tmpStr = "";
  MyMenu.drawAppMenu(F("FACES GET STRING"),F(""),F("ESC"),F(""));
  MyMenu.windowClr();
  M5.Lcd.drawCentreString("WRITE TEXT AND PRESS ENTER (OK)",M5.Lcd.width()/2,M5.Lcd.height()/2,2);
  while(M5.BtnB.wasPressed()){
    M5.update();
  }

  tmpStr = MyMenu.keyboardGetString();
  MyMenu.windowClr();
  M5.Lcd.drawCentreString(tmpStr,M5.Lcd.width()/2,M5.Lcd.height()/2,2);

  while(!M5.BtnB.wasPressed()){
    M5.update();
  }
  
  MyMenu.show();
}

void appSysInfo(){
  MyMenu.drawAppMenu(F("M5 SYSTEM INFO"),F(""),F("ESC"),F(""));

  uint8_t chipRev = ESP.getChipRevision();
  uint8_t cpuSpeed = ESP.getCpuFreqMHz();
  uint32_t flashSize = ESP.getFlashChipSize();
  uint32_t flashSpeed = ESP.getFlashChipSpeed();
  const char * sdkVer = ESP.getSdkVersion();
  String WiFiMAC = getWiFiMac();
  uint32_t ramFree = system_get_free_heap_size();

  while(M5.BtnB.wasPressed()){
    M5.update();
  }
  
  M5.Lcd.drawString(F("CPU_FREQ:"),10,40,2);
  M5.Lcd.drawNumber(cpuSpeed, 120, 40, 2);
  
  M5.Lcd.drawString(F("CHIP_REV:"),10,60,2);
  M5.Lcd.drawNumber(chipRev, 120, 60, 2);
    
  M5.Lcd.drawString(F("FLASH_SIZE:"),10,80,2);
  M5.Lcd.drawNumber(flashSize, 120, 80, 2);

  M5.Lcd.drawString(F("FLASH_SPEED:"),10,100,2);
  M5.Lcd.drawNumber(flashSpeed, 120, 100, 2);

  M5.Lcd.drawString(F("SDK_VERSION:"),10,120,2);
  M5.Lcd.drawString(sdkVer,120,120,2);

  M5.Lcd.drawString(F("WIFI_STA_MAC:"),10,140,2);
  M5.Lcd.drawString(WiFiMAC,120,140,2);

  M5.Lcd.drawString(F("FREE_RAM:"),10,160,2);
  M5.Lcd.drawNumber(ramFree,120,160,2);
    
  while(!M5.BtnB.wasPressed()){
    M5.update();
  }

  MyMenu.show();
}

void appIICScanner(){
  byte error, address;
  int nDevices;
  byte ridx = 0;
  byte lidx = 0;
  boolean scanrun = HIGH;
  
  MyMenu.drawAppMenu(F("I2C SCANNER"),F("SCAN"),F("ESC"),F(""));

  while(M5.BtnB.wasPressed()){
    M5.update();
  }
    
  while(!M5.BtnB.wasPressed()){
    if(scanrun==HIGH){
      scanrun = LOW;
      nDevices = 0;
      for(address = 1; address < 127; address++ ){
        ridx++;
        if(ridx==17){
          ridx = 1;
          lidx++;
        }
        Wire.beginTransmission(address);
        error = Wire.endTransmission();    
        if (error == 0){
          M5.Lcd.drawString(String(address,HEX),0+(ridx*18),45+(lidx*20),2);
          nDevices++;
        }else if (error==4){
          M5.Lcd.drawString(F("ER"),0+(ridx*18),45+(lidx*20),2);
        }else{
          M5.Lcd.drawString(F("--"),0+(ridx*18),45+(lidx*20),2);
        }
      }
      M5.update();
    }else{
      if(M5.BtnA.wasPressed()){
        MyMenu.windowClr();
        ridx = 0;
        lidx = 0;
        scanrun = HIGH;
      }
      M5.update();
    }
  }  
  MyMenu.show();  
}

void appWiFiScanner(){
  uint16_t wifi_count = 0;
  boolean wifi_showlock = LOW;
  byte list_lines = 5;
  uint16_t list_page = 0;
  uint16_t list_pages = 0;
  uint16_t list_lastpagelines = 0;

  MyMenu.drawAppMenu(F("WiFi SCANNER"),F("SCAN"),F("ESC"),F("PAGE"));

  M5.Lcd.drawCentreString(F("SCANNING....."),M5.Lcd.width()/2,M5.Lcd.height()/2,2);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  while(M5.BtnB.wasPressed()){
    M5.update();
  }  

  wifi_count = WiFi.scanNetworks();

  if(wifi_count > 0){    
    if(wifi_count > list_lines){
      list_lastpagelines = wifi_count % list_lines;
      if(list_lastpagelines>0){
        list_pages = (wifi_count - list_lastpagelines) / list_lines;
        list_pages++;
      }else{
        list_pages = wifi_count / list_lines;
      }
    }else{
      list_pages = 1;
    }
  }

  while(!M5.BtnB.wasPressed()){
    if(wifi_count==0){
      if(!wifi_showlock){
        MyMenu.windowClr();
        M5.Lcd.drawCentreString(F("NO NETWORKS FOUND"),M5.Lcd.width()/2,M5.Lcd.height()/2,2);
        wifi_showlock = HIGH;        
      }
    }else{
      if(!wifi_showlock){
        MyMenu.windowClr();
        M5.Lcd.drawCentreString("FOUND "+String(wifi_count)+" NETWORKS, PAGE: "+String(list_page+1)+"/"+String(list_pages),M5.Lcd.width()/2,40,2);
        if((list_page + 1) == list_pages){
          if(list_lastpagelines == 0 and wifi_count >= list_lines){
            for(byte i = 0;i<list_lines;i++){
              M5.Lcd.drawString(WiFi.SSID(i+(list_page*list_lines)),5,80+(i*20),2);
              M5.Lcd.drawString(String(WiFi.RSSI(i+(list_page*list_lines))) + " dB",250,80+(i*20),2);
              M5.Lcd.drawString((WiFi.encryptionType(i+(list_page*list_lines)) == WIFI_AUTH_OPEN)?" ":"*",310,80+(i*20),2);
            }
          }else{
            if(list_pages>1){
              for(byte i = 0;i<list_lastpagelines;i++){
                M5.Lcd.drawString(WiFi.SSID(i+(list_page*list_lines)),5,80+(i*20),2);
                M5.Lcd.drawString(String(WiFi.RSSI(i+(list_page*list_lines))) + " dB",250,80+(i*20),2);
                M5.Lcd.drawString((WiFi.encryptionType(i+(list_page*list_lines)) == WIFI_AUTH_OPEN)?" ":"*",310,80+(i*20),2);
              }            
            }else{
              for(byte i = 0;i<wifi_count;i++){
                M5.Lcd.drawString(WiFi.SSID(i+(list_page*list_lines)),5,80+(i*20),2);
                M5.Lcd.drawString(String(WiFi.RSSI(i+(list_page*list_lines))) + " dB",250,80+(i*20),2);
                M5.Lcd.drawString((WiFi.encryptionType(i+(list_page*list_lines)) == WIFI_AUTH_OPEN)?" ":"*",310,80+(i*20),2);
              }                          
            }
          }
        }else{
            for(byte i = 0;i<list_lines;i++){
              M5.Lcd.drawString(WiFi.SSID(i+(list_page*list_lines)),5,80+(i*20),2);
              M5.Lcd.drawString(String(WiFi.RSSI(i+(list_page*list_lines))) + " dB",250,80+(i*20),2);
              M5.Lcd.drawString((WiFi.encryptionType(i+(list_page*list_lines)) == WIFI_AUTH_OPEN)?" ":"*",310,80+(i*20),2);
            }          
        }
        wifi_showlock = HIGH;        
      }       
    }
    if(M5.BtnA.wasPressed()){
        list_page = 0;
        list_pages = 0;
        MyMenu.windowClr();
        M5.Lcd.drawCentreString(F("SCANNING....."),M5.Lcd.width()/2,M5.Lcd.height()/2,2);
        wifi_count = WiFi.scanNetworks();
        wifi_showlock = LOW;
        if(wifi_count > 0){    
          if(wifi_count > list_lines){
            list_lastpagelines = wifi_count % list_lines;
            if(list_lastpagelines>0){
              list_pages = (wifi_count - list_lastpagelines) / list_lines;
              list_pages++;
            }else{
              list_pages = wifi_count / list_lines;
            }
          }else{
            list_pages = 1;
          }
        }
    }
    if(M5.BtnC.wasPressed()){
      if(wifi_count > 0 and list_pages > 1){
        list_page++;
        if(list_page == list_pages){
          list_page = 0;
        }
        wifi_showlock = LOW;
      }
    }
    M5.update(); 
  }
  MyMenu.show();
}

void appSleep(){
  M5.setWakeupButton(BUTTON_B_PIN);
  M5.powerOFF();
}

void appCfgBrigthness(){
  byte tmp_brigth = byte(EEPROM.read(0));
  byte tmp_lbrigth = 0;
  
  MyMenu.drawAppMenu(F("DISPLAY BRIGHTNESS"),F("-"),F("OK"),F("+"));
  
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  

  while(!M5.BtnB.wasPressed()){
    if(M5.BtnA.wasPressed() and tmp_brigth >= 16){
      tmp_brigth = tmp_brigth - 16;
    }
    if(M5.BtnC.wasPressed() and tmp_brigth <= 239){
      tmp_brigth = tmp_brigth + 16;
    }
    if(tmp_lbrigth != tmp_brigth){
      tmp_lbrigth = tmp_brigth;
      EEPROM.write(0,tmp_lbrigth);
      EEPROM.commit();
      M5.lcd.setBrightness(byte(EEPROM.read(0)));
      MyMenu.windowClr();
      M5.Lcd.drawNumber(byte(EEPROM.read(0)), 120 , 90, 6);
    }
    M5.update();
  }
  MyMenu.show();      
}

void appStopWatch(){
  boolean tmp_run = false;
  float tmp_sec = 0;
  unsigned int tmp_min = 0;
  unsigned long tmp_tmr = 0;
  
  MyMenu.drawAppMenu(F("STOPWATCH"),F("S/S"),F("ESC"),F("RES"));

  M5.Lcd.drawString(F("MIN"),40,120,2);
  M5.Lcd.drawString(F("SEC"),170,120,2);
  M5.Lcd.drawFloat(tmp_sec, 1, 210, 100, 6);
  M5.Lcd.drawNumber(tmp_min, 80, 100, 6);

  while(M5.BtnB.wasPressed()){
    M5.update();
  }  

  while(!M5.BtnB.wasPressed()){
    M5.update();
    if(M5.BtnC.wasPressed()){
      tmp_sec = 0;
      tmp_min = 0;      
      MyMenu.windowClr();
      M5.Lcd.drawString(F("MIN"),40,120,2);
      M5.Lcd.drawString(F("SEC"),170,120,2);
      M5.Lcd.drawFloat(tmp_sec, 1, 210, 100, 6);
      M5.Lcd.drawNumber(tmp_min, 80, 100, 6);
    }
    if(tmp_run){
      if(M5.BtnA.wasPressed()){
        tmp_run = LOW;
      }
      if(millis()-tmp_tmr > 100){
        tmp_tmr = millis();
        tmp_sec = tmp_sec + 0.1;
        if(tmp_sec > 59.9){
          tmp_sec = 0;
          tmp_min++;
          MyMenu.windowClr();
          M5.Lcd.drawString(F("MIN"),40,120,2);
          M5.Lcd.drawString(F("SEC"),170,120,2);
          M5.Lcd.drawFloat(tmp_sec, 1, 210, 100, 6);
          M5.Lcd.drawNumber(tmp_min, 80, 100, 6);
        }
        M5.Lcd.drawFloat(tmp_sec, 1, 210, 100, 6);
        M5.Lcd.drawNumber(tmp_min, 80, 100, 6);
      }      
    }else{
      if(M5.BtnA.wasPressed()){
        //tmp_sec = 0;
        //tmp_min = 0;
        tmp_run = HIGH;
      }
    }
  }
  MyMenu.show();  
}
    
