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
	AGENDA *agenda;
	FILE *arquivo;
	char *buffer, *aux, aux2[11];
	int i, c, a, r, j, n;
	printf ("%s:%d Carregando Dados\n",__FILE__,__LINE__);

	agenda = Dados;
	arquivo = fopen(ARQ_DADOS,"r");
	if (arquivo)
		{
		buffer = (char *) malloc (sizeof(char)*1210);
		if (buffer)
			{
			i=0;
			while(!feof(arquivo))
				{
				fgets(buffer,1210,arquivo);
				if (i > 0)
					{
					aux = (char *) malloc(sizeof(char)*1210);
					r=0;
					for (c=0, a=0; c < strlen(buffer); c++)
						{
						if (buffer[c] != ',')
							{
							aux[a] = buffer[c];
							a++;
							}
						else
							{
							aux[a] = '\0';
							switch(r)
								{
								case 0:
									{
									//printf("%s - %d\n",aux, i);
									agenda->dados[i-1].codigo = atoi(aux);
									//printf("%s - %d\n",aux, agenda->dados[i-1].codigo);
									break;
									}
								case 1:
									{
									//printf("%s\n",aux);
									strcpy(agenda->dados[i-1].nome,aux);
									break;
									}
								case 2:
									{
/*									printf("%s\n",aux);*/
									strcpy(agenda->dados[i-1].ddd,aux);
									break;
									}
								case 3:
									{
/*									printf("%s\n",aux);*/
									for (j=0,n=0; j < strlen(aux); j++)
										{
										if (j == 4)
											{
											aux2[n] = '-';
											n++;
											}
										aux2[n] = aux[j];
										n++;
										}
									aux2[n] = '\0';
									strcpy(agenda->dados[i-1].numero_telefone,aux2);
									break;
									}
								}
							a=0;
							r++;
							}
						}
					aux[a] = '\0';
/*					printf("%s\n",aux);*/
					strcpy(agenda->dados[i-1].observacao,aux);
/*					agenda->dados++;*/
					}
				//printf ("%s",buffer);
				i++;
				}
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
	agenda->regs = i-1;
	free(buffer);
	free(aux);
	agenda->reg_atual=0;
	carregar(agenda);
	}


void fechar (GtkWidget *Objeto, gpointer Dados)
	{
	int i;
	FILE *arquivo;
	AGENDA *dd;

	dd = Dados;
	arquivo = fopen(ARQ_DADOS,"w+");
	//arquivo = fopen("teste.csv","w+");
	if (arquivo)
		{
		fprintf(arquivo,"%d\n",dd->regs);
		for (i=0; i < dd->regs; i++)
			{
			fprintf(arquivo,"%d,%s,%s,%s,%s",dd->dados[i].codigo,dd->dados[i].nome,dd->dados[i].ddd,preparar(1,dd->dados[i].numero_telefone),dd->dados[i].observacao);
			}
		}
	else
		{
		printf ("Erro ao criar arquivo...");
		exit(1);
		}
	fclose(arquivo);
	//Fechar a Janela da Agenda



	gtk_main_quit();
	
	
	}

	
/*funcao excluir*/

void excluir (GtkWidget *Objeto, gpointer Dados)
	{
	printf ("%s:%d Excluindo\n",__FILE__,__LINE__);

	}
/*função editar*/
void editar (GtkWidget *Editar, gpointer Dados)
    {
	printf ("%s:%d Editando\n",__FILE__,__LINE__);

	}
/*funcao cancelar*/

void cancelar (GtkWidget *Cancelar, gpointer Dados )
{
	printf ("%s:%d Cancelando\n",__FILE__,__LINE__);	
}

/*fim funcao excluir*/

/*função novo*/
void novo (GtkWidget *Novo, gpointer Dados)
	{
	AGENDA *dd;

	dd = Dados;
	dd->acao_atual = 1;
	estatus(dd,2);
	gtk_window_set_focus (dd->Janela,GTK_WIDGET(dd->ENome));
	}
/*funcao navegar*/
void navegarprox (GtkWidget *Navegar, gpointer Dados )
	{
	AGENDA *dd;
	//printf ("%s:%d Navegando\n",__FILE__,__LINE__);	
	dd = Dados;
	if (dd->reg_atual < (dd->regs-1))
		{
		dd->reg_atual++;
		carregar(dd);
		}
	}

/*fim funcao navegar*/


/*funcao pesquisar*/


/*fim funcao pesquisar*/

/*funcao salvar*/
void salvar (GtkWidget *Salvar, gpointer Dados )
{
	printf ("%s:%d Salvando\n",__FILE__,__LINE__);	
}

/*fim funcao salvar*/

/*funcao inicio*/
void navegarinic (GtkWidget *Inicio, gpointer Dados )
	{
	AGENDA *dd;
		
	dd = Dados;
	if (dd->reg_atual > 0)
		{
		dd->reg_atual = 0;
		carregar(dd);
		}	
	}

/*fim funcao inicio*/

/*funcao voltar*/
void navegarvolt (GtkWidget *Votar, gpointer Dados )
	{
	AGENDA *dd;
		
	dd = Dados;
	if (dd->reg_atual > 0)
		{
		dd->reg_atual--;
		carregar(dd);
		}
	}
/*fim funcao voltar*/

/*funcao ultimo*/
void navegarulti (GtkWidget *Ultimo, gpointer Dados )
	{
	AGENDA *dd;
		
	dd = Dados;
	if (dd->reg_atual < (dd->regs-1))
		{
		dd->reg_atual = dd->regs-1;
		carregar(dd);
		}	
	}
/*fim funcao ultimo*/


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
			gtk_entry_set_editable (janela->ECodigo,false);
			gtk_entry_set_editable (janela->ENome,false);
			gtk_entry_set_editable (janela->EDDD,false);
			gtk_entry_set_editable (janela->ETelefone,false);
			break;
			}
		case 2:
			{
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [0]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [1]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [2]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [3]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->ENav),false);
			break;
			}
		}
	}

void carregar(AGENDA *dd)
	{
	char *aux;

	//Atualização barra de navegação
	aux = (char *) malloc(sizeof(char)*32);
	sprintf (aux, "%d/%d",(dd->reg_atual+1),dd->regs);
	gtk_entry_set_text(dd->ENav,aux);
	free(aux);
	//Carregando código
	aux = (char *) malloc(sizeof(char)*64);
	sprintf (aux, "%05d",dd->dados[dd->reg_atual].codigo);
	gtk_entry_set_text(dd->ECodigo,aux);
	free(aux);
	//Carregando nome
	gtk_entry_set_text(dd->ENome,dd->dados[dd->reg_atual].nome);
	//Carregando DDD
	gtk_entry_set_text(dd->EDDD,dd->dados[dd->reg_atual].ddd);
	//Carregando Telefone
	gtk_entry_set_text(dd->ETelefone,dd->dados[dd->reg_atual].numero_telefone);
	//Carregando Observacao
	dd->BFObs = gtk_text_view_get_buffer (dd->TVObs);
	gtk_text_buffer_set_text (dd->BFObs,"",0);
/*	gtk_text_buffer_get_bounds (dd->BFObs,dd->bfi,dd->bff);*/
	gtk_text_buffer_set_text (dd->BFObs,dd->dados[dd->reg_atual].observacao,strlen(dd->dados[dd->reg_atual].observacao));
	gtk_text_view_set_buffer (dd->TVObs,dd->BFObs);
	}

/**
 * Tratamento de Informações
 */
char *preparar(int modo, char *entrada)
	{
	char *saida;
	int len, i, j;

	len = strlen(entrada);
	saida = (char *) malloc(sizeof(char)*(2*len));
	switch(modo)
		{
		case 1:
			{
			//Remoção do hifem do número do telefone
			for (i=0,j=0; i < len; i++)
				{
				if (entrada[i] == '-')
					{
					i++;
					}
				saida[j] = entrada[i];
				j++;
				}
			break;
			}
		}

	saida[j] = '\0';
	return (saida);
	}