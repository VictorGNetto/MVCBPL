.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $64, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# vi1 is kept at -20(%rbp)
	# va2[10] is kept at -60(%rbp)

	# vi1 = pi1 + ci1
	movl %edi, %eax
	movl $1, %ecx
	addl %ecx, %eax
	movl %eax, -20(%rbp)

	# set va2 index ci5 with ci2 
	leaq -60(%rbp), %r9
	movq $5, %r8
	imulq $4, %r8
	addq %r8, %r9
	movl %esi, (%r9)

	# set pa2 index ci3 with vi1 
	leaq %rsi, %r9
	movq $3, %r8
	imulq $4, %r8
	addq %r8, %r9
	movl -20(%rbp), (%r9)

	# get va2 index ci5 to vi1
	leaq -60(%rbp), %r9
	movq $5, %r8
	imulq $4, %r8
	addq %r8, %r9
	movl (%r9), -20(%rbp)

	# return pi1 
	movl %edi, %eax

return_f1:
	leave
	ret


