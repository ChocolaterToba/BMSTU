MYCODE SEGMENT 'CODE'
 ASSUME CS:MYCODE, DS:MYCODE
?? 2019/2020 ????????? ?.?. 4-? ??????? 2/3-?? ????? ??5/??? -?????
10
LET DB 'A'
START:
; ???????? ??????????? ???????? ?????? DS
 PUSH CS
 POP DS
; ????? ?????? ??????? ?? ?????
 MOV AH, 02
 MOV DL, LET
 INT 21H
; ???????? ?????????? ?????????
MOV AH, 01H
INT 021H
; ????? ?? ?????????
 MOV AL, 0
 MOV AH, 4CH
 INT 21H
MYCODE ENDS
END START
