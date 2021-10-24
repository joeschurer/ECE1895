/* Group Members
* Joseph Schurer
* Mahya Waddell
* Michael Etter
*
*/

void setup() {
  pinMode(9, OUTPUT);   
  pinMode(7, INPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  
}

void loop() {
  if(digitalRead(7) == HIGH){
    digitalWrite(8,HIGH);
    delay(500);
    digitalWrite(8,LOW);
    digitalWrite(9, HIGH); 
    delay(500);            
    digitalWrite(9, LOW);
    digitalWrite(10,HIGH);
    delay(500);
    digitalWrite(10,LOW);           
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);  
    digitalWrite(10, LOW);  
  }
}
