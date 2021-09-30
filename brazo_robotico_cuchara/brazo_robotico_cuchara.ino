

#include <Servo.h> 
 
Servo myservo1;  // base1 
Servo myservo2;  // base 2
 Servo myservo3;  //codo
 Servo myservo4;  //cuchara
 
 ////////////////VARIABLES INICIALES/////////////////////
 int op;
int pos1 = 90;    // variable base1   ****solo cambiar este valor
int pos2;
 

int p;
int pos3 = 90;    //variable codo   ///hasta 140


int q;
int pos4 = 90;    // variable cuchara


int x=0;

void setup() 
{ 
  Serial.begin(9600);
  myservo1.attach(3);  
  myservo2.attach(5);  
  myservo3.attach(6);  
  myservo4.attach(9);  
  
  base(90,30);
  codo(90,30);
  cuchara(90,30);

} 
 
void loop() 
{ 
  
  if(x==0){
  
  //////////llegar al plato de comida y al usuario///////////
 
   // Sólidos//
cuchara(90,1);
base(110,1);
codo(90,1);
cuchara(20,1);
base(95,1);

cuchara(25,30);
codo(100,5);

cuchara(33,5);
codo(95,50);

cuchara(36,10);
codo(97,10);

cuchara(40,10);
codo(97,10);
base(100,10);

cuchara(43,10);
codo(95,10);
base(98,10);

cuchara(46,50);
codo(105,50);
base(90,50);

cuchara(75,60);
codo(75,60);
base(105,100);


delay(4000);
  
  //     //
  



 
 //x=x+1;
  
 

} 

}

void base(int angulo, int velocidad){
  //base
  if(pos1 <= angulo){ 
  for(pos1; pos1 <= angulo; pos1 += 1) 
  {     
   
    pos2=180-pos1;
    
    myservo1.write(pos1);              
    myservo2.write(pos2);
    Serial.print("Base1 ");
    Serial.print(pos1);
    Serial.print("  ");
    Serial.print("Base2 ");
    Serial.print(pos2);
    Serial.print("     ");
    delay(velocidad);                      
  } 
   } else {
    for(pos1; pos1 >= angulo; pos1 -= 1) 
  {     

    pos2=180-pos1;
    
    myservo1.write(pos1);              
    myservo2.write(pos2);
    Serial.print("Base1 ");
    Serial.print(pos1);
    Serial.print("  ");
    Serial.print("Base2 ");
    Serial.print(pos2);
    Serial.print("     ");
    delay(velocidad);                      
  } 
     
     }
  
  }


void codo (int angulo, int velocidad){
   //codo
     if(pos3 <= angulo){ 
   for(pos3; pos3 <= angulo; pos3 += 1) {     

    myservo3.write(pos3);              
    Serial.print("Base3 ");
    Serial.print(pos3);
    Serial.print("     ");
    delay(velocidad);                       
  }
}else{
    for(pos3; pos3 >= angulo; pos3 -= 1) 
  {             
   
    myservo3.write(pos3);              
    Serial.print("Base3 ");
    Serial.print(pos3);
    Serial.print("     ");
    delay(velocidad);                       
  }
    
    
    }
  }

void cuchara(int angulo, int velocidad){
  if(pos4 <= angulo){ 
  for(pos4; pos4 <= angulo; pos4 += 1) {  

    myservo4.write(pos4);              
    Serial.print("Base4 ");
    Serial.print(pos4);
    Serial.print("     ");
    delay(velocidad);                       
}
}else{
  for(pos4; pos4 >= angulo; pos4 -= 1) {                               
  
    myservo4.write(pos4);              
    Serial.print("Base4 ");
    Serial.print(pos4);
    Serial.print("     ");
    delay(velocidad);                       
}
  
  }
  
  }
  
  int restaurar (int b){
    x=b;
    return x;
    }
  
