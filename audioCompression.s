	.file	"audioCompression.c"
	.text
	.align	2
	.global	pwlog2Reverse
	.type	pwlog2Reverse, %function
pwlog2Reverse:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
	mov	r3, r0
	strb	r3, [fp, #-13]
	ldrb	r3, [fp, #-13]
	mov	r3, r3, asl #24
	mov	r3, r3, asr #24
	cmp	r3, #0
	bge	.L2
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #128
	mov	r1, r3, asr #2
	mvn	r3, #31
	mov	r2, r3
	mov	r3, r1
	add	r3, r2, r3
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L2:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #63
	bls	.L3
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #64
	mov	r1, r3, asr #1
	mvn	r3, #63
	mov	r2, r3
	mov	r3, r1
	add	r3, r2, r3
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L3:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #31
	bls	.L4
	mvn	r3, #127
	mov	r2, r3
	ldrb	r3, [fp, #-13]
	add	r3, r2, r3
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L4:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #15
	bls	.L5
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #16
	mov	r1, r3, asl #1
	mvn	r3, #127
	mov	r2, r3
	mov	r3, r1
	add	r3, r2, r3
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L5:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #7
	bls	.L6
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #8
	mov	r3, r3, asl #2
	add	r3, r3, #96
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L6:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #3
	bls	.L7
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #4
	mov	r3, r3, asl #3
	add	r3, r3, #64
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L7:
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L8
	ldrb	r3, [fp, #-13]	@ zero_extendqisi2
	sub	r3, r3, #2
	mov	r3, r3, asl #4
	add	r3, r3, #32
	and	r3, r3, #255
	str	r3, [fp, #-20]
	b	.L1
.L8:
	mov	r3, #0
	str	r3, [fp, #-20]
.L1:
	ldr	r0, [fp, #-20]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	.size	pwlog2Reverse, .-pwlog2Reverse
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%f\n\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 20
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-32]
	mov	r2, #4
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldr	r0, [r3, #0]
	bl	atoi
	mov	r3, r0
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-32]
	and	r3, r3, #255
	mov	r0, r3
	bl	pwlog2Reverse
	mov	r3, r0
	and	r3, r3, #255
	flts	f0, r3
	stfs	f0, [fp, #-24]
	ldfs	f1, [fp, #-24]
	ldfs	f0, .L10
	fdvs	f0, f1, f0
	stfs	f0, [fp, #-28]
	ldfs	f0, [fp, #-28]
	mvfd	f0, f0
	ldr	r0, .L10+4
	stfd	f0, [sp, #-8]!
	ldmfd	sp!, {r1, r2}
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L11:
	.align	2
.L10:
	.word	1107296256
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.1"
