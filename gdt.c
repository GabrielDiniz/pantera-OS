#include <system.h>

/* Define uma entrada GDT. Nós dizemos packed (empacotado), porque isto previne o
*  compilador de por coisas pensando ser melhores: Previne
*  compilação "otimizada" por empacotamento */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/* Ponteiro especial que inclui o limite: O máximo de bytes
*  tomados pela GDT, menos 1. Outra vez, este PRECISA ser packed (empacotado) */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Nossa GDT, com 3 entradas, e finalmente nosso ponteiro especial de GDT */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* Este é uma função do start.asm. Nós usamos este para apropriadamente
*  recarregar os novo registradores de segmento */
extern void _gdt_flush();

/* Atribui um descritor na Tabela de Descritores Global */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Atribui o endereço do descritor base */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Atribui os limites do descritor */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finalmente, atribui as flags de granularidade e de acesso */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* Precisa ser chamado por main. Este vai atribuir o ponteiro especial
*  GDT, atribui as primeiras 3 entradas na nossa GDT, e então
*  finalmente chama gdt_flush() em nosso arquivo assembly
*  para chamar o processador dizendo onde nossa nova GDT está e atualizar os
*  novos registradores de segmento */
void gdt_install()
{
    /* Atribui o ponteiro GDT e limite */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;

    /* Nosso descritor NULO (NULL) */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* A segunda entrada é nosso Segmento de Código (Code Segment). O endereço base
    *  é 0, o limite é 4GBytes, este usa granularidade de 4KByte,
    *  usa opcodes de 32-bit, e é um descritor de Segmento de Código.
    *  Por favor checar a tabela acima no tutorial
    *  para ver o que exatamente o que cada valor significa */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* A terceira entrada é nosso Segmento de Dados (Data Segment). Este é EXATAMENTE
    *  igual ao nosso segmento de código, mas o tipo de descritor neste
    *  byte de entrada diz que este é um Segmento de Dados */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Descarta a antiga GDT e instala as novas mudanças! */
    _gdt_flush();
}
		