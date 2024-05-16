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



ERROS debito(Arquivos arquivos[], int *pos) {
    char cpf[15];
    printf("Digite seu CPF: ");
    scanf("%14s", cpf);

    int found = 0;
    Arquivos *cliente = NULL;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(arquivos[i].cpf, cpf) == 0) {
            cliente = &arquivos[i];
            found = 1;
            break;
        }
    }

    if (found) {
        int senha;
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (senha == cliente->senha) {
            float valor;
            printf("Digite o valor do saque: ");
            scanf("%f", &valor);

            float saldo_minimo = (cliente->tipo == 0) ? -1000.0 : -5000.0;

            if (cliente->saldo - valor >= saldo_minimo) {
                float taxa = (cliente->tipo == 0) ? 0.05 : 0.03;
                float valor_final = valor + (valor * taxa);
                cliente->saldo -= valor_final;

                printf("R$ %.2f foram debitados de sua conta.\n", valor_final);

                
                cliente->transacoes[cliente->num_transacoes].tipo = 'debito';
                cliente->transacoes[cliente->num_transacoes].valor = valor_final;
                cliente->num_transacoes++;
            } else {
                printf("Saldo limite alcançado.\n");
            }
        } else {
            printf("Senha inválida.\n");
        }
    } else {
        printf("CPF não encontrado.\n");
    }

    return OK;
}

ERROS deposito(Arquivos arquivos[], int *pos) {
    char cpf[15];
    printf("Digite seu CPF: ");
    scanf("%14s", cpf);

    Arquivos *cliente = NULL;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(arquivos[i].cpf, cpf) == 0) {
            cliente = &arquivos[i];
            break;
        }
    }

    if (cliente != NULL) {
        int senha;
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (senha == cliente->senha) {
            float valor;
            printf("Digite o valor do depósito: ");
            scanf("%f", &valor);

            cliente->saldo += valor;
            printf("R$ %.2f foram depositados em sua conta.\n", valor);

            
            cliente->transacoes[cliente->num_transacoes].tipo = 'Deposito';
            cliente->transacoes[cliente->num_transacoes].valor = valor;
            cliente->num_transacoes++;
        } else {
            printf("Senha inválida.\n");
        }
    } else {
        printf("CPF não encontrado.\n");
    }

    return OK;
}



ERROS extrato(Arquivos arquivos[], int *pos) {
    char cpf[15];
    printf("Digite seu CPF: ");
    scanf("%14s", cpf);

    Arquivos *cliente = NULL;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(arquivos[i].cpf, cpf) == 0) {
            cliente = &arquivos[i];
            break;
        }
    }

    if (cliente != NULL) {
        int senha;
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (senha == cliente->senha) {
            printf("Extrato do Cliente:\n");
            printf("Nome: %s\n", cliente->nome);
            printf("CPF: %s\n", cliente->cpf);
            printf("Saldo: %.2f\n", cliente->saldo);
            printf("Transações:\n");
            for (int i = 0; i < cliente->num_transacoes; i++) {
                printf("Tipo: %c, Valor: %.2f\n", cliente->transacoes[i].tipo, cliente->transacoes[i].valor);
            }
        } else {
            printf("Senha inválida.\n");
        }
    } else {
        printf("CPF não encontrado.\n");
    }

    return OK;
}



ERROS transferencia(Arquivos arquivos[], int *pos) {
    char cpf_origem[15], cpf_destino[15];
    printf("Digite seu CPF: ");
    scanf("%14s", cpf_origem);

    Arquivos *origem = NULL;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(arquivos[i].cpf, cpf_origem) == 0) {
            origem = &arquivos[i];
            break;
        }
    }

    if (origem != NULL) {
        int senha;
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (senha == origem->senha) {
            printf("Digite o CPF do destinatário: ");
            scanf("%14s", cpf_destino);

            Arquivos *destino = NULL;
            for (int i = 0; i < *pos; i++) {
                if (strcmp(arquivos[i].cpf, cpf_destino) == 0) {
                    destino = &arquivos[i];
                    break;
                }
            }

            if (destino != NULL) {
                float valor;
                printf("Digite o valor para transferência: ");
                scanf("%f", &valor);

                if (origem->saldo >= valor) {
                    origem->saldo -= valor;
                    destino->saldo += valor;

                    printf("R$ %.2f foram transferidos de %s para %s.\n", valor, origem->nome, destino->nome);

                    
                    origem->transacoes[origem->num_transacoes].tipo = 'T';
                    origem->transacoes[origem->num_transacoes].valor = -valor;
                    origem->num_transacoes++;

                    
                    destino->transacoes[destino->num_transacoes].tipo =  'T' ;
                    destino->transacoes[destino->num_transacoes].valor = valor;
                    destino->num_transacoes++;

                    salvar(arquivos, pos);
                } else {
                    printf("Saldo insuficiente para a transferência.\n");
                }
            } else {
                printf("CPF do destinatário não encontrado.\n");
            }
        } else {
            printf("Senha inválida.\n");
        }
    } else {
        printf("CPF não encontrado.\n");
    }

    return OK;
}









ERROS salvar(Arquivos arquivos[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(arquivos, TOTAL, sizeof(Arquivos), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Arquivos arquivos[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(arquivos, TOTAL, sizeof(Arquivos), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}









void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}