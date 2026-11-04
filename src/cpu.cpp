
#include "bus.h"
#include "cpu.h"

using namespace cpu_6502;

CPU::CPU(Bus* mem) {
    this->bus = mem;
    this->Reset();
}

void CPU::Step() {
    const Byte opcode = Fetch(static_cast<Address>(program_counter));
    ++program_counter;
    Execute(opcode);
}

Byte CPU::Fetch(const Address addr) const { return bus->ReadByte(addr); }

void CPU::pushStack_(const Byte data) {
    const Address effectiveAddr(0x0100 + stack_pointer);
    bus->WriteByte(effectiveAddr, data);
    --stack_pointer;
}

uint8_t CPU::popStack_() {
    ++stack_pointer;
    const Address effectiveAddr(0x0100 + stack_pointer);
    return bus->ReadByte(effectiveAddr);
}

Address CPU::readAddress_() {
    const Address address(bus->ReadWord(static_cast<Address>(program_counter)));
    program_counter += 2;
    return address;
}

/*
 * This is the nastiest function I have ever wrote
 */
void CPU::Execute(const Byte opcode) {
    switch (opcode) {

        // LDA - Load Accumulator
        // Immediate
        case 0xA9: {
            Byte operand = bus->ReadByte(static_cast<Address>(program_counter++));
            accumulator = operand;
            clock_cycles += 2;
            break;
        }
        // Zero-Page
        case 0xA5: {
            Byte operand = bus->ReadByte(static_cast<Address>(program_counter++));
            Byte data = bus->ReadByte(static_cast<Address>(operand));
            accumulator = data;
            clock_cycles += 3;
            break;
        }
        // Zero-Page,X
        case 0xB5: {
            Byte operand = bus->ReadByte(static_cast<Address>(program_counter++));
            Byte data = bus->ReadByte(static_cast<Address>(static_cast<uint8_t>(operand + x_register)));
            accumulator = data;
            clock_cycles += 4;
            break;
        }
        // Absolute
        case 0xAD: {
            Address address = readAddress_();
            Byte data = bus->ReadByte(address);
            accumulator = data;
            clock_cycles += 4;
        }
        // Absolute,X
        case 0xBD: {
            uint16_t address = readAddress_();
            Byte data = bus->ReadByte(Address(static_cast<uint16_t>(address) + x_register));
            accumulator = data;
            clock_cycles += 4;
        }
        case 0xB9: {
        }
        case 0xA1: {
        }
        case 0xB1: {
        }


        default:
            std::cout << "Error - Unimplemented Opcode";
            break;
    }
}