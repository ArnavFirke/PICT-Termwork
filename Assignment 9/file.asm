; Program_1 - Read text file and count blank spaces, lines, and occurrence of a character

section .data
    filename db 'textfile.txt', 0
    filehandle dq 0

section .bss
    buffer resb 256
    char_count resd 1
    line_count resd 1
    blank_count resd 1

section .text
    global _start

_start:
    ; Open the file
    mov eax, 5
    mov ebx, filename
    mov ecx, 0
    int 0x80
    mov [filehandle], eax

    ; Read the file
    mov eax, 3
    mov ebx, [filehandle]
    mov ecx, buffer
    mov edx, 255
    int 0x80

    ; Close the file
    mov eax, 6
    mov ebx, [filehandle]
    int 0x80

    ; Find blank spaces, lines, and occurrence of a character
    xor ebx, ebx ; ebx = 0 (blank_count)
    xor edx, edx ; edx = 0 (line_count)
    mov esi, buffer

check_char:
    lodsb ; Load next character from buffer
    cmp al, 0 ; Check for end of string
    je finish

    ; Check for blank space
    cmp al, ' '
    je increment_blank

    ; Check for newline character
    cmp al, 0x0A
    je increment_line

    ; Check for occurrence of a particular character (e.g., 'A')
    cmp al, 'A'
    je increment_char

    jmp check_char

increment_blank:
    add ebx, 1
    jmp check_char

increment_line:
    add edx, 1
    jmp check_char

increment_char:
    add dword [char_count], 1
    jmp check_char

finish:
    ; Display the results
    mov eax, 1
    mov ebx, 1
    mov ecx, char_count
    mov edx, 4
    int 0x80

    mov eax, 1
    mov ebx, 1
    mov ecx, line_count
    mov edx, 4
    int 0x80

    mov eax, 1
    mov ebx, 1
    mov ecx, blank_count
    mov edx, 4
    int 0x80

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80
