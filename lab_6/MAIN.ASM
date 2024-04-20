.model tiny
.code
.186

MINSPEED EQU 1fh
MAXSPEED EQU 0

CodeSeg SEGMENT PARA PUBLIC 'Code'

org 100h

main:
	jmp init
	origin dd 1 dup(0) ; Оригинальное прерывание
	cur_time db 0 ; текцщее время
	speed db 1fh ; начальная скорость 
	is_init db '$'

	TMP dq 1280 dup(0)

resident:
	pusha
	pushf
	push es
	push ds
	
	; Получаем время
	mov ah, 2h
	int 1ah
	
	; Сравниваем текщие время с сохраненным
	cmp dh, cur_time
	mov cur_time, dh
	je end_resident
	
	; Изменяем скорость
	dec speed
	cmp speed, MAXSPEED
	jg set_speed
	mov speed, MINSPEED
	
	set_speed:
		mov al, 11110011b
		out 60h, al
		mov al, speed
		out 60h, al
		
	end_resident:	
		pop ds
		pop es
		popf
		popa

		jmp cs:origin

init:
	; Получаем адрес обработчика (ES:BX BX[AL*4], ES[AL*4+2])
	mov ah, 35h
	mov al, 1Ch
	int 21h
	
	cmp es:is_init, '$'
	je delete
	
	; Сохраняем исходное прерывание
	mov word ptr cs:origin, bx
	mov word ptr cs:origin[2], es

	; Загружаем резидентскую программу (DS:DX)
	mov ah, 25h
	mov bx, cs
	mov ds, bx
	mov dx, OFFSET resident
	int 21h
	
	mov ah, 09h
	mov dx, OFFSET onMessage
	int 21h
	
	mov dx, OFFSET init
	int 27h
	
onMessage DB "Resident online$"
	
delete:
	; Загружаем адрес исходного прерывания (DS:DX)
	mov dx, word ptr es:origin
	mov ds, word ptr es:origin[2]
	mov ah, 25h
	mov al, 1Ch
	int 21h
	
	mov ah, 49h
	int 21h
	
	mov bx, cs
	mov ds, bx
	mov ah, 09h
	mov dx, OFFSET offMessage
	int 21h
	
	; Возврат к стандартным настройкам (вроде бы)
	mov al, 11110011b
	out 60h, al
	mov al, 00000000b
	out 60h, al
	
	mov ah, 4Ch
	int 21h

offMessage DB "Resident offline$"

CodeSeg ENDS
END main
