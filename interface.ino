





#include "Arduino.h"
const int Pins[12] = {2, 3, 4, 5, 6, 7,19,18,17,16,15,14};
int T=0;
int A=0;

int bit0=39;
int bit1=38;
int bit2=41;
int bit3=40;
int bit4=43;
int bit5=42;
int bit6=45;
int bit7=44;
int bit8=47;
int bit9=46;
int ad0=49;
int ad1=48;
int ad2=51;
int ad3=50;
int ad4=53;
int ad5=52;
int hsk=36;

void setup()
{
 Serial.begin(115200);  // serial

  for (int i = 0; i < 12; i++) {
    pinMode(Pins[i], OUTPUT);
    pinMode(20, OUTPUT); // for speed test
   }
  
  pinMode(bit0, OUTPUT);
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit3, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(bit5, OUTPUT);
  pinMode(bit6, OUTPUT);
  pinMode(bit7, OUTPUT);
  pinMode(bit8, OUTPUT);
  pinMode(bit9, OUTPUT);
  
  pinMode(ad0, OUTPUT);
  pinMode(ad1, OUTPUT);
  pinMode(ad2, OUTPUT);
  pinMode(ad3, OUTPUT);
  pinMode(ad4, OUTPUT);
  pinMode(ad5, OUTPUT);
  pinMode(hsk, OUTPUT);
    
   ADC->ADC_ACR = ADC_ACR_IBCTL(0b01);                   // For frequencies > 500 KHz
}
int Delay_zynq=1000,Delay_adc=50, n_af=18;
boolean toggle = false;
char ch[80],layer1=1,layer2=2;
int c=0, r=0,c2=0,r2=0;
long se[25],se2[25],current[18]; // 18 -> n_af 
float aa;
int d=0;
// receptive fields 
float RF1[25]={0.0, 0.6449175627932842, 0.0, 0.0, 0.0, 0.0, 0.0, 0.607816000313572, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF2[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.38998639031258386, 0.0, 0.0, 0.0, 0.0, 0.6588237182906538, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF3[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5103051593263112, 0.0, 0.48773580128138216, 0.0, 0.0, 0.0, 0.2760306463488543, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF4[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.37798809916562137, 0.539089074894263, 0.0, 0.0, 0.0, 0.0, 0.0, 0.35787552358621255, 0.0, 0.0};
float RF5[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.7148927419541395, 0.0, 0.0, 0.0, 0.0, 0.7278201145767188, 0.5699064695231312, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF6[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.19120967502621844, 0.3824806084738621, 0.0, 0.0, 0.0, 0.0, 0.13124957979644358};
float RF7[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.29045929909409723, 0.7081964338469211, 0.0, 0.0, 0.0};
float RF8[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.649821374693913, 0.11323980464403766, 0.0, 0.0};
float RF9[25]={0.0, 0.0, 0.0, 0.6096140062478451, 0.47948205181450976, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3950430440436383, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF10[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2690879256243027, 0.7042658625972062, 0.7633670241297751, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF11[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.36110029024398194, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10757814815340047, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF12[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4437618733979303, 0.0, 0.0, 0.0, 0.0, 0.6387098305824005, 0.0};
float RF13[25]={0.0, 0.0, 0.1088267682823436, 0.0, 0.0, 0.0, 0.0, 0.460125672382396, 0.25471708713560387, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF14[25]={0.0, 0.0, 0.0, 0.46960964609736777, 0.0, 0.0, 0.0, 0.12965317068341414, 0.6470642821172216, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF15[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.1599161434102262, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6056568745743216, 0.0, 0.0, 0.0, 0.3325259738774794, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF16[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3989484249555587, 0.6264312383591741, 0.0, 0.0};
float RF17[25]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6545054906446706, 0.0, 0.0, 0.0, 0.16056125697673712, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4039205060753346, 0.0, 0.0, 0.0, 0.0, 0.0};
float RF18[25]={0.22776578859978439, 0.0, 0.0, 0.0, 0.0, 0.5893236652501372, 0.09414365506673816, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


void loop()
{
 for (int r=0; r<5;r++){    
      digitalWrite(5,bitRead(r, 2));
      digitalWrite(6,bitRead(r, 1));
      digitalWrite(7,bitRead(r, 0));
 for (int c=0; c<5;c++){      
      digitalWrite(2,bitRead(c, 2));
      digitalWrite(3,bitRead(c, 1));
      digitalWrite(4,bitRead(c, 0));
      delayMicroseconds(Delay_adc);
      int a = analogRead(0);
      se[r*5+c]=1023-a;
      delayMicroseconds(Delay_adc);
      }
    }

for (int i=0;i<n_af;i++){
  aa=0;
  for(int j=0;j<25;j++){
    switch (i) {
  case 0:
    aa+=RF1[j]*se[j];
    break;
  case 1:
    aa+=RF2[j]*se[j];
    break;
  case 2:
    aa+=RF3[j]*se[j];
    break;
  case 3:
    aa+=RF4[j]*se[j];
    break;
  case 4:
    aa+=RF5[j]*se[j];
    break;
  case 5:
    aa+=RF6[j]*se[j];
    break;
  case 6:
    aa+=RF7[j]*se[j];
    break;
  case 7:
    aa+=RF8[j]*se[j];
    break;
  case 8:
    aa+=RF9[j]*se[j];
    break;  
  case 9:
    aa+=RF10[j]*se[j];
    break;
  case 10:
    aa+=RF11[j]*se[j];
    break;
  case 11:
    aa+=RF12[j]*se[j];
    break;
  case 12:
    aa+=RF13[j]*se[j];
    break;
  case 13:
    aa+=RF14[j]*se[j];
    break;
  case 14:
    aa+=RF15[j]*se[j];
    break;
  case 15:
    aa+=RF16[j]*se[j];
    break;
  case 16:
    aa+=RF17[j]*se[j];
    break;
  case 17:
    aa+=RF18[j]*se[j];
    break;
  default:  
    break;
}
    }
    current[i]=aa;
    
  }

  // Normalization
byte maxIndex = 0;
float maxValue = 3000;

for (int i=0 ; i<n_af;i++){
  aa=float(current[i])*(float(1023)/(maxValue+1));
  current[i]=aa;
}
for (int i=6 ; i<n_af;i++){
  aa=int(current[i]/20)*20;
  current[i]=aa;
}
for(int i=0 ; i<n_af;i++){
      delayMicroseconds(Delay_zynq);  
      digitalWrite(hsk,0);
      calc(current[i]);
      digitalWrite(ad5, HIGH);
      add(i);
      delayMicroseconds(Delay_zynq);
      digitalWrite(hsk,1);
      
  }
// send 25 raw taxels' data to PC to visualize pressure pattern
sprintf(ch,"%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d",se[0],se[1],se[2],se[3],se[4],se[5],se[6],se[7],se[8],se[9],se[10],se[11],se[12],se[13],se[14],se[15],se[16],se[17],se[18],se[19],se[20],se[21],se[22],se[23],se[24]);  

   Serial.println(ch);

 for(int i=0 ; i<25;i++){
      delayMicroseconds(Delay_zynq);  
      digitalWrite(hsk,0);
      calc(se[i]);
      digitalWrite(ad5, LOW);
      add(i);
       delayMicroseconds(Delay_zynq);
      digitalWrite(hsk,1);  
  } 
}


int calc(int x)
{
  int b; 
  b=x%2;
  digitalWrite(bit0, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit1, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit2, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit3, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit4, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit5, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit6, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit7, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit8, b);
  x=x/2;
  b=x%2;
  digitalWrite(bit9, b);
}

int add(int x)
{
  int a;
  a=x%2;
  digitalWrite(ad0, a);
  x=x/2;
  a=x%2;
  digitalWrite(ad1, a);
  x=x/2;
  a=x%2;
  digitalWrite(ad2, a);
  x=x/2;
  a=x%2;
  digitalWrite(ad3, a);
  x=x/2;
  a=x%2;
  digitalWrite(ad4, a);

}
