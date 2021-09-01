#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Carro.h"
#include "Funcionario.h"

float saldo;
Pilha *topo;
ListaC *carrosqSaem; 
Lista *inicioF; //Funcionário
int x[3]; //dados struct carros que saem

int main(){
    int condicao, tam;

    printf("Estacionamento SW ");
    topo = criar();

    do{

    printf("\n0. Menu Funcionários\n1. Estacionar carro \n2. Mostrar carros no estacionamento\n3. Resgatar carro\n4. Sair\n = ");
    scanf("%d", &condicao);

    tam = tamanhoPilha(topo);

    switch (condicao){
    case 0:
     menuFuncionario();
     break;

    case 1:
    
     if(topo != NULL){
      if(saldo<300 && tam<3){
        //fflush(stdin);
        leituraPilha();
        tam = tamanhoPilha(topo);

      }else if (saldo >= 300){
        printf("Valor do portão obtido! Nenhum carro pode entrar!");
        if((*topo) == NULL){ //carros retirados
            liberar(topo);
            //criar LDD();
            //leituraLDD();
        }
      }
        break;

    case 2:
        //chamar (menu) funcoes de funcionario
        mostrarPilha(topo);
        break;

    case 3:
         //fflush(stdin);
         if(saldo<300){
            resgatarCarro();
            //tam = tamanhoPilha(topo);

            }else if(saldo>300){
             //resgatarCarroLDD();
            }
        break;
    
    default:
        break;
    }
    }            
       if(saldo<300){
           tam = tamanhoPilha(topo);
       }else{
           //tam = tamanhoLDD(inicio);
       }

       if(tam>=3){
           printf("\nEstacionamento lotado!");
           //break;
           //menuLotado();

      }while(getchar() != '\n');

    }while(condicao != 4);

  printf("Fechamento do estacionamento");
  return 0;
}

void leituraPilha(){
    struct carro *c = malloc(sizeof(struct carro));
    int tam = tamanhoPilha(topo);

    do{
    printf("\n\nPlaca do carro (4 digitos): ");
    scanf("%d", &c->placa);
    while(getchar() != '\n');

    }while(consultarPilha(topo, c->placa) == 1); //já existe essa placa cadastrada

    printf("\nHorário de entrada (digitar por partes, formato 24hrs)\n(HR): ");
    scanf("%d", &c->horaEntrada);
    while(getchar() != '\n');

    printf("\nSegundos: ");
    scanf("%d", &c->sEntrada);
    while(getchar() != '\n');
    
    Pilha *aux = topo;
    if(*topo == NULL){
        aux = inserirCarro(topo, c);
    }else{
        topo = realocar(aux); //**
        aux = inserirCarro(topo, c);
    }               
    topo = aux;
    tam = tamanhoPilha(topo);
}

void mostrarPilha(Pilha *topo){
  Cars *aux = *topo;

  for(int i=0; i<tamanhoPilha(topo); i++){
    printf("\nPlaca: %d | hEntrada: %d | sEntrada %d", aux->dados.placa, aux->dados.horaEntrada, aux->dados.sEntrada);
    aux = aux->prox;
  }
}

void resgatarCarro(){
    int horaSaida, sSaida;
    int placa, tam, cont = 0;

    //fflush(stdout);
        
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
 
    if(saldo<=300){

    if((consultarPilhaRetorno(topo, placa)) == 1){
        estadiaV = estadia(x[1], x[2], horaSaida, sSaida);
        saldo += estadiaV;
        printf("Carro %d deverá sair. (Estadia = %d)", placa, estadiaV);

//REMOÇÃO
   int carremovido = removeCarroPilha(topo);
   
   while(carremovido != placa){
    //Tudo o que for removido precisará retornar
    //Chamar função que seleciona funcionário que irá retirar
    
    carrosqSaem = criarListaCA();
    struct carro c, *ca;
    c.placa = x[0];
    c.horaEntrada = x[1];
    c.sEntrada = x[2];

    ca->placa = x[0];
    ca->horaEntrada = x[1];
    ca->sEntrada = x[2];

    ListaC *aux = carrosqSaem;
    carrosqSaem = insereFinalListaCA(aux, c);

    //Tentativa
    /*Pilha *aux = *topo;
    topo = carrosqSaem;

    inserirCarro(topo, ca);
    Cars *aux2 = *topo;

    while(aux2->prox != NULL){
        aux2 = aux2->prox;
    }
    (*topo)->prox = aux2; //recebe novamente o topo inicial*/

    printf("\nFuncionario x retira Carro %d.", carremovido); //Funcionário (a implementar)
    carremovido = removeCarroPilha(topo);
    cont++;
   } tam = tamanhoPilha(topo);
   
   if(carremovido == placa){
       printf("\nCarro %d saiu! Total %d", carremovido, tam);
   }else{
       printf("\nCarro não encontrado");
   }

    }else{
        printf("Carro não encontrado"); 
    }


   }else if(saldo>300){
       //chamar LDD

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

int consultarPilha(Pilha *topo, int placa){
    if(topo == NULL || (*topo) == NULL){
        return 0;
    }else{
        Cars *aux = *topo;
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

int consultarPilhaRetorno(Pilha *topo, int placa){
    if(topo == NULL || (*topo) == NULL){
        return 0;
    }else{
        Cars *aux = *topo;

        while(aux != NULL){
        if(aux->dados.placa == placa){
            x[1] = aux->dados.horaEntrada;
            x[2] = aux->dados.sEntrada;
            return 1;
        }   
        aux = aux->prox;
        }
            return 0;
    }
}

Pilha *criar(){
    Pilha *topo = (Pilha*)calloc(1, sizeof(Pilha));
    if(topo != NULL){
        *topo = NULL;
        printf("\nAbertura do estacionamento (lotação máxima = 3).");
    }else{
        printf("\nErro ao criar a pilha");
    }        
    
    return topo;
}

Pilha *criarCarrosqSaem(){
    Pilha *carrosqSaem = (Pilha*)calloc(2, sizeof(Pilha));
    if(carrosqSaem != NULL){
        *carrosqSaem = NULL;
        //printf("\nAbertura do estacionamento (lotação máxima = 3).");
    }else{
        printf("\nErro ao criar a pilha auxiliar");
    }        
    
    return carrosqSaem;
}

int tamanhoPilha(Pilha *topo){
    int cont = 0;

    if(topo == NULL){
        return 0;
    }else{
        Cars* aux = *topo;
       
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }

        //printf("\n*Tamanho da pilha: %d\n", cont);
        return cont;
    }
}

void liberar(Pilha *topo){
    if (*topo != NULL){
        Cars *aux;

        while(aux != NULL){
            aux = *topo;
            aux = aux->prox;
            free(aux);

        }free(topo);
    }
}

//Inserção e remoção
Pilha *realocar(Pilha *topo){
    int tam = tamanhoPilha(topo) + 1;
    topo = (Pilha*)realloc(topo, tam*sizeof(Pilha));

  if(topo == NULL){
      printf("Erro ao realocar");
      return NULL; 
    }else{
      return topo; 
    }
}

int lotado(Pilha *topo){
    int tam = tamanhoPilha(topo);

    if(tam>=3){
        return 1;
    }else{
        return 0;
    }
}

Pilha *inserirCarro(Pilha *topo, struct carro *c){
    int tam;
    //tam = tam + 1;
    if(topo == NULL){
        return NULL;
    }else{

      Cars *aux = (Cars*)malloc(sizeof(Cars));
        aux->dados = *c;
        
        //strcpcarremovido(aux->dados.placa, c->placa);

        aux->prox = *topo;
        *topo = aux;

        tam = tamanhoPilha(topo);
        printf("\n");
        printf("Carro %d entrou.", c->placa);
        printf(" Total %d", tam);
        return topo;
    }
}

int removeCarroPilha(Pilha *topo){
    int carremovido;

    if(topo == NULL || (*topo)==NULL){
        return 0;
    }else{
        x[0] = (*topo)->dados.placa;
        carremovido =  x[0];
        x[1] = (*topo)->dados.horaEntrada;
        x[2] = (*topo)->dados.sEntrada;

        Cars *no = *topo;
        *topo = no->prox;
        free(no);

        return carremovido;
    }
}

int consultaTopoPilha(Pilha *topo, struct carro *c){

    if(topo == NULL || (*topo) == NULL){
        return 0;
    }else{
        *c = (*topo)->dados;
        return 1;
    }
}

/*ESTACIONAMENTO*/

ListaC *criarListaCA(){
 
    ListaC *inicioCA = calloc(1, sizeof(inicioCA));
    //mudar num de funcionarios
    
    if(inicioCA==NULL){
        return NULL;
    }else{
        *inicioCA = NULL;
        return inicioCA;
    }
}

ListaC *insereFinalListaCA(ListaC *inicioCA, struct carro c){ //lista alternativa de carros   

//INSERIR Final ListaC
int tam;

  if(inicioCA==NULL){
    return 0;
  }else{

   //tam = tamanhoLista(inicioCA) + 1;
   CarsCA *aux = malloc(sizeof(ListaC));

    if(aux==NULL){
      return 0;
    }else{
      aux->dados = c;
      aux->prox = NULL;

      if((*inicioCA)==NULL){ //insere no inicio
        *inicioCA = aux; 
        return inicioCA;

      }else{

        CarsCA *aux2 = *inicioCA;
        while(aux2->prox != NULL){
          aux2 = aux2->prox;
        }
        aux2->prox = aux;
        *inicioCA = aux2;
        return inicioCA;
      }

        //Chamar funcionario que retira aqui
        //printf("");
      //printf("", fun.nome, fun.ID, fun.idade);
     // return 1;
    }
    
  }
}   

void menuFuncionario(){
    Emp *lista;
    int condicao, id;

    inicioF = criarListaFuncionario();
  
    do{
    printf("\nMENU FUNCIONÁRIOS\n1. Cadastrar funcionário \n2. Mostrar Funcionários \n3. Demitir Funcionário\n4. Ordenar por ID\n5. Ordenar por Idade\n6. Ordenar por nome\n7. Voltar\n= ");
    scanf("%d", &condicao); 

    switch(condicao){
      
     case 1:
      if(inicioF!=NULL){ 
        leituraFuncionario();
      }else{
          printf("Erro ao criar Lista Encadeada de Funcionários");
        }
      break;

     case 2:
      //mostrar condição
      mostrarLista(inicioF);
      break;

     case 3:
      printf("Qual funcionário deseja demitir? (Informar ID [identificador único]): ");
      scanf("%d", &id);
      remove_Lista(inicioF, id);
      break;

      case 4:
      ordenarBubleID(inicioF);
      break;

      case 5:
      ordenarBubleIdade(inicioF);
      break;

      case 6:
      ordenarBubleNome(inicioF);
      break;

    }
    }while(condicao != 7);

    while (getchar() != '\n');

    //liberarFunc(inicioF);
}

void leituraFuncionario(){
    struct funcionario f;

    printf("\nNome do Funcionário: ");
    fgets(f.nome, 30, stdin);
    while (getchar() != '\n');

    //stpcpy(tolower(f.nome), f.nome);

  do{
    printf("\nID: ");
    scanf("%d", &f.ID);
    while (getchar() != '\n');

  }while(consultarFuncionario(inicioF, f.ID) == 1);

    printf("\nIdade: ");
    scanf("%d", &f.idade);
    while (getchar() != '\n');

    //inserir inserção de dados
    //inserir estrutura de repetição e ponto de parada
    if((*inicioF) == NULL){
      insereFinalLista(inicioF, f);
    }else{

      int tam = tamanhoLista(inicioF);
      inicioF = realocarLista(inicioF, tam);
      insereFinalLista(inicioF, f);
      tam = tamanhoLista(inicioF);
    }
}

int consultarFuncionario(Lista *inicioF, int id){
    if(inicioF == NULL || (*inicioF) == NULL){
        return 0;
    }else{
        Emp *aux = *inicioF;
        int cont = 0;

      while(aux != NULL){
        if(aux->dados.ID == id){
            printf("\nEste ID de Funcionário já se encontra cadastrado no sistema");
            return 1;
        }   
        cont++;
        aux = aux->prox;
        }
        return 0;
    }
}

Lista *criarListaFuncionario(){
    
    Lista *emp = calloc(1, sizeof(emp));
    //mudar num de funcionarios
    
    if(emp==NULL){
        return NULL;
    }else{
        *emp = NULL;
        return emp;
    }
}

void *realocarLista(Lista *inicioF, int tam){
    tam = tam + 1;
    inicioF = (Lista*)realloc(inicioF, sizeof(Lista)*tam);

    if(inicioF == NULL){
      printf("Erro ao realocar");
      return NULL; 
    }else{
      return inicioF; 
    }
}

int tamanhoLista(Lista *inicioF){
  int cont = 0;

  if((*inicioF) == NULL){
    return 0;
  }else{
    Emp *aux = *inicioF;
    
    while(aux != NULL){
      cont++;
      aux = aux->prox;
    }

    return cont;
  }
}

void mostrarLista(Lista *inicioF){
  Emp *aux = *inicioF;

  for(int i=0; i<tamanhoLista(inicioF); i++){
    printf("\nNome: %s | ID: %d | Idade %d", aux->dados.nome, aux->dados.ID, aux->dados.idade);
    aux = aux->prox;
  }
}

void mostrarEmp(Emp *ini){
  Emp *aux = ini;
  
  for(int i=0; i<tamanhoLista((Lista*)ini); i++){
    printf("\nNome: %s | ID: %d | Idade %d", aux->dados.nome, aux->dados.ID, aux->dados.idade);
    aux = aux->prox;
  }
}

void liberarFunc(Lista* inicioF){
    if(inicioF != NULL){
      Emp* aux; //= *inicioF;

      while ((*inicioF) != NULL){
        aux = *inicioF;
        *inicioF = (*inicioF)->prox;
        free(aux);
      } free(inicioF);

    }
}

int insereFinalLista(Lista *inicioF, struct funcionario fun){
int tam;

  if(inicioF==NULL){
    return 0;
  }else{

   tam = tamanhoLista(inicioF) + 1;
   Emp *aux = calloc(tam, sizeof(Emp));

    if(aux==NULL){
      return 0;
    }else{
      aux->dados = fun;
      aux->prox = NULL;

      if((*inicioF)==NULL){
        *inicioF = aux; 
      }else{

        Emp *aux2 = *inicioF;
        while(aux2->prox != NULL){
          aux2 = aux2->prox;
        }
        aux2->prox = aux;
      }

      printf("Funcionário de nome %s (ID: %d; Idade: %d) cadastrado; ", fun.nome, fun.ID, fun.idade);
      return 1;
    }
    
  }
}

Lista *remove_Lista(Lista *inicioF, int id){
     if(inicioF==NULL || *inicioF==NULL){
        return NULL;

    }else{
        Emp *ant, *aux = *inicioF;

        while(aux!=NULL && aux->dados.ID != id){

            ant = aux;
            aux = aux->prox;
        }

        if(aux==NULL){
            //não encontrado
            printf("Não encontrado.");
            return NULL;
        }

             //outros casos
        if(aux == *inicioF){ //remover o primeiro
            *inicioF = aux->prox;
             printf("Funcionário de ID %d demitido", id);
        }else{
            ant->prox = aux->prox;//consertando a lista, caso a remoção tenha sido no meio = unindo as pontas soltas
            printf("Funcionário de ID %d demitido", id);
        }

        *inicioF = ant;
        
        free(aux); //o fato de nao estar fazendo isso em outras circunstancias pode estar me prejudicando
        return inicioF;
    }

}

Lista *ordenarBubleID(Lista *inicioF){
    struct funcionario f;
    Emp *pi;// = *inicioF; //talvez eu tenha que criarListaFuncionario um malloc aqui
    Emp *pj;// = (*inicioF)->prox;
    Emp *pfim = NULL;

  if(inicioF == NULL || (*inicioF) == NULL){
    return NULL;
  }else{

    printf("Ordenação usada: ID");

    for(pi=*inicioF; pi->prox != NULL; pi = pi->prox){
      for(pj=*inicioF; pj->prox != pfim; pj = pj->prox){ //problema está aqui

        /*AQUI A PARTE INTEIRA DE DADOS É QUE VAI SER TROCADA EX aux1->dados = aux2->dados;
        */
         //segmentation fault aqui 2h43 31/05
        if((pj->dados.ID) > (pj->prox->dados.ID)){ //segmentation fault aqui 2h40 31/05
            f = pj->dados;
            //(*aux)->dados = (*pj)->dados;
            pj->dados = pj->prox->dados;
            pj->prox->dados = f;        
        }
      }
      pfim = pj;
    }
  }
}

Lista *ordenarBubleIdade(Lista *inicioF){

    struct funcionario f;
    Emp *pi;
    Emp *pj;
    Emp *pfim = NULL;

  if(inicioF == NULL || (*inicioF) == NULL){
    return NULL;
  }else{

    printf("\nOrdenação usada: Idade");

    for(pi=*inicioF; pi->prox != NULL; pi = pi->prox){
      for(pj=*inicioF; pj->prox != pfim; pj = pj->prox){ 

        if((pj->dados.idade) > (pj->prox->dados.idade)){
            f = pj->dados;
            pj->dados = pj->prox->dados;
            pj->prox->dados = f;        
        }
      }
      pfim = pj;
    }
  }
}

Lista *ordenarBubleNome(Lista *inicioF){

    struct funcionario f;
    int cont = 0;
    Emp *pi;
    Emp *pj;
    Emp *pfim = NULL;
    char alfabeto[] = {'a', 'b','c','d', 'e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','v','w','x','y','z'};
    char *fixo, a;

  if(inicioF == NULL || (*inicioF) == NULL){
    return NULL;
  }else{

    printf("\nOrdenação usada: Nome ");

      for(pj=*inicioF; pj->prox != NULL; pj = pj->prox){ 
        for(int i=0; i<25; i++){       

        //stpcpy(fixo, &alfabeto[i]);

    //    stpcpy(a, tolower(pj->dados.nome[0]));

        if((strncmp((pj->dados.nome),  &alfabeto[i], 1))==0 && cont<i){
            f = pj->dados;
            pj->dados = pj->prox->dados;
            pj->prox->dados = f;        
        }
      }
      cont ++;
      }
  }
}
