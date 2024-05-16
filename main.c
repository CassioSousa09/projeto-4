#include <stdio.h>
#include "ponto.h"

int main(){
  funcao fs[] = {cadastrarCliente,deletar,listar,debito,deposito,extrato,transferencia,salvar,carregar};
   Arquivos arquivos[TOTAL];

  
int pos;
int escolha;
do{
  printf("\nMenu principal\n");
  printf("######################\n");
  printf("1 - Criar contato\n");
  printf("2 - deletar cliente\n");
  printf("3 - Listar \n");
  printf("4 - debito\n");
  printf("5 - deposito\n");
  printf("6 - extrato\n");
  printf("7 - tranferencia entre contas\n");
  printf("8 - salvar em bin\n");
  printf("9 - Carregar em bin\n");
  printf("0 - Sair\n");
  printf("######################\n"); 
  printf("escolha a sua opcao:\n");
  scanf("%d", &escolha);
  clearBuffer();
  

      if (escolha > 0 && escolha < 10) {
        ERROS erro = fs[escolha - 1](arquivos, &pos);
        printf("------------------\n");
      } else if (escolha == 0) {
        printf("tchau \n");
      } else {
        printf("**Opção Inválida**\n");
      }
      } while (escolha > 0);
    
  return 0;
  
}

      
