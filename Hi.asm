section .data

msg db 'Hello my friend, Help me pls', 10 ; Create Memory String
l equ $ - msg ; Lean "msg"

section .text

global _start ; Create _start

_start:
 mov rax, 1 ; Mov rax, value sys_read
 mov rdi, 1 ; mov rdi, value sys_read++
 mov rsi, msg ; get value string "msg" for rsi
 mov rdx, l ; Get poin for rdx
 syscall ; get permission for system [Linux]
 
 mov rax, 60 ; get value sys_write
 xor rdi, rdi ; Clear for rdi
 syscall ; Get permission for system [Linux]
 
 