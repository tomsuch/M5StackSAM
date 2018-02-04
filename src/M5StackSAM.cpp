#include "M5StackSAM.h"

M5SAM::M5SAM()
//  : menuList(NULL),
//    menuIDX(0),
//    subMenuIDX(0),
//    menuCount(0)  
{
  levelIDX = 0;
  menuCount[levelIDX] = 0;
  menuIDX = 0;
  menucolor = getrgb(0,0,128);
  windowcolor = getrgb(128,128,128);
  menutextcolor = getrgb(255,255,255);
}

void M5SAM::up(){
  if(menuIDX<menuCount[levelIDX]-1){
    menuIDX++;
    show();
  }
}

void M5SAM::down(){
  if(menuIDX>0){
    menuIDX--;
    show();
  }
}

void M5SAM::GoToLevel(byte inlevel){
  levelIDX = inlevel;
  menuIDX = 0;
  show();
}

void M5SAM::execute(){
  if(menuList[levelIDX][menuIDX].gotoLevel==-1){
    (*menuList[levelIDX][menuIDX].function)();      
  }else{
    GoToLevel(menuList[levelIDX][menuIDX].gotoLevel);
  }
}

void M5SAM::addMenuItem(byte levelID, const char *menu_title,const char *btnA_title,const char *btnB_title,const char *btnC_title, signed char goto_level,  void(*function)())
{
  byte mCnt = menuCount[levelID];
  menuList[levelID] = (MenuCommandCallback *) realloc(menuList[levelID], (mCnt + 1) * sizeof(MenuCommandCallback));
  strncpy(menuList[levelID][mCnt].title, menu_title, M5SAM_MENU_TITLE_MAX_SIZE);
  strncpy(menuList[levelID][mCnt].btnAtitle, btnA_title, M5SAM_BTN_TITLE_MAX_SIZE);
  strncpy(menuList[levelID][mCnt].btnBtitle, btnB_title, M5SAM_BTN_TITLE_MAX_SIZE);
  strncpy(menuList[levelID][mCnt].btnCtitle, btnC_title, M5SAM_BTN_TITLE_MAX_SIZE);
  menuList[levelID][mCnt].gotoLevel = goto_level;
  menuList[levelID][mCnt].function = function;
  menuCount[levelID]++;
}

void M5SAM::show(){
  drawMenu(menuList[levelIDX][menuIDX].title, menuList[levelIDX][menuIDX].btnAtitle, menuList[levelIDX][menuIDX].btnBtitle, menuList[levelIDX][menuIDX].btnCtitle, menucolor, windowcolor, menutextcolor);  
}

void M5SAM::windowClr(){
  M5.Lcd.fillRoundRect(0,32,M5.Lcd.width(),M5.Lcd.height()-32-32,3,windowcolor);    
}

unsigned int M5SAM::getrgb(byte inred, byte ingrn, byte inblue){
  inred = map(inred,0,255,0,31);
  ingrn = map(ingrn,0,255,0,63);
  inblue = map(inblue,0,255,0,31);
  return inred << 11 | ingrn << 5 | inblue;
}

void M5SAM::drawAppMenu(String inmenuttl, String inbtnAttl, String inbtnBttl, String inbtnCttl){
  drawMenu(inmenuttl, inbtnAttl, inbtnBttl, inbtnCttl, menucolor, windowcolor, menutextcolor);
}

void M5SAM::setColorSchema(unsigned int inmenucolor, unsigned int inwindowcolor, unsigned int intextcolor){
  menucolor = inmenucolor;
  windowcolor = inwindowcolor;
  menutextcolor = intextcolor;  
}

void M5SAM::drawMenu(String inmenuttl, String inbtnAttl, String inbtnBttl, String inbtnCttl, unsigned int inmenucolor, unsigned int inwindowcolor, unsigned int intxtcolor){
  M5.Lcd.fillRoundRect(31,M5.Lcd.height()-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(126,M5.Lcd.height()-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(221,M5.Lcd.height()-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(0,0,M5.Lcd.width(),28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(0,32,M5.Lcd.width(),M5.Lcd.height()-32-32,3,inwindowcolor);  
    
  M5.Lcd.setTextColor(intxtcolor);
  M5.Lcd.drawCentreString(inmenuttl,M5.Lcd.width()/2,6,2);

  M5.Lcd.drawCentreString(inbtnAttl,31+30,M5.Lcd.height()-28+6,2);
  M5.Lcd.drawCentreString(inbtnBttl,126+30,M5.Lcd.height()-28+6,2);
  M5.Lcd.drawCentreString(inbtnCttl,221+30,M5.Lcd.height()-28+6,2);  
}

