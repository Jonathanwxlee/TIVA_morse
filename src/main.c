#include <stdint.h>
#include <morse_LED.h>

// define system control registers pulling from 0x400FE608 and 0x400FEA08
#define SYSCTL_RCGCGPIO_R (*(volatile uint32_t *)0x400FE608)
#define SYSCTL_PRGPIO_R (*(volatile uint32_t *)0x400FEA08)

// define peripheral base address
#define GPIO_PORTF_BASE 0x40025000

// define peripheral registers DIR and DEN
#define GPIO_PORTF_DIR_R (*(volatile uint32_t *)(GPIO_PORTF_BASE + 0x400))
#define GPIO_PORTF_DEN_R (*(volatile uint32_t *)(GPIO_PORTF_BASE + 0x51C))
// #define GPIO_PORTF_DATA_R (*(volatile uint32_t *)(GPIO_PORTF_BASE + 0x3FC))

/* GPIO port F has the pins below:
PF0 : Mask:00000001 : 0x01 (Controls user switch 2 idk what this is yet)
PF1 : Mask:00000010 : 0x02 (Controls the Red LED)
PF2 : Mask:00000100 : 0x04 (Controls the Blue LED)
PF3 : Mask:00001000 : 0x08 (Controls the Green LED)
PF4 : Mask:00010000 : 0x10 (Controls user switch 1 idk when this is yet)
*/

// define pin names and their masks for the GPIO port F peripheral
#define RED_LED 0x02
#define BLUE_LED 0x04
#define GREEN_LED 0x08

// define input word
#define WORD_LEN 5

int main(void){
    const char *message = "HELLO";

    // enable clock for GPIO port f peripheral
    SYSCTL_RCGCGPIO_R |= (1U << 5);

    // wait for SYSCTL_PRGPIO_R to indicate peripheral GPIO port f is ready
    while (SYSCTL_PRGPIO_R & (1U << 5) == 0) {
        //Infinite wait until the GPIO port f peripheral is set
    }

    // enable the digital functionality fo GREEN LED pin (PF3)
    GPIO_PORTF_DEN_R |= GREEN_LED;
    // set the direction of GREEN_LED pin (PF3) as output
    GPIO_PORTF_DIR_R |= GREEN_LED;

    volatile uint32_t *green_led_mask_addr = (volatile uint32_t *)(GPIO_PORTF_BASE + (GREEN_LED << 2));
    volatile uint32_t *red_led_mask_addr = (volatile uint32_t *)(GPIO_PORTF_BASE + (RED_LED << 2));

    while (1){ // infinitely repeat the morse. 
        *red_led_mask_addr = 0;
        delay(400000);
        while (*message != '\0') { // iterate over the letters of the word
            const char *morse_sequence = morse_encode(*message);
            // flash morse sequence
            flash_morse_letter(green_led_mask_addr, morse_sequence);
            message++;
        }
        delay(400000);
        *red_led_mask_addr = 1;
    }
}
