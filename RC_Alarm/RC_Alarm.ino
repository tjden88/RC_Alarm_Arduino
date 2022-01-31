#include "GyverTimer.h"

byte PWM_PIN = 11; // Пин сигнала приёмника

byte LEFT_LED = 3; // Пин левого светодиода
byte RIGHT_LED = 6; // Пин правого светодиода
byte BUZZER_PIN = 9; // Пин пищалки


GTimer Timer_Long_Lat(MS, 1400); // Таймер переключения светодиодов
GTimer Timer_Small_Lat(MS); // Таймер малой задержки светодиодов
int small_timeout = 90; // Таймаут мигания светодиодов
byte blinks_count = 3; // Количество миганий каждого светодиода

GTimer Timer_Buzzer(MS, 400); // Таймер пищалки


void setup() {
	pinMode(PWM_PIN, INPUT);
	pinMode(LEFT_LED, OUTPUT);
	pinMode(RIGHT_LED, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	Serial.begin(115200);
}

void loop() {

	int pwm_value = pulseIn(PWM_PIN, HIGH);
	//Serial.println(pwm_value);

	if (pwm_value < 1250) {
		leds_off();
		buzzer_off();
	}
	else if (pwm_value < 1500)
	{
		leds_on();
		buzzer_off();
	}
	else if (pwm_value < 1750)
	{
		leds_blink();
		buzzer_off();
	}
	else if (pwm_value >= 1750)
	{
		leds_blink();
		buzzer_sound();
	}
}


bool nowBlinkRight = false;
bool led_now_on = false;
byte led_blink_count = 0;

void leds_blink() {
	if (Timer_Long_Lat.isReady()) {
		nowBlinkRight = !nowBlinkRight;
		digitalWrite(RIGHT_LED, nowBlinkRight);
		digitalWrite(LEFT_LED, !nowBlinkRight);
		Timer_Small_Lat.setTimeout(small_timeout);
		led_now_on = true;
		led_blink_count = 1;
	}
	led_small_blink(nowBlinkRight ? RIGHT_LED : LEFT_LED);
}


void led_small_blink(byte pin) {
	if (Timer_Small_Lat.isReady()) {
		if (led_blink_count >= blinks_count) {
			digitalWrite(pin, LOW);
			return;
		}

		led_now_on = !led_now_on;
		digitalWrite(pin, led_now_on);

		if (led_now_on) 
			led_blink_count++;

		Timer_Small_Lat.setTimeout(small_timeout);
	}
}

void leds_on() {
	digitalWrite(RIGHT_LED, HIGH);
	digitalWrite(LEFT_LED, HIGH);
}

void leds_off() {
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
}

bool buzzer_is_on = false;

void buzzer_sound() {
	if (Timer_Buzzer.isReady()) {

		buzzer_is_on = !buzzer_is_on;
		digitalWrite(BUZZER_PIN, buzzer_is_on);
	}
}

void buzzer_off() {
	digitalWrite(BUZZER_PIN, LOW);
}
