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
	GtkLabel *LTexto;


	//Alocando memória para montar o programa
	agenda = (AGENDA *) malloc(sizeof(AGENDA));
	if (agenda)
		{
		//Iniciando GTK+
		gtk_init (&argc, &argv);
		//Instanciando a Janela Principal


		agenda->Janela = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_size_request (GTK_WIDGET(agenda->Janela),600,300);
		gtk_window_set_title (agenda->Janela, "Agenda 2014 - PCI");
		Vbox = gtk_vbox_new (false,0);
		agenda->BarraMenu = gtk_toolbar_new ();
		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraMenu),false,false,0);
		agenda->Botoes[0] = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[0]),"Novo Registro","Novo Registro");

		agenda->Botoes[1] = gtk_tool_button_new_from_stock(GTK_STOCK_EDIT);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[1]),"Editar","Editar");

		agenda->Botoes[2] = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[2]),"Salvar Registro","Salvar Registro");

		agenda->Botoes[3] = gtk_tool_button_new_from_stock(GTK_STOCK_CANCEL);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[3]),"Cancelar","Cancelar");

		agenda->Botoes[4] = gtk_tool_button_new_from_stock(GTK_STOCK_REMOVE);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[4]),"Excluir","Excluir");

		agenda->Label = gtk_label_new_with_mnemonic("Pesquisar");
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Label),"Cancelar","Cancelar");

		agenda->EPesquisa = gtk_entry_new();
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->EPesquisa),"Entre com um nome","Entre com um nome");

		agenda->Botoes[5] = gtk_tool_button_new_from_stock(GTK_STOCK_FIND);
		gtk_toolbar_append_widget (agenda->BarraMenu,GTK_WIDGET(agenda->Botoes[5]),"Pesquisar","Pesquisar");
		//Montagem da Tela Interna
		/*Begin*/
		//Primeira linha Inicio
		Hbox = gtk_hbox_new (false,0);
		LTexto = gtk_label_new_with_mnemonic ("Código: ");
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(LTexto),false,false,0);
		agenda->ECodigo = gtk_entry_new ();
		gtk_widget_set_size_request (GTK_WIDGET(agenda->ECodigo),100,-1);
		gtk_entry_set_editable (agenda->ECodigo,false);
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(agenda->ECodigo),false,false,0);
		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(Hbox),false,false,0);
		//Primeira Linha Final
		//Segunda Linha Início

		//Segunda Linha Final
		//Terceira Linha Início
		Hbox = gtk_hbox_new (false,0);
		LTexto = gtk_label_new_with_mnemonic ("DDD: ");
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(LTexto),false,false,0);
		agenda->EDDD= gtk_entry_new ();
		gtk_widget_set_size_request (GTK_WIDGET(agenda->EDDD),32,-1);
		gtk_entry_set_editable (agenda->EDDD,false);
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(agenda->EDDD),false,false,0);
		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(Hbox),false,false,0);


		LTexto = gtk_label_new_with_mnemonic ("Telefone: ");
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(LTexto),false,false,0);
		agenda->ETelefone= gtk_entry_new ();
		gtk_widget_set_size_request (GTK_WIDGET(agenda->ETelefone),60,-1);
		gtk_entry_set_editable (agenda->ETelefone,false);
		gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(agenda->ETelefone),false,false,0);


		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(Hbox),false,false,0);
		//Terceira Linha Final
		//Quarta Linha Início

		//Quarta Linha Final
		//ToolBar Navegação Início
		agenda->BarraNav = gtk_toolbar_new ();
		gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraNav),false,false,0);
		agenda->BotoesNav[2] = gtk_tool_button_new_from_stock(GTK_STOCK_GO_DOWN);
		gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->BotoesNav [2]),"Proximo","Proximo");
		//ToolBar Navegação Final
		/*End*/
		agenda->BarraStatus = gtk_statusbar_new ();
		agenda->statusbar = gtk_statusbar_get_context_id(agenda->BarraStatus, "Agenda Eletrônica");
		agenda->statusbar = gtk_statusbar_push(agenda->BarraStatus, agenda->statusbar, "Agenda Eletrônica - PCI 2014");
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
