.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# vi1 is kept at -12(%rbp)
	# vi2 is kept at -16(%rbp)
	# vi3 is kept at -20(%rbp)

	# vi1 = pi1 + vi2
	movl %edi, %eax
	movl -16(%rbp), %ecx
	addl %ecx, %eax
	movl %eax, -12(%rbp)

	# vi2 = vi1 * ci-5
	movl -12(%rbp), %eax
	movl $-5, %ecx
	imull %ecx, %eax
	movl %eax, -16(%rbp)

	# vi3 = vi1 / vi2
	movl -12(%rbp), %eax
	movl -16(%rbp), %ecx
	cltd
	idivl %ecx
	movl %eax, -20(%rbp)

	# vi1 = vi1 - vi1
	movl -12(%rbp), %eax
	movl -12(%rbp), %ecx
	subl %ecx, %eax
	movl %eax, -12(%rbp)

	# return vi1
	movl -12(%rbp), %eax

return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# if needed %rdx is saved at -24(%rbp) before function call
	# vi1 is kept at -28(%rbp)
	# vi2 is kept at -32(%rbp)

	# vi1 = vi2 / pi3
	movl -32(%rbp), %eax
	movl %edx, %ecx
	movq %rdx, %r8
	cltd
	idivl %ecx
	movq %r8, %rdx
	movl %eax, -28(%rbp)

	# return vi1
	movl -28(%rbp), %eax

return_f2:
	leave
	ret


