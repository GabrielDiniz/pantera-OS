#include <system.h>

/* Estás são ISRs próprias que apontam para nosso tratamento especial de IRQ
*  ao invés da função regular 'fault_handler' */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* Este arranjo é realmente um arranjo de ponteiros de função. Nós usamos
*  estes para tratar de um IRQ de costume para um IRQ dado */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* Este instala um tratador de IRQ de costume para um IRQ dado */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* Este limpa o tratador para um IRQ dado */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/* Normalmente, IRQs 0 até 7 são mapeados para as entradas 8 até 15. Este
*  é um problema no modo protegido, porque a entrada IDT 8 é uma
*  Double Fault! Sem remapeamento, a todo tempo que o IRQ0 dispara,
*  você obterá uma Exceção Double Fault, que NÃO é realmente
*  o que queremos. Nós enviamos para o Controle Programável de
*  Interrupções (PICs - também chamado de 8259's) o comando
*  para fazer IRQ0 até 15 ser remapeado para as entradas IDT 32 até
*  47 */
void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/* Nós primeiramente remapeamos o controle de interrupções, e então instalamos
*  os ISRs apropriados para as entradas corretas na IDT. Este é justamente
*  parecido com a instalação dos tratamentos de exceções */
void irq_install()
{
    irq_remap();

	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Cada dos ISRs de IRQ apontam para esta função, em vez do
*  'fault_handler' em 'isrs.c'. O Controlador de IRQ necessita
*  ser avisado quando você está pronto para servi-lo então, assim
*  você precisa enviar quando um comando "Fim da Interrupção" (0x20).
*  Há dois chips 8259: O primeiro existe em 0x20, o segundo
*  existe em 0xA0. Se o segundo controlador (um IRQ de 8 até
*  15) obtêm uma interrupção, você precisa reconhecer a
*  interrupção de AMBOS controladores, de outro modo, você somente envia
*  um comando FDI (End of Interrupt (EOI)) para o primeiro controlador. 
*  Se você não enviar um FDI, você não obterá mais IRQs */
void irq_handler(struct regs *r)
{
    /* Este é um ponteiro de função vazio */
    void (*handler)(struct regs *r);

    /* Procura se nós temos um tratamento comum para rodar este
    *  IRQ, e então finalmente, roda-lo */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* Se a entrada IDT que foi invocada é maior que 40
    *  (significando IRQ8 - 15), então nós devemos enviar um FDI para
    *  o controlador slave */
    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }

    /* Em qualquer caso, nós deveremos enviar um FDI para o controlador
    *  de interrupções master também */
    outportb(0x20, 0x20);
}