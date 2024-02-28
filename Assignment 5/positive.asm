%macro wrfunc 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro
;Hex to Ascii conversion
%macro HtoA 1
		mov rsi,%1      ;rsi is pointer to num
		mov cl,2h
		%%label1:
			rol al,4 
			mov bl,al
			and bl,0x0f
			cmp bl,9h
			jle %%label2
			add bl,07h	
		%%label2:
			add bl,30h
			mov byte[rsi],bl
			inc rsi
			dec cl
			jnz %%label1
%endmacro
		
Section .data
	array: dq 10h,-56h,-24h,32h,-45h
	cnt: db 5h
	
	
Section .bss

	pcnt: resb 2
	ncnt: resb 2

	
Section .text
global _start
_start:

	mov rsi,array
	mov byte[pcnt],0
	mov byte[ncnt],0

	looparr:
		mov rax,[rsi]
		BT rax,63
		JC negative
		
		inc byte[pcnt]
		jmp next
		

		negative: inc byte[ncnt]
		
		next:
			add rsi,8
			dec byte[cnt]
			jnz looparr
			
		mov al,byte[pcnt]
		HtoA pcnt
		wrfunc 1,1,pcnt,2
		
		mov al,byte[ncnt]
		HtoA ncnt
		wrfunc 1,1,ncnt,2
		
				
	mov rax,60
	mov rdi,0
	syscall
	


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
