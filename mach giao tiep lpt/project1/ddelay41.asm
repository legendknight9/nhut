ddelay41: mov r6,#90h
del412: mov r7,#900
		djnz r7,$
		djnz r6,del412
ret

