e bit p1B0
rs bit p1B1
rw bit p1B2

byteout equ p2

org 0000h
mov 0a2h,#0
lcall khtaolcd
lcall first_line
lcall second_line
sjmp $




