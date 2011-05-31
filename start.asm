; Este é o ponto de entrada do kernel. Nós podemos chamar o main aqui,
; ou nós podemos usar este para atribuir a pilha ou outras coisas simpáticas, principalmente
; talvez atribuir a GDT e segmentos. Por favor note que as interrupções
; estão desativadas neste ponto: Mas vamos liga-las mais tarde!
[BITS 32]
start:
    mov esp, _sys_stack     ; Aponta a pilha para sua nova área de pilha
    jmp stublet

; Está parte DEVE ser 4Byte alinhada, assim resolvemos a questão usando 'ALIGN 4'
ALIGN 4
mboot:
    ; Macros multiboot para fazer umas poucas linhas mais tarde serem mais legíveis
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    ; Este é o cabeçalho do Multiboot GRUB. Uma assinatura de boot
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    
    ; AOUT kludge - precisa ser endereços físicos. Faça uma nota disto:
    ; O script de linker preenche os dados para uns destes!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; Este é um laço sem fim aqui. Faça uma nota disto: Mais tarde, nós
; vamos inserir um 'extern _main', seguido por 'call _main', diretamente
; antes do 'jmp $'.
stublet:
	extern main
	call main
	jmp $


; Brevemente nós vamos adicionar código para carregar a GDT bem aqui!
; Este vai atribuir nossos novos registradores de segmento. Nó precisaremos somente
; fazer algo especial para atribuir CS. Nós faremos o que é chamado de
; um salto longo. Um salto que inclui um segmento assim como um offset.
; Este é declarado em C como 'extern void gdt_flush();'
global _gdt_flush     ; Permite ao código C juntar este
extern gp            ; Diz que '_gp' está em outro arquivo
_gdt_flush:
    lgdt [gp]        ; Carrega GDT com nosso ponteiro especial '_gp'
    mov ax, 0x10      ; 0x10 é o offset na GDT para nosso segmento de dados
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush2   ; 0x08 é o offset para nosso segmento de código: Salto longo!
flush2:
    ret               ; Retorna para o código C!

; Carrega a IDT definida como '_idtp' dentro do processador.
; Este é declarado em C como 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret
		
; Em somente algumas páginas deste tutorial, nós vamos adicionar sua Rotina
; para Serviço de Interrupção (ISRs) bem aqui!

; Em poucas paginas neste tutorial, nós iremos adicionar nossas
; Rotinas para Serviço de Interrupção (ISRs) diretamente aqui!

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0    ; Uma ponta normal de ISR retira uma cópia do código de erro para guardar uma
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

isr2:
    cli
    push byte 0
    push byte 2
    
    jmp isr_common_stub

isr3:
	cli
	push byte 0
	push byte 3
	
	jmp isr_common_stub
	
isr4:
    cli
    push byte 0
    push byte 4
    
    jmp isr_common_stub
                
isr5:
    cli
    push byte 0
    push byte 5
    
    jmp isr_common_stub; 

isr6:
    cli
    push byte 0
    push byte 6

    jmp isr_common_stub

isr7:
    cli
    push byte 0
    push byte 7

    jmp isr_common_stub

isr8:
    cli
    push byte 8
    jmp isr_common_stub

isr9:
    cli
    push byte 0
    push byte 9

    jmp isr_common_stub

isr10:
    cli
    push byte 10

    jmp isr_common_stub

isr11:
    cli
    push byte 11
    
    jmp isr_common_stub

isr12:
    cli
    push byte 12
    
    jmp isr_common_stub

isr13:
    cli
    push byte 13
    
    jmp isr_common_stub

isr14:
    cli
    push byte 14
    
    jmp isr_common_stub

isr15:
    cli
    push byte 0
    push byte 15
    
    jmp isr_common_stub

isr16:
    cli
    push byte 0
    push byte 16
    
    jmp isr_common_stub

isr17:
    cli
    push byte 0
    push byte 17
    
    jmp isr_common_stub

isr18:
    cli
    push byte 0
    push byte 18
    
    jmp isr_common_stub

isr19:
    cli
    push byte 0
    push byte 19
    
    jmp isr_common_stub

isr20:
    cli
    push byte 0
    push byte 20
    
    jmp isr_common_stub

isr21:
    cli
    push byte 0
    push byte 21
    
    jmp isr_common_stub

isr22:
    cli
    push byte 0
    push byte 22
    
    jmp isr_common_stub

isr23:
    cli
    push byte 0
    push byte 23
    
    jmp isr_common_stub

isr24:
    cli
    push byte 0
    push byte 24
    
    jmp isr_common_stub

isr25:
    cli
    push byte 0
    push byte 25
    
    jmp isr_common_stub

isr26:
    cli
    push byte 0
    push byte 26
    
    jmp isr_common_stub

isr27:
    cli
    push byte 0
    push byte 27
    
    jmp isr_common_stub

isr28:
    cli
    push byte 0
    push byte 28
    
    jmp isr_common_stub

isr29:
    cli
    push byte 0
    push byte 29

    jmp isr_common_stub

isr30:
    cli
    push byte 0
    push byte 30

    jmp isr_common_stub

isr31:
    cli
    push byte 0
    push byte 31

    jmp isr_common_stub


; Nós chamamos uma função C aqui. Nós precisamos dizer ao assembler saiba
; que '_fault_handler' existe em outro arquivo
extern fault_handler

; Esta é nossa partes comuns de ISR. Este salva o estado do processador, atribui
; os segmentos para modo kernel, chama o tratamento nível-C de faltas,
; e finalmente restaura a moldura da pilha.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Carrega o descritor de Segmento de Dados do Kernel!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Puxa nossa pilha
    push eax
    mov eax, fault_handler
    call eax       ; Uma chamada especial, preserva o registrador 'eip'
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Limpa o código de erro puxado e o número da ISR puxada
    iret           ; retira 5 coisas de uma vez: CS, EIP, EFLAGS, SS, e ESP!

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 32: IRQ0
irq0:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 32
    jmp irq_common_stub


irq1:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 33
    jmp irq_common_stub

irq2:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 34
    jmp irq_common_stub

irq3:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 35
    jmp irq_common_stub

irq4:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 36
    jmp irq_common_stub

irq5:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 37
    jmp irq_common_stub

irq6:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 38
    jmp irq_common_stub

irq7:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 39
    jmp irq_common_stub

irq8:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 40
    jmp irq_common_stub

irq9:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 41
    jmp irq_common_stub

irq10:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 42
    jmp irq_common_stub

irq11:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 43
    jmp irq_common_stub

irq12:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 44
    jmp irq_common_stub

irq13:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 45
    jmp irq_common_stub

irq14:
    cli
    push byte 0    ; Note que este não puxa um código de erro para a pilha:
                   ; Nós iremos puxar uma imitação de código de erro
    push byte 46
    jmp irq_common_stub

irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern irq_handler

; Esta é uma parte que nós temos criado para IRQ baseado em ISRs. Estes chamam
; '_irq_handler' em nosso código C. Nós devemos criar este em 'irq.c'
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; Está é uma definição do sua seção de BSS. Agora mesmo, nós usaremos
; este justamente para guardar a pilha. Lembre-se que uma pilha atualmente cresce
; para baixo, assim nós declaramos o tamanho dos dados antes de declarar
; o identificador '_sys_stack'
SECTION .bss
    resb 8192               ; Este reserva 8KBytes da memória aqui
_sys_stack:
