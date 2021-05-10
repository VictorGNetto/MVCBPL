.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp


	# return ci0
	movl $0, %eax

return_f1:
	leave
	ret

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp


	# return ci10
	movl $10, %eax

return_f2:
	leave
	ret

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp


	# return ci-100
	movl $-100, %eax

return_f3:
	leave
	ret

