int l = 6;              // Connect Leftmost IR to pin 6
int cl = 5;             // Connect the IR in between Center and Leftmost IR to pin 5
int cr = 3;             // Conncet the IR in between Center and Rightmost IR to pin 3
int c = 7;              // Connest Center IR to pin 7
int r = 8 ;             // Connect Rightmost IR to pin 8
int lastcommand = 2;
const byte dir1 = 12;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 13;   // Connect DIR2 of motor driver to pin 12
const byte dir11 = 4;   // Connect DIR3 of motor driver to pin 4
const byte dir22 = 2;   // Connect DIR4 of motor driver to pin 2
const byte pwm1 = 11;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 10;   // Connect PWM2 of motor driver to pin 10
void setup() {
  pinMode(l,INPUT);
  pinMode(cl,INPUT);
  pinMode(c,INPUT);
  pinMode(cr,INPUT);
  pinMode(r,INPUT);
 
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,HIGH);
  digitalWrite(dir11,LOW);
  digitalWrite(dir22,LOW);
  digitalWrite(pwm1,LOW);
  digitalWrite(pwm2,LOW);
  Serial.begin(115250);
  
}

void loop() {
  int L = digitalRead(l);
  int CR = digitalRead(cr);
  int C= digitalRead(c);
  int CL = digitalRead(cl);
  int R = digitalRead(r);
  int flag = 0;
  if(L && R && C && CL && CR || CR && CL || L && R || L && CR || R && CL) {moveForward();lastcommand = 2;flag =1;}
  if((L || CL )&& flag == 0) {
    moveLeft();lastcommand = 1;
    if(CL == 1 && L == 0) lastcommand = 2;
    }
  else if((R || CR) && flag == 0) {
    moveRight();lastcommand = 3;
    if(R == 0 && L == 1) lastcommand = 2;
  }
  else if(C) {moveForward();lastcommand = 2;}
  else wait();
  
}
void moveLeft() {
  // For robot to move left, right motor has to be faster than left motor
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,LOW);
  digitalWrite(dir11,LOW);
  digitalWrite(dir22,HIGH);
  analogWrite(pwm1,200);
  analogWrite(pwm2,200);
}

void moveRight() {
  // For robot to move right, left motor has to be faster than right motor
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  digitalWrite(dir11,HIGH);
  digitalWrite(dir22,LOW);
  analogWrite(pwm1,200);
  analogWrite(pwm2,200);
}

void moveForward() {
  // For robot to move forward, both motors have to be same speed
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,HIGH);
  digitalWrite(dir11,LOW);
  digitalWrite(dir22,LOW);
  analogWrite(pwm1,250);
  analogWrite(pwm2,250);
}

void wait() {
  Serial.println("wait");
  if(lastcommand == 1) moveLeft();
  if(lastcommand == 2) moveForward();
  if(lastcommand == 3) moveRight();
}
