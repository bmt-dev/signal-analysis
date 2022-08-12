const int pinA = 2;
// B signal on ICP1 (PIN 8)
volatile bool start;

void setup() {
  cli();
  Serial.begin(9600);
  pinMode(pinA, INPUT);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B = (1 << ICNC1) | (0 << ICES1) | (1 << CS12) | (1 << CS10); // 1024 prescaler and falling input capture
  TIMSK1 = (1 << ICIE1);
  TCNT1 = 0;
  attachInterrupt(digitalPinToInterrupt(pinA), ISR_pinA, RISING);
  sei();
}

void loop() {
}

void ISR_pinA( void )
{
  TCNT1 = 0;
  start = true;
}

ISR (TIMER1_CAPT_vect) {
  if (start && ICR1 > 313) { // && ICR1 > 313 (20ms)  625 (40ms)   (message test)
    double time_ = ICR1;
    //Serial.print(time_ * 1 / 16);
    //Serial.print((time_ * 1024 / 16000) + 3.0); //teseo nude
    Serial.print(time_ * 1024 / 16000); //teseo nude
    Serial.println( " ms" );
    start = false;
  }
}
