mycode SEGMENT 'code'
 assume cs:mycode
LET DB   'A'
START:
   PUSH CS
   POP  DS
;����� ������ ������� �� �����
   MOV AH, 02
   MOV DL, LET
   INT 21H
; ����� �� ���������
   mov al, 0
   mov ah, 4ch
   int 21h
mycode ends
end START



