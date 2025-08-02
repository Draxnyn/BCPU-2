set RA, 1
cicle:
    add RAM[0]
    mov RA, RB
    mov RAM[0], RA
    show RA
    jump @cicle
