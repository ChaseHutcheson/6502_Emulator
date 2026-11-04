//
// Created by chasehutch on 11/3/26.
//

#ifndef INC_6502_EMULATOR_TYPES_H
#define INC_6502_EMULATOR_TYPES_H
#include <cstdint>
#include <iomanip>
#include <iostream>

namespace cpu_6502 {
    using Word = uint16_t;
    using WordSigned = int16_t;

    using Byte = uint8_t;
    using ByteSigned = int16_t;

    union Address {
        Word value;
        struct {
            Byte page;
            Byte record;
        };

        Address() = default;

        explicit Address(const Word address) : value(address) {}
        Address(const Byte page, const Byte record) : page(page), record(record) {}

        // Formats the address as a 4 character uppercase hexidecimal string prefixed with $.
        friend std::ostream& operator<<(std::ostream& os, const Address& addr) {
            os << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(4)
                << addr.value;
            return os;
        }
    };
}

#endif //INC_6502_EMULATOR_TYPES_H
