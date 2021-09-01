#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Carros.h"

struct veiculosArvBin{
    struct carro dados;
    struct veiculosArvBin *esq;
    struct veiculosArvBin *dir;
};

struct veiculosAVL{
    int alt;
    struct carro dados; 
    struct veiculosAVL *dir;
    struct veiculosAVL *esq;
};

Lista *inicio;
ArvBin *raiz;
ArvAVL *raizAVL;

int hentradaCarroLDD[2];
int saldo;

/*Número de consultas para entrada e saída de elemento*/
int entradasLDD, saidasLDD;
int entradasABB, saidasABB;
int entradasAVL, saidasAVL;

void main(){
  
 struct carro c;
    int condicao, tam=0, aux, x;

    printf("Estacionamento SW ");
    inicio = criarLDD();
    raiz = criar();
    raizAVL = criarAVL();

    entradasLDD = saidasLDD = entradasABB = saidasABB = entradasAVL = saidasAVL = 0;

    do{
    tam = tamanhoLDD(inicio);

    printf("\n1. Estacionar carro \n2. Mostrar carros estacionados\n3. Resgatar carro\n4. Visualizar eficiência dos métodos de busca\n5. Encerrar sistema (dados serão perdidos)\n = ");
    scanf("%d", &condicao);

    switch (condicao){

    case 1:
        if(inicio != NULL && tam<3){ leituraLDD(); tam = tamanhoLDD(inicio);}
        break;

    case 2:
        if(inicio != NULL && raiz != NULL){

        mostrarLDD(inicio);
        printf("\n/* Exibir Árvore Binária de Busca: ");
        x = menuOrdem(raiz);

            if(x==1){
                preOrdem_ArvBin(raiz);

                printf("\n/* Exibir Árvore AVL: \n");
                preOrdem_ArvAVL(raizAVL);
                
            }else if(x==2){
                emOrdem_ArvBin(raiz);

                printf("\n/* Exibir Árvore AVL: \n");
                emOrdem_ArvAVL(raizAVL);

            }else{
                posOrdem_ArvBin(raiz);

                printf("\n/* Exibir Árvore AVL: \n");
                posOrdem_ArvAVL(raizAVL);
            }

        }
        break;

    case 3:
        resgatarCarro();
        tam = tamanhoLDD(inicio);
        break;

    case 4:
        calculaEficiencia();
    break;
    
    default:
        break;
    }           

    if(tam>=3){ 
        printf("\nEstacionamento lotado!");
    }while(getchar() != '\n');

    }while(condicao != 5);

    liberarLDD(inicio);
    liberaArvBin(raiz);
    liberaArvAVL(raizAVL);
    }


/*GESTÃO DO ESTACIONAMENTO - LISTA DUPLAMENTE ENCADEADA*/
void leituraLDD(){
    struct carro c;
    int tamLDD, tamArvBin, tamAVL;

    do {
    c.ordem = tamanhoLDD(inicio)+1;

    printf("\n\nPlaca do carro (4 digitos): ");
    scanf("%d", &c.placa);
    
    while(getchar() != '\n');

    }while(consultarLDD(inicio, c.placa) == 1); //já existe essa placa cadastrada

    printf("\nHorário de entrada (digitar por partes, formato 24hrs)\n(HR): ");
     scanf("%d", &c.horaEntrada);

      while(getchar() != '\n');

    printf("\nSegundos: ");
     scanf("%d", &c.sEntrada);

      while(getchar() != '\n');
        
    Lista *aux = inicio;
    ArvBin *aux2 = raiz;
    ArvAVL *aux3;

    if(*inicio == NULL || (*raiz) == NULL || (*raizAVL) == NULL){
        aux = inserirCarroLDD(inicio, c);
        insere_arvBin(raiz, c);
        insereAVL(raizAVL, c);

    }else{
        inicio = realocarLDD(aux); 
        raiz = realocar(aux2);
        //raiz = aux2;
        aux = inserirCarroLDD(inicio, c);
        insere_arvBin(raiz, c);

        aux3 = realocarAVL(raizAVL);
        raizAVL = aux3;
        insereAVL(raizAVL, c);

    }   
        inicio = aux;

}

void resgatarCarro(){
    int horaSaida, sSaida;
    int placa;
    int tamanho;

        printf("\n\nPlaca do carro (4 digitos): ");
        scanf("%d", &placa);
        while(getchar() != '\n');

        printf("\nHora de saída (Formato 24hrs): ");
        scanf("%d", &horaSaida);
        while(getchar() != '\n');
    
        printf("\nSegundos no horário de saída (Formato 60s): ");
        scanf("%d", &sSaida);
        while(getchar() != '\n');

    int estadiaV;
    int portaoLDD, portaoABB, portaoAVL;
    portaoLDD = consultarPosicao(inicio, placa);
    portaoABB = consulta_ArvBin(raiz, placa);
    portaoAVL = consulta_ArvAVL(raizAVL, placa);

    if((consultarLDDRetorNo(inicio, placa)) == 1){
        
        estadiaV = estadia(hentradaCarroLDD[0], hentradaCarroLDD[1], horaSaida, sSaida);
        printf("Carro %d deverá sair. (Estadia = %d)", placa, labs(estadiaV));
        
        tamanho = tamanhoLDD(inicio);
            printf("\nLDD: Portão %d\n", portaoLDD);
            printf("\nABB: Portão %d\n", portaoABB);
            printf("\nAVL: Portão %d\n", portaoAVL);

        saldo += estadiaV;

        remove_lista_ordenada(inicio, placa);
        remove_ArvBin(raiz, placa);
        removeAVL(raizAVL, placa);

    }else{
        printf("Carro não encontrado"); 
    }
}

int estadia(int hentrada, int sentrada, int hsaida, int ssaida){
    int estadia;

    if(hentrada > hsaida){
        estadia = (24-(hentrada+hsaida))*12;

        if(ssaida>=1){
            estadia = estadia + 12;
        }

    }else if(hentrada < hsaida){
        estadia = (hsaida-hentrada)*12;

        if(ssaida>=1){
            estadia = estadia + 12;
        }

    }else if(hentrada == hsaida){// se forem iguais
        if(hsaida>=hentrada){
            estadia = 12;
        }else {
            estadia = 24*12;
        }
    }       
    
    return estadia;
}

void mostrarLDD(Lista *inicio){
  Cars *aux = *inicio;

    printf("\n[ Portão 2 ]\n"); //Mais próximo do inicio da lista duplamente encadeada
  for(int i=0; i<tamanhoLDD(inicio); i++){
    printf("\nOrdem %d | Placa: %d | hEntrada: %d | sEntrada %d", aux->dados.ordem, aux->dados.placa, aux->dados.horaEntrada, aux->dados.sEntrada);
    aux = aux->prox;
  }
    printf("\n\n[ Portão 1 ]\n"); //Mais próximo do fim da lista duplamente encadeada

}

Lista *criarLDD(){
    Lista *inicio = (Lista*)calloc(1, sizeof(Lista));

    if(inicio != NULL){
        *inicio = NULL;
    }return inicio;
}

int tamanhoLDD(Lista *inicio){
    int cont = 0;

    if(inicio == NULL){
        return 0;
    }else{
    
        Cars *aux = *inicio;
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }

        return cont;
    }

}

void liberarLDD(Lista *inicio){
    Cars *aux;

    if(inicio != NULL && *inicio != NULL){

        while(*inicio != NULL){
            aux = *inicio;
            *inicio = (*inicio)->prox;
            free(aux);
        }free(inicio);

    }
}

void liberarLDDCars(Cars *ini){
    Cars *aux;

    if(ini != NULL && ini != NULL){

        while(ini != NULL){
            aux = ini;
            ini = ini->prox;
            free(aux);
        }free(ini);

    }
}

Lista *realocarLDD(Lista *inicio){
    int tam = tamanhoLDD(inicio) + 1;
    inicio = (Lista*)realloc(inicio, tam*sizeof(Lista));

  if(inicio == NULL){
      printf("Erro ao realocar");
      return NULL; 
    }else{
      return inicio; 
    }
}

Lista *inserirCarroLDD(Lista *inicio, struct carro c){
    int tam;

    if(inicio == NULL){
        return NULL;
    }else{
        
      Cars *veiculos = (Cars*) malloc(sizeof(Cars));
        
        if(veiculos == NULL){
            return NULL;
        }else{
        entradasLDD++;

        veiculos->dados = c;
        veiculos->ant = NULL;

        if((*inicio) == NULL){ 
            veiculos->ant = NULL;
            *inicio = veiculos;

            tam = tamanhoLDD(inicio);
            printf("\nCarro %d entrou. Total = %d", c.placa, tam);
            while(getchar() != '\n');

            entradasLDD++;
            return inicio;

        }else{
            Cars *aux = *inicio;
            while(aux->prox != NULL){
                aux = aux->prox;
                entradasLDD++;
            }

            aux->prox = veiculos;
            veiculos->ant = aux;
            entradasLDD++;
        }

        tam = tamanhoLDD(inicio);
        printf("\nCarro %d entrou. Total = %d", c.placa, tam);
        while(getchar() != '\n');

        /**/entradasLDD++;
        return inicio;
        }
        }
    }

int remove_lista_ordenada(Lista *inicio, int placa){
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{

        Cars *no = *inicio;

        while(no->prox != NULL && no->dados.placa != placa){
            no = no->prox;
            saidasLDD++;
        }

        if(no == NULL){ //Nao encontrado
            saidasLDD++;
            return 0;
        }

        if(no->ant == NULL){ //remover o primeiro
            *inicio = no->prox;
            saidasLDD++;
        }else{ //final
            no->ant->prox = no->prox;
            saidasLDD++;
        }

        //retirar elemento do meio
        if(no->prox != NULL){
            no->prox->ant = no->ant;
            saidasLDD++;
        }

        free(no);
        saidasLDD++;
        return 1;
    }
}

int consultarLDD(Lista *inicio, int placa){ //Função de busca para inserção para verificar se o carro já está estacionado 
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;
        int cont = 0;

        while(aux != NULL){
        if(aux->dados.placa == placa){
            printf("\nEste carro já se encontra no estacionamento");
            entradasLDD++;
            return 1;
        }   
        cont++;
        aux = aux->prox;
        entradasLDD++;
        }

            entradasABB++;
            return 0;
    }
}

int consultarLDDRetorNo(Lista *inicio, int placa){ //Função auxiliar no cálculo de estadia
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;

        while(aux != NULL){
        if(aux->dados.placa == placa){
            hentradaCarroLDD[0] = aux->dados.horaEntrada;
            hentradaCarroLDD[1] = aux->dados.sEntrada;
            
            saidasLDD++;
            return 1;
        }   
        aux = aux->prox;
        saidasLDD++;
        }

            saidasLDD++;
            return 0;
    }
}

int consultarPosicao(Lista *inicio, int placa){ //Função que retorna o portão
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;
        int cont = 0;

        while(aux != NULL && aux->dados.placa != placa){
            cont++;
            aux = aux->prox;
            saidasLDD++;
        } cont++;

        if(aux->dados.placa == placa){
            saidasLDD++;
            
            if(cont <= tamanhoLDD(inicio)/2){
                return 2;
            }else{
                return 1;
            }

        }else{
            return 0;
        }
        
    }
}


/*Árvore Binária de Busca*/

ArvBin *criar()
{
    ArvBin *raiz = (ArvBin *)calloc(1, sizeof(ArvBin));

    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

ArvBin *realocar(ArvBin *raiz){
    int tam = totalveiculosArvBin(raiz) + 1;
    raiz = (ArvBin *)realloc(raiz, tam * sizeof(ArvBin));

    if (raiz == NULL)
    {
        printf("Erro ao realocar");
        return NULL;
    }
    else
    {
        return raiz;
    }
}

void liberaveiculosArvBin(struct veiculosArvBin *veiculosArvBin)
{
    if (veiculosArvBin == NULL)
    {
        return;
    }
    else
    {
        liberaveiculosArvBin(veiculosArvBin->dir);
        liberaveiculosArvBin(veiculosArvBin->esq);

        free(veiculosArvBin);
        veiculosArvBin = NULL;
    }
}

void liberaArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    else
    {
        liberaveiculosArvBin(*raiz);
        free(raiz);
    }
}

int alturaArvBin(ArvBin *raiz)
{
    if (raiz == NULL || *raiz == NULL){
        return 0;
    }else{

        int alt_esq = alturaArvBin(&((*raiz)->esq));
        int alt_dir = alturaArvBin(&((*raiz)->dir));

        if (alt_esq > alt_dir){
            return (alt_esq + 1);
        }
        else{
            return (alt_dir + 1);
        }
    }
}

int totalveiculosArvBin(ArvBin *raiz){
    if (raiz == NULL || (*raiz) == NULL){
        return 0;
    }else{

        int alt_esq = totalveiculosArvBin(&((*raiz)->esq));
        int alt_dir = totalveiculosArvBin(&((*raiz)->dir));

        return (alt_esq + alt_dir + 1);
    }
}

void preOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    if (*raiz != NULL)
    {
        printf("%d\n", (*raiz)->dados.placa);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    if (*raiz != NULL)
    {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->dados.placa);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    if (*raiz != NULL)
    {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->dados.placa);
    }
}

int insere_arvBin(ArvBin *raiz, struct carro infos){
    if (raiz == NULL){
        return 0;
    }
    struct veiculosArvBin *veiculosArvBinvo;
    veiculosArvBinvo = (struct veiculosArvBin *)malloc(sizeof(struct veiculosArvBin));

    if (veiculosArvBinvo == NULL){
        return 0;
    }else{
        veiculosArvBinvo->dados = infos;
        veiculosArvBinvo->dir = NULL;
        veiculosArvBinvo->esq = NULL;

        if (*raiz == NULL){
            *raiz = veiculosArvBinvo;
            entradasABB++;
        } else{
            struct veiculosArvBin *atual = *raiz;
            struct veiculosArvBin *ant = NULL;

            while (atual != NULL){
                entradasABB++;
                ant = atual;

                if (infos.placa == atual->dados.placa){
                    printf("Dado ja inserido");
                    free(veiculosArvBinvo);
                    entradasABB++;
                    return 0;
                }
                if (infos.placa > atual->dados.placa){
                    atual = atual->dir;
                    entradasABB++;
                }
                else{
                    atual = atual->esq;
                    entradasABB++;
                }
            }
            if (infos.placa > ant->dados.placa){
                ant->dir = veiculosArvBinvo;
                entradasABB++;
            }
            else{
                ant->esq = veiculosArvBinvo;
                entradasABB++;
            }

            entradasABB++;
        }

       entradasABB++;
       return 1;
    }
}

struct veiculosArvBin *remove_atual(struct veiculosArvBin *atual){
    struct veiculosArvBin *veiculosArvBin1, *veiculosArvBin2;

    if (atual->esq == NULL){
        veiculosArvBin2 = atual->dir;
        free(atual);
        saidasABB++;
        return veiculosArvBin2;
    }

    veiculosArvBin1 = atual;
    veiculosArvBin2 = atual->esq;

    while (veiculosArvBin2->dir != NULL){
        veiculosArvBin1 = veiculosArvBin2;
        veiculosArvBin2 = veiculosArvBin2->dir;
        saidasABB++;
    }

    if (veiculosArvBin1 != atual){
        veiculosArvBin1->dir = veiculosArvBin2->esq;
        veiculosArvBin2->esq = atual->esq;
        saidasABB++;
    }

    veiculosArvBin2->dir = atual->dir;
    free(atual);
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if (raiz == NULL){
        return 0;
    }
    struct veiculosArvBin *ant = NULL;
    struct veiculosArvBin *atual = *raiz;

    while (atual != NULL){
        saidasABB++;

        if (valor == atual->dados.placa){

            if (atual == *raiz){

                *raiz = remove_atual(atual);
                saidasABB++;
            }
            else{
                if (ant->dir == atual){
                    ant->dir = remove_atual(atual);
                    saidasABB++;
                }
                else{
                    ant->esq = remove_atual(atual);
                    saidasABB++;
                }

                saidasABB++;
            }

            saidasABB++;
            return 1;
        }

        ant = atual;
        if (valor > atual->dados.placa){
            atual = atual->dir;
            saidasABB++;
        }
        else{
            atual = atual->esq;
            saidasABB++;
        }
    }
}

int consulta_ArvBin(ArvBin *raiz, int placa){ //Retorna o índice do portão 
    int tamanho, cont;
    tamanho = totalveiculosArvBin(raiz);

    if (raiz == NULL){
        return 0;
    }

    struct veiculosArvBin *atual = *raiz;

    while (atual != NULL){
        
        saidasABB++;

        if (placa == atual->dados.placa){
            saidasABB++;

            if(atual->dados.ordem <= (tamanho/2)){
                saidasABB++;

                return 2;
               }else{
                saidasABB++;
                return 1;
               }


        } if(placa > atual->dados.placa){
            //cont++;
            atual = atual->dir;

        }else{
            //cont++;
            atual = atual->esq;
        }
    }

    return 0;
}

void calculaEficiencia(){
    float mediaELDD = entradasLDD/3;
    float mediaEABB = entradasABB/3;
    float mediaEAVL = entradasAVL/3;

    printf("\nMédia do número de consultas para ENTRADA de elementos: ");
    printf("\nMédia na LDD: %.2f", mediaELDD);
    printf("\nMédia na ABB: %.2f", mediaEABB);
    printf("\nMédia na AVL: %.2f", mediaEAVL);

    float mediaSLDD = saidasLDD/3;
    float mediaSABB = saidasABB/3;
    float mediaSAVL = saidasAVL/3;

    printf("\n\nMédia do número de consultas para SAÍDA de elementos: ");
    printf("\nMédia na LDD: %.2f", mediaSLDD);
    printf("\nMédia na ABB: %.2f", mediaSABB);
    printf("\nMédia na AVL: %.2f", mediaSAVL);
}

/*ÁRVORE AVL*/

ArvAVL* criarAVL(){
    ArvAVL *raizAVL = (ArvAVL*)calloc(1, sizeof(ArvAVL));

    if(raizAVL != NULL){
        *raizAVL = NULL;
    }return raizAVL;
}

ArvAVL *realocarAVL(ArvAVL *raizAVL){
    int tam = totalNOsArvAVL(raizAVL) + 1;
    //printf("Tamanho em realoc: %d", tam);
    raizAVL = (ArvAVL *)realloc(raizAVL, tam * sizeof(ArvAVL));

    if (raizAVL == NULL)
    {
        printf("Erro ao realocar");
        return NULL;
    }
    else
    {
        return raizAVL;
    }
}

void liberaNoAVL(struct veiculosAVL* no){
    if(no == NULL){
        return;
    }else{

        liberaNoAVL(no->dir);
        liberaNoAVL(no->esq);

        free(no);
        no = NULL;
    }
}

void liberaArvAVL(ArvAVL* raizAVL){
    if(raizAVL == NULL){
        return;
    }else{
        liberaNoAVL(*raizAVL);
        free(raizAVL);
    }
}

int alturaArvAVL(ArvAVL *raizAVL){
    if(raizAVL == NULL || *raizAVL == NULL){
        return 0;
    }else{

        int alt_esq = alturaArvAVL(&((*raizAVL)->esq));
        int alt_dir = alturaArvAVL(&((*raizAVL)->dir));

        if(alt_esq >alt_dir){
            return (alt_esq + 1);
        }else{
            return (alt_dir + 1);
        }
    }
}

int totalNOsArvAVL(ArvAVL *raizAVL){
    if(raizAVL == NULL || *raizAVL == NULL){
        return 0;
    }else{
        int alt_esq = totalNOsArvAVL(&((*raizAVL)->esq));
        int alt_dir = totalNOsArvAVL(&((*raizAVL)->dir));
        
        return(alt_esq + alt_dir + 1);
    }
}

void preOrdem_ArvAVL(ArvAVL *raizAVL){
    if(raizAVL == NULL){
        return;
    }if (*raizAVL != NULL){
        printf("%d \n", (*raizAVL)->dados.placa);
        preOrdem_ArvAVL(&((*raizAVL)->esq));
        preOrdem_ArvAVL(&((*raizAVL)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raizAVL){
    if(raizAVL == NULL){
        return;
    }if (*raizAVL != NULL){
        emOrdem_ArvAVL(&((*raizAVL)->esq));
        printf("%d \n", (*raizAVL)->dados.placa);
        emOrdem_ArvAVL(&((*raizAVL)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raizAVL){
    if(raizAVL == NULL){
        return;
    }if (*raizAVL != NULL){
        posOrdem_ArvAVL(&((*raizAVL)->esq));
        posOrdem_ArvAVL(&((*raizAVL)->dir));
        printf("%d \n", (*raizAVL)->dados.placa);
    }
}

int altNOAVL(struct veiculosAVL* no){
    if(no == NULL){
        return -1;
    }else{
        return no->alt;
    }
}

int fator_BalanceamentoAVL(struct veiculosAVL* no){
    //printf("\nFator balanceamento: Alturas esq %d dir %d", altNOAVL(no->esq), altNOAVL(no->dir));
    return labs(altNOAVL(no->esq) - altNOAVL(no->dir));
}
 
int maiorAVL(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

void RotacaoLL(ArvAVL *raizAVL){ //Rotação simples a direita (duas inserções a esquerda)
    struct veiculosAVL* no;
    no = (*raizAVL)->esq;
    (*raizAVL)->esq = no->dir;
    no->dir = *raizAVL;

    (*raizAVL)->alt = maiorAVL(altNOAVL((*raizAVL)->esq),
                        altNOAVL((*raizAVL)->dir));


    no->alt = maiorAVL(altNOAVL(no->esq), (*raizAVL)->alt) + 1;

    *raizAVL = no;
}

void RotacaoRR(ArvAVL *raizAVL){ //Rotação simples a esquerda
    struct veiculosAVL* no;
    no = (*raizAVL)->dir;
    (*raizAVL)->dir = no->esq;
    no->esq = *raizAVL;

    (*raizAVL)->alt = maiorAVL(altNOAVL((*raizAVL)->esq),
                        altNOAVL((*raizAVL)->dir));


    no->alt = maiorAVL(altNOAVL(no->dir), (*raizAVL)->alt) + 1;

    *raizAVL = no;
}

void RotacaoLR(ArvAVL *raizAVL){ //Rotação dupla a direita
    RotacaoRR(&(*raizAVL)->esq);
    RotacaoLL(raizAVL);
}

void RotacaoRL(ArvAVL *raizAVL){ //Rotação dupla a esquerda
    RotacaoLL(&(*raizAVL)->dir);
    RotacaoRR(raizAVL);
}

int insereAVL(ArvAVL *raizAVL, struct carro c){
    int res;

    if(*raizAVL == NULL){ //Caso seja o primeiro nó
        struct veiculosAVL* novo;
        novo = (struct veiculosAVL*)malloc(sizeof(struct veiculosAVL));

        if(novo == NULL) return 0;

        novo->dados = c; 
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *raizAVL = novo;
        entradasAVL++;
        return 1;
    }else{
        struct veiculosAVL *atual = *raizAVL;
        entradasAVL++;

        if(c.placa < atual->dados.placa){
            entradasAVL++;

            if((res=insereAVL(&(atual->esq), c)) == 1){
                entradasAVL++;

                if(fator_BalanceamentoAVL(atual) >= 2){
                    entradasAVL++;
 
                    if(c.placa < (*raizAVL)->esq->dados.placa){
                        entradasAVL++;
                        RotacaoLL(raizAVL);
                    }else{
                        entradasAVL++;
                        RotacaoLR(raizAVL);
                    }
                }
            }
        }else if(c.placa > atual->dados.placa){
            entradasAVL++;

            if((res=insereAVL(&(atual->dir), c)) == 1){
                entradasAVL++;
                if(fator_BalanceamentoAVL(atual) >= 2){
                    entradasAVL++;
            
                    if((*raizAVL)->dir->dados.placa < c.placa){
                        entradasAVL++;
                        RotacaoRR(raizAVL);

                    }else{
                        entradasAVL++;
                        RotacaoRL(raizAVL);
                    }
                }
                }
        }else{
            entradasAVL++;
            printf("Valor duplicado!\n");
            return 0;
        }

    atual->alt = maiorAVL(altNOAVL(atual->esq), altNOAVL(atual->dir))+1;

    return res;
    }

}

int removeAVL(ArvAVL *raizAVL, int placa){
int res;

      if(*raizAVL == NULL){
          //printf("\nEsta placa não se encontra no estacionamento"); 
          saidasAVL++;
          return 0;
          
      }else{
        if(placa < (*raizAVL)->dados.placa){
            saidasAVL++;

         if((res=removeAVL(&((*raizAVL)->esq), placa)) == 1){
             saidasAVL++;

            if(fator_BalanceamentoAVL(*raizAVL) >= 2){
                saidasAVL++;
        
                if(altNOAVL((*raizAVL)->dir->esq) <= altNOAVL((*raizAVL)->dir->dir)){
                    saidasAVL++;
                    RotacaoRR(raizAVL);
                }else{
                    saidasAVL++;
                    RotacaoRL(raizAVL);
                }
            }
         }
        }else if((*raizAVL)->dados.placa < placa){
            saidasAVL++;

          if((res=removeAVL(&((*raizAVL)->dir), placa)) == 1){
              saidasAVL++;

            if(fator_BalanceamentoAVL(*raizAVL) >= 2){
                saidasAVL++;

                if(altNOAVL((*raizAVL)->esq->dir) <= altNOAVL((*raizAVL)->esq->esq)){
                    saidasAVL++;
                    RotacaoLL(raizAVL);

                }else{

                    saidasAVL++;
                    RotacaoLR(raizAVL);
                }
            }
        }
        }else if((*raizAVL)->dados.placa == placa){ //REMOÇÃO DE FATO
            saidasAVL++;

            if((*raizAVL)->esq == NULL || (*raizAVL)->dir == NULL){ //Verifica se possui dois filhos
                saidasAVL++;

                struct veiculosAVL* oldNode = (*raizAVL);
                
                if((*raizAVL)->esq != NULL){
                    saidasAVL++;
                    
                    *raizAVL = (*raizAVL)->esq;
                }else{
                    saidasAVL++;

                    *raizAVL = (*raizAVL)->dir;
                }free(oldNode);
            
            }else{ //Caso possua verifica qual o menor
                saidasAVL++;
                struct veiculosAVL* temp = procuraMenorAVL((*raizAVL)->dir);

                (*raizAVL)->dados.placa= temp->dados.placa;

                removeAVL(&(*raizAVL)->dir, (*raizAVL)->dados.placa);
                saidasAVL++;
                
                if(fator_BalanceamentoAVL(*raizAVL) >= 2){
                    saidasAVL++;

                    if(altNOAVL((*raizAVL)->esq->dir) <= altNOAVL((*raizAVL)->esq->esq)){
                        saidasAVL++;
                        RotacaoLL(raizAVL);
                    }else{
                        saidasAVL++;
                        RotacaoLR(raizAVL);
                    }
                }

            }
              return 1;
        }

        return res;
      }
}

struct veiculosAVL* procuraMenorAVL(struct veiculosAVL* atual){ //Resolve caso de retirada de nó com 2 filhos
    struct veiculosAVL *no1 = atual;
    struct veiculosAVL *no2 = atual->esq;
    
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
}

int consulta_ArvAVL(ArvAVL *raizAVL, int placa){
    int tamanho, cont;
    tamanho = totalNOsArvAVL(raizAVL);

    if (raizAVL == NULL){
        saidasAVL++;
        return 0;
    }

    struct veiculosAVL *atual = *raizAVL;

    while (atual != NULL){
        
        saidasAVL++;

        if (placa == atual->dados.placa){
            saidasAVL++;
            cont++;

            if(atual->dados.ordem <= (tamanho/2)){
                saidasAVL++;

                return 2;

               }else{
                saidasAVL++;

                return 1;
               }


        } if(placa > atual->dados.placa){
            cont++;
            saidasAVL++;
            atual = atual->dir;

        }else{
            cont++;
            saidasAVL++;
            atual = atual->esq;
        } 
    }
    return 0;
}
