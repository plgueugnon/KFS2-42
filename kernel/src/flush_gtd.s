; Source: http://www.osdever.net/bkerndev/Docs/gdt.htm
; More explanations here: https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global _gdt_flush     ; Allows the C code to link to this
extern _gp            ; Says that '_gp' is in another file
_gdt_flush:
    lgdt [_gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret               ; Returns back to the C code!