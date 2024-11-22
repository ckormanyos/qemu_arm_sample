qemu_arm_sample
==================

<p align="center">
    <a href="https://github.com/ckormanyos/qemu_arm_sample/actions">
        <img src="https://github.com/ckormanyos/qemu_arm_sample/actions/workflows/qemu_arm_sample.yml/badge.svg" alt="QEMU"></a>
    <a href="https://github.com/ckormanyos/qemu_arm_sample/blob/master/LICENSE">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://godbolt.org/z/aTvWrGEz1" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

`ckormanyos/qemu_arm_sample` provides a fully-functioning benchmark
program executed in QEMU simulating a bare-metal embedded
ARM(R) Cortex(R) M4F device. The simulated device is
the STMicroelectronics(R) STM32F429 ARM(R) Cortex(R)-M4F.

The
[benchmark program](https://github.com/ckormanyos/qemu_arm_sample/blob/main/ref_app/src/app/benchmark/app_benchmark_crc.cpp)
executes a 32-bit CRC calculation and verifies the expected result in QEMU.
GDB is used as a debugger to verify the program result in the QEMU run.
The debugger is controlled via commands in the
[GDB script](https://github.com/ckormanyos/qemu_arm_sample/blob/main/ref_app/target/build/test_app_benchmarks_emulator.gdb).

CI runs on `ubuntu-latest` in GHA.
