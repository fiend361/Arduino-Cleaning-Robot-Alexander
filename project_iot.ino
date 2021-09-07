// the right motor
const int motor_en_r = 3;
const int motor_in1 = 4;
const int motor_in2 = 2;
// the left motor
const int motor_en_l = 5;
const int motor_in3 = 8;
const int motor_in4 = 7;

int state = 0;

bool mop = false;

void set_movement_speed(int spd) { 
  digitalWrite(motor_en_r, spd);
  digitalWrite(motor_en_l, spd);
}

void move_forward() {
  // right motor forward 
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);

  // left motor forward 
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, LOW);
}

void move_backward() {
  // right motor backward 
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);

  // left motor backward 
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, HIGH);
}

void turn_right() {
  // right motor backward 
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);

  // left motor forward 
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, LOW);
}

void move_left() {
  // right motor forward 
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);

  // left motor backward 
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, HIGH);
}

void stop_movement() {
  // right motor stop 
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);

  // left motor stop 
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, LOW);
}

void start_mopping() {
  
}

void stop_mopping() {
  
}

void setup() {
  // motors
  pinMode(motor_en_r, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);
  
  pinMode(motor_en_l, OUTPUT);
  pinMode(motor_in3, OUTPUT);
  pinMode(motor_in4, OUTPUT);

  // serial
  Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  if (state == 'w') {
    Serial.println("w");
    move_forward();
    
  } else if (state == 's') {
    Serial.println("s");
    move_backward();
    
  } else if (state == 'l') {
    Serial.println("l");
    move_left();
    
  } else if (state == 'r') {
    Serial.println("r");
    turn_right();
    
  } else if (state == 'm') {
    Serial.println("m");
    if (mop) {
      mop = false;
      stop_mopping();
      
    } else {
      mop = true;
      start_mopping();
      
    }
    
  } else if (state == 'p') {
    Serial.println("p");
    stop_movement();
    
  }

  state = 0;

//  set_movement_speed(128);
}
