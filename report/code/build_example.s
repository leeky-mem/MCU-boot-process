	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"build_example.c"
	.text
	.global	global_var
	.data
	.align	2
	.type	global_var, %object
	.size	global_var, 4
global_var:
	.word	1
	.bss
	.align	2
local_var_bss:
	.space	4
	.size	local_var_bss, 4
	.data
	.align	2
	.type	local_var_data, %object
	.size	local_var_data, 4
local_var_data:
	.word	5
	.text
	.align	2
	.syntax unified
	.arm
	.type	local_sum, %function
local_sum:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r2, r3
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	local_sum, .-local_sum
	.section	.rodata
	.align	2
.LC0:
	.ascii	"The sum is: %d\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r3, .L5
	ldr	r3, [r3]
	ldr	r2, .L5+4
	ldr	r2, [r2]
	mov	r1, r2
	mov	r0, r3
	bl	local_sum
	mov	r3, r0
	ldr	r2, .L5+8
	str	r3, [r2]
	ldr	r3, .L5+8
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L5+12
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	extern_var
	.word	local_var_data
	.word	local_var_bss
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Arch Repository) 12.2.0"
