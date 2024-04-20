StkSeg SEGMENT PARA STACK 'STACK'
	DB 200h DUP (?)
StkSeg ENDS

DataS SEGMENT WORD 'DATA'
HelloMessage 	DB 13
		DB 10
		DB 'Hello, world !'
		DB '$'
DataS ENDS

Code SEGMENT WORD 'CODE'
	ASSUME CS:Code, DS:DataS
DispMsg:
	mov AX,DataS
	mov DS,AX
	mov DX,OFFSET HelloMessage
	mov AH,9
	mov CX,1
	
	labecd ll:
		int 21h
		loop labell

;	labell:
;		int 21h
;		dec CX
;		jnz labell
		
	mov AH,7
	INT 21h
	mov AH,4Ch
	INT 21h
Code ENDS
	END DispMsg
