//
// Created by chasehutch on 11/2/26.
//

#ifndef INC_6502_EMULATOR_BUS_H
#define INC_6502_EMULATOR_BUS_H

#include <array>
#include <cstddef>
#include <cstdint>

class Bus {
public:
    virtual ~Bus() = default;
    virtual uint8_t Read(uint16_t addr) = 0;
    virtual void Write(uint16_t addr, uint8_t data) = 0;
};

class MemoryBus : public Bus {
    std::array<uint8_t, 65536> mem;

public:
    ~MemoryBus() override = default;
    uint8_t Read(uint16_t addr) override;
    void Write(uint16_t addr, uint8_t data) override;
    void LoadProgram(uint16_t addr, const std::array<uint8_t, 65536> &program);
};


#endif //INC_6502_EMULATOR_BUS_H
