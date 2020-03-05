/*
 * GPIO.c
 *
 *  Created on:
 *      Author:
 */

// For the code you place here, you may use your code that uses register references.
// However, I encourage you to start using the Driver Library as soon as possible.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "myGPIO.h"

#define BOOSTER_TOPBUTTON BIT1 //the top button of the booster pack is controlled by pin 5.1
#define BOOSTER_BOTTOMBUTTON BIT5 //the bottom button of the booster pack is controlled by pin 3.5
#define LAUNCHPAD_S2 BIT4 //the rightmost button of the launchpad is controlled by pin 1.4
#define LAUNCHPAD_S1 BIT1//the leftmost button of the launchpad is controlled by pin 1.1
#define PRESSED 0

// TODO: Create a function to initialize the GPIO.
// Even though this assignment does not use all of the pushbuttons, you should write one function that does a complete GPIO init.
void initGPIO()
{
    //initialize the buttons on the launchpad using registers
    P1DIR = P1DIR & ~LAUNCHPAD_S1;
    P1REN = P1REN | LAUNCHPAD_S1;
    P1OUT = P1OUT | LAUNCHPAD_S1;
    P1DIR = P1DIR & ~LAUNCHPAD_S2;
    P1REN = P1REN | LAUNCHPAD_S2;
    P1OUT = P1OUT | LAUNCHPAD_S2;
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);//launchpad LED 1
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0);//launchpad LED 2 red
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1);//launchpad LED 2 green
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN2);//launchpad LED 2 blue
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN6);//booster LED red
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN4);//booster LED green
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN6);//booster LED blue
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P5, GPIO_PIN1);//top button on booster
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P3, GPIO_PIN5);//bottom button on booster
    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN6);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN2);//turned off all LEDs
}

// TODO: Create a function to return the status of Launchpad Pushbutton S1
unsigned char checkStatus_LaunchpadS1()
{
    return ((P1IN & LAUNCHPAD_S1) == LAUNCHPAD_S1);
}

// TODO: Create a function to return the status of Launchpad Pushbutton S2
unsigned char checkStatus_LaunchpadS2()
{
    return ((P1IN & LAUNCHPAD_S2) == LAUNCHPAD_S2);
}

// TODO: Create a function to return the status of Boosterpack Pushbutton S1
unsigned char checkStatus_BoosterpackS1()
{
    return ((P5IN & BOOSTER_TOPBUTTON) == BOOSTER_TOPBUTTON);
}

// TODO: Create a function to return the status of Boosterpack Pushbutton S2
unsigned char checkStatus_BoosterpackS2()
{
    return ((P3IN & BOOSTER_BOTTOMBUTTON) == BOOSTER_BOTTOMBUTTON);
}

// TODO: Create a function to turn on Launchpad LED1.
void turnOn_LaunchpadLED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
}

// TODO: Create a function to turn off Launchpad LED1.
void turnOff_LaunchpadLED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
}

// TODO: Create a function to turn on the Red Launchpad LED2.
void turnOn_LaunchpadLED2Red()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);
}

// TODO: Create a function to turn off the Red Launchpad LED2.
void turnOff_LaunchpadLED2Red()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);
}

// TODO: Create a function to turn on the Green Launchpad LED2.
void turnOn_LaunchpadLED2Green()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN1);
}

// TODO: Create a function to turn off the Green Launchpad LED2.
void turnOff_LaunchpadLED2Green()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1);
}

// TODO: Create a function to turn on the Blue Launchpad LED2.
void turnOn_LaunchpadLED2Blue()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN2);
}

// TODO: Create a function to turn off the Blue Launchpad LED2.
void turnOff_LaunchpadLED2Blue()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN2);
}

// TODO: Create a function to turn on the Red Boosterpack LED2.
void turnOn_BoosterpackLEDRed()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN6);
}

// TODO: Create a function to turn off the Red Boosterpack LED2.
void turnOff_BoosterpackLEDRed()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);
}

// TODO: Create a function to turn on the Green Boosterpack LED2.
void turnOn_BoosterpackLEDGreen()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
}

// TODO: Create a function to turn off the Green Boosterpack LED2.
void turnOff_BoosterpackLEDGreen()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
}

// TODO: Create a function to turn on the Blue Boosterpack LED2.
void turnOn_BoosterpackLEDBlue()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN6);
}

// TODO: Create a function to turn off the Green Boosterpack LED2.
void turnOff_BoosterpackLEDBlue()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN6);
}
