#include "Cpu6502.h"

#include <cstdint>
#include <ios>
#include <iostream>

#include "Bus.h"

Cpu6502::Cpu6502(Bus* mem) {
    this->bus = mem;
    this->Reset();
}

void Cpu6502::pushStack_(Byte data) {
    Word effectiveAddr = 0x0100 + sp;
    bus->Write(effectiveAddr, data);
    --sp;
}

uint8_t Cpu6502::popStack_() {
    ++sp;
    Word effectiveAddr = 0x0100 + sp;
    return bus->Read(effectiveAddr);
}

void Cpu6502::Step() {
    Byte opcode = Fetch(pc);
    ++pc;
    Execute(opcode);
}

const std::array<Cpu6502::Instruction, 256>& Cpu6502::table_() {
    static const auto table = [] {
        std::array<Instruction, 256> t{};
        t.fill({.mnemonic = "???", .run = [](Cpu6502&) {}, .cycles = 0});

        t[0xA5] = {
            .mnemonic = "LDA",
            .run = [](Cpu6502& c) -> void { c.loadAccumulator_(c.addrZeroPage_()); },
            .cycles = 3,
        };
        t[0xA9] = {
            .mnemonic = "LDA",
            .run = [](Cpu6502& c) -> void { c.loadAccumulator_(c.addrImmediate_()); },
            .cycles = 2,
        };
        t[0xB5] = {
            .mnemonic = "LDA",
            .run = [](Cpu6502& c) -> void { c.loadAccumulator_(c.addrZeroPageX_()); },
            .cycles = 4,
        };
        return t;
    }();
    return table;
}

void Cpu6502::Execute(Byte opcode) {
    const Instruction& ins = table_()[opcode];
    if (ins.cycles == 0) {
        return;
    }
    page_crossed = false;
    ins.run(*this);
    clock_cycles += ins.cycles;
}

uint8_t Cpu6502::Fetch(uint16_t addr) { return bus->Read(addr); }

void Cpu6502::loadAccumulator_(Word addr) { std::cout << "RECEIVED ADDRESS: " << std::hex << addr << std::dec << ".\n"; a = bus->Read(addr); }