#include <system.h>
#include <keyboard.h>
#include <IO.h>
#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_COMMAND_PORT 0x64

static uint8_t key_queue_num;
static uint8_t key_queue[32];

//there will be a function in stdio that will abstract this away so the programer does not need to worry about it
uint8_t read_key_queue() {
    return key_queue[0];
}

void clear_key_queue() {
    for(int i = 0; i < 31; i++) {
        key_queue[i] = 0;
    }
}

void pop_from_key_queue() {
    
    for(int i = 0; i <= key_queue_num; i++) {
        key_queue[i] = key_queue[i+1];
    }
    key_queue_num--;
}

//only the driver can use this function
void push_to_key_queue(uint8_t keycode) {
    if(key_queue_num == 0) {
        return;
    }
    key_queue_num++;
    key_queue[key_queue_num] = keycode;
}

//when a key is pressed this will check the output buffer status in the status register and if it is true then will add it to the qeue the process can ether handle the input directly of take input from the os stdlib
void ps2_keyboard_handler(cpu_ctx ctx) {
    int code;
    if (inb(KEYBOARD_STATUS_COMMAND_PORT) & 1) {
        code = inb(KEYBOARD_DATA_PORT);
    }
    push_to_key_queue(code);
}

