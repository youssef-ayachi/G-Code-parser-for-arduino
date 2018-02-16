#include <Stepper.h>            //Librairie pour piloter les moteurs pas à pas
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
const int pasParRotation = 200;  //Nombre de pas pour réaliser un tour
Stepper StepperX(pasParRotation, 2,5);
Stepper StepperY(pasParRotation, 3,6); 
Stepper StepperZ(pasParRotation, 4,7);  
int vit=5000;
char c;
float stepx = 500, stepy=500, stepz=500;
float nx, ny, nz, nj, ni, ng, nm;
int ne, nf;
float ax, ay, az, ae;
float sx, sy, sz;
int sg, sf, se;
int xb, yb, zb, eb, gb, fb;
int li;
int lc, ext;
float StepInc = 1;
//char var[10];
int p = 0;
int tour = 3;
int interx;
boolean affiche;


void setup(){
  Serial.begin(9600);
  Serial.println("printer"); 
  lcd.init(); 
  screen(1,0, "Imprimante 3D", true);
  screen(1,1, "Multifonctions", false);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);
  pinMode(A7, INPUT);
  StepperZ.setSpeed(5000);      //Vitesse de déplacement
  //StepperZ.step(10000.5555*stepz); 
  StepperX.setSpeed(vit);
  StepperY.setSpeed(vit);
  StepperZ.setSpeed(vit);         
  delay(100);
}

void screen(int col, int line, String st, boolean cl){
  if(cl==true){lcd.clear();}
  lcd.backlight();
  lcd.setCursor(col, line);
  lcd.print(st);
}

void loop(){
 delay(200);
 affiche=true;
 while(1){
  while ( Serial.available()>0 ){
// getcodech();
 StepperY.step(sy*stepy);              
 StepperZ.step(sz*stepz);
 if (sg==2 || sg==3){
    cercle(sx, sy);
 }else if(sg==0 || sg==1){
 /*for(int i=0; i<tour; i++){
     interx = analogRead(A7);
    if(interx> 600){
      if(sx>0){
        sx=sx;
      }else if(sx<0){
        sx=(sx*-1);
      }
     StepperX.step(sx*stepx);
    }else{
     StepperX.step(sx*stepx);
    } 
   // StepperX.step(sx*stepx);
  }   
  for(int i=0; i<tour; i++){      
   StepperY.step(sy*stepy); 
  }
 for(int i=0; i<tour; i++){              
   StepperZ.step(sz*stepz);
 }*/
 }
 } 
 
 if(ext!=se){
 screen(0,1, "Extrudeur", true);
 screen(0,2,(String)se, false);
 digitalWrite(12, se);
 delay(1000);
 digitalWrite(12, 0);
 ext=se;  
 }
 sx=0;
 sy=0;
 sz=0;
}
 //Serial.flush();     
}

/*void getcodech(){
  boolean com;
  char ch;
  int av;
  int h;
  h=0;
  p=0;
  ax = nx; 
  ay = ny; 
  az = nz;
  lc=1;
  av = Serial.available();
  while(Serial.available()>0){
    ch=Serial.read();
    Serial.print("commande envoye : ");
    Serial.println(ch);
   if(ch=='(' || ch==';'){
    com=true;
    //Serial.flush();
    return NULL; 
   }
   if(ch==' ' || ch=='\r' ||ch=='\n' || Serial.available() == 0 ){
     h=0;
    char* G = strchr(var, 'G');
    char* X = strchr(var, 'X');
    char* Y = strchr(var, 'Y');
    char* Z = strchr(var, 'Z' );
    char* E = strchr(var, 'E' );
    char* F = strchr(var, 'F' );
    char* I = strchr(var, 'I' );
    char* J = strchr(var, 'J' );
    char* M = strchr(var, 'M' );
    if(G!=NULL){
      ng=atof(var+1);
    }else if(X!=NULL){
      nx=atof(var+1);
    }else if(Y!=NULL){
      ny=atof(var+1);
    } else if(Z!=NULL){
      nz=atof(var+1);
    }else if(E!=NULL){
      ne=atoi(var);
    }else if(F!=NULL){
      nf=atoi(var);
    }else if(I!=NULL){
      ni=atof(var+1);
    }else if(J!=NULL){
      nj=atof(var+1);
    }else if(M!=NULL){
      nm=atof(var+1);
      }
    memset(var,0,sizeof(var));
    }else if (ch!=' '){
      var[h++]=ch;
    }
  }
   sx = ax-nx;
   sy = ay-ny;
   sz = nz;
   se = ne;
   sg = (int)ng;
   sf = nf;
 if(nf>vit){
   vit = nf;
  }
if (affiche==true && av>0){
Serial.print("moteur x N : ");
Serial.println(nx);
Serial.print("moteur y N : ");
Serial.println(ny);
Serial.print("moteur Z N : ");
Serial.println(nz);
Serial.print("valeur I : ");
Serial.println(ni);
Serial.print("valeur J : ");
Serial.println(nj);
Serial.print("valeur G : ");
Serial.println(sg);
Serial.print("moteur X Step : ");
Serial.println(sx);
Serial.print("moteur Y Step : ");
Serial.println(sy);
Serial.print("moteur Z Step : ");
Serial.println(sz);
Serial.print("Nombre d'axes : ");
Serial.println((int)ng);
Serial.print("vitesse de deplacement : ");
Serial.println(vit);
Serial.print("Serial : ");
Serial.println(av);
}

 if (lc>0){
   screen(0,0, "MotorX : " ,true);
   screen(10,0, (String)sx,false);
   screen(0,1, "MotorY : " ,false);
   screen(10,1, (String)sy,false);
   screen(0,2, "MotorZ : " ,false);
   screen(10,2, (String)sz,false); 
   screen(0,3, "N Axes : " ,false);
   screen(10,3, (String)sg,false); 
   lc=0;
  }
 //Serial.flush();    
}*/

void cercle(float x1, float y1){ 
  x1 = (int)(x1*60);
  y1 = (int)(y1*60);
  float x0 = ax;
  float y0 = ay;
  long dx = abs(x1-x0);
  long dy = abs(y1-y0);
  int sxc = x0<x1 ? StepInc : -StepInc;
  int syc = y0<y1 ? StepInc : -StepInc;
  long i;
  long over = 0;
  if (dx > dy) {
    for (i=0; i<dx; ++i) {
      StepperX.step(sxc);
      over+=dy;
      if (over>=dx) {
        over-=dx;
        StepperY.step(syc);
      }
    }
  }
  else {
    for (i=0; i<dy; ++i) {
      StepperY.step(syc);
      over+=dx;
      if (over>=dy) {
        over-=dy;
        StepperX.step(sxc);
      }
    }    
  }
  ax = x1;
  ay = y1;
}

