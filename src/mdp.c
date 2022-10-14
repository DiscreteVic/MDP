#include "mdp.h"
#include "common.h"




void mdpCreatePort(uint32_t gpioAdd, uint8_t pinOffs, struct mdpPort *port){

    port->gpioBaseAddress = gpioAdd;
    port->pinOffset = pinOffs;

}

void mdpSetPort(struct mdpPort port, bool value){
    uint32_t currentReg, resultReg;
    uint32_t regAddr = port.gpioBaseAddress;
    uint8_t offset = port.pinOffset;

    currentReg = *((uint32_t *)regAddr);

    if(value == 1) resultReg = currentReg | (0x00000001 << offset);
    else  resultReg = currentReg & ~(0x00000001 << offset);

    *((uint32_t *)regAddr) = resultReg;
}