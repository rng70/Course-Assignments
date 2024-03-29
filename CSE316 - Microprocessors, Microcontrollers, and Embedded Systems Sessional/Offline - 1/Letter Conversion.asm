.MODEL SMALL

.STACK 100H

.DATA
    CLR EQU 0DH
    RLF EQU 0AH
    
    MSG1 DB 'ENTER A UPPER CASE LETTER: $'
    MSG2 DB CLR, RLF, 'IN LOWER CASE IT IS: $'
    MSG3 DB CLR, RLF, 'ONE', 27H, 'S COMPLEMENT IS: $' 
    CHAR DB ?
    COMP DB ?

.CODE

MAIN PROC
    ;INITIALIZE DS
    MOV AX, @DATA
    MOV DS, AX
    
    ;DISPLAY MESSAGE FOR USER
    LEA DX, MSG1
    MOV AH, 9
    INT 21H

    ;INPUT A UPPERCASE CHARACTER
         
    MOV AH, 1
    INT 21H  
    
    ;CONVERT TO LOWERCASE
    
    ADD AL, 1FH
    MOV CHAR, AL
    
    ;CONVERT TO ONE'S COMPLEMENT
    ;1'S COMPLEMENT = 2'S COMPLEMENT - 1
    SUB AL, 1FH
    NEG AL
    SUB AL, 1
    MOV COMP, AL
    
    ;DISPLAY THE MESSAGE BEFORE SHOWING LOWERCASE LETTER
    LEA DX, MSG2
    MOV AH, 9
    INT 21H  
    
    ;DISPLAY THE LOWERCASE LETTER  
    MOV AH, 2
    MOV DL, CHAR
    INT 21H
    
    ;DISPLAY THE MESSAGE BEFORE SHOWING ONE'S COMPLEMENT
    LEA DX, MSG3
    MOV AH, 9
    INT 21H
    
    ;DISPLAY ONE'S COMPLEMENT
    MOV AH, 2
    MOV DL, COMP
    INT 21H
    
    
    
;DOX exit
    MOV AH, 4CH
    INT 21H
  
MAIN ENDP

    END MAIN