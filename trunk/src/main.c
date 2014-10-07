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
	char *buffer;
	int registros;
	AGENDA *agenda;
	AGENDA_DADOS *dados_agenda;
	GtkVBox *Vbox;
	GtkHBox *Hbox;
	GtkLabel *LTexto;
	GtkFrame *FBox;
	
	FILE *dados_tel;

	registros = 0;
	dados_tel = fopen(ARQ_DADOS,"r+");
	if (dados_tel)
		{
		buffer = (char *) malloc (sizeof(char)*32);
		if (buffer)
			{
			fgets(buffer,32,dados_tel);
			registros = atoi(buffer);
			}
		else
			{
			printf ("Erro ao alocar memória para o buffer.\n");
			exit(1);
			}
		}
	else
		{
		printf ("Erro ao abrir arquivo de dados..\n");
		exit(1);
		}
	fclose(dados_tel);
	//Alocando memória para carregar os dados
	dados_agenda = (AGENDA_DADOS *) malloc (sizeof(AGENDA_DADOS)*registros);
	if (dados_agenda)
		{

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
			g_signal_connect (GTK_WIDGET(agenda->Botoes[3]), "clicked" ,G_CALLBACK (cancelar), agenda);
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
			
			Hbox = gtk_hbox_new (false,0);
			LTexto = gtk_label_new_with_mnemonic ("Nome:   ");
			gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(LTexto),false,false,0);
			agenda->ENome = gtk_entry_new ();
			//gtk_widget_set_size_request (GTK_WIDGET(agenda->ENome),400,-1);
			gtk_entry_set_editable (agenda->ENome,false);
			gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(agenda->ENome),true,true,0);
			gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(Hbox),false,true,0);
		
			//Segunda Linha Final
			//Terceira Linha Início
			Hbox = gtk_hbox_new (false,0);
			LTexto = gtk_label_new_with_mnemonic ("DDD: ");
			gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(LTexto),false,false,0);
			agenda->EDDD= gtk_entry_new ();
			gtk_entry_set_max_length (agenda->EDDD,3);
			gtk_widget_set_size_request (GTK_WIDGET(agenda->EDDD),40,-1);
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
			
			Hbox = gtk_hbox_new (false,0);
			FBox = gtk_frame_new ("Observação: ");
			gtk_box_pack_start (GTK_BOX(Hbox),GTK_WIDGET(FBox),true,true,0);
			agenda->TVObs= gtk_text_view_new ();
			gtk_widget_set_size_request (GTK_WIDGET(agenda->TVObs),-1,40);
			gtk_text_view_set_editable (agenda->TVObs,false);
			gtk_container_add (GTK_CONTAINER(FBox),GTK_WIDGET(agenda->TVObs));
			gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(Hbox),false,false,0);

			//Quarta Linha Final
			//ToolBar Navegação Início
			agenda->BarraNav = gtk_toolbar_new ();

			gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraNav),false,false,0);
			agenda->BTNav[0] = gtk_button_new_from_stock(GTK_STOCK_GOTO_FIRST);
			gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->BTNav [0]),"Inicio","Inicio");


			agenda->BTNav[1] = gtk_button_new_from_stock(GTK_STOCK_GO_BACK);
			gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->BTNav [1])," Voltar","Voltar");


			agenda->ENav = gtk_entry_new ();
			gtk_entry_set_text (agenda->ENav , "1/1");//criar entry
			gtk_widget_set_size_request (GTK_WIDGET(agenda->ENav),70,-1);
			gtk_entry_set_editable (agenda->ENav,false);
			gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->ENav ),"1/1","1/1");

			gtk_entry_set_alignment( agenda->ENav, 0.5 );
								   /*Entry			posição*/
				
			gtk_box_pack_start (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraNav),false,false,0);
			
		
			//agenda->BotoesNav[2] = gtk_tool_button_new_from_stock(GTK_STOCK_GO_FORWARD);
			agenda->BTNav[2] = gtk_button_new_from_stock(GTK_STOCK_GO_FORWARD);
			gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->BTNav [2]),"Proximo","Proximo");

										
			//ToolBar Navegação Final
			agenda->BTNav[3] = gtk_button_new_from_stock(GTK_STOCK_GOTO_LAST);
			gtk_toolbar_append_widget (agenda->BarraNav,GTK_WIDGET(agenda->BTNav [3])," Ultimo","Ultimo");
			
			/*End*/
			agenda->BarraStatus = gtk_statusbar_new ();
			agenda->statusbar = gtk_statusbar_get_context_id(agenda->BarraStatus, "Agenda Eletrônica");
			agenda->statusbar = gtk_statusbar_push(agenda->BarraStatus, agenda->statusbar, "Agenda Eletrônica - PCI 2014");
			gtk_box_pack_end (GTK_BOX(Vbox),GTK_WIDGET(agenda->BarraStatus),false,false,0);
			//Conectando o sinal de Abrir na Janela
			g_signal_connect (GTK_WIDGET(agenda->Janela), "show" ,G_CALLBACK (abrir), dados_agenda);
			//Conectando o sinal de Fechar na janela
	/*	    g_signal_connect (GTK_WIDGET(agenda->Janela), "destroy" ,G_CALLBACK (gtk_main_quit), agenda);*/
			g_signal_connect (GTK_WIDGET(agenda->Janela), "destroy" ,G_CALLBACK (fechar), agenda);

			g_signal_connect (GTK_WIDGET(agenda->Botoes[4]), "clicked" ,G_CALLBACK (excluir), agenda);
			g_signal_connect (GTK_WIDGET(agenda->BTNav[2]), "clicked" ,G_CALLBACK (navegarprox), agenda);
			g_signal_connect (GTK_WIDGET(agenda->BTNav[0]), "clicked" ,G_CALLBACK (navegarinic), agenda);
			g_signal_connect (GTK_WIDGET(agenda->BTNav[1]), "clicked" ,G_CALLBACK (navegarvolt), agenda);
			g_signal_connect (GTK_WIDGET(agenda->BTNav[3]), "clicked" ,G_CALLBACK (navegarulti), agenda);
			g_signal_connect (GTK_WIDGET(agenda->Botoes[2]), "clicked" ,G_CALLBACK (salvar), agenda);

			//Mostrando a janela e seu Objetos
			gtk_container_add (GTK_CONTAINER(agenda->Janela),GTK_WIDGET(Vbox));
			gtk_widget_show_all (GTK_WIDGET(agenda->Janela));

			estatus(agenda,1);
			gtk_window_set_focus(agenda->Janela, GTK_WIDGET(agenda->EPesquisa));
			
			//Iniciando o Loop do GTK+
			gtk_main ();
			}
		else
			{
			printf ("Erro ao inicar programa\n");
			exit(1);
			}
		}
	else
		{
		printf ("Erro ao alocar memória para os dados\n");
		exit(1);
		}
	return 0;
	}
