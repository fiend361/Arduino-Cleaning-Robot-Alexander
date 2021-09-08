// the right motor
const int motor_en_r = 3;
const int motor_in1 = 4;
const int motor_in2 = 2;

// the left motor
const int motor_en_l = 5;
const int motor_in3 = 8;
const int motor_in4 = 7;

// ultrasonic sensor
const int trigPin = 11;
const int echoPin = 10;

// nodemcu mode toggle pin
const int node_pin = 9;

// mopping pin for toggling the transistor
const int mop_pin = 6;

const int robot_speed = 100;

int state = 0;

bool mop = false;
bool auto_mode = false;

void set_movement_speed(int spd)
{
  analogWrite(motor_en_r, spd);
  analogWrite(motor_en_l, spd);
}

void move_forward()
{
  // right motor forward
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);

  // left motor forward
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, LOW);
}

void move_backward()
{
  // right motor backward
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);

  // left motor backward
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, HIGH);
}

void turn_right()
{
  // right motor backward
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);

  // left motor forward
  digitalWrite(motor_in3, HIGH);
  digitalWrite(motor_in4, LOW);
}

void turn_left()
{
  // right motor forward
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);

  // left motor backward
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, HIGH);
}

void stop_movement()
{
  // right motor stop
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);

  // left motor stop
  digitalWrite(motor_in3, LOW);
  digitalWrite(motor_in4, LOW);
}

void start_mopping()
{
  digitalWrite(mop_pin, HIGH);
}

void stop_mopping()
{
  digitalWrite(mop_pin, LOW);
}

double get_front_distance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  double duration = pulseIn(echoPin, HIGH);
  double distance = duration * 0.034 / 2;

  Serial.println(distance);

  return distance;
}

void setup()
{
  // motors
  pinMode(motor_en_r, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);

  pinMode(motor_en_l, OUTPUT);
  pinMode(motor_in3, OUTPUT);
  pinMode(motor_in4, OUTPUT);

  // serial
  Serial.begin(9600);

  // ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // nodemcu mode toggle pin
  pinMode(node_pin, INPUT);

  // mopping pin
  pinMode(mop_pin, OUTPUT);

  set_movement_speed(255);
}

void loop()
{
//  Serial.println(get_front_distance());
  if (digitalRead(node_pin) == HIGH)
  {
    auto_mode = true;
        Serial.println("auto");
  }
  else if (digitalRead(node_pin) == LOW)
  {
    auto_mode = false;
        Serial.println("manual");
  }

  if (auto_mode)
  {
    // code for the automatic mode
    if (get_front_distance() < 6.0)
    {
      // there is an obstacle
      stop_movement();
      turn_left();
    }
    else
    {
      move_forward();
    }

//    mop = true;
//    start_mopping();
  }
  else
  {
    // code for the manual mode
    if (Serial.available() > 0)
    {
      state = Serial.read();
    }

    if (state == 'w')
    {
      Serial.println("w");
      move_forward();
    }
    else if (state == 's')
    {
      Serial.println("s");
      move_backward();
    }
    else if (state == 'l')
    {
      Serial.println("l");
      turn_left();
    }
    else if (state == 'r')
    {
      Serial.println("r");
      turn_right();
    }
    else if (state == 'm')
    {
      state = 'p';
      Serial.println("m");
      if (mop)
      {
        mop = false;
        stop_mopping();
      }
      else
      {
        mop = true;
        start_mopping();
      }
    }
    else
    {
      Serial.println("p");
      stop_movement();
    }
  }
}
