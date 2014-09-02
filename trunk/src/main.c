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
	GtkVBox *Vbox;
	GtkHBox *Hbox;

	//Alocando memória para montar o programa
	agenda = (AGENDA *) malloc(sizeof(AGENDA));
	if (agenda)
		{
		//Iniciando GTK+
		gtk_init (&argc, &argv);
		//Instanciando a Janela Principal
		agenda->Janela = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_size_request (GTK_WIDGET(agenda->Janela),400,300);
		gtk_window_set_title (agenda->Janela, "Agenda 2014 - PCI");
		Vbox = gtk_vbox_new (false,0);
		agenda->BarraMenu = gtk_toolbar_new ();
		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraMenu),false,false,0);
		agenda->Botoes[0] = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[0]),"Novo Registro","Novo Registro");
		agenda->BarraStatus = gtk_statusbar_new ();
		agenda->statusbar = gtk_statusbar_get_context_id(agenda->BarraStatus, "Agenda Eletrônica");
		agenda->statusbar = gtk_statusbar_push(agenda->BarraStatus, agenda->statusbar, "Agenda Eletrônica - PCI 2014");
		gtk_box_pack_end (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraStatus),false,false,0);
		//Conectando o sinal de Fechar na janela
		g_signal_connect (GTK_WIDGET(agenda->Janela), "destroy" ,G_CALLBACK (gtk_main_quit), agenda);
		//Mostrando a janela e seu Objetos
		gtk_container_add (GTK_CONTAINER(agenda->Janela),GTK_WIDGET(Vbox));
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