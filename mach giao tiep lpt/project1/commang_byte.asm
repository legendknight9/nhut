command_byte:
clr rs
ljmp bdelay
data_byte: setb rs
bdelay: clr rw
	clr e
nop

setb e
nop
nop

mov byteout,#0ffh

setb rw
clr rs
clr e

nop
nop
setb e
lcall ddelay100
ret