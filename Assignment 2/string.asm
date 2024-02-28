%macro wrfunc 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro
Section .data
	string: db "Enter the String: "
	len: equ $-string
	count: db 2
	
Section .bss
	array: resb 200
	num: resb 4
Section .text
global _start

_start:
	;print string
	wrfunc 1,1,string,len

	;read 
	wrfunc 0,0,array,200
	
	;length that is stored in rax
	
	dec al   ;remove enter key byte
	mov rbp,num  ;rbp is pointer to num
	
	;HEX to ASCII convertion
loop:
	rol al,4		;as 1 digit is stored as nibble 4 bits
	mov bl,al
	AND bl,0x0F		;masking of bl 
	
	CMP bl,09h
	JBE addfunc   ;jump below or equal
	add bl,7h
addfunc: 
	add bl,30h
		
	mov [rbp],bl
	inc rbp
	dec byte[count]
	JNZ loop
	
	wrfunc 1,1,num,4
	
	mov rax,60
	mov rdi,0
	syscall
	
	
	
