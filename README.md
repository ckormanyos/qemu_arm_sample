qemu_arm_sample
==================

<p align="center">
    <a href="https://github.com/ckormanyos/qemu_arm_sample/actions">
        <img src="https://github.com/ckormanyos/qemu_arm_sample/actions/workflows/qemu_arm_sample.yml/badge.svg" alt="QEMU"></a>
    <a href="https://github.com/ckormanyos/qemu_arm_sample/blob/master/LICENSE">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://godbolt.org/z/ve74r8za8" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

`ckormanyos/qemu_arm_sample` provides a fully-functioning sample
of a benchmark program executed in QEMU simulating a bare-metal
embedded ARM(R) Cortex(R) M4F device.

The simulated device is the STMicroelectronics(R) STM32F429 ARM(R) Cortex(R) M4F.
The benchmark program executes a 32-bit CRC calculation
and verifies the expected result in QEMU.

CI runs on `ubuntu-latest` in GHA.
