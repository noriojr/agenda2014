/***************************************************************************
 *            agenda.h
 *
 *  Qui agosto 28 21:43:20 2014
 *  Copyright  2014  Alcione Ferreira
 *  <user@host>
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#ifndef __AGENDA_H__
#define __AGENDA_H__ 1

#ifndef __agenda_dados__
#define __agenda_dados__ 1

typedef struct DADOS
	{
	long int codigo;
	char nome[101];
	char ddd[4];
	char numero_telefone[11];
	char observacao[1024];
	
	} AGENDA_DADOS;
#endif /*__agenda_dados__*/

#define ARQ_DADOS "dados.csv"

typedef struct Agenda
	{
	GtkWindow *Janela;
	GtkToolbar *BarraMenu, *BarraNav;
	GtkToolButton *Botoes[6], *BotoesNav[4];
	GtkStatusbar *BarraStatus;
	GtkEntry *EPesquisa, *ECodigo, *ENome, *EDDD, *ETelefone, *ENav;
	GtkTextView *TVObs;
	GtkLabel *Label;
	GtkButton *Pesq, *BTNav[4];
	guint statusbar;
	} AGENDA;

#define false 0
#define true 1

/**
 * Função para Abrir o Programa
 */
void abrir(GtkWidget *, gpointer );

/**
 * Função para fechar o Programa
 */
void fechar (GtkWidget *, gpointer);
void excluir (GtkWidget *, gpointer);

#endif /*__AGENDA_H__*/