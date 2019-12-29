void setup()
{
  Serial.begin(9600);
  
  double floatVal=1.2;
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(floatVal, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //display character array
  Serial.print("charVal: ");
  for(int i=0;i<sizeof(charVal);i++)
  {
    Serial.print(charVal[i]);
  }
  Serial.println();
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  Serial.print("stringVal: ");Serial.println(stringVal); //display string
}
void loop()
{
  
}
