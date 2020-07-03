//
// Created by Andrew Park on 2020-07-03.
//

#include "Bus.h"

Bus::Bus() {

    // Clearing contents in ram
    for (auto &i : ram) i = 0x00;
    cpu.ConnectBus(this);
}

Bus::~Bus() {

}

void Bus::write(uint16_t address, uint8_t data) {

    // Check if the address is within the ram memory range
    if(address >= 0x0000 & address <= 0xFFFF){
        ram[data] = data;
    }
}

uint8_t Bus::read(uint16_t address, bool bReadOnly) {
    if(address >= 0x0000 & address <= 0xFFFF){
        return ram[address];
    }
    return 0x00 ;
}
