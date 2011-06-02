#include <system.h>
#include <lib/strings.h>
#include <lib/colors.h>



/* Este guardará a trilha de quanto tiques que o sistema
*  tem sido corrido */
int timer_ticks = 0;
int show_time = 1;
int time = 0;

int ReadFromCMOS(int _register)
{
	unsigned char tvalue;
	
	asm("cli");             /* Disable interrupts*/
	outportb(0x70,_register);
	tvalue = inportb(0x71);
	tvalue = (int)( (tvalue & 0xF0) >> 1) + ( (tvalue & 0xF0) >> 3) + (tvalue & 0xf);
        asm("sti");         /* Enable interrupts*/
	return tvalue;
}
/* Trata o temporizador. Neste caso, é muito simples: nós
*  incrementamos a variável 'timer_ticks' sempre que o temporizador
*  dispara. Por padrão, o temporizador dispara 18.222 tempos
*  por segundo. Como 18.222Hz? Algum engenheiro na IBM deve
*  ter fumado alguma coisa simplesmente */
void timer_handler(struct regs *r)
{
	/* Incrementa nosso 'tick count' */
    timer_ticks++;
	
    /* Todo 18ª vez (aproximadamente 1 segundo), nós vamos
    *  mostrar uma mensagem na tela */
    /*if (timer_ticks % 18 == 0)
    {	
		time++;
        if(show_time)
		{*/
			settextcolor(MAGENTA,BLACK);
			putlc(itoa(ReadFromCMOS(0x4)),0,70);
			putlc(":",0,72);
			putlc(itoa(ReadFromCMOS(0x2)),0,73);
			putlc(":",0,75);
			putlc(itoa(ReadFromCMOS(0x0)),0,76);
			settextcolor(0xf,0x0);
		/*}
    }*/
}

/* Atribui o relógio do sistema instalando o temporizador
*  no IRQ0 */
void timer_install()
{
    /* Instala 'timer_handler' no IRQ0 */
    irq_install_handler(0, timer_handler);
}

/* Este ficar continuamente no laço até o tempo dado
*  ser alcançado */
void timer_wait(int ticks)
{
	unsigned long eticks;

	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks);
}
