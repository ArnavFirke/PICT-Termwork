; Program_2 - FAR PROCEDURES for further processing

section .data
    extern char_count : dword
    extern line_count : dword
    extern blank_count : dword

section .text
    global _start

_start:
    ; Calculate the sum of blank spaces, lines, and character occurrences
    mov eax, [char_count]
    add eax, [line_count]
    add eax, [blank_count]

    ; Display the sum
    mov ebx, 1
    mov ecx, eax
    mov edx, 4
    mov eax, 1
    int 0x80

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80