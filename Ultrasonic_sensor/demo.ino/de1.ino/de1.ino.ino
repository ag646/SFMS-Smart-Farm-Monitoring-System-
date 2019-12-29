int resval = 0; // holds the value
int respin = A5; // sensor pin used
int ans;
void setup() {
// start the serial console
Serial.begin(9600);
}
void loop() 
{
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
  if (resval<=100)
  { 
    Serial.println("Water Level: Empty");
    ans=0;
  } 
  else if (resval>100 && resval<=300)
  { 
    Serial.println("Water Level: Low");
    ans=1; 
  } 
  else if (resval>300 && resval<=330)
  { 
    Serial.println("Water Level: Medium");
    ans=2;
  } 
  else if (resval>330)
  {
    Serial.println("Water Level: High");
    ans=4;
  }
delay(1000);
}
