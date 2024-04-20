EXTERN input_num: near
EXTERN output_bin_num: near
EXTERN output_hex_num: near
EXTERN hight_degree: near

StackSeg SEGMENT PARA STACK 'Stack'
	DB 64 DUP(?)
StackSeg ENDS

DataSeg SEGMENT PARA PUBLIC 'Data'
	Menu DB 'Menu:', 10, 13
	     DB '    0. Exit', 10, 13
	     DB '    1. Input number (decimal with sign)', 10, 13
	     DB '    2. Output number (binary with sign)', 10, 13
	     DB '    3. Output number (hex without sign)', 10, 13
	     DB '    4. Find minimal highter degree', 10, 13
	     
	NewLine DB 10, 13, '$'
	
	ErrorMsg DB 'Wrong command!', 10, 13, '$'

	func_array dd 1 dup(quit)
		   dd 1 dup(input_num)
		   dd 1 dup(output_bin_num)
		   dd 1 dup(output_hex_num)
		   dd 1 dup(hight_degree)
DataSeg ENDS

CodeSeg SEGMENT PARA PUBLIC 'Code'
	ASSUME CS:CodeSeg, DS:DataSeg, SS:StackSeg
	
quit:
	mov ah, 4ch
	int 21h	
	ret
	
print_new_line:
	mov ah, 9
	mov dx, OFFSET NewLine
	int 21h
	ret

print_menu:
	mov ah, 9
	mov dx, OFFSET Menu
	int 21h
	ret
	
read_com:
	mov ah, 1
	int 21h
	mov bx, 0
	sub al, '0'
	mov bl, al
	
	call print_new_line
	ret
	
error_msg:
	mov ah, 09
	mov dx, OFFSET ErrorMsg
	int 21h

main:
	while_true:
		mov ax, DataSeg
		mov ds, ax
		call print_menu
		call read_com
		
		cmp bx, 4
		jg error_msg
		
		lea si, func_array
		mov ax, 4
		mul bx
		add si, ax
		call near ptr [si]
		jmp while_true
CodeSeg ENDS
END main
	
	
