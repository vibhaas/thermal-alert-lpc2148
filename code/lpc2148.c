#include <lpc214x.h>
#include <stdio.h>

#define THRESHOLD_TEMP 45.0
#define LCD_RS (1<<24)
#define LCD_EN (1<<25)
#define ALERT_PIN (1<<10)

void delay_ms(unsigned int ms) {
unsigned int i, j;
for(i=0; i<ms; i++)
for(j=0; j<6000; j++);
}

void lcd_cmd(unsigned char cmd) {
IO1CLR = 0x03FF0000;
IO1SET = (cmd << 16);
IO1CLR = LCD_RS;
IO1SET = LCD_EN;
delay_ms(2);
IO1CLR = LCD_EN;
}

void lcd_data(unsigned char data) {
IO1CLR = 0x03FF0000;
IO1SET = (data << 16);
IO1SET = LCD_RS;
IO1SET = LCD_EN;
delay_ms(2);
IO1CLR = LCD_EN;
}

void lcd_init() {
IO1DIR |= 0x03FF0000;
lcd_cmd(0x38);
lcd_cmd(0x0C);
lcd_cmd(0x01);
lcd_cmd(0x80);
}

void lcd_string(char *str) {
while(*str) {
lcd_data(*str++);
}
}

unsigned int adc_read() {
unsigned int val;
PINSEL1 |= (1<<24);
PINSEL1 &= ~(1<<25);

AD0CR = 0x01200002;

while(!(AD0GDR & 0x80000000));

val = (AD0GDR >> 6) & 0x3FF;
return val;
}

int main() {
unsigned int adc_val;
float temp;
char buffer[16];
int temp_int, temp_frac;

IO0DIR |= ALERT_PIN;
IO0CLR = ALERT_PIN;

lcd_init();
lcd_string("Machine Temp:");
delay_ms(1000);

while(1) {
adc_val = adc_read();

temp = ((float)adc_val * 3.3 * 100.0) / 1024.0;

temp_int = (int)temp;
temp_frac = (int)((temp - temp_int) * 100);

sprintf(buffer, "Temp: %d.%02d C ", temp_int, temp_frac);
lcd_cmd(0x80);
lcd_string(buffer);

lcd_cmd(0xC0);
if (temp > THRESHOLD_TEMP) {
IO0SET = ALERT_PIN;
lcd_string("!! OVERHEAT !! ");
} else {
IO0CLR = ALERT_PIN;
lcd_string("Status: NORMAL ");
}

delay_ms(500);
}
}
