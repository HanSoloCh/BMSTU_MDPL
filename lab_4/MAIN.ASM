PUBLIC ROWS
PUBLIC COLUMNS
PUBLIC MATRIX

EXTERN input_matrix: near
EXTERN output_matrix: near
EXTERN swap_nums: near

STKSEG SEGMENT PARA STACK 'Stack'
	DB 200h DUP (?)
STKSEG ENDS

DATASEG SEGMENT PARA 'Data'
	ROWS DB 0
	COLUMNS DB 0
	MATRIX DB 9 * 9 DUP (0)
DATASEG ENDS 


CODESEG SEGMENT PARA PUBLIC 'Code'
	ASSUME DS:DATASEG, CS:CODESEG
main:
	mov ax, DATASEG
	mov ds, ax
	call input_matrix
	call swap_nums
	call output_matrix
	
	mov ah, 4Ch
	int 21h
CODESEG ENDS
	END main
