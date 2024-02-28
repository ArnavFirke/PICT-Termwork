section .data
	fact_msg db 10,13 ,'Enter the no for find Factorial :'
	fact_len equ $ - fact_msg
	fact_m db 10,13," Result of Factorial no is: "	
	fact_l equ $ - fact_m


section .bss
	fact resb 1
	dispbuff resb 01
	numascii resb 01
	num resb 01
	ans resb 01


%macro print 02
 mov eax,04
 mov ebx,01
 mov ecx,%1
 mov edx,%2
 int 80h
%endmacro
%macro read 02
 mov eax,03
 mov ebx,00
 mov ecx,%1
 mov edx,%2
 int 80h
%endmacro


section .text
global _start ;must be declared for using gcc
_start: ;tell linker entry point
	print fact_msg,fact_len
	read numascii,03
	call packnum
 	mov [num],bx
 	
 	;for calculating factorial no
 	call proc_fact
	mov [ans],ax
 	print fact_m,fact_l
	mov bx,[ans]
	call disp


 	mov eax,1 ;system call number (sys_exit)
 	mov ebx,00
 	int 0x80 ;call kernel
	proc_fact:
 		mov ax, 1
 		cmp bl, 1
 		jg do_calculation
 		ret
	do_calculation:
 		dec bl
 		call proc_fact
 		inc bl
 		mul bl ;ax = al * bl
 		ret
	packnum:
		mov bl,0
		mov ecx,02
		mov esi,numascii
	up1:
		rol bl,04
		mov al,[esi]
		cmp al,39h
		jbe skip1
		sub al,07h
	skip1: sub al,30h
		add bl,al
		inc esi
		loop up1
 		ret
	disp:
		mov ecx,4
		mov edi,dispbuff
	dup1:
		rol bx,4
		mov al,bl
		and al,0fh
		cmp al,09
		jbe dskip
		add al,07h
	dskip: add al,30h
		mov [edi],al
		inc edi
		loop dup1
		print dispbuff,4
		ret
