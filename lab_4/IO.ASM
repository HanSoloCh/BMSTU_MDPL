EXTERN ROWS: BYTE
EXTERN COLUMNS: BYTE
EXTERN MATRIX: BYTE

PUBLIC input_matrix
PUBLIC output_matrix

CODESEG SEGMENT PARA PUBLIC 'Code'
	ASSUME CS:CODESEG
	
input_num:
	mov ah, 1h
	int 21h
	mov bl, al
	sub bl, "0"
	ret
	
input_matrix:
	call input_num
	mov ROWS, bl
	
	call print_space
	
	call input_num
	mov COLUMNS, bl
	
	call print_end_line
	
	mov ch, 0
	mov si, 0
	input_row:
		mov cl, 0
		mov bx, 0
		input_col:
			mov ah, 1h
			int 21h
			mov MATRIX[si][bx], al
			
			call print_space
			
			inc cl
			inc bx
			cmp cl, COLUMNS
			jne input_col
		
		call print_end_line
		
		inc ch
		add si, 9h
		
		cmp ch, ROWS
		jne input_row
	ret

output_matrix:
	call print_end_line
	mov ch, 0
	mov si, 0
    	print_row:
        	mov cl, 0
		mov bx, 0
        	print_col:
            		mov ah, 2h
            		mov dl, matrix[si][bx]
            		int 21h

            		inc bx

            		call print_space

            		inc cl
            		cmp cl, COLUMNS
            		jne print_col

        	call print_end_line

        	add si, 9

		inc ch
		cmp ch, ROWS
		jne print_row
    	ret
    	
print_end_line:
	mov ah, 2h
   	mov dl, 10
    	int 21h
    	ret
    	
print_space:
	mov ah, 2h
	mov dl, " "
	int 21h
	ret
CODESEG ENDS
END
