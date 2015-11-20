second_line: 
mov A,#0c0h
lcall ktao
mov dptr,#sline_data
lcall write
ret
