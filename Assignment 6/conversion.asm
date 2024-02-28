section .data
    prompt db 'Enter your choice (a/b/c): ', 0
    input db 0
    hex_msg db 'Enter 4-digit Hex number: ', 0
    bcd_msg db 'Equivalent BCD number: ', 0
    bcd_num times 4 db 0
    bcd_num_len equ $ - bcd_num
    bcd_hex_msg db 'Enter 5-digit BCD number: ', 0
    hex_msg_len equ $ - hex_msg
    hex_num times 5 db 0
    hex_num_len equ $ - hex_num
    hex_bcd_msg db 'Equivalent Hex number: ', 0

section .text
    global _start
    
_start:
    ; Print the prompt and read user's choice
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 27
    int 0x80

    ; Read user's choice
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 2
    int 0x80

    ; Check the user's choice
    cmp byte [input], 'a'
    je hex_to_bcd
    cmp byte [input], 'b'
    je bcd_to_hex
    cmp byte [input], 'c'
    je exit_program

    ; Invalid choice, print error message and exit
    invalid_choice:
    mov eax, 4
    mov ebx, 1
    mov ecx, invalid_msg
    mov edx, 17
    int 0x80
    jmp _start

hex_to_bcd:
    ; Print the hex number prompt and read the input
    mov eax, 4
    mov ebx, 1
    mov ecx, hex_msg
    mov edx, hex_msg_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, hex_num
    mov edx, hex_num_len
    int 0x80

    ; Convert the hex number to BCD
    mov esi, hex_num
    mov edi, bcd_num
    mov ecx, 4
    
convert_hex_to_bcd:
    mov al, [esi]
    sub al, 0x30  ; Convert ASCII digit to binary
    add al, 9     ; Add 9 to get correct BCD value
    and al, 0x0F  ; Clear upper nibble
    mov [edi], al
    
    inc esi
    inc edi
    loop convert_hex_to_bcd

    ; Print the BCD number
    mov eax, 4
    mov ebx, 1
    mov ecx, bcd_msg
    mov edx, 21
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, bcd_num
    mov edx, bcd_num_len
    int 0x80

    jmp _start

bcd_to_hex:
    ; Print the BCD number prompt and read the input
    mov eax, 4
    mov ebx, 1
    mov ecx, bcd_hex_msg
    mov edx, 23
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, bcd_num
    mov edx, bcd_num_len
    int 0x80

    ; Convert the BCD number to hex
    mov esi, bcd_num
    mov edi, hex_num
    mov ecx, 4

convert_bcd_to_hex:
    mov al, [esi]
    and al, 0x0F   ; Clear upper nibble
    add al, 0x30   ; Convert binary to ASCII digit
    mov [edi], al
    
    inc esi
    inc edi
    loop convert_bcd_to_hex

    ; Print the hex number
    mov eax, 4
    mov ebx, 1
    mov ecx, hex_bcd_msg
    mov edx, 25
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, hex_num
    mov edx, hex_num_len
    int 0x80

    jmp _start

exit_program:
    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80
