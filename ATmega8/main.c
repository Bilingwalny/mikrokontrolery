#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

//definicje LED
#define LED_PIN (1<<PB0)
#define LED_TOG PORTB ^= LED_PIN	//neguj bity
#define LED_ON PORTB &= ~LED_PIN
#define LED_OFF PORTB |= LED_PIN

//definicje klawisza
#define KEY_PIN (1<<PD0)
#define KEY2_PIN (1<<PD1)
#define KEY_DOWN (!( PIND & KEY_PIN))
#define KEY2_DOWN (!( PIND & KEY2_PIN))

uint8_t EEMEM ee_zmienna = 0; //inicjalizujesz j¹ 0
volatile uint8_t zmienna = 3;
uint8_t licznik = 0;

void zapisz_zmienne(void);
void odczytaj_zmienne(void);
uint8_t klawisz_wcisniety(void);
uint8_t klawisz2_wcisniety(void);

int main(void) {
	PORTA = 255;
	PORTB = 255;
	PORTC = 255;
	PORTD = 255;
	DDRB = 255;
	DDRD &= ~KEY_PIN;

	if( klawisz2_wcisniety())
		zapisz_zmienne();
	//odkomentuj zeby ponownie dzialalo urzadzenie (zrob przyciskiem)

	odczytaj_zmienne();



	while (1)
	{
		if(klawisz_wcisniety() && zmienna == 3)	//sprawdzam czy w EEPROM jest zmienna 3
		{
			LED_TOG;
			_delay_ms(100);
			licznik++;
			if( licznik == 6 )
			{
				zmienna = 49;
				zapisz_zmienne();
			}
		}
	}
}

void zapisz_zmienne(void) {
	eeprom_write_byte(&ee_zmienna, zmienna);
}

void odczytaj_zmienne(void) {
	zmienna = eeprom_read_byte(&ee_zmienna);
}

uint8_t klawisz_wcisniety(void) {
	if ( KEY_DOWN) {
		_delay_ms(80);
		if ( KEY_DOWN)
			return 1;
	}
	return 0;
}

uint8_t klawisz2_wcisniety(void) {
	if ( KEY2_DOWN) {
		_delay_ms(80);
		if ( KEY2_DOWN)
			return 1;
	}
	return 0;
}
