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
str2 db "Maximum of given numbers = "
str2_len equ $-str2

mov rbx,0
count1 db 05
count2 db 05

Section .bss
nos resb 100
num resb 10

Section .text
global _start
_start:
	rwrite 01,01,str1,str1_len
	;mov rax,01
	;mov rdi,01
	;mov rsi,str1
	;mov rdx,str1_len
	;syscall
	
	
	mov r8,0
	mov r8,nos
	
	loop1:
		mov rax,0
		mov rdi,0
		mov rdx,2
		syscall

		add r8,2
		dec byte[count1]
		JNZ loop1
	
	rwrite 01,01,str2,str2_len	
	;mov rax,01
	;mov rdi,01
	;mov rsi,str2
	;mov rdx,str2_len
	;syscall
	
	mov rsi,nos
	mov r9,[rsi]
	Max:
		cmp rsi,r9
		JG Inc
		mov r9,[rsi]
	
		Inc:
			add rsi,2
			dec byte[count2]
			JNZ Max
	

	mov al,[r9]
	mov rbp, num
	mov cl,2
	up:
		rol al,4
		mov dl,al
		and dl,0fh
		cmp dl,09h ; comparing whether it is less than 9 
		 jbe next1 ; it will jump to 
		 add dl,07 ; if it is greater than 09h then we add 07
		 
	next1:
		add dl, 30h 
		
	mov [rbp] ,dl
	
	inc rbp
	dec cl ; decrementing the counter
	jnz up
	

	rwrite 01,01,num,10

	;loop2:
		;mov rax,01
		;mov rdi,01
		;mov rdx,17
		;syscall
		
		;add rsi,17
		;dec byte[count2]
		;JNZ loop2
		
	exit:
	mov rax,60
	mov rdx,0
	syscall
		
