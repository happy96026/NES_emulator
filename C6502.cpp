//
// Created by Andrew Park on 2020-07-03.
//

#include "C6502.h"
#include "Bus.h"
//#include <cstdint>
//#include "olc6502.h"

C6502::C6502() {
    using c = C6502;
//    (INSTRUCTION){ "BRK", &c::BRK, &c::IMM, 7 };
    lookup = /*{{ "BRK", &c::BRK, &c::IMM, 7 }};*/
            {
                    { "BRK", &c::BRK, &c::IMM, 7 },{ "ORA", &c::ORA, &c::IZX, 6 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 3 },{ "ORA", &c::ORA, &c::ZP0, 3 },{ "ASL", &c::ASL, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "PHP", &c::PHP, &c::IMP, 3 },{ "ORA", &c::ORA, &c::IMM, 2 },{ "ASL", &c::ASL, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::NOP, &c::IMP, 4 },{ "ORA", &c::ORA, &c::ABS, 4 },{ "ASL", &c::ASL, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BPL", &c::BPL, &c::REL, 2 },{ "ORA", &c::ORA, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "ORA", &c::ORA, &c::ZPX, 4 },{ "ASL", &c::ASL, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "CLC", &c::CLC, &c::IMP, 2 },{ "ORA", &c::ORA, &c::ABY, 4 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "ORA", &c::ORA, &c::ABX, 4 },{ "ASL", &c::ASL, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
                    { "JSR", &c::JSR, &c::ABS, 6 },{ "AND", &c::AND, &c::IZX, 6 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "BIT", &c::BIT, &c::ZP0, 3 },{ "AND", &c::AND, &c::ZP0, 3 },{ "ROL", &c::ROL, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "PLP", &c::PLP, &c::IMP, 4 },{ "AND", &c::AND, &c::IMM, 2 },{ "ROL", &c::ROL, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "BIT", &c::BIT, &c::ABS, 4 },{ "AND", &c::AND, &c::ABS, 4 },{ "ROL", &c::ROL, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BMI", &c::BMI, &c::REL, 2 },{ "AND", &c::AND, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "AND", &c::AND, &c::ZPX, 4 },{ "ROL", &c::ROL, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "SEC", &c::SEC, &c::IMP, 2 },{ "AND", &c::AND, &c::ABY, 4 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "AND", &c::AND, &c::ABX, 4 },{ "ROL", &c::ROL, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
                    { "RTI", &c::RTI, &c::IMP, 6 },{ "EOR", &c::EOR, &c::IZX, 6 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 3 },{ "EOR", &c::EOR, &c::ZP0, 3 },{ "LSR", &c::LSR, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "PHA", &c::PHA, &c::IMP, 3 },{ "EOR", &c::EOR, &c::IMM, 2 },{ "LSR", &c::LSR, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "JMP", &c::JMP, &c::ABS, 3 },{ "EOR", &c::EOR, &c::ABS, 4 },{ "LSR", &c::LSR, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BVC", &c::BVC, &c::REL, 2 },{ "EOR", &c::EOR, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "EOR", &c::EOR, &c::ZPX, 4 },{ "LSR", &c::LSR, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "CLI", &c::CLI, &c::IMP, 2 },{ "EOR", &c::EOR, &c::ABY, 4 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "EOR", &c::EOR, &c::ABX, 4 },{ "LSR", &c::LSR, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
                    { "RTS", &c::RTS, &c::IMP, 6 },{ "ADC", &c::ADC, &c::IZX, 6 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 3 },{ "ADC", &c::ADC, &c::ZP0, 3 },{ "ROR", &c::ROR, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "PLA", &c::PLA, &c::IMP, 4 },{ "ADC", &c::ADC, &c::IMM, 2 },{ "ROR", &c::ROR, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "JMP", &c::JMP, &c::IND, 5 },{ "ADC", &c::ADC, &c::ABS, 4 },{ "ROR", &c::ROR, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BVS", &c::BVS, &c::REL, 2 },{ "ADC", &c::ADC, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "ADC", &c::ADC, &c::ZPX, 4 },{ "ROR", &c::ROR, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "SEI", &c::SEI, &c::IMP, 2 },{ "ADC", &c::ADC, &c::ABY, 4 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "ADC", &c::ADC, &c::ABX, 4 },{ "ROR", &c::ROR, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
                    { "???", &c::NOP, &c::IMP, 2 },{ "STA", &c::STA, &c::IZX, 6 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 6 },{ "STY", &c::STY, &c::ZP0, 3 },{ "STA", &c::STA, &c::ZP0, 3 },{ "STX", &c::STX, &c::ZP0, 3 },{ "???", &c::XXX, &c::IMP, 3 },{ "DEY", &c::DEY, &c::IMP, 2 },{ "???", &c::NOP, &c::IMP, 2 },{ "TXA", &c::TXA, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "STY", &c::STY, &c::ABS, 4 },{ "STA", &c::STA, &c::ABS, 4 },{ "STX", &c::STX, &c::ABS, 4 },{ "???", &c::XXX, &c::IMP, 4 },
                    { "BCC", &c::BCC, &c::REL, 2 },{ "STA", &c::STA, &c::IZY, 6 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 6 },{ "STY", &c::STY, &c::ZPX, 4 },{ "STA", &c::STA, &c::ZPX, 4 },{ "STX", &c::STX, &c::ZPY, 4 },{ "???", &c::XXX, &c::IMP, 4 },{ "TYA", &c::TYA, &c::IMP, 2 },{ "STA", &c::STA, &c::ABY, 5 },{ "TXS", &c::TXS, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 5 },{ "???", &c::NOP, &c::IMP, 5 },{ "STA", &c::STA, &c::ABX, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "???", &c::XXX, &c::IMP, 5 },
                    { "LDY", &c::LDY, &c::IMM, 2 },{ "LDA", &c::LDA, &c::IZX, 6 },{ "LDX", &c::LDX, &c::IMM, 2 },{ "???", &c::XXX, &c::IMP, 6 },{ "LDY", &c::LDY, &c::ZP0, 3 },{ "LDA", &c::LDA, &c::ZP0, 3 },{ "LDX", &c::LDX, &c::ZP0, 3 },{ "???", &c::XXX, &c::IMP, 3 },{ "TAY", &c::TAY, &c::IMP, 2 },{ "LDA", &c::LDA, &c::IMM, 2 },{ "TAX", &c::TAX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "LDY", &c::LDY, &c::ABS, 4 },{ "LDA", &c::LDA, &c::ABS, 4 },{ "LDX", &c::LDX, &c::ABS, 4 },{ "???", &c::XXX, &c::IMP, 4 },
                    { "BCS", &c::BCS, &c::REL, 2 },{ "LDA", &c::LDA, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 5 },{ "LDY", &c::LDY, &c::ZPX, 4 },{ "LDA", &c::LDA, &c::ZPX, 4 },{ "LDX", &c::LDX, &c::ZPY, 4 },{ "???", &c::XXX, &c::IMP, 4 },{ "CLV", &c::CLV, &c::IMP, 2 },{ "LDA", &c::LDA, &c::ABY, 4 },{ "TSX", &c::TSX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 4 },{ "LDY", &c::LDY, &c::ABX, 4 },{ "LDA", &c::LDA, &c::ABX, 4 },{ "LDX", &c::LDX, &c::ABY, 4 },{ "???", &c::XXX, &c::IMP, 4 },
                    { "CPY", &c::CPY, &c::IMM, 2 },{ "CMP", &c::CMP, &c::IZX, 6 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "CPY", &c::CPY, &c::ZP0, 3 },{ "CMP", &c::CMP, &c::ZP0, 3 },{ "DEC", &c::DEC, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "INY", &c::INY, &c::IMP, 2 },{ "CMP", &c::CMP, &c::IMM, 2 },{ "DEX", &c::DEX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 2 },{ "CPY", &c::CPY, &c::ABS, 4 },{ "CMP", &c::CMP, &c::ABS, 4 },{ "DEC", &c::DEC, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BNE", &c::BNE, &c::REL, 2 },{ "CMP", &c::CMP, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "CMP", &c::CMP, &c::ZPX, 4 },{ "DEC", &c::DEC, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "CLD", &c::CLD, &c::IMP, 2 },{ "CMP", &c::CMP, &c::ABY, 4 },{ "NOP", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "CMP", &c::CMP, &c::ABX, 4 },{ "DEC", &c::DEC, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
                    { "CPX", &c::CPX, &c::IMM, 2 },{ "SBC", &c::SBC, &c::IZX, 6 },{ "???", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "CPX", &c::CPX, &c::ZP0, 3 },{ "SBC", &c::SBC, &c::ZP0, 3 },{ "INC", &c::INC, &c::ZP0, 5 },{ "???", &c::XXX, &c::IMP, 5 },{ "INX", &c::INX, &c::IMP, 2 },{ "SBC", &c::SBC, &c::IMM, 2 },{ "NOP", &c::NOP, &c::IMP, 2 },{ "???", &c::SBC, &c::IMP, 2 },{ "CPX", &c::CPX, &c::ABS, 4 },{ "SBC", &c::SBC, &c::ABS, 4 },{ "INC", &c::INC, &c::ABS, 6 },{ "???", &c::XXX, &c::IMP, 6 },
                    { "BEQ", &c::BEQ, &c::REL, 2 },{ "SBC", &c::SBC, &c::IZY, 5 },{ "???", &c::XXX, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 8 },{ "???", &c::NOP, &c::IMP, 4 },{ "SBC", &c::SBC, &c::ZPX, 4 },{ "INC", &c::INC, &c::ZPX, 6 },{ "???", &c::XXX, &c::IMP, 6 },{ "SED", &c::SED, &c::IMP, 2 },{ "SBC", &c::SBC, &c::ABY, 4 },{ "NOP", &c::NOP, &c::IMP, 2 },{ "???", &c::XXX, &c::IMP, 7 },{ "???", &c::NOP, &c::IMP, 4 },{ "SBC", &c::SBC, &c::ABX, 4 },{ "INC", &c::INC, &c::ABX, 7 },{ "???", &c::XXX, &c::IMP, 7 },
            };
}


C6502::~C6502() {

}

uint8_t C6502::read(uint16_t address){
    return bus->read(address, false);
}

void C6502::write(uint16_t address, uint8_t data) {
    bus->write(address, data);
}

void C6502::clock() {
    if(cycles == 0){
        opcode = read(pc++);
        cycles = lookup[opcode].cycles;
        uint8_t extraCycle1 = (this->*lookup[opcode].addrmode)();
        uint8_t extraCycle2 = (this->*lookup[opcode].operate)();
        cycles += (extraCycle1 & extraCycle2);
    }
    cycles--;
}

void C6502::reset() {

}

void C6502::irq() {

}

void C6502::nmi() {

}

uint8_t C6502::fetch() {
    return 0;
}

uint8_t C6502::GetFlag(C6502::FLAGS6502 flag) {
    return 0;
}

void C6502::SetFlag(C6502::FLAGS6502 flag, bool v) {
    if (v) sr |= flag;
    else sr &= flag;
}


uint8_t C6502::IMM() {
    addrAbs = pc++;
    return 0;
}

uint8_t C6502::ABS() {
    uint16_t low = read(pc++);
    uint16_t high = read(pc++);
    addrAbs = (high << 8) | low;
    return 0;
}

uint8_t C6502::ZP0() {
    addrAbs = read(pc++);
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t C6502::ZPX() {
    addrAbs = (read(pc++) + x);
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t C6502::ZPY() {
    addrAbs = (read(pc++) + y);
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t C6502::ABX() {
    return 0;
}

uint8_t C6502::ABY() {
    return 0;
}

uint8_t C6502::IMP() {
    return 0;
}

uint8_t C6502::REL() {
    return 0;
}

uint8_t C6502::IZX() {
    return 0;
}

uint8_t C6502::IZY() {
    return 0;
}

uint8_t C6502::IND() {
    return 0;
}

uint8_t C6502::ADC() {
    return 0;
}

uint8_t C6502::AND() {
    return 0;
}

uint8_t C6502::ASL() {
    return 0;
}

uint8_t C6502::BBR() {
    return 0;
}

uint8_t C6502::BBS() {
    return 0;
}

uint8_t C6502::BCC() {
    return 0;
}

uint8_t C6502::BCS() {
    return 0;
}

uint8_t C6502::BEQ() {
    return 0;
}

uint8_t C6502::BIT() {
    return 0;
}

uint8_t C6502::BMI() {
    return 0;
}

uint8_t C6502::BNE() {
    return 0;
}

uint8_t C6502::BPL() {
    return 0;
}

uint8_t C6502::BRA() {
    return 0;
}

uint8_t C6502::BRK() {
    return 0;
}

uint8_t C6502::BVC() {
    return 0;
}

uint8_t C6502::BVS() {
    return 0;
}

uint8_t C6502::CLC() {
    return 0;
}

uint8_t C6502::CLD() {
    return 0;
}

uint8_t C6502::CLI() {
    return 0;
}

uint8_t C6502::CLV() {
    return 0;
}

uint8_t C6502::CMP() {
    return 0;
}

uint8_t C6502::CPX() {
    return 0;
}

uint8_t C6502::CPY() {
    return 0;
}

uint8_t C6502::DEC() {
    return 0;
}

uint8_t C6502::DEX() {
    return 0;
}

uint8_t C6502::DEY() {
    return 0;
}

uint8_t C6502::EOR() {
    return 0;
}

uint8_t C6502::INC() {
    return 0;
}

uint8_t C6502::INX() {
    return 0;
}

uint8_t C6502::INY() {
    return 0;
}

uint8_t C6502::JMP() {
    return 0;
}

uint8_t C6502::JSR() {
    return 0;
}

uint8_t C6502::LDA() {
    return 0;
}

uint8_t C6502::LDX() {
    return 0;
}

uint8_t C6502::LDY() {
    return 0;
}

uint8_t C6502::LSR() {
    return 0;
}

uint8_t C6502::NOP() {
    return 0;
}

uint8_t C6502::ORA() {
    return 0;
}

uint8_t C6502::PHA() {
    return 0;
}

uint8_t C6502::PHP() {
    return 0;
}

uint8_t C6502::PHX() {
    return 0;
}

uint8_t C6502::PHY() {
    return 0;
}

uint8_t C6502::PLA() {
    return 0;
}

uint8_t C6502::PLP() {
    return 0;
}

uint8_t C6502::PLX() {
    return 0;
}

uint8_t C6502::PLY() {
    return 0;
}

uint8_t C6502::RMB() {
    return 0;
}

uint8_t C6502::ROL() {
    return 0;
}

uint8_t C6502::ROR() {
    return 0;
}

uint8_t C6502::RTI() {
    return 0;
}

uint8_t C6502::RTS() {
    return 0;
}

uint8_t C6502::SBC() {
    return 0;
}

uint8_t C6502::SEC() {
    return 0;
}

uint8_t C6502::SED() {
    return 0;
}

uint8_t C6502::SEI() {
    return 0;
}

uint8_t C6502::SMB() {
    return 0;
}

uint8_t C6502::STA() {
    return 0;
}

uint8_t C6502::STX() {
    return 0;
}

uint8_t C6502::STY() {
    return 0;
}

uint8_t C6502::STZ() {
    return 0;
}

uint8_t C6502::TAX() {
    return 0;
}

uint8_t C6502::TAY() {
    return 0;
}

uint8_t C6502::TRB() {
    return 0;
}

uint8_t C6502::TSB() {
    return 0;
}

uint8_t C6502::TSX() {
    return 0;
}

uint8_t C6502::TXA() {
    return 0;
}

uint8_t C6502::TXS() {
    return 0;
}

uint8_t C6502::TYA() {
    return 0;
}

uint8_t C6502::XXX() {
    return 0;
}
