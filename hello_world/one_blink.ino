/* Group Members
* Joseph Schurer
* Mahya Waddell
* Michael Etter
*
* BIG MIKE WAS HERE
*/

void setup() {
  pinMode(9, OUTPUT);  
  pinMode(7, INPUT);
}

void loop() {
  if(digitalRead(7) == HIGH){
    digitalWrite(9, HIGH); 
    delay(1000);           
    digitalWrite(9, LOW);  
    delay(1000);            
  } else {
    digitalWrite(9, LOW); 
  }
}
