%macro wrfunc 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro
Section .data
	string db "Enter 5 numbers:",0x10
	len equ $-string
	count db 05
	
Section .bss
	array resb 100
	
Section .text
global _start

_start:

	;mov r8,array
	
	mov byte[count],5
	
	;display string
	mov rax,1
	mov rdi,1
	mov rsi,string
	mov rdx,len
	syscall
	
	mov rsi,array
	looparr:
		mov rax,0
		mov rdi,0
		mov rdx,17
		syscall
		
		add rsi,17
		dec byte[count]
		JNZ looparr
		
	mov byte[count],05
	mov rsi,array
	
	loop1:
		mov rax,1
		mov rdi,1
		;mov rsi,array
		mov rdx,17
		syscall
		
		add rsi,17
		dec byte[count]
		JNZ loop1
	
	mov rax,60
	mov rdi,0
	syscall
	

