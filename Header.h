/* 
 * File:   Header.h
 * Author: theus
 *
 * Created on 2 de Setembro de 2013, 23:20
 */

#ifndef HEADER_H
#define	HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_PAGINA 10

const char *nomeArquivoPaginas = "paginas.out";
const char *nomeArquivoTries = "nos.out";
const char *nomeArquivoAuxiliar = "auxiliar.out";

typedef struct Palavra{
	char self[50];
	int tipo;
	//int subTipo1, subTipo2, subTipo3;
        char classe, genero, numero; 
        int pessoa, conjugacao;
}Palavra;

typedef struct Pagina{
	int prox;
	Palavra palavras[TAM_PAGINA];
}Pagina;

typedef struct No{
	int pai, fEsq, fDir;
        bool terminal;
	char valor;
	int pos;
}No;

typedef struct Auxiliar{
	int primeiroNo, ultimoNo, primeiraPagina, ultimaPagina;
}Auxiliar;

void inserePalavra(char *asPalavra, char acClasse, char acGenero, char acNumero, int aiPessoa, int aiConjugacao );
void AtualizaNo(No *no, int aiPosicao);
void AtualizaPagina(Pagina *pagina, int aiPosicao);
No* CarregaNo(int aiPosicao);
Pagina* CarregaPagina(int aiPosicao);
int GetPrimeiraPagina();
int GetPrimeiroNo();
int GetUltimaPagina();
int GetUltimoNo();
void GravaNovaPagina(Pagina *aPagina);
void GravaNovoNo(No *aNo);
void SetPrimeiraPagina(int aiNovo);
void SetPrimeiroNo(int aiNovo);
void SetUltimaPagina(int aiNovo);
void SetUltimoNo(int aiNovo);
void InicializaArquivos();
void InicializaPalavra(Palavra *aoPalavra);
void InicializaNo(No *aoNo);
void InicializaPagina(Pagina *aoPagina);
void OrdenaPagina(Pagina *pagina);
bool PaginaCheia(Pagina *aoPagina);

#endif	/* HEADER_H */

