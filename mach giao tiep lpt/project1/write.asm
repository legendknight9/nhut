write:
mov A,#0
movc A,@a+dptr
cjne A,#99h,writea

writea:
mov byteout,a
acall data_byte
inc dptr
sjmp write
