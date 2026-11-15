#ifndef MORSE_H
#define MORSE_H



// This function should take the letter as input and output a sequence of some sort
const char *morse_encode(char letter);

void flash_morse_letter(volatile uint32_t *led_data_r, char* seq);

#endif


