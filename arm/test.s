	.section .text
	.global _start
	.arm
	
_start:
	mov r0, #2		@ stdout
	adr r1, label		@ address of string
	mov r2, #14 		@ Size of string
	mov r7, #4		@ syscall number for 'write'
	svc #0			@ invoke syscall

_exit:
	mov r7, #1		@ syscall number for 'exit'
	svc #0			@ invoke syscall

label:
	.string "Hello World!\n"		@ string
	
