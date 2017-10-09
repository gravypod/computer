

# left = 5
set 5, r0

# right = 5
set 10, r1

# return into [done]
set [done], r3

# Call mul
set [mul], r4
jmp r4

done: hlt

!mul.asm
