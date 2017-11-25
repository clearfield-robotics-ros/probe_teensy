
static int motorDirection = 1;
float zeroPosition = 0;

static int countsPerRotation = 12;
static int gearRatio = 27; //reduction
static int leadScrewPitch = 8; //mm

static int maxPWM = 230;
static int minPWM = 0;
int retpwm = 0;

int setPWM(float pwm) {  

  pwm = abs(pwm);
  pwm = pwm/100*maxPWM; // convert % to PWM
  
  if (pwm < minPWM)
    return minPWM;
  else if (pwm > maxPWM)
    return maxPWM;
  else return pwm;
}

void setupMotor() {
  pinMode(motorPWM, OUTPUT);
  pinMode(motorDIR, OUTPUT);
}

void runMotor(float speed) { // Percentage

  // Set direction
  if (speed*motorDirection < 0)
    digitalWrite(motorDIR, LOW);
  else
    digitalWrite(motorDIR, HIGH);
  
  // Set direciton
  retpwm = setPWM(speed);
  analogWrite(motorPWM, setPWM(speed));
}

void setMotorZero() {
  zeroPosition = getRawMotorPosition();
}

float getRawMotorPosition() {
  return (enc.read()*motorDirection*leadScrewPitch)/(countsPerRotation*gearRatio);
}

float getMotorPosition() {
  return getRawMotorPosition() - zeroPosition;
}

float getMotorSpeed() {
  return retpwm;  
}



