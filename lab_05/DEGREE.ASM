.386
PUBLIC hight_degree

MsgSegment SEGMENT USE16 PARA Public 'Data'
	first_msg db 'Minimum degree of 2 greater then input number - ', '$'
	new_line db 10, 13, '$'
MsgSegment ENDS

CodeSeg SEGMENT USE16 PARA PUBLIC 'Code'
print_first_msg:
	mov ah, 09
	mov dx, OFFSET first_msg
	int 21h
	ret
	
print_new_line:
	mov ah, 09
	mov dx, OFFSET new_line
	int 21h
	ret
	
print_digit:
	mov ah, 02
	add dl, '0'
	int 21h	
	ret
	
	
hight_degree:
	mov ax, es
	mov ds, ax
	
	mov ax, [di]
	mov bx, 0
	bsr bx, ax
	inc bx
	
	ASSUME ds:MsgSegment
	mov ax, MsgSegment
	mov ds, ax
	call print_first_msg
	
	mov ax, bx
	mov ch, 10
	div ch
	
	cmp al, 0
	je print_sec_digit
	
	xchg bh, ah
	mov dl, al
	call print_digit
	xchg bh, ah
	
	print_sec_digit:
	
	mov dl, ah
	call print_digit
	
	call print_new_line
	
	ret
CodeSeg ENDS
END
