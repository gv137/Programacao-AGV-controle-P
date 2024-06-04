class DCMotor {  
  int spd = 255, pin1, pin2;
  
  public:  
  
    void Pinout(int in1, int in2){ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      }   
    void Speed(int in1){ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
      spd = in1;
      }     
    void Forward(){ // Forward é o método para fazer o motor girar para frente
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
      }   
    void Backward(){ // Backward é o método para fazer o motor girar para trás
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
      }
    void Stop(){ // Stop é o metodo para fazer o motor ficar parado.
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      }
   };


// ------- Motores
   DCMotor MotorA, MotorB;
   int velocidade = 90;  
   
// ------- SENSORES
int sensor [5] = {0,0,0,0,0};
int sensor_1 = 22;
int sensor_2 = 24;
int sensor_3 = 26;
int sensor_4 = 28; 

// ------- LED
int Led_1 = 33;
int Led_2 = 35;
int Led_3 = 37;
int Led_4 = 39;

// ------- Controle PID
int erro = 0;
int Kp = 41;
int corrigir = 0;

// ------- Bluetooth
int i = 0;
int j = 0;
int state_rec;
char state;
#define AutoManual 50

void controle_P(){
  
  corrigir = Kp * erro;

  //Serial.println(erro);

  MotorA.Speed(velocidade + corrigir);
  MotorB.Speed(velocidade - corrigir);

  MotorA.Forward();
  MotorB.Forward();  
  
}

void ler_sensor(){
  sensor[1] = digitalRead (sensor_1);
  sensor[2] = digitalRead (sensor_2);
  sensor[3] = digitalRead (sensor_3);
  sensor[4] = digitalRead (sensor_4);
  
  // ---- 
  //  Leitura dos sensores a partir do Serial Monitor
  //  Serial.print(sensor[1]); Serial.print(" ");
  //  Serial.print(sensor[2]); Serial.print(" ");
  //  Serial.print(sensor[3]); Serial.print(" ");
  //  Serial.println(sensor[4]); Serial.println(" ");
  //  delay(1000);
 
  // 
  // ---- 
}

void virar180() {

 
}

void setup() {
  MotorA.Pinout(5,6); // Seleção dos pinos que cada motor usará, como descrito na classe.
  MotorB.Pinout(10,9); 
  
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);

  pinMode (sensor_1, INPUT);
  pinMode (sensor_2, INPUT);
  pinMode (sensor_3, INPUT);
  pinMode (sensor_4, INPUT);
  pinMode (Led_1, OUTPUT);
  pinMode (Led_2, OUTPUT);
  pinMode (Led_3, OUTPUT);
  pinMode (Led_4, OUTPUT);
  pinMode(AutoManual,INPUT);

}

void loop() {


  ler_sensor();

  //0 1 1 0 erro = 0     --- frente
  //1 1 0 0 erro = -1    --- meia esquerda
  //1 0 0 0 erro = -2    --- esquerda completa
  //0 0 1 1 erro = 1     --- meia direita 
  //0 0 0 1 erro = 2     --- direita completa


        if ((sensor[1] == HIGH) && (sensor[2] == LOW ) && (sensor[3]== LOW )  && (sensor[4]== LOW ))     (erro = -2);
   else if ((sensor[1] == LOW ) && (sensor[2] == HIGH) && (sensor[3]== LOW )  && (sensor[4]== LOW ))     (erro = -1);
   else if ((sensor[1] == LOW ) && (sensor[2] == HIGH) && (sensor[3]== HIGH)  && (sensor[4]== LOW ))     (erro = +0);
   else if ((sensor[1] == LOW ) && (sensor[2] == LOW ) && (sensor[3]== HIGH)  && (sensor[4]== LOW ))     (erro = +1);
   else if ((sensor[1] == LOW ) && (sensor[2] == LOW ) && (sensor[3]== LOW )  && (sensor[4]== HIGH))     (erro = +2);
   else if (sensor[1] == HIGH && sensor[2] == HIGH && sensor[3]== HIGH  && sensor[4]== HIGH){


  MotorA.Stop();
  MotorB.Stop();
  delay(2500);   

 
  
    //MotorA.Speed(90);
    MotorB.Speed(90);
    
    //delay(1500);

    MotorA.Stop();
    MotorB.Backward();

    delay(1950);

  //MotorA.Stop();
  // MotorB.Stop(); 
   }
   



  controle_P();
  controle_LED();
  bluetooth();
}


 void controle_LED(){
       if(sensor[1] == LOW && sensor[2] == HIGH && sensor[3] == HIGH && sensor[4] == LOW) 
       {
       digitalWrite(Led_1, LOW);
       digitalWrite(Led_2, HIGH);
       digitalWrite(Led_3, HIGH);
       digitalWrite(Led_4, LOW);
 }

       else if(sensor[1] == LOW && sensor[2] == LOW && sensor[3] == HIGH && sensor[4] == LOW) 
 {
       digitalWrite(Led_1, LOW);
       digitalWrite(Led_2, LOW);
       digitalWrite(Led_3, HIGH);
       digitalWrite(Led_4, LOW);
 }
       else if(sensor[1] == LOW && sensor[2] == HIGH && sensor[3] == LOW && sensor[4] == LOW)
 {
       digitalWrite(Led_1, LOW);
       digitalWrite(Led_2, HIGH);
       digitalWrite(Led_3, LOW);
       digitalWrite(Led_4, LOW);
 }
      else if(sensor[1] == LOW && sensor[2] == LOW && sensor[3] == LOW && sensor[4] == HIGH)
 {
       digitalWrite(Led_1, LOW);
       digitalWrite(Led_2, LOW);
       digitalWrite(Led_3, LOW);
       digitalWrite(Led_4, HIGH);
 }
     else if(sensor[1] == HIGH && sensor[2] == LOW && sensor[3] == LOW && sensor[4] == LOW)
 {
       digitalWrite(Led_1, HIGH);
       digitalWrite(Led_2, LOW);
       digitalWrite(Led_3, LOW);
       digitalWrite(Led_4, LOW);
 }
     else if(sensor[1] == HIGH && sensor[2] == HIGH && sensor[3] == HIGH && sensor[4] == HIGH)
   
 {
       digitalWrite(Led_1, HIGH);
       digitalWrite(Led_2, HIGH);
       digitalWrite(Led_3, HIGH);
       digitalWrite(Led_4, HIGH);
 }
 }


 void bluetooth()
{

 while (digitalRead(50)) {
    if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }
 
  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    velocidade = 0;
  }
  else if (state == '4') {
    velocidade = 50;
  }
  else if (state == '6') {
    velocidade = 80;
  }
  else if (state == '7') {
    velocidade = 100;
  }
  else if (state == '8') {
    velocidade = 130;
  }
  else if (state == '9') {
    velocidade = 150;
  }
  else if (state == 'q') {
    velocidade = 200;
  }
 
 
  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade);

  MotorA.Forward();
  MotorB.Forward();
  }
 
    else if (state == 'I') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade - 20);

  MotorA.Forward();
  MotorB.Forward();
  }
 
    else if (state == 'G') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade + 20);

  MotorA.Forward();
  MotorB.Forward();
  }
 
  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade);

  MotorA.Backward();
  MotorB.Backward();
  }
 
   else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade - 20);

  MotorA.Backward();
  MotorB.Backward();
  }
  
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
  MotorA.Speed(velocidade);
  MotorB.Speed(velocidade + 20);

  MotorA.Backward();
  MotorB.Backward();
  }
 
  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    MotorA.Backward();
    MotorB.Forward();
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    MotorA.Forward();
    MotorB.Backward();
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    MotorA.Stop();
    MotorB.Stop();
  }
  }
}
