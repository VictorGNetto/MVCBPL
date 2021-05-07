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
	subq $144, %rsp

	# vi1 is kept at -12(%rbp)
	# va2[30] is kept at -132(%rbp)
	# vi3 is kept at -136(%rbp)

return_f2:
	leave
	ret

.globl f4
f4:
	pushq %rbp
	movq %rsp, %rbp
	subq $160, %rsp

	# vi1 is kept at -28(%rbp)
	# va2[10] is kept at -68(%rbp)
	# va3[20] is kept at -148(%rbp)

return_f3:
	leave
	ret

