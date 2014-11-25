/***************************************************************************
 *            agenda.h
 *
 *  Qui agosto 28 21:43:20 2014
 *  Copyright  2014  Alcione Ferreira
 *  <user@host>
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <icones.h>
#include <ctype.h>

#ifndef __AGENDA_H__
#define __AGENDA_H__ 1

#ifndef __agenda_dados__
#define __agenda_dados__ 1

typedef struct DADOS
	{
	long int codigo;
	char nome[101];
	char ddd[4];
	char numero_telefone[11];//9999-9999
	char observacao[1024];
	char nome_pesquisa[3];
	} AGENDA_DADOS;
#endif /*__agenda_dados__*/

#define ARQ_DADOS "dados.csv"
#define IMG_ICO "img/agenda.ico"

typedef struct Agenda
	{
	GtkWindow *Janela;
	GtkToolbar *BarraMenu, *BarraNav;
	GtkToolButton *Botoes[6], *BotoesNav[4];
	GtkStatusbar *BarraStatus;
	GtkEntry *EPesquisa, *ECodigo, *ENome, *EDDD, *ETelefone, *ENav;
	GtkTextView *TVObs;
	GtkTextBuffer *BFObs;
	GtkTextIter bfi, bff;
	GtkLabel *Label;
	GtkButton *Pesq, *BTNav[4];
	guint statusbar;
	AGENDA_DADOS *dados;
	long int regs;
	long int reg_atual;
	int acao_atual;
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
void navegarprox (GtkWidget *, gpointer);
void salvar (GtkWidget *, gpointer);

void navegarinic (GtkWidget *, gpointer);
void navegarvolt (GtkWidget *, gpointer);
void navegarulti (GtkWidget *, gpointer);
/**
 * Função para cancelar 
 */
void cancelar (GtkWidget *, gpointer);

/**
 * Procedimento para setar o status da janela
 */
void estatus(AGENDA* , int );
/**
 * Função novo
 */
void novo (GtkWidget *, gpointer);
/**
 * função editar
 */
void editar (GtkWidget *, gpointer);


/**
 * Procedimento para preencher campos da janela
 */
void carregar(AGENDA *);

/**
 * Tratamento de Informações
 */
char *preparar(int, char *);
/**
 * Função Foco
 */
void foco_ddd (GtkWidget *, gpointer); 

void foco_telefone (GtkWidget *, gpointer);

void foco_obs (GtkWidget *, gpointer);

void foco_pesq (GtkWidget *, gpointer);

void pesquisar (GtkWidget *, gpointer);

void so_numero (GtkWidget *, gpointer);

#endif /*__AGENDA_H__*/