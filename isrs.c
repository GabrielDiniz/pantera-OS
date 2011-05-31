#include <system.h>

/* Estás são protótipos de funções de toda as tratamentos de
*  exceções: As primeiras 32 entradas na IDT são reservadas
*  pela Intel, e são designadas para interrupções de serviços! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* Está é uma função muito repetitiva... não é difícil, é
*  somente aborrecedor. Como você pode ver, nós atribuímos as 32 entradas
*  na IDT para as primeiras 32 ISRs. Nós não podemos usar um laço for
*  para este, porque não a caminho de se obter os nomes das funções
*  que correspondem para cada entrada. Nós atribuímos as flags de
*  entrada para 0x8E. Fazer que a entrada esteja presente, está
*  rodando em ring 0 (nível kernel), e que os 5 bits inferiores
*  estejam atribuídos para o requerido '14', que é representado por 'E' 
*  em hexadecimal. */
void isrs_install()
{
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)isr25, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)isr26, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)isr27, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)isr28, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}

/* Este é um simples arranjo de string. Que contêm as mensagens que
*  correspondem para cada e toda exceção. Nós obtemos a mensagem
*  correta acessando por:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
{
    "Não existe divisão por zero, porra!",
    "Debug",
	"Non Maskable Interrupt",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
	"Error",
    "Reserved",
    "Reserved"
};

/* Todas nossas exceções tratadas pelas Rotinas de Serviço de Interrupção vão
*  apontar para esta função. Este vai nos dizer qual exceção tem
*  ocorrido! Diretamente agora, nós simplesmente vamos parar o sistema pelo usando um
*  laço sem fim. Todas ISRs desabilitam interrupções enquanto estes estão sendo
*  servidos como um mecanismo de 'tranca' para prevenir que um IRQ
*  ocorra e perdendo as estruturas de dados do kernel */
void fault_handler(struct regs *r)
{
    /* Está é uma falta cujo o números é de 0 até 31? */
    if (r->int_no < 32)
    {
        /* Exibe a descrição para a Exceção que ocorreu.
        *  Neste tutorial, nós vamos simplesmente parar o sistema usando um
        *  laço infinito */
        puts(exception_messages[r->int_no]);
        puts(" Exception. Sistema Parado!\n");
        //for (;;);
    }
}