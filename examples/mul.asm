#	Implements multiplication function
#		left * right = out
#		jmp return
#	r0 = left
#	r1 = right
#	r2 = out
#	r3 = return addr
#	internal addresses
#		r102 = 0
#		r103 = 1
#		r104 = internal loop counter counting up to equal r1
#		r105 = comparison flag
mul:	set [mul_l], r100
	set [mul_a], r101
	set 0, r102
	set 1, r103
	set 0, r104

	mul_l:	cmp r104, r1, r105
		cmp r105, r102, r105

		jmpc r101, r105

		jmp r3

	mul_a:	add r0, r2, r2
		add r103, r104, r104
		jmp r100
