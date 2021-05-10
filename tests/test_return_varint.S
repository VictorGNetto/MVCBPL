.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# vi1 is kept at -4(%rbp)

	# return vi1
	movl -4(%rbp), %eax

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
	# vi3 is kept at -12(%rbp)

	# return vi3
	movl -12(%rbp), %eax

return_f2:
	leave
	ret


.globl f3
f3:
	pushq %rbp
	movq %rsp, %rbp
	subq $144, %rsp

	# vi1 is kept at -4(%rbp)
	# va2[30] is kept at -124(%rbp)
	# vi3 is kept at -128(%rbp)
	# va4[1] is kept at -132(%rbp)
	# vi5 is kept at -136(%rbp)

	# return vi5
	movl -136(%rbp), %eax

return_f3:
	leave
	ret


