StkSeg SEGMENT PARA STACK 'STACK'
	DB 200h DUP (?)
StkSeg ENDS

DataS SEGMENT para 
	string DB 200h DUP (?)
DataS ENDS

CODESEG SEGMENT WORD 'CODE'
	ASSUME CS:CodeS, DS:DataS
	
input_str:
	mov AH, 10
	mov DX, OFFSET string
	INT 21h
	
	ret
	
output_str:
	mov DL, 10
	mov AH, 2
	INT 21h
	
	mov BL, string + 4
	sub BL, 32
	mov DL, BL
	INT 21h
	ret
	
main:
	mov ax, DataS
	mov ds, ax
	call input_str
	call output_str
	
	mov AH, 4Ch
	INT 21h

CODESEG ENDS
	END main
