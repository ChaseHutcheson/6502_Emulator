#include "Bus.h"

#include <cstdint>

uint8_t MemoryBus::Read(const uint16_t addr) { return mem[addr]; }
void MemoryBus::Write(const uint16_t addr, const uint8_t data) { mem[addr] = data; }

void MemoryBus::LoadProgram(const uint16_t addr, const std::array<uint8_t, 65536> &program) {
    size_t index = 0;
    for (const auto& element : program) {
        // Wrap around when out of bounds
        mem[static_cast<uint16_t>(addr + index)] = element;
        index++;
    }
}