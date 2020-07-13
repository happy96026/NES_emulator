//
// Created by Andrew Park on 2020-07-03.
// http://www.obelisk.me.uk/6502/reference.html
//

#include "C6502.h"
#include "Bus.h"

C6502::C6502() {
    using c = C6502;
    lookup =
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

// Interrupts

void C6502::reset() {
    ar = 0;
    x = 0;
    y = 0;
    sp = 0xFD;
    sr = 0x00 | U;

    addrAbs = 0xFFFC;
    uint16_t low = read(addrAbs + 0);
    uint16_t high = read(addrAbs + 1);

    pc = (high << 8) | low;

    addrRel = 0x0000;
    addrAbs = 0x0000;
    fetched = 0x00;

    cycles = 8;
}

void C6502::irq() {
    if (GetFlag(I) == 0){
        write(0x0100 + sp--, (pc >> 8) & 0x00FF);
        write(0x0100 + sp--, pc & 0x00FF);

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        write(0x0100 + sp--, sr);

        addrAbs = 0xFFFE;
        uint16_t low = read(addrAbs + 0);
        uint16_t high = read(addrAbs + 1);
        pc = (high << 8) | low;

        cycles = 7;
    }

}

void C6502::nmi() {
    write(0x0100 + sp--, (pc >> 8) & 0x00FF);
    write(0x0100 + sp--, pc & 0x00FF);

    SetFlag(B, 0);
    SetFlag(U, 1);
    SetFlag(I, 1);
    write(0x0100 + sp--, sr);

    addrAbs = 0xFFFA;
    uint16_t low = read(addrAbs + 0);
    uint16_t high = read(addrAbs + 1);
    pc = (high << 8) | low;

    cycles = 8;
}

uint8_t C6502::fetch() {
    if(!(lookup[opcode].addrmode == &C6502::IMP)){
        fetched = read(addrAbs);
    }
    return fetched;
}

uint8_t C6502::GetFlag(C6502::FLAGS6502 flag) {
    return 0;
}

void C6502::SetFlag(C6502::FLAGS6502 flag, bool v) {
    if (v) sr |= flag;
    else sr &= flag;
}

// Addressing Modes

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
    uint16_t low = read(pc++);
    uint16_t high = read(pc++);

    addrAbs = (high<< 8) | low;
    addrAbs += x;

    if ((addrAbs & 0xFF00) != (high << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

uint8_t C6502::ABY() {
    uint16_t low = read(pc++);
    uint16_t high = read(pc++);

    addrAbs += (high << 8) | low;
    addrAbs += y;

    if ((addrAbs % 0xFF00) != (high << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

uint8_t C6502::IMP() {
    fetched = ar;
    return 0;
}

uint8_t C6502::REL() {
    addrRel = read(pc++);
    if(addrRel & 0x80){
        addrRel |= 0xFF00;
    }
    return 0;
}

uint8_t C6502::IZX() {
    uint16_t t = read(pc++);

    uint16_t low = read((uint16_t)(t+(uint16_t)x) & 0x00FF);
    uint16_t high = read((uint16_t)(t+(uint16_t)x+1) & 0x00FF);

    addrAbs = (high << 8) | low;

    return 0;
}

uint8_t C6502::IZY() {
    uint16_t t = read(pc++);

    uint16_t low = read(t & 0x00FF);
    uint16_t high = read((t+1) & 0x00FF);

    addrAbs = (high << 8) | low;
    addrAbs += y;

    if((addrAbs & 0x00FF) != (high << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

uint8_t C6502::IND() {
    uint16_t ptrLow = read(pc++);
    uint16_t ptrHigh = read(pc++);

    uint16_t ptr = (ptrHigh << 8) | ptrLow;

    if(ptrLow == 0x00FF){ // Simulating page boundary hardware bug
        addrAbs = (read(ptr & 0xFF00) << 8) | read(ptr+0);
    }
    else{
        addrAbs = (read(ptr+1) << 8) | read(ptr+0);
    }

    return 0;
}

// Opcodes

uint8_t C6502::ADC() {
    fetch();

    // Check for Overflow
    uint16_t tmp = (uint16_t)ar + (uint16_t)fetched + (uint16_t)GetFlag(C);
    SetFlag(C, tmp > 255);
    SetFlag(Z, (tmp & 0x00FF) == 0);
    SetFlag(N, tmp & 0x80);
    SetFlag(V, (~((uint16_t)ar ^ (uint16_t)fetched) & ((uint16_t)ar ^ (uint16_t)tmp)) & 0x0080);
    ar = tmp & 0x00FF;
    return 1;
}

// Bitwise AND
uint8_t C6502::AND() {
    fetch();
    ar = ar & fetched;
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 1;
}

// Arithmetic Shift Left
uint8_t C6502::ASL() {
    fetch();
    ar = ar & fetched;
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 0;
}

uint8_t C6502::BBR() {
    return 0;
}

uint8_t C6502::BBS() {
    return 0;
}

// Branch if Carry Clear
uint8_t C6502::BCC() {
    if(GetFlag(C) == 0){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

/* From data sheet
 * Add 1 to N if branch occurs to same page
 * Add 2 to N if branch occurs to different page
 */
// Branch if Carry Set
uint8_t C6502::BCS() {
    if(GetFlag(C) == 1){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

// Branch if Equal
uint8_t C6502::BEQ() {
    if(GetFlag(Z) == 1){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}


uint8_t C6502::BIT() {
    fetch();
    uint16_t tmp = ar & fetched;
    SetFlag(Z, (tmp & 0x00FF) == 0x00);
    SetFlag(N, fetched & (1 << 7));
    SetFlag(V, fetched & (1 << 6));
    return 0;
}

// Branch if Negative
uint8_t C6502::BMI() {
    if(GetFlag(N) == 1){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

// Branch if Not Equal
uint8_t C6502::BNE() {
    if(GetFlag(Z) == 0){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

// Branch if Positive
uint8_t C6502::BPL() {
    if(GetFlag(N) == 0){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

uint8_t C6502::BRA() {
    return 0;
}

// Break
uint8_t C6502::BRK() {
    pc++;

    SetFlag(I, 1);
    write(0x0100 + sp--, (pc >> 8) & 0x00FF);
    write(0x0100 + sp--, pc & 0x00FF);

    SetFlag(B, 1);
    write(0x0100 + sp--, sr);
    SetFlag(B, 0);

    pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
    return 0;
}

// Branch if Overflow Clear
uint8_t C6502::BVC() {
    if(GetFlag(V) == 0){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

// Branch if Overflow Set
uint8_t C6502::BVS() {
    if(GetFlag(V) == 1){
        cycles++;
        addrAbs = pc + addrRel;
        if((addrAbs & 0xFF00) != (pc & 0xFF00)){
            cycles++;
        }
        pc = addrAbs;
    }
    return 0;
}

// Clear Carry Flag
uint8_t C6502::CLC() {
    SetFlag(C, false);
    return 0;
}

// Clear Decimal Flag
uint8_t C6502::CLD() {
    SetFlag(D, false);
    return 0;
}

// Clear Disable-Interrupt Flag (Disable Interrupt)
uint8_t C6502::CLI() {
    SetFlag(I, false);
    return 0;
}

// Clear Overflow Flag
uint8_t C6502::CLV() {
    SetFlag(V, false);
    return 0;
}

// Compare Accumulator
uint8_t C6502::CMP() {
    fetch();
    uint16_t tmp = (uint16_t)ar - (uint16_t)fetched;
    SetFlag(C, ar >= fetched);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    return 1;
}

// Compare X Register
uint8_t C6502::CPX() {
    fetch();
    uint16_t tmp = (uint16_t)x - (uint16_t)fetched;
    SetFlag(C, x >= fetched);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    return 0;
}

// Compare Y Register
uint8_t C6502::CPY() {
    fetch();
    uint16_t tmp = (uint16_t)y - (uint16_t)fetched;
    SetFlag(C, y >= fetched);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    return 0;
}

// Decrement Value at Memory Location
uint8_t C6502::DEC() {
    fetch();
    uint16_t tmp = fetched - 1;
    write(addrAbs, tmp & 0x00FF);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    return 0;
}

// Decrement Value at X Register
uint8_t C6502::DEX() {
    x--;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Decrement Value at Y Register
uint8_t C6502::DEY() {
    y--;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);
    return 0;
}

// Bitwise Logic OR
uint8_t C6502::EOR() {
    fetch();
    ar = ar & fetched;
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 0;
}

// Increment Value at Memory Location
uint8_t C6502::INC() {
    fetch();
    uint16_t tmp = fetched + 1;
    write(addrAbs, tmp & 0x00FF);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    return 0;
}

// Increment Value at X Register
uint8_t C6502::INX() {
    x++;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Increment Value at Y Register
uint8_t C6502::INY() {
    y++;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);
    return 0;
}

// Jump to Location
uint8_t C6502::JMP() {
    pc = addrAbs;
    return 0;
}

// Jump to Subroutine
uint8_t C6502::JSR() {
    pc--;

    write(0x0100 + sp--, (pc >> 8) & 0x00FF);
    write(0x0100 + sp--, pc & 0x00FF);

    pc = addrAbs;
    return 0;
}

// Load Accumulator
uint8_t C6502::LDA() {
    fetch();
    ar = fetched;
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 1;
}

// Load X Register
uint8_t C6502::LDX() {
    fetch();
    x = fetched;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Load Y Register
uint8_t C6502::LDY() {
    fetch();
    y = fetched;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);
    return 0;
}

// Logical Shift Right
uint8_t C6502::LSR() {
    fetch();
    SetFlag(C, fetched & 0x0001);
    uint16_t tmp = fetched >> 1;
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);

    if(lookup[opcode].addrmode == &C6502::IMP){
        ar = tmp & 0x00FF;
    }
    else{
        write(addrAbs, tmp & 0x00FF);
    }
    return 0;
}

// No Operation
uint8_t C6502::NOP() {
    if(opcode == 0xFC){
        return 1;
    }
    return 0;
}

// Logical Inclusive OR
uint8_t C6502::ORA() {
    fetch();
    ar = ar | fetched;
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 0;
}

// Push Accumulator
uint8_t C6502::PHA() {
    write(0x0100 + sp, ar);
    sp--;
    return 0;
}

// Push Processor Status
uint8_t C6502::PHP() {
    write(0x0100 + sp--, sr | B | U);
    SetFlag(B, 0);
    SetFlag(U, 0);
    return 0;
}

uint8_t C6502::PHX() {
    return 0;
}

uint8_t C6502::PHY() {
    return 0;
}

// Pull Accumulator
uint8_t C6502::PLA() {
    sp++;
    ar = read(0x0100 + sp);
    SetFlag(Z, ar == 0x00);
    SetFlag(N, ar & 0x80);
    return 0;
}

// Pull Processor Status
uint8_t C6502::PLP() {
    sp++;
    sr = read(0x00 + sp);
    SetFlag(U, 1);
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

// Rotate Left
uint8_t C6502::ROL() {
    fetch();
    uint16_t tmp = (uint16_t)(fetched << 1) | GetFlag(C);
    SetFlag(C, tmp & 0xFF00);
    SetFlag(Z, (tmp & 0x00FF) == 0x0000);
    SetFlag(N, tmp & 0x0080);
    if(lookup[opcode].addrmode == &C6502::IMP){
        ar = tmp & 0x00FF;
    }
    else{
        write(addrAbs, tmp & 0x00FF);
    }
    return 0;
}

// Rotate Right
uint8_t C6502::ROR() {
    fetch();
    uint16_t tmp = (uint16_t)(fetched << 7) | (fetched >> 1);
    SetFlag(C, fetched & 0x01);
    SetFlag(Z, (tmp & 0x00FF) == 0x00);
    SetFlag(N, tmp & 0x0080);
    if(lookup[opcode].addrmode == &C6502::IMP){
        ar = tmp & 0x00FF;
    }
    else{
        write(addrAbs, tmp & 0x00FF);
    }
    return 0;
}

// Return from Interrupt
uint8_t C6502::RTI() {
    sr = read(0x0100 + ++sp);
    sr &= ~B;
    sr &= ~U;

    pc = (uint16_t)read(0x0100 + ++sp);
    pc |= (uint16_t)read(0x0100 + ++sp) << 8;
    return 0;
}

// Return from Subroutine
uint8_t C6502::RTS() {
    sp++;
    pc = (uint16_t)read(0x0100 + sp);
    sp++;
    pc |= (uint16_t)read(0x0100 + sp) << 8;
    pc++;
    return 0;
}

// Subtract with Carry
uint8_t C6502::SBC() {
    fetch();

    uint16_t value = (((uint16_t)fetched) ^ 0x00FF);

    uint16_t tmp = (uint16_t)ar + value + (uint16_t)GetFlag(C);
    SetFlag(C, tmp > 255);
    SetFlag(Z, (tmp & 0x00FF) == 0);
    SetFlag(N, tmp & 0x80);
    SetFlag(V, (~((uint16_t)ar ^ value) & ((uint16_t)ar ^ (uint16_t)tmp)) & 0x0080);
    ar = tmp & 0x00FF;
    return 0;
}

// Set Carry Flag
uint8_t C6502::SEC() {
    SetFlag(C, 1);
    return 0;
}

// Set Decimal Flag
uint8_t C6502::SED() {
    SetFlag(D, 1);
    return 0;
}

// Set Interrupt Disable
uint8_t C6502::SEI() {
    SetFlag(I, 1);
    return 0;
}

uint8_t C6502::SMB() {
    return 0;
}

// Store Accumulator
uint8_t C6502::STA() {
    write(addrAbs, ar);
    return 0;
}

// Store X Register
uint8_t C6502::STX() {
    write(addrAbs, x);
    return 0;
}

// Store Y Register
uint8_t C6502::STY() {
    write(addrAbs, y);
    return 0;
}

uint8_t C6502::STZ() {
    return 0;
}

// Transfer Accumulator to X
uint8_t C6502::TAX() {
    x = ar;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Transfer Accumulator to Y
uint8_t C6502::TAY() {
    y = ar;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y == 0x80);
    return 0;
}

uint8_t C6502::TRB() {
    return 0;
}

uint8_t C6502::TSB() {
    return 0;
}

// Transfer Stack Pointer to X
uint8_t C6502::TSX() {
    x = sp;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Transfer X to Accumulator
uint8_t C6502::TXA() {
    ar = x;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);
    return 0;
}

// Transfer X to Stack Pointer
uint8_t C6502::TXS() {
    sp = x;
    return 0;
}

// Transfer Y to Accumulator
uint8_t C6502::TYA() {
    ar = y;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);
    return 0;
}

uint8_t C6502::XXX() {
    return 0;
}
