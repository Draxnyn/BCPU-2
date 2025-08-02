set RA, 2
set RB, 2
cicle:
    add RAM[0]
    show RA
    mov RAM[0], RA
    jump @cicle
