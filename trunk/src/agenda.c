/***************************************************************************
 *            agenda.c
 *
 *  Qui agosto 28 21:43:20 2014
 *  Copyright  2014  Alcione Ferreira
 *  <user@host>
 ****************************************************************************/

#include <agenda.h>

void ordenar (AGENDA *agenda) 
	{

	AGENDA_DADOS aux;
	int i,j,qtde;
	
	for(i=0; i<qtde; i++)/**percorre o campo nome dos regisros*/
		{
		for(j=0; j<qtde; j++)/**percorre o campo nome dos regisros*/
			{
			if(strcmp(agenda->dados[i].nome_pesquisa,agenda->dados[j].nome_pesquisa) < 0) 
				{
				aux = agenda->dados[i];
				agenda->dados[i] = agenda->dados[j];
				agenda->dados[j] = aux;
				}
			}
		}
	}

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
									strcpy(agenda->dados[i-1].nome_pesquisa,preparar(2,agenda->dados[i-1].nome));
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
					if (aux[a-1] == '\n')
						{
						aux[a-1] = '\0';
						}
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
	estatus(agenda,1);
	ordenar(agenda);
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
			if (i < dd->regs-1)
				{
				fprintf(arquivo,"\n");
				}
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
	AGENDA *dd;
	dd = Dados;
	dd->acao_atual = 2;
	estatus(dd,2);
	printf ("%s:%d Editando\n",__FILE__,__LINE__);
	gtk_window_set_focus (dd->Janela,GTK_WIDGET(dd->ENome));
	}
/*funcao cancelar*/

void cancelar (GtkWidget *Cancelar, gpointer Dados )
	{
	AGENDA *agenda;
	
	agenda = Dados;
	agenda->acao_atual = 0;
	estatus(agenda,1);
	carregar(agenda);
	}

/*fim funcao excluir*/

/*função novo*/
void novo (GtkWidget *Novo, gpointer Dados)


	{
	AGENDA *dd;
	
	dd = Dados;
	dd->acao_atual = 1;
	estatus(dd,2);
	gtk_entry_set_text(dd->ECodigo,"");
	gtk_entry_set_text(dd->ENome,"");
	gtk_entry_set_text(dd->EDDD,"");
	gtk_entry_set_text(dd->ETelefone,"");
	dd->BFObs = gtk_text_view_get_buffer (dd->TVObs);
	gtk_text_buffer_set_text (dd->BFObs,"",0);

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
	AGENDA *dd;
	AGENDA_DADOS dd_aux;
	dd = Dados;

	strcpy(dd_aux.nome,gtk_entry_get_text(dd->ENome));
	strcpy(dd_aux.nome_pesquisa,preparar(2,dd_aux.nome));
	strcpy(dd_aux.ddd,gtk_entry_get_text(dd->EDDD));
	strcpy(dd_aux.numero_telefone,gtk_entry_get_text(dd->ETelefone));
	dd->BFObs = gtk_text_view_get_buffer (dd->TVObs);
	gtk_text_buffer_get_start_iter (dd->BFObs, &dd->bfi);
	gtk_text_buffer_get_end_iter (dd->BFObs, &dd->bff);
	strcpy(dd_aux.observacao,gtk_text_buffer_get_text (dd->BFObs,&dd->bfi,&dd->bff,false));
	switch(dd->acao_atual)
		{
		case 1:
			{
			dd_aux.codigo = dd->dados[dd->regs-1].codigo+1;
			dd->regs++;
			dd->reg_atual = dd->regs-1;
			break;
			}
		case 2:
			{
			dd_aux.codigo = dd->dados[dd->reg_atual].codigo;
			break;
			}
		}
	dd->dados[dd->reg_atual] = dd_aux;
	carregar(dd);
	estatus(dd,1);
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
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[4]),true);
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
			gtk_entry_set_editable (janela->EPesquisa,true);
			gtk_window_set_focus (janela->Janela,GTK_WIDGET(janela->EPesquisa));
			break;
			}
		case 2:
			{
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[0]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[1]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[2]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[3]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[4]),false);
				
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [0]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [1]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [2]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->BTNav [3]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->ENav),false);
			gtk_entry_set_editable (janela->ENome,true);
			gtk_entry_set_editable (janela->EDDD,true);
			gtk_entry_set_editable (janela->ETelefone,true);
			gtk_text_view_set_editable (janela->TVObs,true);
			
			}
		case 3:
			{
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[0]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[1]),false);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[2]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[3]),true);
			gtk_widget_set_sensitive (GTK_WIDGET(janela->Botoes[4]),false);	
			break;
			}
		}
	}

void carregar(AGENDA *dd)
	{
	char *aux;

	//Atualização barra de navegação
	aux = (char *) malloc(sizeof(char)*32);
	sprintf (aux, "%ld/%ld",(dd->reg_atual+1),dd->regs);
	gtk_entry_set_text(dd->ENav,aux);
	free(aux);
	//Carregando código
	aux = (char *) malloc(sizeof(char)*64);gtk_entry_set_text(dd->ECodigo,aux);
	sprintf (aux, "%05ld",dd->dados[dd->reg_atual].codigo);
	gtk_entry_set_text(dd->ECodigo,aux);
	free(aux);
	//Carregando nome
	gtk_entry_set_text(dd->ENome,dd->dados[dd->reg_atual].nome);
	printf ("%s\n",dd->dados[dd->reg_atual].nome_pesquisa);
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
	char *saida, buff[7];
	int len, i, j;

	len = strlen(entrada);
	saida = (char *) malloc(sizeof(char)*(6*len));
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
		//Preparar campo de pesquisa
		case 2:
			{
			for (i=0; i < len; i++)
				{
				saida[i] = toupper(entrada[i]);
				}
			j = 3;
			printf ("%s - %d\n",saida,j);
			break;
			}
		}

	saida[j] = '\0';
	return (saida);
	}

void foco_ddd (GtkWidget *Objeto, gpointer Dados)
	{
	AGENDA *dd;
	dd = Dados;

	gtk_window_set_focus(dd->Janela,GTK_WIDGET(dd->EDDD));
	}

void foco_telefone (GtkWidget *Objeto, gpointer Dados)
	{
	AGENDA *dd;
	dd = Dados;

	gtk_window_set_focus(dd->Janela,GTK_WIDGET(dd->ETelefone));
	}
void foco_obs (GtkWidget *Objeto, gpointer Dados)
	{
	AGENDA *dd;
	dd = Dados;

	gtk_window_set_focus(dd->Janela,GTK_WIDGET(dd->TVObs));
	}
	
void foco_pesq (GtkWidget *Objeto, gpointer Dados)
	{
	AGENDA *dd;
	dd = Dados;

	gtk_window_set_focus(dd->Janela,GTK_WIDGET(dd->Botoes[5]));
	}
	
void pesquisar (GtkWidget *Objeto, gpointer Dados)
	{
	printf ("Pesquisando...\n");
	}