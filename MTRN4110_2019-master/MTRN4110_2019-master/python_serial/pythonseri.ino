// Date : 08/07/2019
// Author: Annie Wang
// github: https://github.com/annie7777

String str;
void setup() {
    Serial.begin(9600);
    Serial.write("Power On and ");
}

void loop()
{
    while(!Serial.available());

    while (Serial.available() > 0) {
    Serial.println("Arduino: ");
    Serial.write(Serial.read());
    str = Serial.readString()+ "Arduino";
    Serial.print(str);
    Serial.flush();
    }
   
}
