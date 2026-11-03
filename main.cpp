#include <gtest/gtest.h>

#include "Bus.h"
#include "Cpu6502.h"

class LoadAccumulatorTest : public ::testing::Test {
    protected:
    MemoryBus mem{};
    Cpu6502 cpu{&mem};

    void SetUp() override {
        Cpu6502::CPUState cpuState{
            .ProgramCounter = 0x8000,
            .Accumulator = 0,
            .XRegister = 0,
            .YRegister = 0,
            .StatusRegister = 0,
            .StackPointer = 0,
        };

        cpu.SetCPUState(cpuState);
    };
};

TEST_F(LoadAccumulatorTest, Immediate) {
    mem.LoadProgram(0x8000, {0xA9, 0x01});

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x01);
    EXPECT_EQ(cpu.GetProgramCounter(), 0x8002);

};

TEST_F(LoadAccumulatorTest, ZeroPage) {
    mem.LoadProgram(0x8000, {0xA5, 0xFF});
    mem.Write(0x00FF, 0x01);

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x01);
    EXPECT_EQ(cpu.GetProgramCounter(), 0x8002);
};

TEST_F(LoadAccumulatorTest, ZeroPageX) {
    Cpu6502::CPUState cpuState{
        .ProgramCounter = 0x8000,
        .Accumulator = 0,
        .XRegister = 0x0F,
        .YRegister = 0,
        .StatusRegister = 0,
        .StackPointer = 0,
    };

    cpu.SetCPUState(cpuState);
    mem.LoadProgram(0x8000, {0xB5, 0x80});
    mem.Write(0x8F, 0x01);

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x01);
    EXPECT_EQ(cpu.GetProgramCounter(), 0x8002);
};
