/* 
 * File:   Main.c
 * Author: theus
 *
 * Created on 2 de Setembro de 2013, 23:20
 */


#include "Header.h"


int main() {
    char f = ' ';
    char palavra[30], classe, genero, numero;
    int pessoa, conjugacao;
    
    InicializaArquivos();

    do {
        scanf(" %c", &f);
        switch (f) {
            case 'i': 
                scanf(" %s", palavra);
                scanf(" %c", &classe);
                if (classe == 's') {
                    scanf(" %c", &genero);
                    scanf(" %c", &numero);
                    inserePalavra(palavra, classe, genero, numero, -1, -1);
                }
                if (classe == 'a') {
                    scanf(" %c", &genero);
                    inserePalavra(palavra, classe, genero, 'z', -1, -1);
                }
                if (classe == 'p')
                    inserePalavra(palavra, classe, 'z', 'z', -1, -1);
                if (classe == 'v') {
                    scanf(" %d", &pessoa);
                    scanf(" %c", &numero);
                    scanf(" %d", &conjugacao);
                    inserePalavra(palavra, classe, 'z', numero, pessoa, conjugacao);
                }      
                break;
            case 't':
                //porTroca();
                break;
            case 'a':
               // porInsercao();
                break;
            case 'r':
                //porRemocao();
                break;
            case 'f':
                //dadosDePalavra();
                break;
            case 'o':
                //palavraEmOrde();
                break;
            case 'p':
               //imprimeEstrutura();
                break;
            case 'd':
                //removePalavra();
                break;
        }
    } while (f != 'e');

    return 0;
}

void InicializaArquivos() {
	
	FILE *fpAuxiliar;
	Auxiliar *inicializador;

	fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
	if(fpAuxiliar == NULL) {
		FILE *fpIndices;
		FILE *fpPaginas;
		fpAuxiliar = fopen(nomeArquivoAuxiliar, "w+b");
		fpIndices = fopen(nomeArquivoTries, "w+b");
		fpPaginas = fopen(nomeArquivoPaginas, "w+b");
		inicializador = (Auxiliar*)malloc(sizeof(Auxiliar));
		inicializador->primeiraPagina = 0;
		inicializador->ultimaPagina = -1;
		inicializador->primeiroNo = 0;
		inicializador->ultimoNo = -1;
		fwrite(inicializador, sizeof(struct Auxiliar), 1, fpAuxiliar);
		fclose(fpIndices);
		fclose(fpPaginas);
	}
	fclose(fpAuxiliar);
}

void inserePalavra(char *asPalavra, char acClasse, char acGenero, char acNumero, int aiPessoa, int aiConjugacao ){
    printf("Palavra: %s Classe: %c Genero: %c Numero %c Pessoa %d Conjugacao %d\n", asPalavra, acClasse, acGenero, acNumero, aiPessoa, aiConjugacao);
    Pagina *loPagina;
    int i;
    //cria uma nova palavra com os dados fornecidos pelo usuario
    Palavra *loNovaPalavra;
    loNovaPalavra = (Palavra*)malloc(sizeof(Palavra));
    strcpy(loNovaPalavra->self, asPalavra);
    loNovaPalavra->classe = acClasse;
    loNovaPalavra->genero = acGenero;
    loNovaPalavra->numero = acNumero;
    loNovaPalavra->pessoa = aiPessoa;
    loNovaPalavra->conjugacao = aiConjugacao;
    //Se eh a primeira vez que uma palavra eh cadastrada
    if(GetUltimaPagina() == -1) {        
        loPagina = (Pagina*)malloc(sizeof(Pagina));
        InicializaPagina(loPagina);
        loPagina->palavras[0] = *loNovaPalavra;
        GravaNovaPagina(loPagina);
        return;
    }
    //Se nenhum no foi criado ainda
    if(GetUltimoNo() == -1) {
        loPagina = CarregaPagina(GetPrimeiraPagina()); 
        //Se a pagina nao esta cheia
        if(!PaginaCheia(loPagina)) {
            for(i = 0; i < TAM_PAGINA; i++) {
                if(loPagina->palavras[i].classe == 'z') {
                    loPagina->palavras[i] = *loNovaPalavra;
                    OrdenaPagina(loPagina);
                    AtualizaPagina(loPagina, 0);
                    return;
                }
            }
        }
        //A pagina esta cheia e eh preciso criar o primeiro No (talvez mais de um), uma nova pagina e dividir as palavras
        No *loNovoNo;
        Pagina *loNovaPagina;
        loNovoNo = (No*)malloc(sizeof(No));
        loNovaPagina = (Pagina*)malloc(sizeof(Pagina));
        InicializaNo(loNovoNo);
        InicializaPagina(loNovaPagina);
    }
    
}

void OrdenaPagina(Pagina *pagina) {
	Palavra *palavraAuxiliar;
	int i, j;
	palavraAuxiliar = (Palavra*)malloc(sizeof(Palavra));
	for(i = 0; i < TAM_PAGINA - 1; i++) {
		for(j = i + 1; j < TAM_PAGINA; j++) {
			if(pagina->palavras[j].classe != 'z') {
				if(strcmp(pagina->palavras[i].self, pagina->palavras[j].self) > 0) {
					*palavraAuxiliar = pagina->palavras[i];
					pagina->palavras[i] = pagina->palavras[j];
					pagina->palavras[j] = *palavraAuxiliar;
				}
			}
		}
	}
}

bool PaginaCheia(Pagina *aoPagina) {
    int i;
    for (i = 0; i < TAM_PAGINA; i++) {
        if (aoPagina->palavras[i].classe == 'z')
            return false;
    }
    return true;
}

void InicializaPalavra(Palavra *aoPalavra) {
    //aoPalavra->self = "";
    strcpy(aoPalavra->self, "");
    aoPalavra->tipo = -1;
    aoPalavra->genero = 'z';
    aoPalavra->classe = 'z';
    aoPalavra->numero = 'z';
    aoPalavra->conjugacao = -1;
    aoPalavra->pessoa = -1;   
}

void InicializaNo(No *aoNo) {
    aoNo->fDir = -1;
    aoNo->fEsq = -1;
    aoNo->pos = -1;
    aoNo->valor = '\n';
    aoNo->terminal = true;
}

void InicializaPagina(Pagina *aoPagina) {
    Palavra *palavra;
    int i;
    palavra = (Palavra*)malloc(sizeof(Palavra));
    InicializaPalavra(palavra);
    aoPagina->prox = -1;
    for(i = 0; i <TAM_PAGINA; i++)
        aoPagina->palavras[i] = *palavra;
}

void AtualizaNo(No *no, int aiPosicao) {
    FILE *fpNos;
    fpNos = fopen(nomeArquivoTries, "r+b");
    fseek(fpNos, aiPosicao * sizeof (No), SEEK_SET);
    fwrite(no, sizeof (No), 1, fpNos);
    fclose(fpNos);
}

void AtualizaPagina(Pagina *pagina, int aiPosicao) {
    FILE *fpPaginas;
    fpPaginas = fopen(nomeArquivoPaginas, "r+b");
    fseek(fpPaginas, aiPosicao * sizeof (Pagina), SEEK_SET);
    fwrite(pagina, sizeof ( Pagina), 1, fpPaginas);
    fclose(fpPaginas);
}

No* CarregaNo(int aiPosicao) {
    FILE *fpNos;
    No *no;
    no = (No*) malloc(sizeof (No));

    fpNos = fopen(nomeArquivoTries, "r+b");
    fseek(fpNos, aiPosicao * sizeof (No), SEEK_SET);
    fread(no, sizeof (No), 1, fpNos);
    fclose(fpNos);
    return no;
}

Pagina* CarregaPagina(int aiPosicao) {
    FILE *fpPaginas;
    Pagina *pagina;
    pagina = (Pagina*) malloc(sizeof (Pagina));

    fpPaginas = fopen(nomeArquivoPaginas, "r+b");
    fseek(fpPaginas, aiPosicao * sizeof ( Pagina), SEEK_SET);
    fread(pagina, sizeof ( Pagina), 1, fpPaginas);
    fclose(fpPaginas);
    return pagina;
}

int GetPrimeiraPagina() {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
    return inicializador->primeiraPagina;
}

int GetPrimeiroNo() {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
    return inicializador->primeiroNo;
}

int GetUltimaPagina() {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
    return inicializador->ultimaPagina;
}

int GetUltimoNo() {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
    return inicializador->ultimoNo;
}

void GravaNovaPagina(Pagina *aPagina) {
    FILE *fpPaginas;
    fpPaginas = fopen(nomeArquivoPaginas, "r+b");
    int indice = GetUltimaPagina();
    if (indice == -1) {
        fwrite(aPagina, sizeof ( Pagina), 1, fpPaginas);
        SetUltimaPagina(0);
    } else {
        fseek(fpPaginas, (indice + 1) * sizeof ( Pagina), SEEK_SET);
        fwrite(aPagina, sizeof ( Pagina), 1, fpPaginas);
        SetUltimaPagina(indice + 1);
    }
    fclose(fpPaginas);
}

void GravaNovoNo(No *aNo) {
    FILE *fpNos;
    fpNos = fopen(nomeArquivoTries, "r+b");
    int indice = GetUltimoNo();
    if (indice == -1) {
        fwrite(aNo, sizeof ( No), 1, fpNos);
        SetUltimoNo(0);
    } else {
        fseek(fpNos, (indice + 1) * sizeof ( No), SEEK_SET);
        fwrite(aNo, sizeof ( No), 1, fpNos);
        SetUltimoNo(indice + 1);
    }
    fclose(fpNos);
}

void SetPrimeiraPagina(int aiNovo) {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    inicializador->primeiraPagina = aiNovo;
    rewind(fpAuxiliar);
    fwrite(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
}

void SetPrimeiroNo(int aiNovo) {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    inicializador->primeiroNo = aiNovo;
    rewind(fpAuxiliar);
    fwrite(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
}

void SetUltimaPagina(int aiNovo) {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    inicializador->ultimaPagina = aiNovo;
    rewind(fpAuxiliar);
    fwrite(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
}

void SetUltimoNo(int aiNovo) {
    FILE *fpAuxiliar;
    Auxiliar *inicializador;

    fpAuxiliar = fopen(nomeArquivoAuxiliar, "r+b");
    inicializador = (Auxiliar*) malloc(sizeof (Auxiliar));
    fread(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    inicializador->ultimoNo = aiNovo;
    rewind(fpAuxiliar);
    fwrite(inicializador, sizeof ( Auxiliar), 1, fpAuxiliar);
    fclose(fpAuxiliar);
}

