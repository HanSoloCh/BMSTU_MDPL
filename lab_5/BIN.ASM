PUBLIC output_bin_num

binnum SEGMENT PARA PUBLIC 'Data'
	binary_num db 15 dup(0)
	last_digit db 1 dup(0)
		  db 10, 13, '$'
binnum ENDS

CodeSeg SEGMENT PARA PUBLIC 'Code'
output_bin_num:
	mov ax, es
	mov ds, ax
	mov ax, [di] ; в ax хранится число
	
	ASSUME ds:binnum
	mov bx, binnum
	mov ds, bx
	
	mov si, offset last_digit ; младший разряд
	
	xor ah, ah
	
	mov ch, 128
	and ch, al
	
	cmp ch, 128
	jne skip_inv
	neg al
	mov bx, ax
	mov ah, 02
	mov dl, '-'
	int 21h
	mov ax, bx
	skip_inv:
		mov bx, 2 ; делитель
	write_loop:
		mov dx, 0
		div bx
		add dl, '0'
		mov [si], dl
		dec si
		
		cmp ax, 0
		jne write_loop
	inc si
	mov ah, 09
	mov dx, si
	int 21h
	ret
CodeSeg ENDS
END
