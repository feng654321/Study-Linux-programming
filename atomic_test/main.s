	.file	"main.c"
	.text
	.section	.text._ZNSt6thread24_M_thread_deps_never_runEv,"axG",@progbits,_ZNSt6thread24_M_thread_deps_never_runEv,comdat
	.p2align 4
	.weak	_ZNSt6thread24_M_thread_deps_never_runEv
	.type	_ZNSt6thread24_M_thread_deps_never_runEv, @function
_ZNSt6thread24_M_thread_deps_never_runEv:
.LFB838:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE838:
	.size	_ZNSt6thread24_M_thread_deps_never_runEv, .-_ZNSt6thread24_M_thread_deps_never_runEv
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv:
.LFB1363:
	.cfi_startproc
	jmp	*8(%rdi)
	.cfi_endproc
.LFE1363:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.text
	.p2align 4
	.globl	_Z7thread1v
	.type	_Z7thread1v, @function
_Z7thread1v:
.LFB1165:
	.cfi_startproc
	movl	$1, y(%rip)
	movl	$1, x(%rip)
	ret
	.cfi_endproc
.LFE1165:
	.size	_Z7thread1v, .-_Z7thread1v
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev:
.LFB1360:
	.cfi_startproc
	movq	$_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE+16, (%rdi)
	jmp	_ZNSt6thread6_StateD2Ev
	.cfi_endproc
.LFE1360:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev
	.set	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev:
.LFB1362:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	$_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE+16, (%rdi)
	call	_ZNSt6thread6_StateD2Ev
	movq	%rbx, %rdi
	movl	$16, %esi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm
	.cfi_endproc
.LFE1362:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"void thread2()"
.LC1:
	.string	"main.c"
.LC2:
	.string	"y == 1"
	.text
	.p2align 4
	.globl	_Z7thread2v
	.type	_Z7thread2v, @function
_Z7thread2v:
.LFB1166:
	.cfi_startproc
	movl	x(%rip), %eax
	cmpl	$1, %eax
	je	.L13
.L8:
	ret
	.p2align 4,,10
	.p2align 3
.L13:
	cmpl	$1, y(%rip)
	je	.L8
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$.LC0, %ecx
	movl	$15, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
	.cfi_endproc
.LFE1166:
	.size	_Z7thread2v, .-_Z7thread2v
	.section	.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_,"axG",@progbits,_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.type	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_, @function
_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_:
.LFB1273:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1273
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	$0, (%rdi)
	movl	$16, %edi
.LEHB0:
	call	_Znwm
.LEHE0:
	movl	$_ZNSt6thread24_M_thread_deps_never_runEv, %edx
	leaq	8(%rsp), %rsi
	movq	%rbx, %rdi
	movq	$_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE+16, (%rax)
	movq	%rbp, 8(%rax)
	movq	%rax, 8(%rsp)
.LEHB1:
	call	_ZNSt6thread15_M_start_threadESt10unique_ptrINS_6_StateESt14default_deleteIS1_EEPFvvE
.LEHE1:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L14
	movq	(%rdi), %rax
	call	*8(%rax)
.L14:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L18:
	.cfi_restore_state
	movq	%rax, %rbx
.L16:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L17
	movq	(%rdi), %rax
	call	*8(%rax)
.L17:
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1273:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_,"aG",@progbits,_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_,comdat
.LLSDA1273:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1273-.LLSDACSB1273
.LLSDACSB1273:
	.uleb128 .LEHB0-.LFB1273
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1273
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L18-.LFB1273
	.uleb128 0
	.uleb128 .LEHB2-.LFB1273
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1273:
	.section	.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_,"axG",@progbits,_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_,comdat
	.size	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_, .-_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.weak	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_
	.set	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_,_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1167:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1167
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$_Z7thread1v, %esi
	movq	%rsp, %rdi
.LEHB3:
	call	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_
.LEHE3:
	movl	$_Z7thread2v, %esi
	leaq	8(%rsp), %rdi
.LEHB4:
	call	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_
.LEHE4:
	movq	%rsp, %rdi
.LEHB5:
	call	_ZNSt6thread4joinEv
	leaq	8(%rsp), %rdi
	call	_ZNSt6thread4joinEv
.LEHE5:
	cmpq	$0, 8(%rsp)
	jne	.L28
	cmpq	$0, (%rsp)
	jne	.L28
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L28:
	.cfi_restore_state
	call	_ZSt9terminatev
.L32:
	movq	%rax, %rdi
	jmp	.L29
.L31:
	movq	%rax, %rdi
	jmp	.L30
	.section	.gcc_except_table,"a",@progbits
.LLSDA1167:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1167-.LLSDACSB1167
.LLSDACSB1167:
	.uleb128 .LEHB3-.LFB1167
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB1167
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L31-.LFB1167
	.uleb128 0
	.uleb128 .LEHB5-.LFB1167
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L32-.LFB1167
	.uleb128 0
.LLSDACSE1167:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC1167
	.type	main.cold, @function
main.cold:
.LFSB1167:
.L29:
	.cfi_def_cfa_offset 32
	cmpq	$0, 8(%rsp)
	jne	.L28
.L30:
	cmpq	$0, (%rsp)
	jne	.L28
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
	.cfi_endproc
.LFE1167:
	.section	.gcc_except_table
.LLSDAC1167:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC1167-.LLSDACSBC1167
.LLSDACSBC1167:
	.uleb128 .LEHB6-.LCOLDB3
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSEC1167:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
	.weak	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.rodata._ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"aG",@progbits,_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 32
	.type	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 59
_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.string	"NSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE"
	.weak	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.rodata._ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"aG",@progbits,_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 8
	.type	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 24
_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.quad	_ZTINSt6thread6_StateE
	.weak	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.rodata._ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"aG",@progbits,_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 8
	.type	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 40
_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.quad	0
	.quad	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.globl	x
	.bss
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.zero	4
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.zero	4
	.ident	"GCC: (GNU) 13.1.1 20230511 (Red Hat 13.1.1-2)"
	.section	.note.GNU-stack,"",@progbits
