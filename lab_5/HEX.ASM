PUBLIC output_hex_num

hexnum SEGMENT PARA PUBLIC 'Data'
	hex_array db 3 dup(0)
	last_digit db 1 dup(0)
		   db 10, 13, '$'
hexnum ENDS

CodeSeg SEGMENT PARA PUBLIC 'Code'
output_hex_num:
	mov ax, es
	mov ds, ax
	mov ax, [di]
	
	
	ASSUME ds:hexnum
	mov bx, hexnum
	mov ds, bx
	
	mov bx, 16
	
	mov si, OFFSET last_digit
	
	
	write_num:
		mov dx, 0
		div bx
		add dl, '0'
		
		cmp dl, '9'
		jle not_letter
		add dl, 7
		
		not_letter:
		mov [si], dl
		dec si
		
		cmp ax, 0
		jne write_num
	inc si
	mov ah, 09
	mov dx, si
	int 21h
	ret
	
CodeSeg ENDS
END
	
