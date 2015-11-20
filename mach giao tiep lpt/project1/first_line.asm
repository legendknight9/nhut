first_line: 
mov A,#080h
lcall ktao
mov dptr,#fline_data
lcall write
ret
