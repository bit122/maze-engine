.section .text
.global _start

_start:
    ldr   x0, =stack_top
    mov   sp, x0
    bl    main
1:  wfe
    b 1b

.section .bss
    .align 12
    .space 4096
stack_top: