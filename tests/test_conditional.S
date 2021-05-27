.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# vi1 is kept at -4(%rbp)

	# vi1 = ci123
	movl $123, -4(%rbp)

	# if vi1
# begin_if0:
	movl -4(%rbp), %eax
	cmpl $0, %eax
	je end_if0

	# vi1 = ci0
	movl $0, -4(%rbp)
end_if0:

	# return vi1
	movl -4(%rbp), %eax

return_f1:
	leave
	ret


.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $64, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# va1[10] is kept at -48(%rbp)
	# vi2 is kept at -52(%rbp)

	# if ci-1
# begin_if1:
	movl $-1, %eax
	cmpl $0, %eax
	je end_if1

	# set va1 index ci9 with ci144
	leaq -48(%rbp), %r9
	movq $9, %r8
	imulq $4, %r8
	addq %r8, %r9
end_if1:

	# get va1 index ci9 to vi2
	leaq -48(%rbp), %r9
	movq $9, %r8
	imulq $4, %r8
	addq %r8, %r9
	movl (%r9), -52(%rbp)

	# if pi1
# begin_if2:
	movl %edi, %eax
	cmpl $0, %eax
	je end_if2

	# return vi2
	movl -52(%rbp), %eax
	jmp return_f2
end_if2:

	# return ci0
	movl $0, %eax

return_f2:
	leave
	ret


