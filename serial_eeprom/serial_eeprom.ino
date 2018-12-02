#include <EEPROM.h>

String mystring, command;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    command = Serial.readString();
  }
  if(!command.equals("")){                                      //Send Command with format "#XXXX" to save the string to eeprom
    Serial.print("command: ");
    Serial.println(command);
    if(command[0] == '#'){
      mystring = command.substring(1);
      Serial.println("====== STRING SAVED ======");
      Serial.println(mystring);
      writeStringEEPROM(mystring);
    }
    if(command[0] == '*'){                                      //Send Command with format "*" to read the string in the eeprom
      mystring = readStringEEPROM();  
      Serial.print("MyString : ");
      Serial.println(mystring);
    }
    command = "";
  }
}

// --------------------------
// readStringEEPROM() is used to read the data String inside the eeprom
// --------------------------
String readStringEEPROM(){                              
  String str;
  for(int i = 0 ; i < EEPROM.length() ; i++){
    byte x = EEPROM.read(i);
    char c = char(x);
    str += c;
  }
  
  return str;
}

// --------------------------
// writeStringEEPROM() is used to write String data inside the eeprom
// --------------------------
void writeStringEEPROM(String str){
  for(int i = 0 ; i < str.length()+1 ; i++){
    EEPROM.write(i, str[i]);
  }
}

// --------------------------
// clearStringEEPROM() is used to clear the data inside the eeprom
// --------------------------
void clearStringEEPROM(){
  for(int i = 0 ; i < EEPROM.length() ; i++){
    EEPROM.write(i, 0);
  }
}
