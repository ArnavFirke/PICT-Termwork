%macro print 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

section .data
	menu  db 10, "Menu : ", 10,"1. Addition", 0ah,"2. Subtraction", 0ah," 3. Multiplication", 0ah, " 4. Division",0ah
	len equ $-menu

	msg db "Enter choice : "
	len2 equ $-msg

	n1 dq 5H
	n2 dq 3H


section .bss
	choice resb 4
	result resb 16


section .text
global _start
_start:

	print 1,1,menu,len
	print 1,1,msg,len2
	print 0,0,choice,4

	cmp byte[choice],31H
	je o1
	cmp byte[choice],32H
	je o2
	cmp byte[choice],33H
	je o3
	cmp byte[choice],34H
	je o4

	o1:
		mov al,[n1]
		mov bl,[n2]
		add al,bl
		mov [result] ,al
		call HtoA
		print 1,1,result,16
		call exit


	o2:
		mov al,[n1]
		mov bl,[n2]
		sub al,bl
		mov [result] ,al
		call HtoA
		print 1,1,result,16
		call exit


	o3:
		mov rax,[n1]
		mov rbx,[n2]
		mul rbx
		push rax
		call HtoA
		pop rax
		print 1,1,result,16
		call exit


	o4:
		xor rdx,rdx
		mov rax,[n1]
		mov ebx,[n2]
		div ebx
		push rdx
		call HtoA
		print 1,1,result,16
		pop rdx
		mov rax ,rdx
		call HtoA
		print 1,1,result,16
		call exit


	exit:
		mov rax,60
		mov rdi,0
		syscall


	HtoA:
		mov r8,result
		mov cl,2

	up:
		rol al,4
		mov bl,al
		AND bl,0FH
		cmp bl,09H
		jbe l1
		add bl,07H

	l1:
		add bl,30H
		mov byte[r8],bl
		inc r8
		dec cl
		jnz up 

	ret

