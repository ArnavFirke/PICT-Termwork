section .data
    gdtr_msg db "GDTR/LDTR Table Content:", 0
    idtr_msg db "IDTR Table Content:", 0
    table_data dq 0

section .text
    global _start

_start:
    ; Display GDTR/LDTR Table Content
    mov rax, 0x2C
    sgdt qword [table_data]  ; Load GDTR/LDTR table content into table_data
    mov rdi, gdtr_msg
    call display_message
    mov rsi, qword [table_data]
    call display_value

    ; Display IDTR Table Content
    sidt qword [table_data]  ; Load IDTR table content into table_data
    mov rdi, idtr_msg
    call display_message
    mov rsi, qword [table_data]
    call display_value

    ; Exit the program
    mov eax, 60
    xor edi, edi
    syscall

display_message:
    ; Function to display a null-terminated message
    mov rax, 1
    mov edx, 0xFFFFFFFF
    xor ecx, ecx
    cld
    repne scasb
    not ecx
    dec ecx
    mov edx, ecx
    mov eax, 1
    mov edi, 1
    syscall
    ret

display_value:
    ; Function to display a 64-bit value
    mov rax, 1
    mov edi, 1
    xor ecx, ecx
    mov cl, 16
    shl rcx, cl
    or rcx, 16
    mov edi, 0
    mov esi, 0
    mov edx, 16
    call display_hex
    mov cl, 16
    shr rsi, cl
    mov edx, 16
    call display_hex
    mov cl, 16
    shr rsi, cl
    mov edx, 16
    call display_hex
    mov cl, 16
    shr rsi, cl
    mov edx, 16
    call display_hex
    ret

display_hex:
    ; Function to display a 16-bit hex value
    mov ecx, 4
    loop_display:
    rol esi, 4
    mov dl, byte [hex_chars + esi]
    mov [rsp + 7], dl
    mov eax, 1
    mov edi, 1
    mov edx, 1
    lea esi, [rsp + 7]
    syscall
    dec ecx
    jnz loop_display
    ret

hex_chars db "0123456789ABCDEF"

