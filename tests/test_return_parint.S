.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp


	# return pi1
	movl %edi, %eax

return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp


	# return pi2
	movl %esi, %eax

return_f2:
	leave
	ret


.globl f5
f5:
	pushq %rbp
	movq %rsp, %rbp


	# return pi3
	movl %edx, %eax

return_f5:
	leave
	ret


