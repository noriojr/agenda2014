/***************************************************************************
 *            main.c
 *
 *  Qui agosto 28 21:42:19 2014
 *  Copyright  2014  Alcione Ferreira
 *  <user@host>
 ****************************************************************************/
#include <agenda.h>

int main (int argc, char **argv)
	{
	AGENDA *agenda;

	//Alocando memória para montar o programa
	agenda = (AGENDA *) malloc(sizeof(AGENDA));
	if (agenda)
		{
		//Iniciando GTK+
		gtk_init (&argc, &argv);
		//Instanciando a Janela Principal
		agenda->Janela = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		//Conectando o sinal de Fechar na janela
		g_signal_connect (GTK_WIDGET(agenda->Janela), "destroy",G_CALLBACK (gtk_main_quit), agenda);
		//Mostrando a janela e seu Objetos
		gtk_widget_show_all (GTK_WIDGET(agenda->Janela));
		//Iniciando o Loop do GTK+
		gtk_main ();
		}
	else
		{
		printf ("Erro ao inicar programa\n");
		exit(1);
		}
	return 0;
	}