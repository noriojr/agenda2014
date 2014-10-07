/***************************************************************************
 *            agenda.c
 *
 *  Qui agosto 28 21:43:20 2014
 *  Copyright  2014  Alcione Ferreira
 *  <user@host>
 ****************************************************************************/

#include <agenda.h>

void abrir (GtkWidget *Objeto, gpointer Dados)
	{
	AGENDA_DADOS *dados;
	printf ("%s:%d Carregando Dados\n",__FILE__,__LINE__);

	dados = Dados;
	
	}


void fechar (GtkWidget *Objeto, gpointer Dados)
	{
	printf ("%s:%d Fechando Programa\n",__FILE__,__LINE__);
	gtk_main_quit();

	}
/*funcao excluir*/

void excluir (GtkWidget *Objeto, gpointer Dados)
	{
	printf ("%s:%d Excluindo\n",__FILE__,__LINE__);

	}
/*funcao cancelar*/

void cancelar (GtkWidget *Cancelar, gpointer Dados )
{
	printf ("%s:%d Cancelando\n",__FILE__,__LINE__);	
}

/*fim funcao excluir*/


/*funcao navegar*/
void navegar (GtkWidget *Navegar, gpointer Dados )
{
	printf ("%s:%d Navegando\n",__FILE__,__LINE__);	
}

/*fim funcao navegar*/


/*funcao pesquisar*/


/*fim funcao pesquisar*/



/**
 * Procedimento status da janela
 */

void estatus(AGENDA* janela, int modo)
	{
	switch(modo)
		{
		case 1:
			{
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[0]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[1]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[2]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[3]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[4]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[5]),true);
			gtk_entry_set_editable (janela->EPesquisa,true);
			
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [0]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [1]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [2]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [3]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->ENav),false);

			break;
			}
		}
	}