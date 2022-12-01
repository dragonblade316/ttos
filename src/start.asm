bits 32
align 4

global start

section .text
start:
	; Set up stack pointer.
	mov esp, stack_end
	
	cli ;disable interupts

	extern kernel_main
	call kernel_main ; call c code

	hlt

; <tables>
global gdt_flush
extern gdtr
gdt_flush:
    lgdt [gdtr]        ; Load the GDT with our 'gdtr' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret

global idt_load
extern idtr
idt_load:
    lidt [idtr]
    ret
; </tables>

; TODO fin this
; <paging>
;global enable_paging
;enable_paging:
;    mov eax, page_directory
;    mov cr3, eax
;
;    mov eax, cr0
;    or eax, 0x80000001
;    mov cr0, eax



;TODO So basicly have a handler that will push the isr vector num onto the stack then enter c with the stack frame that the number is on as an argument

%macro isr_err_stub 1
isr_stub_%+%1:
    pushad ;push cpu_ctx onto stack
    mov eax, %1 ;err code
    push eax ;push err code onto stack
    call exception_handler
    pop eax
	popad
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    pushad ;push cpu_ctx onto stack
    mov eax, %1 ;err code
    push eax ;push err code onto stack
    call exception_handler
    pop eax
	popad
    iret
%endmacro

%macro irq_entry 1
irq_entry_%+%1:
    pushad ;push cpu_ctx onto stack
    mov eax, %1 ;err code
    push eax ;push err code onto stack
    call irq_handler
    pop eax
	popad
    iret
%endmacro

extern irq_handler
extern exception_handler
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
isr_no_err_stub 32

irq_entry 0
irq_entry 1
irq_entry 2
irq_entry 3
irq_entry 4
irq_entry 5
irq_entry 6
irq_entry 7
irq_entry 8
irq_entry 9
irq_entry 10
irq_entry 11
irq_entry 12
irq_entry 13
irq_entry 14
irq_entry 15




global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    33
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep

global irq_entry_table
irq_entry_table:
%assign i 0 
%rep    16
    dd irq_entry_%+i ; use DQ instead if targeting 64-bit
%assign i i+1
%endrep


SECTION .bss

stack_begin:
    RESB 4096  ; Reserve 4 KiB stack space
stack_end: