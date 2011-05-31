#include <system.h>
#include <lib/strings.h>
#include <lib/colors.h>



/* Este guardará a trilha de quanto tiques que o sistema
*  tem sido corrido */
int timer_ticks = 0;
int show_time = 1;
int time = 0;
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
    if (timer_ticks % 18 == 0)
    {	
		time++;
        if(show_time)
		{
			settextcolor(MAGENTA,BLACK);
			putlc(itoa(time),0,75);
			settextcolor(0xf,0x0);
		}
    }
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

/*void DateAndTime()
{
	int RTCaddress, RTCdata, RTCtimeSecond, RTCtimeHour, RTCtimeMinute, RTCtimeDay, RTCtimeMonth, RTCtimeYear;
   // Set RTCaddress and RTCdata respectively first...
	RTCaddress = 0x70;
	RTCdata = 0x71; 
	asm
	(
	l1:    
		movb $10, %al           ;Get RTC register A
		out %al, RTCaddress        ; Think RTCaddress needs to be declared...
		in RTCdata, %al            ; RTCdata needs to be declared
		test $80, %al            ;Is update in progress?
		jne .l1             ; yes, wait
										
		movb $0, %al            ;Get seconds (00 to 59)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeSecond]

		movb $2, %al         ;Get minutes (00 to 59)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeMinute]

		movb $4, %al         ;Get hours (see notes)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeHour]

		movb $7, %al          ;Get day of month (01 to 31)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeDay]

		movb $8, %al         ;Get month (01 to 12)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeMonth]

		movb $9, %al         ;Get year (00 to 99)
		out %al, RTCaddress
		in RTCdata, %al
		movb %al, [RTCtimeYear]

		ret);
}*/