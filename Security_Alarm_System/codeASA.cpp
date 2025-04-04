//Smart Security Alarm System Code

float temp; 
float vout; 
float vout1; 
int redled = 13, greenled = 12; 
int gasSensor; 
int piezo = 7;
int ldr;

void setup() 
{ 
  pinMode(A0,INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT);
  pinMode(redled,OUTPUT); 
  pinMode(greenled,OUTPUT); 
  pinMode(piezo,OUTPUT); 
  Serial.begin(9600); 
} 

void loop() 
{ 
  vout=analogRead(A1); 
  vout1=(vout/1023)*5000; 
  temp=(vout1-500)/10; 
  delay(100);  						 // Allow sensor values to settle
  gasSensor=analogRead(A0);
  ldr = analogRead(A2); 
  Serial.print(ldr);
  
  if (temp>=80) 
  { 
    digitalWrite(redled,HIGH); 
  } 
  else 
  { 
    digitalWrite(redled,LOW); 
  } 
  if (gasSensor>=100) 
  { 
    digitalWrite(piezo,HIGH); 
  } 
  else 
  { 
    digitalWrite(piezo,LOW); 
  }
  
  
  if( ldr <= 100)
  {
    Serial.print("Alarm! ");        // an obstacle has been detected
  
    digitalWrite(piezo, HIGH);      // turn on alarm
    digitalWrite(redled, HIGH);     // turn on the led indicators
    digitalWrite(greenled, LOW);
    delay(600);
    digitalWrite(piezo, LOW);  
    digitalWrite(redled, LOW);
    digitalWrite(greenled, HIGH);
    delay(600); 
    
  }  
  
  Serial.print(" ");
  Serial.print("in DegreeC= "); 
  Serial.print(" "); 
  Serial.print(temp); 
  Serial.print("\t"); 
  Serial.print("GasSensor= "); 
  Serial.print(" "); 
  Serial.print(gasSensor); 
  Serial.println(); 
  delay(1000); 
}