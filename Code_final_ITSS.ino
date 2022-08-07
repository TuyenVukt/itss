#include <Servo.h>
#define trig 11 //chân trig của HC-SR04
#define echo 10//chân echo của HC-SR04
#define ser 9

Servo srf05;  // create servo object to control a servo
//Khai báo chân tín hiệu motor A
int enA = 3;
int in1 = 2;
int in2 = 4; 
 
//Khai báo chân tín hiệu cho motor B
int in3 = 7; 
int in4 = 6; 
int enB = 5;  

int allow_distance = 10;//cm
int allow_side = 20;

void setup()
{
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT); 
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(trig,OUTPUT);//chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);//chân echo sẽ nhận tín hiệu
    srf05.attach(ser);  // dây vàng
}
 
void tien()
{
    
        digitalWrite(in1, HIGH);//PHẢI
        digitalWrite(in2, LOW);
        analogWrite(enB, 120); 
        
        digitalWrite(in3, HIGH);//TRÁI
        digitalWrite(in4, LOW);
        analogWrite(enA, 100); 
        delay(200);

 
} 

void lui()
{
    
        digitalWrite(in1, LOW);//Trái
        digitalWrite(in2, HIGH);
        
        digitalWrite(in3, LOW);//Phải
        digitalWrite(in4, HIGH);
        
        analogWrite(enB, 120); 
        analogWrite(enA, 100); 
        delay(200);

 
} 
void dung()
{
    

        digitalWrite(in1, LOW);//PHẢI
        digitalWrite(in2, LOW);
                 
        digitalWrite(in4, LOW);//TRÁI
        digitalWrite(in3, LOW);
        delay(500);
} 
void re_phai()
{
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
         
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        
        
        analogWrite(enB, 190); 
        analogWrite(enA, 100); 
        delay(300);
} 

void re_trai()
{
    
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW); 
                
        analogWrite(enB, 100); 
        analogWrite(enA, 170); 
        delay(300);
} 

int objectDistance_cm (byte angle)
{
  srf05.write(angle);
  delay(400);
  unsigned long duration;//biến đo thời gian
  int distance;//biến lưu khoảng cách

  /* phát xung từ chân trig */
  digitalWrite(trig,0);//tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);// phát xung từ chân trig
  delayMicroseconds(5);// xung có độ dài 5 microSeconds
  digitalWrite(trig,0);//tắt chân trig
  
  /* tính toán thời gian */
  duration = pulseIn(echo,HIGH);//đo độ rộng xung HIGH ở chân echo. ( http://arduino.vn/reference/pulsein )
  distance = int(duration/2/29.412);//tính khoảng cách đến vật.

  return distance;
}


 
void loop() 
{
  int front_distance=objectDistance_cm (90);
  int left_distance;
  int right_distance;

  if (front_distance > allow_distance)
    {
      tien();
      dung();
    }

     if (front_distance <= allow_distance)
    {    
      lui();
      dung();
      left_distance = objectDistance_cm (180); //đo khoảng cách bên trái
      right_distance = objectDistance_cm (0); //đo khoảng cách bên phải
      while(left_distance <= allow_side && right_distance <= allow_side ){
        lui();
        dung();
        left_distance = objectDistance_cm (180); //đo khoảng cách bên trái
        right_distance = objectDistance_cm (0); //đo khoảng cách bên phải
      }
        if  (left_distance > right_distance)
      {
        re_trai();
        dung();
      }
      else if  (left_distance < right_distance)
        {
          re_phai();
          dung();
        }
       else {
        re_phai();
        dung();
       }
      
        }
     
}
