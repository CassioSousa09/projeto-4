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