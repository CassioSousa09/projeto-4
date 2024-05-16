# define TOTAL 300
#define SAQUES 100



typedef struct {
    char nome[50];
    int cpf[12]; 
    int senha;
    float saldo;
    char tipo[10];
struct {
    char tipo; 
    float valor;
} transacoes[SAQUES];
int num_transacoes;


} Arquivos;



typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;

typedef ERROS (*funcao)(Arquivos[], int*);

ERROS cadastrarCliente (Arquivos arquivos[], int *pos);
ERROS deletar (Arquivos arquivos[], int *pos);
ERROS listar (Arquivos arquivos[], int *pos);
ERROS debito (Arquivos arquivos[], int *pos);
ERROS deposito (Arquivos arquivos[], int *pos);
ERROS extrato (Arquivos arquivos[], int *pos);
ERROS transferencia (Arquivos arquivos[], int *pos);
ERROS salvar (Arquivos arquivos[], int *pos);
ERROS carregar (Arquivos arquivos[], int *pos);


void clearBuffer();