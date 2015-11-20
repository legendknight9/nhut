

khtaolcd:
setb e
clr rs
clr rw
mov a,#38h
lcall ktao
lcall ddelay41

mov A,#38h
lcall ktao
lcall ddelay100

mov A,#38h
lcall ktao

mov A,#0ch
lcall ktao
mov A,#01h
Lcall ktao

mov A,#06h
lcall ktao

mov A,#80h
lcall ktao

mov A,#0h
lcall ktao

ret




