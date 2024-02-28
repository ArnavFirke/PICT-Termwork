%macro rwrite 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

Section .data
str1 db "Enter String = "
str1_len equ $-str1
str2 db "Length of String = "
str2_len equ $-str2

Section .bss
	name resb 200
	num resb 10
	
Section .text
global _start
_start:

	; Displaying the message
	rwrite 1,1,str1, str1_len
	
	; taking input from user
	rwrite 0,0,name,200
	
	;
	dec al
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
	
	;displaying message
	rwrite 1,1,str2,str2_len
	
	;length of string
	rwrite 1,1,num,10
		
	
	
	mov rax,60
	mov rdx,0
	syscall
		
