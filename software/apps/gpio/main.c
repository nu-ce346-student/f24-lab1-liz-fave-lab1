// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"


#define BUTTON_A 14  // Button A is P0.14
#define BUTTON_B 23  // Button B is P0.23
#define MICROPHONE_LED 20  // Microphone LED is P0.20

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here
    gpio_config(21, GPIO_OUTPUT);  // ROW1
    gpio_config(22, GPIO_OUTPUT);  // ROW2
    gpio_config(15, GPIO_OUTPUT);  // ROW3
    gpio_config(24, GPIO_OUTPUT);  // ROW4
    gpio_config(19, GPIO_OUTPUT);  // ROW5
    gpio_config(28, GPIO_OUTPUT);  // COL1
    gpio_config(11, GPIO_OUTPUT);  // COL2
    gpio_config(31, GPIO_OUTPUT);  // COL3
    gpio_config(37, GPIO_OUTPUT);  // COL4
    gpio_config(30, GPIO_OUTPUT);  // COL5

    // Set all rows high
    gpio_set(21);
    gpio_set(22);
    gpio_set(15);
    gpio_set(24);
    gpio_set(19);

    // Clear all columns (set them low)
    gpio_clear(28);
    gpio_clear(11);
    gpio_clear(31);
    gpio_clear(37);
    gpio_clear(30);

    // Print GPIO information
    gpio_print();
                                                                                                                           
  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  //
/*  
    
     NRF_GPIO->DIR = (1 << 20); // Set P0.20 as output
    NRF_GPIO->OUT = (1 << 20);  // Set P0.20 high (turn on LED)
*/


    // Configure Button A and Button B as inputs
    gpio_config(BUTTON_A, GPIO_INPUT);
    gpio_config(BUTTON_B, GPIO_INPUT);

    // Configure Microphone LED as output
    gpio_config(MICROPHONE_LED, GPIO_OUTPUT);

    // Turn off the Microphone LED initially
    gpio_clear(MICROPHONE_LED);
	

  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    //
/*
	 // Read Button A and Button B states
        bool button_a_pressed =  gpio_read(BUTTON_A); // Active low, so invert
        bool button_b_pressed = gpio_read(BUTTON_B); // Active low, so invert
//	printf("Button A: %d, Button B: %d\n", button_a_pressed, button_b_pressed);
        // If Button A is pressed, turn on the Microphone LED
        if (button_a_pressed) {
//		nrf_delay_ms(50);
	//	if (gpio_read(BUTTON_A)) {
            gpio_set(MICROPHONE_LED);
	    printf("LED On\n");
        
	}
        // If Button B is pressed, turn off the Microphone LED
	 if (button_b_pressed) {
//		nrf_delay_ms(50);
	//	if (gpio_read(BUTTON_B)) {
            gpio_clear(MICROPHONE_LED);
	    printf("LED off\n");
	
	} */

	  if (gpio_read(BUTTON_A) == 0) {
		  gpio_set(MICROPHONE_LED);}

	  if (gpio_read(BUTTON_B) == 0) {
                  gpio_clear(MICROPHONE_LED);}
  

    nrf_delay_ms(100);
  }
}

