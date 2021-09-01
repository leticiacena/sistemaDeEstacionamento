struct funcionario{
    int ID;
    char nome[30];
    int idade;
};

typedef struct funcionario f;
typedef struct empregados *Lista;

struct empregados{
    struct funcionario dados;
    struct empregados *prox;
};

typedef struct empregados Emp;


//Início da Lista (ponteiro para ponteiro)
Lista *inicio;

//Funções
Lista *criarListaFuncionario();
void liberarFunc(Lista* inicio);
void *realocarLista(Lista *inicio, int tam);
int tamanhoLista(Lista *inicio);
void mostrarLista(Lista *inicio);
int insereFinalLista(Lista *inicio, struct funcionario fun);
Lista *ordenarBuble();
Lista *ordenarBubleID(Lista *inicio);
Lista *ordenarBubleIdade(Lista *inicio);
Lista *ordenarBubleNome(Lista *inicio);
Lista *remove_Lista(Lista *inicio, int id);

int consultarFuncionario(Lista *inicio, int id);
void leituraFuncionario();
void menuFuncionario();