PUBLIC input_num

CodeSeg SEGMENT PARA PUBLIC 'Code'
input_num:
	mov bx, 0
	mov dx, 0
	mov ch, 10
	mov cl, 0
	start_input:
		mov ah, 1
		int 21h
		
		cmp al, 13
		je end_input
		
		cmp al, 45 ; обработка минуса
		je neg_num
		
		mov dl, al
		sub dl, '0'
		
		mov ax, bx
		mul ch
		add ax, dx
		mov bx, ax
		
		jmp start_input
		
 	end_input:
 		cmp cl, 1 ; проверка на минус
 		jne save_input
 		neg bx
 		
 	save_input:
 		mov ax, es
 		mov ds, ax
 		mov [di], bl
 		mov [di + 1], bh
 		ret
 		
neg_num:
	mov cl, 1
	jmp start_input
CodeSeg ENDS
END
