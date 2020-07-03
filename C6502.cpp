//
// Created by Andrew Park on 2020-07-03.
//

#include "C6502.h"
#include "bus.h"

C6502::C6502() {

}

C6502::~C6502() {

}

uint8_t C6502::read(uint16_t address){
    return bus->read(address, false);
}

void C6502::write(uint16_t address, uint8_t data) {
    bus->write(address, data);
}
