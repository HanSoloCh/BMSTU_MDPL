## Лабораторная работа №1
### Создание простейшей программы на ассемблере. Отладчик.

Практическое задание:
1. Создайте файл hello.asm с текстом
``` asm
.MODEL TINY
.DOSSEG
.DATA
    MSG DB "Hello, World!", 0Dh, 0Ah, '$'
.CODE
.STARTUP
    MOV AH, 09h
    MOV DX, OFFSET MSG
    INT 21h
    MOV AH, 4Ch
    INT 21h
END
```
2. Запустите ML.EXE /AT hello.asm.
3. Посмотрите, какие файлы были созданы компилятором. Определите их размер.
   Просмотрите файл в любом hex-viewer’е, проанализируйте содержимое файла
   и изучите возможности просмотровщика.
4. Запустите скомпилированную программу.
5. Запустите AFDPRO.EXE HELLO.COM.
6. Изучите возможности отладчика.