# arm 汇编学习

ldr = Load Word
ldrh = Load unsigned Half Word
ldrsh = Load signed Half Word
ldrb = Load unsigned Byte
ldrsb = Load signed Byte

str = Store Word
strh = Store unsigned Half Word
strsh = Store signed Half Word
strb = Store unsigned Byte
strsb = Store signed Byte


Endianness

There are two basic ways of viewing bytes in memory: Little-Endian(LE) or Big-Endian(BE). The difference is the byte-order in which each byte of an object is stored in memory. On little-endian machines like Intel x86, the least-significant-byte is
stored at the lowest address(the address closetst to zero). On big-endian machines the most-significant-byte is stored at the lowest address. The ARM architecture was little-endian before version 3, since then it is big-endian, which means this it
features a setting which allows for switchable endianness. On ARMv6 for example, instructions are fixed little-endian and data accesses can be either little-endian or big-endian as controlled by bit 9, the E bit, of the Program Status Register(CPSR)


ARM Registers

The amount of registers depends on the ARM version. According to the ARM Reference Manual, there are 30 general-purpose 32-bit registers, with the exception of ARMv6-M and ARMv7-M based processors. The first 16 registers are accessible in user-level
mode, the additional registers are available in privileged software execution(with the execption of ARMv6-M and ARMv7-M). In this tutorial series we will work with the registers that are accessible in any privileged mode: r0-15. These 16 registers
can be split into two groups: general purpose and special purpose registers.

r0-r11: general purpose registers.

r12-r15 and CPSR: special purpose registers.

r13 SP(Stack Pointer):

r14 LR(Link Register):

r15 RC(Progame Counter):