#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "CarroLDD.h"

Lista *inicio;
int hentradaCarroLDD[2];
int saldo;

void main(){
  
 struct carro c;
    int condicao, tam;

    printf("Estacionamento SW ");
    inicio = criarLDD();

    do{

    printf("\n1. Estacionar carro \n2. Mostrar carros dentro\n3. Resgatar carro\n4. Encerrar sistema (dados serão perdidos)\n = ");
    scanf("%d", &condicao);

    switch (condicao){
    case 1:
    
         if(inicio != NULL){
             leituraLDD();
             tam = tamanhoLDD(inicio);

             //leituraLDD();
            }

        /*Quando saldo for >300*/
        break;

    case 2:
        //chamar (menu) funcoes de funcionario
        mostrarLDD(inicio);
        break;

    case 3:
            resgatarCarro();
            tam = tamanhoLDD(inicio);
             //resgatarCarroLDD();
        break;
    
    default:
        break;
    }           

       if(tam>=3){
        printf("\nEstacionamento lotado!");
           //menuLotado();

      }while(getchar() != '\n');

    }while(condicao != 4);

    liberarLDD(inicio);

    }

void leituraLDD(){
    struct carro c;
    int tam;

    do {
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

    if(*inicio == NULL){
        aux = inserirCarroLDD(inicio, c);
    }else{
        inicio = realocarLDD(aux); //**
        aux = inserirCarroLDD(inicio, c);
    }   
        inicio = aux;
        tam = tamanhoLDD(inicio);

}

void resgatarCarro(){
    int horaSaida, sSaida;
    int placa;

    /*No método remover será preciso fazer o tratamento de encontrar por qual portão será mais proximo sair*/
        
        printf("\n\nPlaca do carro (4 digitos): ");
        scanf("%d", &placa);
        while(getchar() != '\n');

        printf("\nHora de saída (Formato 24hrs): ");
        scanf("%d", &horaSaida);
        while(getchar() != '\n');
    
        printf("\nSegundos no horário de saída (Formato 60s): ");
        scanf("%d", &sSaida);
        while(getchar() != '\n');

        //Fazer calculo de quantas hrs
        //Multiplicar pelo valor da hora/estacionamento - c.divida = (..-/..)*12 (2 ifs)
        //atualizar saldo - saldo += c.divida;

    //removerCarroLDD(inicio, placa);
    int estadiaV;

    if((consultarLDDRetorno(inicio, placa)) == 1){
        estadiaV = estadia(hentradaCarroLDD[0], hentradaCarroLDD[1], horaSaida, sSaida);
        printf("Carro %d deverá sair. (Estadia = %d)", placa, estadiaV);
        saldo += estadiaV;

        removeCarro(inicio, placa);
    }else{
        printf("Carro não encontrado"); //nova
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
    printf("\nPlaca: %d | hEntrada: %d | sEntrada %d", aux->dados.placa, aux->dados.horaEntrada, aux->dados.sEntrada);
    aux = aux->prox;
  }
    printf("\n\n[ Portão 1 ]\n"); //Mais próximo do fim da lista duplamente encadeada

}

/*
void menuLotado(){
    int condicao, tam;

    do{

    printf("\nEstacionamento lotado!");
    printf("\n1. Resgatar carro \n2. Gestão de funcionários\n3. Voltar\n = ");
    scanf("%d", &condicao);

    switch (condicao)
    {
    case 1:
        resgatarCarro();
        tam = tamanhoLDD(inicio);

        //resgatarCarroLDD();
        break;

    case 2:
        //gestaoFuncionarios
        tam = tamanhoLDD(inicio);

    case 3:
        //sair 
        tam = tamanhoLDD(inicio);
        break;
    
    default:
        break;
    }

    }while(tam >= 3);

    main();
}
*/

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
        
      Cars *no = (Cars*) malloc(sizeof(Cars));
        
        if(no == NULL){
            return NULL;
        }else{

        no->dados = c;
        no->ant = NULL;

        /*Depois de remover todos os carros dá erro na inserção novamente*/
        if((*inicio) == NULL){ //se a Lista estiver vazia
            no->ant = NULL;
            *inicio = no;

            tam = tamanhoLDD(inicio);
            printf("\nCarro %d entrou. Total = %d", c.placa, tam);
            while(getchar() != '\n');
            return inicio;

        }else{
            Cars *aux = *inicio;
            while(aux->prox != NULL){
                aux = aux->prox;
            }

            aux->prox = no;
            no->ant = aux;
        }
        //fflush(stdin);

        tam = tamanhoLDD(inicio);
        printf("\nCarro %d entrou. Total = %d", c.placa, tam);
        while(getchar() != '\n');
        return inicio;
        }

        }
    }

/*Erros nessa função*/
Lista *removerCarroLDD(Lista *inicio, int placa){
    int tam, cont = 0;

    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{

        Cars *aux = *inicio;

        while(aux->prox != NULL && aux->dados.placa != placa){
            cont++;
            aux = aux->prox;
        }
        printf("*cont: %d\n", cont); 

        if(aux == NULL){ //Nao encontrado
            while(getchar() != '\n');
            printf("Carro %d não encontrado", placa);
            return NULL;
        }else{

        if(aux->ant == NULL){ //remover o primeiro
            *inicio = aux->prox;
            tam = tamanhoLDD(inicio);
            while(getchar() != '\n');
            printf("Carro %d saiu! Total = %d", placa, tam);

            //return inicio;
        }else{ //no meio
            aux->ant->prox = aux->prox;
            /**inicio = aux;
            printf("Carro %d saiu! Total = ", placa);
            return inicio;*/ 
        }

        printf("*cont: %d", cont);

        //meio - nao é o último? 
        if(aux->prox != NULL){
            aux->prox->ant = aux->ant;
            tam = tamanhoLDD(inicio);
            while(getchar() != '\n');
            printf("Carro %d saiu! Total = %d", placa, tam);

        }
        }

        *inicio = aux;

        free(aux);
        return inicio;
    }
}

int consultarLDD(Lista *inicio, int placa){
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;
        int cont = 0;

        while(aux != NULL){
        if(aux->dados.placa == placa){
            printf("\nEste carro já se encontra no estacionamento");
            return 1;
        }   
        cont++;
        aux = aux->prox;
        }
            return 0;
    }
}

int consultarLDDRetorno(Lista *inicio, int placa){
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;

        while(aux != NULL){
        if(aux->dados.placa == placa){
            hentradaCarroLDD[0] = aux->dados.horaEntrada;
            hentradaCarroLDD[1] = aux->dados.sEntrada;
            return 1;
        }   
        aux = aux->prox;
        }
            return 0;
    }
}

int consultarPosicao(Lista *inicio, int placa){ //quando ja sei que o elemento esta na lista
    if(inicio == NULL || (*inicio) == NULL){
        return 0;
    }else{
        Cars *aux = *inicio;
        int cont = 0;

        printf("Consultar posição");
        while(aux != NULL && aux->dados.placa != placa){
            //printf("\nEste carro já se encontra no estacionamento");
            //return 1;
        cont++;
        printf("\ncont %d: ", cont);
        aux = aux->prox;
        }          cont++; //a posição de fato

        
        printf("\ncont %d: ", cont);
        return cont;
    }
}

int removeCarro(Lista *inicio, int placa){
    int tam = tamanhoLDD(inicio);

    if(inicio == NULL || (*inicio) == NULL){
     return 0;
    }else{
        Cars *aux = *inicio;
        int pos = consultarPosicao(inicio, placa);
        
        if(pos == 1){ //Elimina início
            //aux = (*inicio)->prox;                
            *inicio = aux->prox;

           // if(aux->ant == NULL){ //remover unico elemento
            //}else{*inicio = aux->prox;
            if(aux->prox != NULL){
              aux->prox->ant = NULL; //inicio->prox->ant
            }

           // }

            free(aux);

            //chamar funcionario
            tam = tamanhoLDD(inicio);
            printf("\nPortão 2\nCarro %d saiu! Total = %d", placa, tam);

        }else if(pos == 3 && tam == 3 || pos == 2 && tam ==2){ /*talvez esteja trocado com o de pos==3*/
            //else{
                while(aux->prox != NULL){
                aux = aux->prox;
                }if(aux->ant != NULL){
                    aux->ant->prox = NULL;
                } //já atualiza inicio?

            tam = tamanhoLDD(inicio);
            printf("\nPortão 1\nCarro %d saiu! Total = %d", placa, tam);
            free(aux);

            }else if(pos == 2 && tam == 3){
                while(aux->prox != NULL && aux->dados.placa != placa){
                aux = aux->prox;
                }   aux->prox->ant = aux->ant; //o no que aponta pra proximo do termo anterior deve apontar para
            aux->ant->prox = aux->prox;

            tam = tamanhoLDD(inicio);
            //Informar carro que sai antes (inicio)
            //Chamar funcionario;
            printf(" retira Carro %d ", (*inicio)->dados.placa);
            printf("\nPortão 2\nCarro %d saiu! Total = %d", placa, tam);

            //Chamar funcionário seguinte
            printf(" retorna Carro %d ", (*inicio)->dados.placa);

            //A escolha aqui é pelo portão 2 pois como só é possível entrar pelo 1 simultaneamente pode ter algum carro entrando e outro funcionario facilitando este processo
            free(aux);
        }
    }
}
