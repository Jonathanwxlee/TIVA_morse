#include <stdint.h>

void delay(volatile uint32_t count)
{
    while (count > 0)
    {
        count--;
    }
}

const char *morse_encode(char letter){
    switch (letter) {
        case 'A': return ".-";
        case 'B': return "-...";
        case 'C': return "-.-.";
        case 'D': return "-..";
        case 'E': return ".";
        case 'F': return "..-.";
        case 'G': return "--.";
        case 'H': return "....";
        case 'I': return "..";
        case 'J': return ".---";
        case 'K': return "-.-";
        case 'L': return ".-..";
        case 'M': return "--";
        case 'N': return "-.";
        case 'O': return "---";
        case 'P': return ".--.";
        case 'Q': return "--.-";
        case 'R': return ".-.";
        case 'S': return "...";
        case 'T': return "-";
        case 'U': return "..-";
        case 'V': return "...-";
        case 'W': return ".--";
        case 'X': return "-..-";
        case 'Y': return "-.--";
        case 'Z': return "--..";
    }
}

static void led_dot(volatile uint32_t* led_data_r){
    *led_data_r = 0x08;
    delay(800000);
    *led_data_r = 0;
}

static void led_dash(volatile uint32_t* led_data_r){
    *led_data_r = 0x08;
    delay(2400000);
    *led_data_r = 0;
}

void flash_morse_letter(volatile uint32_t* led_data_r, const char* seq){
    while (*seq != '\0') {
        if (*seq == '.') {
            led_dot(led_data_r);
        } else {
            led_dash(led_data_r);
        }
        seq++;
        delay(400000); // in between sequence symbols
    }
}
