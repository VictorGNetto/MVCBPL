.text

.globl f100
f100:
	pushq %rbp
	movq %rsp, %rbp


	# return ci0
	movl $0, %eax

return_f100:
	leave
	ret


.globl f101
f101:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call

	# return ci0
	movl $0, %eax

return_f101:
	leave
	ret


.globl f102
f102:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call

	# return ci0
	movl $0, %eax

return_f102:
	leave
	ret


.globl f103
f103:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# if needed %rdx is saved at -24(%rbp) before function call

	# return ci0
	movl $0, %eax

return_f103:
	leave
	ret


.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp

	# vi1 is kept at -4(%rbp)

	# vi1 = call f100
	call f100
	movl %eax, -4(%rbp)

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

	# vi1 = call f101 vi1
	movl -4(%rbp), %edi  # 1o parameter
	call f101
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

	# vi1 = call f102 pa1 ci-5
	movq %rdi, -8(%rbp)
	movq -8(%rbp), %rdi  # 1o parameter
	movl $-5, %esi  # 2o parameter
	call f102
	movl %eax, -12(%rbp)
	movq -8(%rbp), %rdi

	# return ci0
	movl $0, %eax

return_f3:
	leave
	ret


.globl f4
f4:
	pushq %rbp
	movq %rsp, %rbp
	subq $48, %rsp

	# if needed %rdi is saved at -8(%rbp) before function call
	# if needed %rsi is saved at -16(%rbp) before function call
	# vi1 is kept at -20(%rbp)
	# va2[5] is kept at -40(%rbp)

	# vi1 = call f103 pa1 pi2 va2
	movq %rdi, -8(%rbp)
	movq %rsi, -16(%rbp)
	movq -8(%rbp), %rdi  # 1o parameter
	movl -16(%rbp), %esi  # 2o parameter
	movq -40(%rbp), %rdx  # 3o parameter
	call f103
	movl %eax, -20(%rbp)
	movq -8(%rbp), %rdi
	movq -16(%rbp), %rsi

	# return ci0
	movl $0, %eax

return_f4:
	leave
	ret


