#include <system.h>
#include <lib/screen.h>

/* Você necessitará escrever esse você mesmo!  */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	
    /* Adicione código aqui para cópiar 'count' bytes de dados de 'src' para
    *  'dest', finalmente retornar 'dest' */
	while(count--)
	{
		*dest++ = *src++;
	}
	return dest;

}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    /* Adicione código aqui para atribuir 'count' bytes em 'dest' para 'val'.
    *  Outra vez, retorne 'dest' */
	while(count--)
	{
		*dest++ = val;
	}
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{


    /* Igual como acima, mas neste momento, nós trabalhamos com um ponteiro
    *  'val' e 'dest' de 16-bit. Seu código pode ser uma cópia exata do
    *  acima, providencie que suas variáveis locais se quaisquer, sejam
    *  unsigned short */
	while(count--)
	{
		*dest++ = val;
	}
	return dest;
}

int strlen(const char *str)
{
    /* Neste faço um laço através no arranjo (array) 'str', retornando quantos
    *  caracteres foram encontrados antes de achar um 0.
    *  Em poucas palavras, este retorna o comprimento de um string */
	int i=0;
	while(*str++ !='\0'){
		i++;
	}
	return i;
}

/* Nós vamos usar este mais tarde para ler as portas E/S para obter dados
*  de dispositivos tal como o teclado. Nós estamos usando o que é chamado de
*  'inline assembly' nestas rotinas para realmente fazer o trabalho */
unsigned char inportb (unsigned short _port)
{
	
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* Nós usamos este para escrever em portas E/S para enviar dados para dispositivos. Este
*  vai ser usados no próximo tutorial para mudar a posição do cursor no modo texto.
*  Outra vez, nós usamos algum inline assembly para uma coisa que simplesmente
*  não pode ser feita em C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

extern timer_ticks;
void sleep(int seconds){
	while(timer_ticks < timer_ticks + (seconds * 18222));
}
/* Este é uma função main() muito simples. Todo que faz é um
*  laço infinito. Este vai ser usado para nosso laço 'ocioso' */
int main()
{
    /* Você poderá adicionar comandos depois aqui */
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();
	__asm__ __volatile__ ("sti");
	
	init_video();
	int a;
	
	settextcolor(WHITE,BLACK);
	box(2,2,24,75);
	
	
    /* ...e deixe esse laço aqui. Há um laço sem fim em
    *  'start.asm' também, caso você acidentalmente deletar a próxima linha */
    for (;;);
	
	return 0;
}