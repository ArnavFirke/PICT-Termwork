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

section .data

	src_block: db 1,2,3,4,5,6,7,8,9,10
	dst_block: db 0,0,0,0,0,0,0,0,0,0

section .text
global _start

_start:
    ; Without Overlapping
    ; Load source address
    mov rsi, src_block
    ; Load destination address
    mov rdi, dst_block
    ; Load block size
    mov rcx, 10
    ; Perform the transfer
    rep movsb
	
	mov rsi,dst_block
	
	looparr:
		mov rax,1
		mov rdi,1
		mov rdx,10
		syscall
		
		add rsi,1
		dec rcx
		JNZ looparr
	
	
    ; With Overlapping
    ; Load source address
    mov rsi, dst_block
    ; Load destination address
    mov rdi, dst_block+3
    ; Load block size
    mov rcx, 7
    ; Perform the transfer
    rep movsb

    ; Exit
    mov eax, 0
    mov ebx, 0
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
