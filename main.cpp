#include <gtest/gtest.h>

#include "bus.h"
#include "cpu.h"

class LoadAccumulatorTest : public ::testing::Test {
    protected:
    MemoryBus mem;
    CPU cpu{&mem};

    void SetUp() override {
        CPU::CPUState cpuState{
            .program_counter_value = 0x8000,
            .accumulator_value = 0x00,
            .x_register_value = 0x00,
            .y_register_value = 0x00,
            .status_register_value = 0x00,
            .stack_pointer_value = 0x00,
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
    CPU::CPUState cpuState{
        .program_counter_value = 0x8000,
        .accumulator_value = 0x00,
        .x_register_value = 0x0F,
        .y_register_value = 0x00,
        .status_register_value = 0x00,
        .stack_pointer_value = 0x00,
    };

    cpu.SetCPUState(cpuState);
    mem.LoadProgram(0x8000, {0xB5, 0x80});
    mem.Write(0x8F, 0x01);

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x01);
    EXPECT_EQ(cpu.GetProgramCounter(), 0x8002);
};
