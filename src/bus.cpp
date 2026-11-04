#include "bus.h"

#include <cstdint>

Byte MemoryBus::ReadByte(const Word addr) {
    Address address(addr);
    return mem[address.value];
}

void MemoryBus::WriteByte(const Word addr, const Byte data) {
    Address address(addr);
    mem[address.value] = data;
}
Word MemoryBus::ReadWord(const Word addr) {
    Address address(addr);
    return mem[address.value] | (static_cast<Word>(mem[address.value + 1]) << 8);
}
void MemoryBus::WriteWord(const Word addr, const Word data) {
    Address address(addr);
    mem[address.value] = static_cast<uint8_t>(data);
    mem[static_cast<Word>(address.value + 1)] = static_cast<Byte>(data >> 8);
}

void MemoryBus::LoadProgram(const Word addr, const std::array<Byte, 65536> &program) {
    size_t index = 0;
    for (const auto& element : program) {
        // Wrap around when out of bounds
        mem[static_cast<uint16_t>(addr + index)] = element;
        index++;
    }
}