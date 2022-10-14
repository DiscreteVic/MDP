#ifndef MDP
#define MDP

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef enum{
    false = 0,
    true = 1
} bool;


struct mdpPort{
    uint32_t gpioBaseAddress;
    uint8_t pinOffset;
};

void mdpCreatePort(uint32_t gpioAdd, uint8_t pinOffs, struct mdpPort *port);

void mdpSetPort(struct mdpPort port, bool value);





#endif