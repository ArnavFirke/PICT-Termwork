%macro wrfunc 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

%macro hextoascii 1
	mov rbp,%1
	mov rcx,2
	%%up3: rol bl,04
        mov dl,bl
        AND dl,0Fh
        cmp dl,09h
        jbe %%up3
        add dl,07h
    %%next1:
        add dl,30h
        mov [rbp],dl
        inc rbp
        dec rcx
        jnz %%up3
%endmacro

Section .data
	str1: db "1.Addition",0x0A
	len1: equ $-str1
	str2: db "2.Subtraction",0x0A
	len2: equ $-str2
	str4: db "4.Division",0x0A
	len4: equ $-str4
	str3: db "3.Multiplication",0x0A
	len3: equ $-str3
	str5: db "5.Exit",0x0A
	len5: equ $-str5
	count: db 2
	
Section .bss
	ans: resb 2

Section .text
global _start

_start:

	wrfunc 1,1,str1,len1
	wrfunc 1,1,str2,len2
	wrfunc 1,1,str3,len3
	wrfunc 1,1,str4,len4

	wrfunc 0,0,rax,5

	wrfunc 1,1,rax,5
    
		mov rax,60
		mov rdi,0
		syscall
