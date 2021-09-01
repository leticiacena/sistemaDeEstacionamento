
struct carro{
    int ordem;
    int placa;
    int horaEntrada;
    int sEntrada;
};

typedef struct veiculos *Lista;

struct veiculos{
    struct veiculos *ant;
    struct carro dados;
    struct veiculos *prox;
};

typedef struct veiculos Cars; //Tipo auxiliar para Lista duplamente encadeada
typedef struct veiculosArvBin* ArvBin; 
//typedef struct veiculosArvBin ABB;Tipo auxiliar para Árvore Binária de Busca

Lista *criarLDD();
int tamanhoLDD(Lista *inicio);
void liberarLDD(Lista *inicio);
void liberarLDDCars(Cars *ini);
Lista *realocarLDD(Lista *inicio);
Lista *inserirCarroLDD(Lista *inicio, struct carro c);
Lista *removerCarroLDD(Lista *inicio, int placa);

int consultarLDD(Lista *inicio, int placa); //Consulta para entrada
int consultarPosicao(Lista *inicio, int placa); //quando ja sei que o elemento esta na lista
int consultarLDDRetorNo(Lista *inicio, int placa); //Consulta para saída
int removeCarro(Lista *inicio, int placa);
int estadia(int hentrada, int sentrada, int hsaida, int ssaida);

void leituraLDD();
void resgatarCarro();
void menuLotado();
void mostrarLDD(Lista *inicio);

/*Árvore Binária de Busca*/
int menuOrdem(ArvBin *raiz);
void leituraArvBin();

ArvBin* criar();
ArvBin *realocar(ArvBin *li);

void liberaveiculosArvBin(struct veiculosArvBin* veiculosArvBin);
void liberaArvBin(ArvBin *raiz);
int alturaArvBin(ArvBin *raiz);
int totalveiculosArvBin(ArvBin *raiz);

void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

int menuOrdem(ArvBin *raiz);
int insere_arvBin(ArvBin* raiz, struct carro infos);
struct veiculosArvBin* remove_atual(struct veiculosArvBin* atual);
int remove_ArvBin(ArvBin *raiz, int valor);
int consulta_ArvBin(ArvBin *raiz, int valor);

void calculaEficiencia();
int remove_lista_ordenada(Lista *inicio, int placa);

//void atualizaOrdemLDD();
//void atualizaOrdemABB();

int consultarPosicaoABB(ArvBin *raiz, int placa);

//ÁRVORE AVL 
typedef struct veiculosAVL* ArvAVL;
 
ArvAVL* criarAVL();
ArvAVL *realocarAVL(ArvAVL *raizAVL);

void liberaNoAVL(struct veiculosAVL* no);
void liberaArvAVL(ArvAVL *raizAVL);

int alturaArvAVL(ArvAVL *raizAVL);
int totalNOsArvAVL(ArvAVL *raizAVL);

void preOrdem_ArvAVL(ArvAVL *raizAVL);
void emOrdem_ArvAVL(ArvAVL *raizAVL);
void posOrdem_ArvAVL(ArvAVL *raizAVL);

int altNOAVL(struct veiculosAVL* no);
int fator_BalanceamentoAVL(struct veiculosAVL* no);
int maiorAVL(int x, int y);

void RotacaoLL(ArvAVL *raizAVL);
void RotacaoRR(ArvAVL *raizAVL);
void RotacaoLR(ArvAVL *raizAVL);
void RotacaoRL(ArvAVL *raizAVL);

int insereAVL(ArvAVL *raizAVL, struct carro c);
int removeAVL(ArvAVL *raizAVL, int placa);
struct veiculosAVL* procuraMenorAVL(struct veiculosAVL* atual);

int menu(ArvAVL *raiz);
int menuOrdemAVL(ArvAVL *raizAVL);
int consulta_ArvAVL(ArvAVL *raiz, int placa);
