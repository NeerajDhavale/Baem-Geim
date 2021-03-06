/*
 * LabGPIO.hpp
 *
 *  Created on: Sep 2, 2018
 *      Author: Neeraj Dhavale
 */

//#ifndef LABGPIO_HPP_
#define LABGPIO_HPP_
#ifndef LABGPIO_H
#define LABGPIO_H

#include <stdint.h>
#include "LPC17xx.h"
#include "tasks.hpp"
#include "FreeRTOS.h"
#include "uart0_min.h"
extern void vControlLED(void);
extern void vControlLEDExter(void *p);
extern void vReadSwitch(uint8_t PortNum,uint8_t PinNum);


class LabGPIO_1
{
private:
    /**
     * port, pin and any other variables should be placed here.
     * NOTE: that the state of the pin should not be recorded here. The true
     *      source of that information is embedded in the hardware registers
     */
    uint8_t PortNum;
    uint8_t PinNum;
    volatile LPC_GPIO_TypeDef *ptrLabGPIO;


public:
    /**
     * You should not modify any hardware registers at this point
     * You should store the port and pin using the constructor.
     *
     * @param {uint8_t} pin  - pin number between 0 and 32
     */
    //LabGPIO_1(uint8_t pin);
    /**
     * Should alter the hardware registers to set the pin as an input
     */
    void setAsInput();
    /**
     * Should alter the hardware registers to set the pin as an input
     */
    void setAsOutput();
    /**
     * Should alter the set the direction output or input depending on the input.
     *
     * @param {bool} output - true => output, false => set pin to input
     */
    void setDirection(bool output);
    /**
     * Should alter the hardware registers to set the pin as high
     */
    void setHigh();
    /**
     * Should alter the hardware registers to set the pin as low
     */
    void setLow();
    /**
     * Should alter the hardware registers to set the pin as low
     *
     * @param {bool} high - true => pin high, false => pin low
     */
    void set(bool high);
    /**
     * Should return the state of the pin (input or output, doesn't matter)
     *
     * @return {bool} level of pin high => true, low => false
     */
    bool getLevel();

    //void vControlLED( uint8_t *pin);
    ~LabGPIO_1();
};

#endif /* LABGPIO_HPP_ */
