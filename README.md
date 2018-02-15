# M5StackSAM

A simple to use library for creating an application menu on the M5Stack platform.

M5STACK FACES SUPPORT:

	SUPPORT for M5STACK-FACES QWERTY keyboart
	keyboardGetString(); - return String entered by keyboard
	EXAMPLE:
		String tmpStr = "";
		tmpStr = MyMenu.keyboardGetString(); - write text and press ENTER (OK) on keyboard
		

LIST FUNCTIONS:
	
	clearList(); - cler list buffer and settings
	setListCaption("LIST - CAPTION"); - set list caption
	addList("ITEM TEXT"); - add item to list
	showList(); - show created list
	nextList(); - select next item
	getListID() - get ID of selected item as byte
	getListString() - get ITEM TEXT of selected item as String


CHANGING COLOR SCHEMA:

	setColorSchema(MENU_COLOR, WINDOW_COLOR, TEXT_COLO);
	COLORS are uint16_t (RGB565 format).
	getrgb(byte R, byte G, byte B); - CALCULATING RGB565 format
  
	HERCULES MONITOR COLOR SCHEMA
	setColorSchema(MyMenu.getrgb(0,0,0), MyMenu.getrgb(0,0,0), MyMenu.getrgb(0,255,0));
   
ADD MENU ITEM
   
	 addMenuItem(SUBMENU_ID,MENU_TITTLE,BTN_A_TITTLE,BTN_B_TITTLE,BTN_C_TITTLE,SELECTOR,FUNCTION_NAME);
      SUBMENU_ID byte [0-7]: TOP MENU = 0, SUBMENUs = [1-7]
      SELECTOR
             IF SELECTOR = -1 then execute() run function with name in last parameter (FUNCTION_NAME)
             IF SELECTOR = [0-7] then execute() switch menu items to SUBMENU_ID
      FUNCTION_NAME: name of function to run....

OTHER
		
		show(); - Show/Resfresh actual menu position
		execute(); - run APP / Switch menu level
		up() - menu UP
		down() - menu DOWN
		drawAppMenu(APP_TITTLE,BTN_A_TITTLE,BTN_B_TITTLE,BTN_C_TITTLE); - Create and show app GUI template
		windowClr(); - clear menu window
		getrgb(byte R, byte G, byte B); - CALCULATING RGB565 format
		
REQUIRED:

		MSStack library: https://github.com/m5stack/M5Stack
		
	
