//
// Created by chasehutch on 11/2/26.
//

#ifndef INC_6502_EMULATOR_BUS_H
#define INC_6502_EMULATOR_BUS_H

#include <array>
#include <cstdint>

#include "types.h"

using namespace cpu_6502;

class Bus {
public:
    virtual ~Bus() = default;
    virtual Byte ReadByte(Word addr) = 0;
    virtual void WriteByte(Word addr, Byte data) = 0;
    virtual Word ReadWord(Word addr) = 0;
    virtual void WriteWord(Word addr, Word data) = 0;
};

class MemoryBus : public Bus {
    std::array<uint8_t, 65536> mem;

public:
    ~MemoryBus() override = default;
    virtual Byte ReadByte(Word addr) = 0;
    virtual void WriteByte(Word addr, Byte data) = 0;
    virtual Word ReadWord(Word addr) = 0;
    virtual void WriteWord(Word addr, Word data) = 0;
    void LoadProgram(uint16_t addr, const std::array<uint8_t, 65536> &program);
};


#endif //INC_6502_EMULATOR_BUS_H
