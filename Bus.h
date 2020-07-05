//
// Created by Andrew Park on 2020-07-03.
//
#pragma once

#ifndef NES_EMULATOR_BUS_H
#define NES_EMULATOR_BUS_H
#include <iostream>
#include <cstdint>
#include "C6502.h"
#include <vector>
#include <map>

class Bus {

public:
    Bus();
    ~Bus();

    C6502 cpu;
//    uint8_t a123 = 64;
    std::vector<uint8_t> ram = std::vector<uint8_t>(64 * 1024, 0);
//    int i{1}, s{5}, len{0};
//    std::vector<int> v(s);
//    std::vector<int> second (4,100);

    void write(uint16_t address, uint8_t data);
    uint8_t read(uint16_t address, bool bReadOnly = false);
};


#endif //NES_EMULATOR_BUS_H
