//
// Created by chasehutch on 11/2/26.
//

#ifndef INC_6502_EMULATOR_CPU6502_H
#define INC_6502_EMULATOR_CPU6502_H

#include "types.h"
#include "bus.h"

class CPU {
   public:
    explicit CPU(Bus* mem);

    void Step();

    [[nodiscard]] Byte Fetch(Address addr) const;

    void Execute(Byte opcode);

    struct CPUState {
        Word program_counter_value;
        Byte accumulator_value;
        Byte x_register_value;
        Byte y_register_value;
        Byte status_register_value;
        Byte stack_pointer_value;
    };

    void SetCPUState(CPUState& cpu_state);

    void Reset();

    // ---- HELPER FUNCTIONS ----
    [[nodiscard]] Word GetProgramCounter() const { return program_counter; };
    [[nodiscard]] Byte GetAccumulator() const { return accumulator; };
    [[nodiscard]] Byte GetXRegister() const { return x_register; };
    [[nodiscard]] Byte GetYRegister() const { return y_register; };
    [[nodiscard]] Byte GetStatusRegister() const { return status_register; };
    [[nodiscard]] Byte GetStackPointer() const { return stack_pointer; };
    static bool IsBit7Set(const Byte bit) { return bit & (1 << 7); };

   private:
    // Registers
    Word program_counter;
    Byte accumulator;
    Byte x_register;
    Byte y_register;
    Byte status_register;
    Byte stack_pointer;
    
    // Oprogram_counterode Table
    struct Instruction {
        const char* mnemonic;
        void (*run)(CPU&);
        Byte cycles;  // 0 = unimplemented
    };
    static const std::array<Instruction, 256>& table_();

    void pushStack_(uint8_t data);
    uint8_t popStack_();

    uint64_t clock_cycles{};
    Bus* bus = nullptr;

    bool page_crossed = false;

    // ---- HELPER FUNCTIONS ----
    void setCarryFlag_() { status_register |= (1 << 0);}
    void setZeroFlag_(){ status_register |= (1 << 1);}
    void setInterruptDisableFlag_(){ status_register |= (1 << 2);}
    void setDecimalModeFlag_(){ status_register |= (1 << 3);}
    void setOverflowFlag_(){ status_register |= (1 < 6);}
    void setNegativeFlag_(){ status_register |= (1 < 7);}

    void clearCarryFlag_() { status_register |= ~(1 << 0);}
    void clearZeroFlag_(){ status_register |= ~(1 << 1);}
    void clearInterruptDisableFlag_() { status_register |= ~(1 << 2);}
    void clearDecimalModeFlag_() { status_register |= ~(1 << 3);}
    void clearOverflowFlag_() { status_register |= ~(1 << 6);}
    void clearNegativeFlag_() { status_register |= ~(1 << 7);}

    Address readAddress_();


};


#endif //INC_6502_EMULATOR_CPU6502_H
