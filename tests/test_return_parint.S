.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call

	# return pi1
	movl %edi, %eax

return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call

	# return pi2
	movl %esi, %eax

return_f2:
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

	# return pi3
	movl %edx, %eax

return_f5:
	leave
	ret


