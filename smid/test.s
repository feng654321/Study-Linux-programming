	.file	"test.c"
	.text
	.p2align 4
	.globl	add_arrays
	.type	add_arrays, @function
add_arrays:
.LFB22:
	.cfi_startproc
	testl	%ecx, %ecx
	jle	.L1
	movslq	%ecx, %rcx
	xorl	%eax, %eax
	salq	$2, %rcx
	.p2align 4,,10
	.p2align 3
.L3:
	movss	(%rdi,%rax), %xmm0
	addss	(%rsi,%rax), %xmm0
	movss	%xmm0, (%rdx,%rax)
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE22:
	.size	add_arrays, .-add_arrays
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movl	$64000000, %edi
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	call	malloc
	movl	$64000000, %edi
	movq	%rax, %r12
	call	malloc
	movl	$64000000, %edi
	movq	%rax, %rbp
	call	malloc
	movdqa	.LC0(%rip), %xmm1
	movdqa	.LC1(%rip), %xmm2
	movq	%rax, %r13
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L7:
	movdqa	%xmm1, %xmm0
	paddd	%xmm2, %xmm1
	cvtdq2ps	%xmm0, %xmm0
	movups	%xmm0, (%r12,%rax)
	addps	%xmm0, %xmm0
	movups	%xmm0, 0(%rbp,%rax)
	addq	$16, %rax
	cmpq	$64000000, %rax
	jne	.L7
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L8:
	movups	(%r12,%rax), %xmm0
	movups	0(%rbp,%rax), %xmm3
	addps	%xmm3, %xmm0
	movups	%xmm0, 0(%r13,%rax)
	addq	$16, %rax
	cmpq	$64000000, %rax
	jne	.L8
	movq	%r13, %rbx
	leaq	40(%r13), %r14
	.p2align 4,,10
	.p2align 3
.L9:
	pxor	%xmm0, %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	addq	$4, %rbx
	cvtss2sd	-4(%rbx), %xmm0
	call	printf
	cmpq	%rbx, %r14
	jne	.L9
	movq	%r12, %rdi
	call	free
	movq	%rbp, %rdi
	call	free
	movq	%r13, %rdi
	call	free
	popq	%rbx
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.ident	"GCC: (GNU) 13.1.1 20230511 (Red Hat 13.1.1-2)"
	.section	.note.GNU-stack,"",@progbits
