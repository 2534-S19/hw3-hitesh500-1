#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.


    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);
    unsigned int n = 7;
    unsigned char passVal=0xFF;
    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        //changeLaunchpadLED2(count0);

        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired()==true){
            count0++;
            count0=count0%8;
           changeLaunchpadLED2(count0);
        }
        else{
            changeLaunchpadLED2(count0);
        }



        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if (timer1Expired()==true){
            bool pressed = checkStatus_BoosterpackS1();
            if (pressed==true){
                passVal=passVal&~passVal<<n;
                n--;
            }
            else{
                passVal=passVal|passVal<<n;
                n--;
            }
            if (fsmBoosterpackButtonS1(passVal)==true){
                count1++;
                count1=count1%8;
                changeBoosterpackLED(count1);
                n=7;
            }
            else{
                n=7;
            }
        }


        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.



        // TODO: If a completed, debounced button press has occurred, increment count1.



    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    switch (count){
    case 0://red
        turnOn_LaunchpadLED2Red();
        break;
    case 1://green
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        break;
    case 2://yellow
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Red();
        break;
    case 3://blue
        turnOff_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        break;
    case 4://magenta
        turnOn_LaunchpadLED2Blue();
        turnOn_LaunchpadLED2Red();
        break;
    case 5: //cyan
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
        turnOn_LaunchpadLED2Green();
        break;
    case 6: //white
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
        turnOn_LaunchpadLED2Green();
        break;
    case 7: //off
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Green();
        break;
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    switch (count){
    case 0://red
        turnOn_BoosterpackLEDRed();
        break;
    case 1://green
        turnOff_BoosterpackLEDRed();
        turnOn_BoosterpackLEDGreen();
        break;
    case 2://yellow
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        break;
    case 3://blue
        turnOff_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDBlue();
        break;
    case 4://magenta
        turnOn_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDRed();
        break;
    case 5: //cyan
        turnOff_BoosterpackLEDRed();
        turnOn_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        break;
    case 6: //white
        turnOn_BoosterpackLEDRed();
        turnOn_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        break;
    case 7: //off
        turnOff_BoosterpackLEDRed();
        turnOff_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
        break;
    }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    bool pressed = false;
    typedef enum {up,down} state;
    static state currentState = up;
    switch (currentState){
    case up:
        if (buttonhistory==0xFF){
            currentState = down;
        }
        break;
    case down:
        if (currentState==0x00){
            currentState=up;
            pressed = true;
        }
        break;
    }
    return pressed;
}
