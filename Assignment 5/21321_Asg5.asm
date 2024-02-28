%macro rwrite 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

%macro Hex_to_Ascii 1
	mov rsi,%1
	mov cl, 2h
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
	str1 db "Count of positive numbers = "
	str1_len equ $-str1
	str2 db 0x0a,"Count of negative numbers = ",
	str2_len equ $-str2
	str3 db 0x0a
	str3_len equ $-str3
	
	arr dq -22h,12h,4h,-54h,67h
	cnt db 05
	
Section .bss
	ncnt resb 2
	pcnt resb 2
	
Section .text
global _start
_start:
	mov byte[pcnt],0
	mov byte[ncnt],0
	
	mov rsi,arr
	back:
		mov rbx, [rsi]
		bt rbx,63
		JC negative
		inc byte[pcnt]
		jmp Step1
		
	negative:
		inc byte[ncnt]
	
	Step1:
		add rsi,8
		dec byte[cnt]
		jnz back
		
	rwrite 1,1,str1,str1_len
	mov al,byte[pcnt]
	Hex_to_Ascii pcnt
	rwrite 1,1,pcnt,2
	
	;rwrite 1,1,str3,str3_len
	
	rwrite 1,1,str2,str2_len
	mov al,byte[ncnt]
	Hex_to_Ascii ncnt
	rwrite 1,1,ncnt,2
	
	rwrite 1,1,str3,str3_len
	
	mov rax,60
	mov rdx,0
	syscall
