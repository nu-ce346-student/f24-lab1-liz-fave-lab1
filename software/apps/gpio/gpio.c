#include "gpio.h"
#include <stdio.h>

typedef struct{
  // Step 3:
  // Add register definitions here
  //

  
    volatile uint32_t RESERVED0[321];  // space to align registers correctly 
    volatile uint32_t OUT;         // Output register
    volatile uint32_t OUTSET;      // Output set register
    volatile uint32_t OUTCLR;      // Output clear register
    volatile uint32_t IN;          // Input register
    volatile uint32_t DIR;         // Direction register
    volatile uint32_t DIRSET;      // Direction set register
    volatile uint32_t DIRCLR;      // Direction clear register
   volatile uint32_t RESERVED1[120];  // Reserved space before PIN_CNF registers
    volatile uint32_t PIN_CNF[32]; // Configuration for each pin	
} gpio_reg_t;

//base addresses for the GPIO Port
						
	#define GPIO_PORT_0_BASE (0x50000000UL) //port 0 base address
	#define GPIO_PORT_1_BASE (0x50000300UL) // port 1 base address

	
// Create pointers to the GPIO registers for both ports
	static volatile  gpio_reg_t* const GPIO_PORT[2] = {
   	 (gpio_reg_t*) 0x50000000, // Port 0
   	 (gpio_reg_t*) 0x50000300  // Port 1
};

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  //
    
    uint32_t port = (gpio_num >> 5) & 0x1;  // Determine port (0 or 1)
    uint32_t pin_number = gpio_num & 0x1F;   // Pin number (0 to 31)

	  // Default PIN_CNF settings
    uint32_t pin_cnf = 0;
 
    if (dir == GPIO_OUTPUT) {
        // Set as output
        pin_cnf |= (1 << 0); // Set the DIR field in PIN_CNF (bit 0 = 1)
	 //  can clear PULL and SENSE settings for outputs
      //  pin_cnf &= ~((1 << 1) | (1 << 2)); // Clear PULL and SENSE bits
    } else {
        // Set as input
        pin_cnf &= ~(1 << 0); // Set the DIR field in PIN_CNF (bit 0 = 0)
        pin_cnf |= (1 << 1); // Enable the input buffer (PULL) if needed (if active low)
   	 // Enable pull-up resistor for active-low buttons
    // pin_cnf |= (1 << 2);  // Set pull-up resistor (bit 2 = 1) for active-low
    }

    // Configure PIN_CNF for the pin
    GPIO_PORT[port]->PIN_CNF[pin_number] = pin_cnf; 
    
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured
  //

    uint32_t port = (gpio_num >> 5) & 0x1;  // Determine port (0 or 1)
    uint32_t pin_number = gpio_num & 0x1F;   // Pin number (0 to 31)

    GPIO_PORT[port]->OUTSET = (1 << pin_number); // Set the output high
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured

    uint32_t port = (gpio_num >> 5) & 0x1;  // Determine port (0 or 1)
    uint32_t pin_number = gpio_num & 0x1F;   // Pin number (0 to 31)

    GPIO_PORT[port]->OUTCLR = (1 << pin_number); // Set the output low
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured

    uint32_t port = (gpio_num >> 5) & 0x1;  // Determine port (0 or 1)
    uint32_t pin_number = gpio_num & 0x1F;   // Pin number (0 to 31)

    // Return the current state of the specified pin
    bool pin_state =  (GPIO_PORT[port]->IN & (1 << pin_number)) ? 1 : 0;
    // true if high
  	return !pin_state;
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  //

     printf("GPIO Port 0 OUT Address: %p\n", &(GPIO_PORT[0]->OUT));
     printf("GPIO Port 0 OUTSET  Address: %p\n", &(GPIO_PORT[0]->OUTSET));
     printf("OUTCLR Address: %p\n", (void*)&(GPIO_PORT[0]->OUTCLR));
    printf("IN Address: %p\n", (void*)&(GPIO_PORT[0]->IN));
    printf("DIR Address: %p\n", (void*)&(GPIO_PORT[0]->DIR));
printf("PIN_CNF[0]: %p\n", (void*)&GPIO_PORT[0]->PIN_CNF[14]);
printf("PIN_CNF[3]: %p\n", (void*)&GPIO_PORT[1]->PIN_CNF[3]);
    printf("OUTCLR Address: %p\n", (void*)&(GPIO_PORT[1]->OUT));
    printf("IN Address: %p\n", (void*)&(GPIO_PORT[1]->OUTSET));
    printf("OUTCLR Address: %p\n", (void*)&(GPIO_PORT[1]->OUTCLR));
    printf("IN Address: %p\n", (void*)&(GPIO_PORT[1]->IN));
    printf("DIR Address: %p\n", (void*)&(GPIO_PORT[1]->DIR));

}

