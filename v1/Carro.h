
struct carro{
    int placa;
    int horaEntrada;
    int sEntrada;
    //int horaSaida;
   // int sSaida;
   // float divida;
};

//typedef struct carro *c;

typedef struct veiculos *Pilha;
typedef struct veiculos *ListaC; //alternativo

struct veiculos{
    struct carro dados;
    struct veiculos *prox;
};

typedef struct veiculos Cars;
typedef struct veiculos CarsCA; //alternativo

Pilha *criar();
int tamanhoPilha(Pilha *topo);
void liberar(Pilha *topo);
Pilha *realocar(Pilha *topo);
Pilha *inserirCarro(Pilha *topo, struct carro *c);
Pilha *removeCarroT(Pilha *topo, int placa);
void mostrarPilha(Pilha *topo);
//Pilha *removeCarro(Pilha *topo, char placa);

void leituraPilha();
void resgatarCarro();
void menuLotado();

/*Para lidar com carros que saem da Pilha mas retornam*/
ListaC *criarListaCA();
ListaC *insereFinalListaCA(ListaC *inicioCA, struct carro c);//lista alternativa de carros  

/*Para remoção*/
int removeCarroPilha(Pilha *topo);
int consultaTopoPilha(Pilha *topo, struct carro *c);

/*Baseadas em LDD*/
int consultarPilhaRetorno(Pilha *topo, int placa);
int consultarPilha(Pilha *topo, int placa);
int estadia(int hentrada, int sentrada, int hsaida, int ssaida);

