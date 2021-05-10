.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp


return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp


return_f2:
	leave
	ret


.globl f5
f5:
	pushq %rbp
	movq %rsp, %rbp


return_f5:
	leave
	ret


