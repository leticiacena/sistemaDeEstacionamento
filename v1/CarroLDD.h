
struct carro{
    int placa;
    int horaEntrada;
    int sEntrada;
    //int horaSaida;
    //float divida;
};

typedef struct veiculos *Lista;

struct veiculos{
    struct veiculos *ant;
    struct carro dados;
    struct veiculos *prox;
};

typedef struct veiculos Cars;

Lista *criarLDD();
int tamanhoLDD(Lista *inicio);
void liberarLDD(Lista *inicio);
void liberarLDDCars(Cars *ini);
Lista *realocarLDD(Lista *inicio);
Lista *inserirCarroLDD(Lista *inicio, struct carro c);
Lista *removerCarroLDD(Lista *inicio, int placa);

int consultarLDD(Lista *inicio, int placa);
int consultarPosicao(Lista *inicio, int placa); //quando ja sei que o elemento esta na lista
int consultarLDDRetorno(Lista *inicio, int placa);
int removeCarro(Lista *inicio, int placa);
int estadia(int hentrada, int sentrada, int hsaida, int ssaida);

void leituraLDD();
void resgatarCarro();
void menuLotado();
void mostrarLDD(Lista *inicio);
