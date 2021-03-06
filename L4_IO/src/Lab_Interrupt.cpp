/*
 * Lab_Interrupt.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: Neeraj Dhavale
 */

#include "Lab_Interrupt.hpp"


IsrPointer user_callback1 = &interrupt_callback;
IsrPointer user_callback2 = &interrupt_callback_2;

void LabGpioInterrupts::Initialize()
{
    NVIC_EnableIRQ(EINT3_IRQn);

}

bool LabGpioInterrupts::AttachInterruptHandler(uint8_t port, uint32_t pin, IsrPointer pin_isr, InterruptCondition condition)
{

    if(port == 2)
        pin_isr_map[1][pin] ={pin_isr};
    else
        pin_isr_map[port][pin] ={pin_isr};

    if(port == 0)
    {
        if(condition == kRisingEdge)
        {
           LPC_GPIOINT->IO0IntEnR |= (1<<pin);
        }

        else if(condition == kFallingEdge)
        {
            LPC_GPIOINT->IO0IntEnF |= (1<<pin);
        }
        else if(condition == kBothEdges)
        {
            (LPC_GPIOINT->IO2IntEnF |= (1<<pin))||(LPC_GPIOINT->IO2IntEnR |= (1<<pin));
        }
        else
            ;//do nothing

    }

    if(port == 2)
    {
        if(condition == kFallingEdge)
        {
                LPC_GPIOINT->IO2IntEnF |= (1<<pin);
        }

        else if(condition == kRisingEdge)
        {
            uart0_puts("TT");
            LPC_GPIOINT->IO2IntEnR |= (1<<pin);
        }
        else if(condition == kBothEdges)
        {
            (LPC_GPIOINT->IO2IntEnF |= (1<<pin))||(LPC_GPIOINT->IO2IntEnR |= (1<<pin));
        }
        else
            ;//do nothing
    }

    return 1;
}


void LabGpioInterrupts::HandleInterrupt(void)
{
    uint8_t i;


        for(i=0;i<32;i++)
        {
            if((LPC_GPIOINT->IO0IntStatR>>i) & 0x01)
            {
                LPC_GPIOINT->IO0IntClr |= (1<<i);
                pin_isr_map[0][i]();
                break;
            }
        }

        for(i=0;i<32;i++)
        {

            if((LPC_GPIOINT->IO2IntStatR>>i)& 0x01)
            {
                uart0_puts("HandlerInt");
                LPC_GPIOINT->IO2IntClr |= (1<<i);
                pin_isr_map[1][i]();
                break;
            }
        }

        for(i=0;i<32;i++)
                {
                    if((LPC_GPIOINT->IO0IntStatF>>i) & 0x01)
                    {
                        LPC_GPIOINT->IO0IntClr |= (1<<i);
                        pin_isr_map[0][i]();
                        break;
                    }
                }

                for(i=0;i<32;i++)
                {

                    if((LPC_GPIOINT->IO2IntStatF>>i)& 0x01)
                    {
                        uart0_puts("HandlerInt");
                        LPC_GPIOINT->IO2IntClr |= (1<<i);
                        pin_isr_map[1][i]();
                        break;
                    }
                }

}



void interrupt_callback_2(void)
{
    uart0_puts("Interrupt 2 received");

    //NVIC_EnableIRQ(EINT3_IRQn);
}


