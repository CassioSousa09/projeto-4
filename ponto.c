#include "ponto.h"
#include <stdio.h>


ERROS cadastrarCliente(Arquivos arquivos[], int *pos) {
  if(*pos >= TOTAL)
    return MAX_TAREFA;


  printf("Digite o nome do cliente: ");
      fgets(arquivos[*pos].nome, sizeof(arquivos[*pos].nome), stdin);
      arquivos[*pos].nome[strcspn(arquivos[*pos].nome, "\n")] = 0;

      printf("Digite o seu CPF (11 caracteres): ");
      scanf("%14s", arquivos[*pos].cpf);

      printf("Digite a quantia inicial em sua conta: ");
      scanf("%f", &arquivos[*pos].saldo);

      printf("Digite seu tipo de conta (COMUM ou PLUS): ");
      scanf("%9s", arquivos[*pos].tipo);

      printf("Digite sua senha: ");
      scanf("%d", &arquivos[*pos].senha);

      printf("Cliente cadastrado com sucesso!\n");

      (*pos)++; 

      return OK;
  }




  ERROS deletar(Arquivos arquivos[], int *pos) {
    char cpf[15];
    printf("Digite o CPF do cliente para apagar: ");
    scanf("%14s", cpf);

    int found = 0;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(arquivos[i].cpf, cpf) == 0) {
            found = 1;
            for (int j = i; j < *pos - 1; j++) {
                arquivos[j] = arquivos[j + 1];
            }
            (*pos)--;
            break;
        }
    }

    if (found) {
        printf("Cliente apagado com sucesso!\n");
        salvar(arquivos, pos);
    } else {
        printf("CPF não encontrado.\n");
    }

    return OK;
}




ERROS listar(Arquivos arquivos[], int *pos) {
    printf("Lista de clientes:\n");
    for (int i = 0; i < *pos; i++) {
        Arquivos cliente = arquivos[i];
        printf("Nome: %s, CNPJ: %s, Saldo: %.2f, Tipo: %s\n",
               cliente.nome, cliente.cpf, cliente.saldo, cliente.tipo);
    }

    return OK;
}