set RA, 1
set RB, 1

cicle:
    add RAM[0]
    show RA
    mov RAM[0], RA
    jump @cicle
