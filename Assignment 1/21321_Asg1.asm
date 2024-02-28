%macro rwrite 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

Section .data
str1 db "Enter 5 64 bit numbers = ",0x10" "
str1_len equ $-str1
str2 db "Your entered 64 bit numbers are = "
str2_len equ $-str2

mov rbx,0
count1 db 05
count2 db 05

Section .bss
nos resb 100
new resb 100

Section .text
global _start
_start:
	rwrite 01,01,str1,str1_len
	;mov rax,01
	;mov rdi,01
	;mov rsi,str1
	;mov rdx,str1_len
	;syscall
	
	
	mov rsi,0
	mov rsi,nos
	
	loop1:
		mov rax,0
		mov rdi,0
		mov rdx,17
		syscall

		add rsi,17
		dec byte[count1]
		JNZ loop1
	
	rwrite 01,01,str2,str2_len	
	;mov rax,01
	;mov rdi,01
	;mov rsi,str2
	;mov rdx,str2_len
	;syscall
	
	
	mov rsi,nos

	loop2:
		mov rax,01
		mov rdi,01
		mov rdx,17
		syscall
		
		add rsi,17
		dec byte[count2]
		JNZ loop2
		
	mov rax,60
	mov rdx,0
	syscall
		
