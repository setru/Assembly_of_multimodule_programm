section .data
    const4 dq 4.0
    format db "%lf", 0Ah, 0
section .bss
    ost resq 1
    x resq 1
    cwr resw 1
section .text
global f1
global f2
global f3

f1:
    push ebp
    mov ebp, esp
    and esp, -16
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fst qword[x]
    fld1
    faddp
    fld qword[const4]
    fxch
    fdivp
    fld1
    faddp
    leave
    ret
    
f2:
    push ebp
    mov ebp, esp
    and esp, -16
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fld qword[ebp + 8]
    fmulp
    leave
    ret
    
f3:
    push ebp
    mov ebp, esp
    and esp, -16
    finit
    fld1
    fld qword[ebp + 8]
    fchs
    fprem
    fst qword[ost]
    f2xm1
    faddp
    fld qword[ebp + 8]
    fchs
    fsub qword[ost]
    fld1
    fscale
    fmul st2
    leave
    ret
