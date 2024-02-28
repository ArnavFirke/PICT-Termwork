%macro wrfunc 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

Section .data
	array: db 10h,56h,24h,32h,45h
	count: db 2h
	
Section .bss
	cnt: resb 2
	num:resb 2
	
Section .text
global _start
_start:

	mov byte[cnt],5h
	mov rsi,array
	mov al,0
	
	looparr:
		cmp al,[rsi]
		jg skip
		mov al,[rsi]
	
		skip:
			inc rsi
			dec byte[cnt]
			jnz looparr
		
		;Hex to Ascii conversion
		mov rsi,num      ;rsi is pointer to num
		mov cl,2h
		label1:
			rol al,4 
			mov bl,al
			and bl,0x0f
			cmp bl,9h
				jle label2
			add bl,07h	
		label2:
			add bl,30h
			mov byte[rsi],bl
			inc rsi
			dec cl
			jnz label1
	
	next:		
		wrfunc 1,1,num,2
	
				
	mov rax,60
	mov rdi,0
	syscall
	


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
