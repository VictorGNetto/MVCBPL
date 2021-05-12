.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# vi1 is kept at -4(%rbp)

	# vi1 = ci123
	movl $123, -4(%rbp)

	# return ci0
	movl $0, %eax

return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# vi1 is kept at -4(%rbp)
	# vi2 is kept at -8(%rbp)

	# vi1 = vi2
	movl -8(%rbp), %eax
	movl %eax, -4(%rbp)

	# return ci0
	movl $0, %eax

return_f2:
	leave
	ret


.globl f3
f3:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# vi1 is kept at -12(%rbp)

	# vi1 = pi1
	movl %edi, -12(%rbp)

	# return ci0
	movl $0, %eax

return_f3:
	leave
	ret


.globl f4
f4:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# vi1 is kept at -20(%rbp)

	# vi1 = pi2
	movl %esi, -20(%rbp)

	# return ci0
	movl $0, %eax

return_f4:
	leave
	ret


.globl f5
f5:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# if needed %rdx is saved at -24(%rbp) before function call
	# vi1 is kept at -28(%rbp)

	# vi1 = pi3
	movl %edx, -28(%rbp)

	# return ci0
	movl $0, %eax

return_f5:
	leave
	ret


