#include "GyverTimer.h"

byte PWM_PIN = 3; // ��� ������� ��������

byte LEFT_LED = 5; // ��� ������ ����������
byte RIGHT_LED = 6; // ��� ������� ����������
byte BUZZER_PIN = 0; // ��� �������


GTimer Timer_Long_Lat(MS, 1400); // ������ ������������ �����������
GTimer Timer_Small_Lat(MS); // ������ ����� �������� �����������
int small_timeout = 90; // ������� ������� �����������
byte blinks_count = 3; // ���������� ������� ������� ����������

void setup() {
	pinMode(PWM_PIN, INPUT);
	Serial.begin(115200);
}

void loop() {

	int pwm_value = pulseIn(PWM_PIN, HIGH);
	//Serial.println(pwm_value);

	if (pwm_value < 1250) {
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

void buzzer_sound() {
	Serial.println("buzzer_sound");
}
