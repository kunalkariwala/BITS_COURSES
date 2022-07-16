.model tiny
.data
    ent db 2 dup(?)
    a1 db 'Chemical Engineering $'
    a3 db 'Electrical & Electronics $'
    a4 db 'Mechanical Engineering $'
    a7 db 'Computer Science $'
    a8 db 'Electronics & Instrumentation $'
    aa db 'Electronics & Communication $'
    b1 db 'A1'
    b3 db 'A3'
    b4 db 'A4'
    b7 db 'A7'
    b8 db 'A8'
    bb db 'AA'
    disnl db 0DH, 0AH,'$'
.code
.startup

;taking the 2 character input
lea di, ent
mov cx,2
x0: mov ah, 01h
    int 21h
    mov [di],al
    inc di
    dec cx
    jnz x0

;comparing with A1
mov cx,2
lea di,ent
lea si,b1
x1: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz x2
    inc si
    inc di
    dec cx
    jnz x1
    ;string matched therefore print A1
    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, a1
    mov ah, 09h
    int 21h
    jmp xn

x2: mov cx,2
    lea di,ent
    lea si,b3
x3: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz x4
    inc si
    inc di
    dec cx
    jnz x3

    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, a3
    mov ah, 09h
    int 21h
    jmp xn

x4: mov cx,2
    lea di,ent
    lea si,b4
x5: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz x6
    inc si
    inc di
    dec cx
    jnz x5

    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, a4
    mov ah, 09h
    int 21h
    jmp xn

x6: mov cx,2
    lea di,ent
    lea si,b7
x7: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz x8
    inc si
    inc di
    dec cx
    jnz x7

    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, a7
    mov ah, 09h
    int 21h
    jmp xn

x8: mov cx,2
    lea di,ent
    lea si,b8
x9: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz x10
    inc si
    inc di
    dec cx
    jnz x9

    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, a8
    mov ah, 09h
    int 21h
    jmp xn

x10:mov cx,2
    lea di,ent
    lea si,bb
x11: mov bl,[di]
    mov bh,[si]
    cmp bl,bh
    jnz xn
    inc si
    inc di
    dec cx
    jnz x11

    lea dx, disnl
    mov ah, 09h
    int 21h

    lea dx, aa
    mov ah, 09h
    int 21h

xn: 
.exit
end