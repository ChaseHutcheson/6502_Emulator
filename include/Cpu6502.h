//
// Created by chasehutch on 11/2/26.
//

#ifndef INC_6502_EMULATOR_CPU6502_H
#define INC_6502_EMULATOR_CPU6502_H


#include <cstdint>
#include <iostream>
#include <ostream>

#include "Bus.h"

using Word = uint16_t;
using Byte = uint8_t;

class Cpu6502 {
   public:
    explicit Cpu6502(Bus* mem);

    void Step();
    Byte Fetch(uint16_t addr);
    void Execute(uint8_t opcode);

    struct CPUState {
        Word ProgramCounter;
        Byte Accumulator;
        Byte XRegister;
        Byte YRegister;
        Byte StatusRegister;
        Byte StackPointer;
    };

    void SetCPUState(CPUState& cpu_state) {
        pc = cpu_state.ProgramCounter;
        a = cpu_state.Accumulator;
        x = cpu_state.XRegister;
        y = cpu_state.YRegister;
        sr = cpu_state.StatusRegister;
        sp = cpu_state.StackPointer;
    };

    void Reset() {
        pc = 0x8000;
        a = 0;
        x = 0;
        y = 0;
        sr = 0;
        sp = 0;
        clock_cycles = 0;
    };

    // ---- HELPER FUNCTIONS ----
    [[nodiscard]] Word GetProgramCounter() const { return pc; };
    [[nodiscard]] Byte GetAccumulator() const { return a; };
    [[nodiscard]] Byte GetXRegister() const { return x; };
    [[nodiscard]] Byte GetYRegister() const { return y; };
    [[nodiscard]] Byte GetStatusRegister() const { return sr; };
    [[nodiscard]] Byte GetStackPointer() const { return sp; };
    static bool IsBit7Set(const Byte bit) { return bit & (1 << 7); };

   private:
    // Registers
    Word pc{};
    Byte a{};
    Byte x{};
    Byte y{};
    Byte sr{};
    Byte sp{};

    // Opcode Table
    struct Instruction {
        const char* mnemonic;
        void (*run)(Cpu6502&);
        Byte cycles;  // 0 = unimplemented
    };
    static const std::array<Instruction, 256>& table_();

    void pushStack_(uint8_t data);
    uint8_t popStack_();

    uint64_t clock_cycles{};
    Bus* bus = nullptr;

    bool page_crossed = false;

    // ---- HELPER FUNCTIONS ----
    void setCarryFlag_() { sr |= (1 << 0);}
    void setZeroFlag_(){ sr |= (1 << 1);}
    void setInterruptDisableFlag_(){ sr |= (1 << 2);}
    void setDecimalModeFlag_(){ sr |= (1 << 3);}
    void setOverflowFlag_(){ sr |= (1 < 6);}
    void setNegativeFlag_(){ sr |= (1 < 7);}

    void clearCarryFlag_() { sr |= ~(1 << 0);}
    void clearZeroFlag_(){ sr |= ~(1 << 1);}
    void clearInterruptDisableFlag_() { sr |= ~(1 << 2);}
    void clearDecimalModeFlag_() { sr |= ~(1 << 3);}
    void clearOverflowFlag_() { sr |= ~(1 << 6);}
    void clearNegativeFlag_() { sr |= ~(1 << 7);}

    // ---- ADDRESSING MODES ----
    Word addrImmediate_() { return pc++; }
    Word addrZeroPage_() { return bus->Read(pc++); }
    Word addrZeroPageX_() { return (bus->Read(pc++) + x) & 0xFF; }
    Word addrZeroPageY_() { return (bus->Read(pc++) + y) & 0xFF; }

    // ---- OPERATIONS ----
    // Load Operations
    void loadAccumulator_(Word addr);
    void loadXRegister_();
    void loadYRegister_();

    // Store Operations
    void storeAccumulator_();
    void storeXRegister_();
    void storeYRegister_();

    // Transfer Operations
    void transferAccumulatorToX_();
    void transferAccumulatorToY_();
    void transferXToAccumulator_();
    void transferYToAccumulator_();

    // Stack Operations
    void transferStackPointerToX_();
    void transferXToStackPointer_();
    void pushAccumulatorOntoStack_();
    void pushProccesorStatusOntoStack_();
    void pullAccumulatorFromStack_();
    void pullProccesorStatusFromStack_();

    // Logical Operations
    void logicalAnd_();
    void exclusiveOr_();
    void logicalInclusiveOr_();
    void bitTest_();

    // Arithmetic Operations
    void addWithCarry_();
    void subtractWithCarry_();
    void compareAccumulator_();
    void compareXRegister_();
    void compareYRegister_();

    // Increment and Decrement Operations
    void incrementMemoryLocation_();
    void incrementXRegister_();
    void incrementYRegister_();
    void decrementMemoryLocation_();
    void decrementXRegister_();
    void decrementYRegister_();

    // Shift Operations
    void arithmeticShiftLeft_();
    void logicalShiftRight_();
    void rotateLeft_();
    void rotateRight_();

    // Jump and Call Operations
    void jump_();
    void jumpSubroutine_();
    void returnFromSubroutine_();

    // Branch Operations
    void branchIfCarryFlagClear_();
    void branchIfCarryFlagSet_();
    void branchIfZeroFlagClear_();
    void branchIfZeroFlagSet_();
    void branchIfNegativeFlagClear_();
    void branchIfNegativeFlagSet_();
    void branchIfOverflowFlagClear_();
    void branchIfOverflowFlagSet_();

    // System Operations
    void forceInterrupt_();
    void noOperation_();
    void returnFromInterrupt_();
};


#endif //INC_6502_EMULATOR_CPU6502_H
