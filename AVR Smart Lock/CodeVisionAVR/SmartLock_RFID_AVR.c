/*******************************************************
Project : RFID Lock with time and temp support
Date    : 10 August 2024
Author  : Nariman Ziaie
Company : Islamic Azad University Central Tehran Branch

Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Standard Input/Output functions
#include <string.h>
#include <stdio.h>

// Declare your global variables here
unsigned int temperature;
char s[15];

#define RFID_LENGTH 12
char rfid[RFID_LENGTH + 1];  // Adjust size for RFID string +1 for null termination
volatile unsigned char rfid_index = 0;
volatile unsigned char rfid_complete = 0;

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE 0xC0

#define TIMEOUT_THRESHOLD 5000  // Timeout threshold in milliseconds

unsigned int read_adc(unsigned char adc_input) {
    ADMUX = adc_input | (ADC_VREF_TYPE & 0xff);
    delay_us(10);
    ADCSRA |= 0x40;
    while ((ADCSRA & 0x10) == 0);
    ADCSRA |= 0x10;
    return ADCW;
}

// Function to initialize USART
void usart_init(unsigned int baud) {
    unsigned int UBR_val = (500000 / baud) - 1;
    UCSRB = (1 << RXEN) | (1 << TXEN);  // Enable receiver and transmitter
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);  // 8 data bits, 1 stop bit
    UBRRL = UBR_val;  // Set baud rate
    UBRRH = (UBR_val >> 8);
}

void usart_send_char(unsigned char ch) {
    while(!(UCSRA & (1<<UDRE)));
    UDR = ch;
}

void usart_send_str(unsigned char *str) {
    while(*str!='\0')
    {
        while(!(UCSRA & (1<<UDRE)));
        UDR = *str;
        str++;
    }
}

unsigned char usart_receive() {
    while (!(UCSRA & (1 << RXC)));  // Wait for data to be received
    return UDR;  // Return received data
}

unsigned char usart_receive_string() {
    unsigned char i=0;
    char str[13];
    for(i=0;i<13;i++)
    {
        str[i] = usart_receive();                // this will take in 12 digit RFID number
    }
    return *str;
}

void process_rfid(unsigned char ch) {
    if (rfid_index < RFID_LENGTH) {
        rfid[rfid_index++] = ch;
        if (rfid_index == RFID_LENGTH) {
            rfid[RFID_LENGTH] = '\0';  // Null-terminate the string
            rfid_complete = 1;  // Mark the RFID as complete
        }
    } else {
        rfid_index = 0;  // Reset index if overflow
    }
}

void reset_rfid() {
    rfid_index = 0;
    rfid_complete = 0;
}

interrupt [EXT_INT0] void ext_int0_isr(void) {
    unsigned long timeout_counter = 0;
    unsigned char ch;

    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_puts("Scan RFID:");
    printf("Please Scan your RFID TAG: \n");

    reset_rfid();  // Reset RFID status

    while (timeout_counter < TIMEOUT_THRESHOLD) {
        if (UCSRA & (1 << RXC)) {  // Check if data received
            ch = usart_receive();
            process_rfid(ch);
            timeout_counter = 0;  // Reset timeout if data is received
        }

        if (rfid_complete) {
            lcd_clear();
            if (strncmp(rfid, "160066A5EC39", RFID_LENGTH) == 0) {  // Compare RFID with predefined ID
                lcd_gotoxy(0, 0);
                lcd_puts("Valid Card");
                lcd_gotoxy(0,1);
                lcd_puts("Door unlocked");
                printf("The Card is VALID, Door will be unlocked. \n");
                PORTB |= (1 << 0);  // Turn on LED or relay
                delay_ms(5000);
                PORTB &= ~(1 << 0);  // Turn off LED or relay
            } else {
                lcd_gotoxy(0, 0);
                lcd_puts("Invalid Card");
                lcd_gotoxy(0,1);
                lcd_puts("Door locked");
                printf("The Card is INVALID, Door remains locked. \n");
                PORTB &= ~(1 << 0);  // Turn off LED or relay
            }
            delay_ms(1000);  // Hold the result on the screen for 1 second
            break;  // Exit the RFID scan mode
        }

        delay_ms(1);
        timeout_counter++;
    }

    lcd_clear();  // Clear the LCD after timeout or valid/invalid card check
}

void main(void) {
    // Declare your local variables here
    char seconds = 0, minutes = 0, hours = 0, A[16];

    // Initialize Ports
    // Port A initialization
    DDRA  = 0x00;
    PORTA = 0x00;

    // Port B initialization
    DDRB  = 0x01;  // Set PORTB.0 as output (for LED/Relay control)
    PORTB = 0x00;  // Initialize PORTB to low

    // Port C initialization
    DDRC = 0xF7; 
    
    // Initialize other ports (if needed)

    // ADC initialization
    // ADC Clock frequency: 1000.000 kHz
    // ADC Voltage Reference: AREF pin
    // ADC Auto Trigger Source: ADC Stopped
    ADMUX = ADC_VREF_TYPE & 0xff;
    ADCSRA = 0x83;
    // SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTC Bit 0
    // RD - PORTC Bit 1
    // EN - PORTC Bit 2
    // D4 - PORTC Bit 4
    // D5 - PORTC Bit 5
    // D6 - PORTC Bit 6
    // D7 - PORTC Bit 7
    // Characters/line: 16
    lcd_init(16);
    lcd_clear();

    // Initialize USART for RFID communication (9600 baud rate)
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 9600
    usart_init(9600);

    // Initialize external interrupt on INT0 (PD2)
    // INT0: On
    // INT0 Mode: Falling Edge
    GICR |= (1 << INT0);  // Enable INT0
    MCUCR |= (1 << ISC01);  // Trigger INT0 on falling edge
    GIFR |= (1 << INTF0);  // Clear INT0 interrupt flag

    // Enable global interrupts
    #asm("sei");

    lcd_gotoxy(0,0);
    lcd_puts("Developed by:");
    lcd_gotoxy(0,1);
    lcd_puts("Nariman Ziaie");
    delay_ms(1000);

    while (1) {
        // Update time
        seconds++;
        if (seconds > 59) {
            seconds = 0;
            minutes++;
        }
        if (minutes > 59) {
            minutes = 0;
            hours++;
        }
        if (hours > 23) {
            hours = minutes = seconds = 0;
        }

        // Display time on the LCD
        sprintf(A, "Time: %02u:%02u:%02u ", hours, minutes, seconds);
        lcd_gotoxy(0, 0);
        lcd_puts(A);

        // Read temperature and display it
        temperature = read_adc(0);
        sprintf(s, "Actual Temp=%u", temperature / 4);
        lcd_gotoxy(0, 1);
        lcd_puts(s);

        delay_ms(1000);  // Update time and temp every second
    }
}
