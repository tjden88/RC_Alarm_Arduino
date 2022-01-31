byte PWM_PIN = 3; // Пин сигнала приёмника

byte LEFT_LED = 0; // Пин левого светодиода
byte RIGHT_LED = 0; // Пин правого светодиода
byte BUZZER_PIN = 0; // Пин пищалки



void setup() {
	pinMode(PWM_PIN, INPUT);
	Serial.begin(115200);
}

void loop() {

	int pwm_value = pulseIn(PWM_PIN, HIGH);
	Serial.println(pwm_value);

	if (pwm_value < 100) {
		leds_blink();
		buzzer_alarm();
	}
	else if (pwm_value < 1250) {
		leds_off();
	}
	else if (pwm_value < 1500)
	{
		leds_on();
	}
	else if (pwm_value < 1750)
	{
		leds_blink();
	}
	else if (pwm_value >= 1750)
	{
		leds_blink();
		buzzer_sound();
	}
}

void leds_blink() {
	Serial.println("leds_blink");
}

void leds_on() {
	Serial.println("leds_on");
}

void leds_off() {
	Serial.println("leds_off");
}

void buzzer_sound() {
	Serial.println("buzzer_sound");
}
void buzzer_alarm() {
	Serial.println("buzzer_alarm");
}
