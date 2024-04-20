EXTERN ROWS: byte
EXTERN COLUMNS: byte
EXTERN MATRIX: byte

PUBLIC swap_nums


CODESEG SEGMENT PARA PUBLIC 'Code'
swap_nums:
	mov si, 0
	mov ch, 0
	for_row:
		mov dx, 0
		mov bx, 0
		mov cl, 0
		for_col:
            		mov al, matrix[si][bx]
            		xchg bx, dx
			mov ah, matrix[si][bx]
			xchg bx, dx
			
			cmp al, ah
			 
			jng skip_swap
			mov dx, bx
			
			skip_swap:
				inc bx
				inc cl
				cmp cl, COLUMNS
				jne for_col
				
		call swap
		inc ch
		add si, 9h
		
		cmp ch, ROWS
		jne for_row
	ret

swap:
	xchg bx, dx
	mov al, matrix[si][bx]
	mov ah, matrix[si][0]
	
	mov matrix[si][bx], ah
	mov matrix[si][0], al
	
	xchg bx, dx
	ret
	
CODESEG ENDS
END
	
