#include <reg51.h>
#include <stdio.h>

#define THRESHOLD_TEMP 45.0

sbit LCD_RS = P3^0;
sbit LCD_RW = P3^1;
sbit LCD_EN = P3^2;
sbit ADC_WR = P3^3;
sbit ADC_RD = P3^4;
sbit ADC_INTR = P3^5;
sbit ALERT_PIN = P3^7;

void delay_ms(unsigned int ms) {
unsigned int i, j;
for(i=0; i<ms; i++)
for(j=0; j<1275; j++);
}

void lcd_cmd(unsigned char cmd) {
P1 = cmd;
LCD_RS = 0;
LCD_RW = 0;
LCD_EN = 1;
delay_ms(2);
LCD_EN = 0;
}

void lcd_data(unsigned char data) {
P1 = data;
LCD_RS = 1;
LCD_RW = 0;
LCD_EN = 1;
delay_ms(2);
LCD_EN = 0;
}

void lcd_init() {
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

unsigned char adc_read() {
unsigned char val;
ADC_WR = 0;
delay_ms(1);
ADC_WR = 1;

while(ADC_INTR);

ADC_RD = 0;
val = P2;
ADC_RD = 1;

return val;
}

int main() {
unsigned char adc_val;
float temp;
char buffer[16];
int temp_int, temp_frac;

ALERT_PIN = 0;
lcd_init();
lcd_string("Machine Temp:");
delay_ms(1000);

while(1) {
adc_val = adc_read();

temp = ((float)adc_val * 5.0 * 100.0) / 256.0;

temp_int = (int)temp;
temp_frac = (int)((temp - temp_int) * 100);

sprintf(buffer, "Temp: %d.%02d C ", temp_int, temp_frac);
lcd_cmd(0x80);
lcd_string(buffer);

lcd_cmd(0xC0);
if(temp > THRESHOLD_TEMP) {
ALERT_PIN = 1;
lcd_string("!! OVERHEAT !! ");
} else {
ALERT_PIN = 0;
lcd_string("Status: NORMAL ");
}

delay_ms(500);
}
}
