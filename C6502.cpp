//
// Created by Andrew Park on 2020-07-03.
//

#include "C6502.h"
#include "Bus.h"

C6502::C6502() {
    using c = C6502;
    lookup = {{ "BRK", &c::BRK, &c::IMM, 7 }};
//    {
//        { "BRK", &ar::BRK, &ar::IMM, 7 },{ "ORA", &ar::ORA, &ar::IZX, 6 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 3 },{ "ORA", &ar::ORA, &ar::ZP0, 3 },{ "ASL", &ar::ASL, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "PHP", &ar::PHP, &ar::IMP, 3 },{ "ORA", &ar::ORA, &ar::IMM, 2 },{ "ASL", &ar::ASL, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "ORA", &ar::ORA, &ar::ABS, 4 },{ "ASL", &ar::ASL, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BPL", &ar::BPL, &ar::REL, 2 },{ "ORA", &ar::ORA, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "ORA", &ar::ORA, &ar::ZPX, 4 },{ "ASL", &ar::ASL, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "CLC", &ar::CLC, &ar::IMP, 2 },{ "ORA", &ar::ORA, &ar::ABY, 4 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "ORA", &ar::ORA, &ar::ABX, 4 },{ "ASL", &ar::ASL, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//        { "JSR", &ar::JSR, &ar::ABS, 6 },{ "AND", &ar::AND, &ar::IZX, 6 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "BIT", &ar::BIT, &ar::ZP0, 3 },{ "AND", &ar::AND, &ar::ZP0, 3 },{ "ROL", &ar::ROL, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "PLP", &ar::PLP, &ar::IMP, 4 },{ "AND", &ar::AND, &ar::IMM, 2 },{ "ROL", &ar::ROL, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "BIT", &ar::BIT, &ar::ABS, 4 },{ "AND", &ar::AND, &ar::ABS, 4 },{ "ROL", &ar::ROL, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BMI", &ar::BMI, &ar::REL, 2 },{ "AND", &ar::AND, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "AND", &ar::AND, &ar::ZPX, 4 },{ "ROL", &ar::ROL, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "SEC", &ar::SEC, &ar::IMP, 2 },{ "AND", &ar::AND, &ar::ABY, 4 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "AND", &ar::AND, &ar::ABX, 4 },{ "ROL", &ar::ROL, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//        { "RTI", &ar::RTI, &ar::IMP, 6 },{ "EOR", &ar::EOR, &ar::IZX, 6 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 3 },{ "EOR", &ar::EOR, &ar::ZP0, 3 },{ "LSR", &ar::LSR, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "PHA", &ar::PHA, &ar::IMP, 3 },{ "EOR", &ar::EOR, &ar::IMM, 2 },{ "LSR", &ar::LSR, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "JMP", &ar::JMP, &ar::ABS, 3 },{ "EOR", &ar::EOR, &ar::ABS, 4 },{ "LSR", &ar::LSR, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BVC", &ar::BVC, &ar::REL, 2 },{ "EOR", &ar::EOR, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "EOR", &ar::EOR, &ar::ZPX, 4 },{ "LSR", &ar::LSR, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "CLI", &ar::CLI, &ar::IMP, 2 },{ "EOR", &ar::EOR, &ar::ABY, 4 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "EOR", &ar::EOR, &ar::ABX, 4 },{ "LSR", &ar::LSR, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//        { "RTS", &ar::RTS, &ar::IMP, 6 },{ "ADC", &ar::ADC, &ar::IZX, 6 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 3 },{ "ADC", &ar::ADC, &ar::ZP0, 3 },{ "ROR", &ar::ROR, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "PLA", &ar::PLA, &ar::IMP, 4 },{ "ADC", &ar::ADC, &ar::IMM, 2 },{ "ROR", &ar::ROR, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "JMP", &ar::JMP, &ar::IND, 5 },{ "ADC", &ar::ADC, &ar::ABS, 4 },{ "ROR", &ar::ROR, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BVS", &ar::BVS, &ar::REL, 2 },{ "ADC", &ar::ADC, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "ADC", &ar::ADC, &ar::ZPX, 4 },{ "ROR", &ar::ROR, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "SEI", &ar::SEI, &ar::IMP, 2 },{ "ADC", &ar::ADC, &ar::ABY, 4 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "ADC", &ar::ADC, &ar::ABX, 4 },{ "ROR", &ar::ROR, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//        { "???", &ar::NOP, &ar::IMP, 2 },{ "STA", &ar::STA, &ar::IZX, 6 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "STY", &ar::STY, &ar::ZP0, 3 },{ "STA", &ar::STA, &ar::ZP0, 3 },{ "STX", &ar::STX, &ar::ZP0, 3 },{ "???", &ar::XXX, &ar::IMP, 3 },{ "DEY", &ar::DEY, &ar::IMP, 2 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "TXA", &ar::TXA, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "STY", &ar::STY, &ar::ABS, 4 },{ "STA", &ar::STA, &ar::ABS, 4 },{ "STX", &ar::STX, &ar::ABS, 4 },{ "???", &ar::XXX, &ar::IMP, 4 },
//        { "BCC", &ar::BCC, &ar::REL, 2 },{ "STA", &ar::STA, &ar::IZY, 6 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "STY", &ar::STY, &ar::ZPX, 4 },{ "STA", &ar::STA, &ar::ZPX, 4 },{ "STX", &ar::STX, &ar::ZPY, 4 },{ "???", &ar::XXX, &ar::IMP, 4 },{ "TYA", &ar::TYA, &ar::IMP, 2 },{ "STA", &ar::STA, &ar::ABY, 5 },{ "TXS", &ar::TXS, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "???", &ar::NOP, &ar::IMP, 5 },{ "STA", &ar::STA, &ar::ABX, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },
//        { "LDY", &ar::LDY, &ar::IMM, 2 },{ "LDA", &ar::LDA, &ar::IZX, 6 },{ "LDX", &ar::LDX, &ar::IMM, 2 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "LDY", &ar::LDY, &ar::ZP0, 3 },{ "LDA", &ar::LDA, &ar::ZP0, 3 },{ "LDX", &ar::LDX, &ar::ZP0, 3 },{ "???", &ar::XXX, &ar::IMP, 3 },{ "TAY", &ar::TAY, &ar::IMP, 2 },{ "LDA", &ar::LDA, &ar::IMM, 2 },{ "TAX", &ar::TAX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "LDY", &ar::LDY, &ar::ABS, 4 },{ "LDA", &ar::LDA, &ar::ABS, 4 },{ "LDX", &ar::LDX, &ar::ABS, 4 },{ "???", &ar::XXX, &ar::IMP, 4 },
//        { "BCS", &ar::BCS, &ar::REL, 2 },{ "LDA", &ar::LDA, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "LDY", &ar::LDY, &ar::ZPX, 4 },{ "LDA", &ar::LDA, &ar::ZPX, 4 },{ "LDX", &ar::LDX, &ar::ZPY, 4 },{ "???", &ar::XXX, &ar::IMP, 4 },{ "CLV", &ar::CLV, &ar::IMP, 2 },{ "LDA", &ar::LDA, &ar::ABY, 4 },{ "TSX", &ar::TSX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 4 },{ "LDY", &ar::LDY, &ar::ABX, 4 },{ "LDA", &ar::LDA, &ar::ABX, 4 },{ "LDX", &ar::LDX, &ar::ABY, 4 },{ "???", &ar::XXX, &ar::IMP, 4 },
//        { "CPY", &ar::CPY, &ar::IMM, 2 },{ "CMP", &ar::CMP, &ar::IZX, 6 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "CPY", &ar::CPY, &ar::ZP0, 3 },{ "CMP", &ar::CMP, &ar::ZP0, 3 },{ "DEC", &ar::DEC, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "INY", &ar::INY, &ar::IMP, 2 },{ "CMP", &ar::CMP, &ar::IMM, 2 },{ "DEX", &ar::DEX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "CPY", &ar::CPY, &ar::ABS, 4 },{ "CMP", &ar::CMP, &ar::ABS, 4 },{ "DEC", &ar::DEC, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BNE", &ar::BNE, &ar::REL, 2 },{ "CMP", &ar::CMP, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "CMP", &ar::CMP, &ar::ZPX, 4 },{ "DEC", &ar::DEC, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "CLD", &ar::CLD, &ar::IMP, 2 },{ "CMP", &ar::CMP, &ar::ABY, 4 },{ "NOP", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "CMP", &ar::CMP, &ar::ABX, 4 },{ "DEC", &ar::DEC, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//        { "CPX", &ar::CPX, &ar::IMM, 2 },{ "SBC", &ar::SBC, &ar::IZX, 6 },{ "???", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "CPX", &ar::CPX, &ar::ZP0, 3 },{ "SBC", &ar::SBC, &ar::ZP0, 3 },{ "INC", &ar::INC, &ar::ZP0, 5 },{ "???", &ar::XXX, &ar::IMP, 5 },{ "INX", &ar::INX, &ar::IMP, 2 },{ "SBC", &ar::SBC, &ar::IMM, 2 },{ "NOP", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::SBC, &ar::IMP, 2 },{ "CPX", &ar::CPX, &ar::ABS, 4 },{ "SBC", &ar::SBC, &ar::ABS, 4 },{ "INC", &ar::INC, &ar::ABS, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },
//        { "BEQ", &ar::BEQ, &ar::REL, 2 },{ "SBC", &ar::SBC, &ar::IZY, 5 },{ "???", &ar::XXX, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 8 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "SBC", &ar::SBC, &ar::ZPX, 4 },{ "INC", &ar::INC, &ar::ZPX, 6 },{ "???", &ar::XXX, &ar::IMP, 6 },{ "SED", &ar::SED, &ar::IMP, 2 },{ "SBC", &ar::SBC, &ar::ABY, 4 },{ "NOP", &ar::NOP, &ar::IMP, 2 },{ "???", &ar::XXX, &ar::IMP, 7 },{ "???", &ar::NOP, &ar::IMP, 4 },{ "SBC", &ar::SBC, &ar::ABX, 4 },{ "INC", &ar::INC, &ar::ABX, 7 },{ "???", &ar::XXX, &ar::IMP, 7 },
//    };
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
    return 0;
}

uint8_t C6502::ZP0() {
    return 0;
}

uint8_t C6502::ZPX() {
    return 0;
}

uint8_t C6502::ZPY() {
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
