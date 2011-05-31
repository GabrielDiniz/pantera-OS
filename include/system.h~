#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* SCRN.C */
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void scroll(void);
extern void move_csr(void);

/* GDT.C */
extern void gdt_install();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

/* IDT.C */
extern void idt_install();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

/* ISRS.C */
extern void isrs_install();

/* Este define qual pilha estamos olhando depois de um ISR estar rodando */
struct regs
{
	unsigned int ds, es, fs, gs;      /* últimos segmentos puxados */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* puxado por 'pusha' */
	unsigned int int_no, err_code;    /* nosso 'push byte #' e ecodes (códigos de erro) faz isto */
	unsigned int eip, cs, eflags, useresp, ss;   /* puxados pelo processador automaticamente */ 
}regs;

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();
		
/* TIMER.C */
extern void timer_install();
extern void timer_wait(int ticks);

/* KB.C */
extern void keyboard_install();

#endif
		