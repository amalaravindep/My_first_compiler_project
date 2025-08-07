	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp),%eax
	movl	%eax, %esi
	leaq .LC0(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	nop
	leave
	ret

	.globl	main
	.type	main, @function
main:
	pusht%rbp
	movq %rsp, %rbp
	movq	$2, %r8
	movq	$5, %r9
	imulq	%r8, %r9
	movq	$5, %r8
	movq	$6, %r9
	addq	%r8, %r9
	movq	$8, %r8
	subq	%r8, %r9
	movq	$7, %r8
	movq	$3, %r10
	movq	%r8,%rax
	cqo
	idivq	%r10
	movq	%rax,%r8
	movq	$2, %r10
	imulq	%r8, %r10
	addq	%r9, %r10
	movq	$5, %r8
	movq	$7, %r8
	movq	$4, %r9
	movq	%r8,%rax
	cqo
	idvq	%r9
	movq	%rdx,%r8
	movq	$3, %r9
	movq	%r8,%rax
	cqo
	idivq	%r9
	movq	%rax,%r8
	movq	$8, %r9
	addq	%r8, %r9
	movl $0, %eax
	popq %rbp
	ret
