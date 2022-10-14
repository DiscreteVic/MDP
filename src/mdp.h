#ifndef MDP
#define MDP

#define REGISTER_SIZE           32U
#define MS_CYCLES               2826U // IMPORTANT!!! Hardware dependent! Value for RK3308


#define UART_START_BIT          1U
#define UART_DATA_FRAME_BITS    8U
#define UART_STOP_BITS          2U // 2 Stop bits improve the stability
#define UART_TOTAL_FRAME_BITS   UART_START_BIT + UART_DATA_FRAME_BITS + UART_STOP_BITS

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef enum{
    low = 0,
    high = 1
} mdpBool;


struct mdpPort{
    uint32_t gpioBaseAddress;
    uint8_t pinOffset;
    uint32_t msCycles;
    uint32_t period;
};



void mdpWait(uint32_t milliseconds);

void mdpCreatePort(uint32_t gpioAdd, uint8_t pinOffs, uint32_t msCycles, uint32_t period, struct mdpPort *port);

void mdpSetPort(struct mdpPort port, mdpBool value);

mdpBool mdpGetPort(struct mdpPort port);

void mdpInitPort(struct mdpPort port);

void mdpBareDisplayValue(struct mdpPort port, uint32_t value);

void mdpUARTDisplayValue(struct mdpPort port, uint8_t value);


#endif