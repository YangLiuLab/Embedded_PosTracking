#include "ADC.h"

int fMPin   = 4;      // master closk pin,  FTM1, 3,4
int ADCclk  = 5;      // ADC trigger Clock, FTM0, 5,6,9,10,20,21,22,23
int SHPin   = 21;     // shift gate pin, 
int ICGPin  = 22;     // intergration clear gate pin, 
int ADCPin = 23;   // ADC read data from sensor

unsigned long fM  = 2000000;   // 2 MHz, master clock freqency
unsigned int tINT = 5000;     // 5 ms, intergration time
unsigned long tICG = 6000;    // 6ms  > tINT;      

uint16_t Pixels[4000];
elapsedMicros tus;
//uint16_t ROI[101];
//float Position = 0;
//int id = 0;
//int ROIw = 0;
//int ROIs = 0;

void setup()
{
  pinMode(ADCPin, INPUT);
  pinMode(SHPin,     OUTPUT);
  pinMode(ICGPin,    OUTPUT);
  pinMode(fMPin,     OUTPUT);   
  pinMode(ADCclk,    OUTPUT);
  
  Serial.begin(115200);
  
  digitalWriteFast(SHPin, HIGH);
  digitalWriteFast(ICGPin, LOW);

  analogWriteResolution(4);             // f <= 3.75 MHz
  analogWriteFrequency(fMPin, fM);
  analogWrite(fMPin,8);              // duty cycle: 50% 
  analogWriteFrequency(ADCclk, fM/4);
  analogWrite(ADCclk, 8);             // duty cycle: 50% 

  adc->setReference(ADC_REFERENCE::REF_3V3, ADC_0); 
  adc->setAveraging(1);                 // set number of averages
  adc->setResolution(12);               // set bits of resolution
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED); 
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED); 
  adc->adc0->singleMode();              

  noInterrupts();
}

void TCD1304(){
         
  while (!digitalReadFast(ADCclk)){}         
  digitalWriteFast(ICGPin, HIGH);
  digitalWriteFast(SHPin, LOW);
  tus = 0;
  delayMicroseconds(2);
  digitalWriteFast(SHPin, HIGH);
  nrSHs = 1;
  delayMicroseconds(2);
  digitalWriteFast(ICGPin, LOW);       
  for (i=0; i<3694; i++){ 
    while (!digitalReadFast(ADCclk)){}         
    buffer[i] = analogRead(ADCPin); 
    if (tus >= nrSHs * t_int){             
      digitalWriteFast(SHPin, LOW);
      delayMicroseconds(2);
      digitalWriteFast(SHPin, HIGH);
      nrSHs++;
    }
  }
  while (tus < tICG){}
}

//void ROIsize()
// {
//  int id = 0;
//  int tempmin = 0;
//  int tempmax = 10000;
//  int temp = 0;
//
//  for (int j = 33+51; j < 3679-51; j++)
//  {
//       if (Pixels[j]>tempmax)
//       {
//        tempmax = Pixel[j];
//        id = j;
//       }
//       if (Pixels[j]<tempmin)
//       {
//        tempmin = Pixel[j];
//       }
//  }
//
//  int bg = tempmin + (tempmax-tempmin)/10;
//  float c = 0;
//    for (int n=-50; n<50; n++)
//    {
//      temp = Pixels[id+n] - bg;
//      if (temp<0)
//          temp = 0;
//      ROI[n+50] = temp;      
//    }
//
//    float A = 0;
//    float B = 0;
//    for (int n=-50; n<50; n++)
//    {
//      A += ROI[n+50]*n;
//      B += ROI[n+50];      
//    }
//    c = A/B;
//    for (int n=-50; n<50; n++)
//    {
//      D += ROI[n+50]*(n-c);
//    }
//    ROIw = 4*sqrt(D)/B -0.5;
//    ROIs = 2*ROIw + 1;
// }
//
//void ePhasor()
// {
//    for (int n=-ROIw; n<ROIw; n++)
//    {
//     real += Pixels[id+n]*cos(2*pi*(n+ROIw)/ROIs);
//     imag += -Pixels[id+n]*sin(2*pi*(nROIw)/ROIs);
//    }
//    Position = -(atan(imag/real)/(2*pi/ROIw)-0.5) + id;
// }

void loop(){
    TCD1304();
//    ROIsize();
//    ePhasor();
//    Serial.println(Position,3);
}
