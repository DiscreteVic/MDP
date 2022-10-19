#include "mdp.h"


//---------------------------------------------------
// msCycles -> cycles equivalents to a millisecond
//---------------------------------------------------
void mdpWait(uint32_t milliseconds){
    uint32_t i, j;

    //AVOID TO USE MULTIPLICATION DUE TO RESOURCES CONSUPTION (TO BE CONFIRMED)
    for(j = 0; j < milliseconds; j++){

        //CYCLES VAULE OBTAINED EXPERIMENTALY
        for(i = 0; i < MS_CYCLES; i++);
    }
}

void mdpCreatePort(uint32_t gpioAdd, uint8_t pinOffs, uint32_t msCycles, uint32_t period, struct mdpPort *port){

    port->gpioBaseAddress = gpioAdd;
    port->pinOffset = pinOffs;
    port->msCycles = msCycles;
    port->period = period;

}

void mdpSetPort(struct mdpPort port, mdpBool value){
    uint32_t currentReg, resultReg;
    uint32_t regAddr = port.gpioBaseAddress;
    uint8_t offset = port.pinOffset;

    currentReg = *((uint32_t *)regAddr);

    if(value == 1) resultReg = currentReg | (0x00000001 << offset);
    else  resultReg = currentReg & ~(0x00000001 << offset);

    *((uint32_t *)regAddr) = resultReg;
}

mdpBool mdpGetPort(struct mdpPort port){
    uint32_t currentReg;
    uint32_t regAddr = port.gpioBaseAddress;
    uint8_t offset = port.pinOffset;

    currentReg = *((uint32_t *)regAddr);

    return (currentReg & (0x00000001 << offset)) >> offset;
}

void mdpInitPort(struct mdpPort port){
    mdpSetPort(port, 1);
}

void mdpBareDisplayValue(struct mdpPort port, uint32_t value){
    uint32_t i;
    mdpBool regBit;
    //Start communication 
    // 1 Period to low
    mdpSetPort(port, 0);
    mdpWait(port.period);


    //Start Transmission 
    for(i = 0; i < REGISTER_SIZE; i++){
        regBit = ((value >> i) & 0x0001);
        mdpSetPort(port, regBit);
        mdpWait(port.period);
    }
    

    //Stop communication 
    // 1 Period to low
    mdpSetPort(port, 0);
    mdpWait(port.period);
    mdpSetPort(port, 1);
}
// baudrate = 1/period(ms) , ex. period=1ms bd=1000bps
void mdpUARTDisplayValue(struct mdpPort port, uint8_t value){
    uint32_t i;
    mdpBool regBit;

    for(i = 0; i < UART_TOTAL_FRAME_BITS; i++){
        //Start Bit
        if(i < UART_START_BIT) mdpSetPort(port, 0);
        else if(i <= UART_DATA_FRAME_BITS)  mdpSetPort(port, (value >> (i - 1)) & 0x01);
        else if(i > UART_DATA_FRAME_BITS)  mdpSetPort(port, 1);
        mdpWait(port.period);
    }
    
}

void mdpUARTPrint(struct mdpPort port, uint8_t* toPrint){
    int i;
    for(i = 0; toPrint[i] != '\0'; i++){
        mdpUARTDisplayValue(port, toPrint[i]);
    }
}
