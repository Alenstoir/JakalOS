org 0x7C00
call loader
call video

cli ; отключить прерывания
mov ax, 0 ; обнуленеие сегментных регистров
mov ss, ax ; обнуленеие сегментных регистров
mov ds, ax ; обнуленеие сегментных регистров
mov fs, ax ; обнуленеие сегментных регистров
mov es, ax ; обнуленеие сегментных регистров
mov gs, ax ; обнуленеие сегментных регистров
mov sp, 0xfffc ; выделение 4 байта в стек
lgdt[gdtable] ; загрузка таблицы дескрипторов
mov eax, cr0
or eax, 1
mov cr0, eax

mov esi, [bUffer + 0x28]

jmp MyCode:0x8000 ; переход по "Дескриптор:Адрес"
ret

video:
        mov ax, 0x4f01
        mov cx, 0x118 ; 1024x768
        mov di, bUffer
        int 0x10

        mov ax, 0x4f02
        mov bx, 0x4118
        int 0x10
ret

loader:
        mov ah, 2
        mov al, 127
        mov ch, 0
        mov cl, 2
        mov dh, 0
        mov dl, 0x80
        mov bx, 0x8000
        int 0x13 
ret


Table_D_Begin:

null_d:
dq 0

code_d:
dw 0xFFFF ; предел памяти
dw 0 ; филлер
db 0 ; филлер
db 10011010b ; флаги: 
; p - определяет что дескриптор заполнен и используется, 1 бит. 
; dpl - уровень привилегий дескриптора, 2 бита. 
; s - определяет дескриптор как системный/не системный, 1 бит. 
; c - определяет что дескриптор будет содержать исполняемый код (1), или данные (0), 1 бит. 
; edc - разрешает расширение области памяти, описываемой дескриптором в сторону области данных(1) или стека(0), 1 бит.
; r/w - разрешение на чтение/запись, 1 бит.
; A - был ли запрос к дескриптору, 1 бит.
db 11001111b ;
db 0 ; филлер

data_d:
dw 0xFFFF ; предел памяти
dw 0 ; филлер
db 0 ; филлер
db 0b10010010 ; флаги: 
; p - определяет что дескриптор заполнен и используется, 1 бит. 
; dpl - уровень привилегий дескриптора, 2 бита. 
; s - определяет дескриптор как системный/не системный, 1 бит. 
; c - определяет что дескриптор будет содержать исполняемый код (1), или данные (0), 1 бит. 
; edc - разрешает расширение области памяти, описываемой дескриптором в сторону области данных(1) или стека(0), 1 бит.
; r/w - разрешение на чтение/запись, 1 бит.
; A - был ли запрос к дескриптору, 1 бит.
db 0b11001111 ;
db 0 ; филлер

Table_D_End:

gdtable:
dw Table_D_End-Table_D_Begin
dd Table_D_Begin

bUffer dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

MyCode equ code_d - Table_D_Begin