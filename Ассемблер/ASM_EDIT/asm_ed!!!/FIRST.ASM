mycode SEGMENT 'code'
 assume cs:mycode
LET DB   'A'
START:
   PUSH CS
   POP  DS
;Вывод одного символа на экран
   MOV AH, 02
   MOV DL, LET
   INT 21H
; Выход из программы
   mov al, 0
   mov ah, 4ch
   int 21h
mycode ends
end START



