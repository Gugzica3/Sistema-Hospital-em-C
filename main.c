/* Sistema de Hospital em C */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura para armazenar uma data */
typedef struct {
  int dia, mes, ano;
} Data;

/* Estrutura que representa um paciente */
typedef struct {
  char nome[100];
  int idade;
  char rg[10];
  Data entrada; // Data de entrada do paciente
} Registro;

/* Nó da lista encadeada de pacientes */
typedef struct ELista {
  Registro *dados;
  struct ELista *proximo; // Ponteiro para o próximo nó da lista
} ELista;

/* Estrutura que representa a lista de pacientes */
typedef struct {
  ELista *inicio; // Ponteiro para o início da lista
  int quantidade; // Quantidade de pacientes na lista
} Lista;

/* Nó da fila de atendimento */
typedef struct EFila {
  Registro *dados;
  struct EFila *proximo; // Ponteiro para o próximo nó da fila
} EFila;

/* Estrutura que representa a fila de atendimento */
typedef struct {
  EFila *head;    // Ponteiro para o início da fila
  EFila *tail;    // Ponteiro para o fim da fila
  int quantidade; // Quantidade de pacientes na fila
} Fila;

/* Nó da árvore binária de busca */
typedef struct EABB {
  Registro *dados;
  struct EABB *FilhoEsq,
      *FilhoDir; // Ponteiros para os filhos esquerdo e direito
} EABB;

/* Estrutura que representa a árvore binária */
typedef struct {
  EABB *raiz;     // Ponteiro para a raiz da árvore
  int quantidade; // Quantidade de pacientes na árvore
} ABB;

/* Nó da pilha usada para desfazer operações */
typedef struct EPilha {
  Registro *dados;
  char operacao[20]; // Descrição da operação (CADASTRAR, REMOVER, ATUALIZAR)
  struct EPilha *proximo; // Ponteiro para o próximo nó da pilha
} EPilha;

/* Estrutura que representa a pilha */
typedef struct {
  EPilha *topo; // Ponteiro para o topo da pilha
} Pilha;

/* Função auxiliar para limpar o buffer do teclado */
/* Imagine que o buffer é como um balde onde a gente joga as coisas que não
 * queremos. */
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

/* ===================== Função 'sobre' ===================== */

/* Exibe informações sobre o programa */
void sobre() {
  printf("\n========== Sobre o Programa ==========\n");
  printf("Sistema de Hospital\n");
  printf("Desenvolvido por: Gustavo Bertoluzzi e Isabella Rosseto\n");
  printf("Ciclo: Noturno\n");
  printf("Curso: Ciência da computação\n");
  printf("Disciplina: Estrutura de dados\n");
  printf("Data: 02/11/2024\n");
}
/* ===================== BLOCO 1: Cadastro de Pacientes (Lista)
 * ===================== */

/* Inicializa a lista de pacientes */
/* Pense na lista como uma corrente onde cada elo é um paciente. */
void inicializarLista(Lista *lista) {
  lista->inicio = NULL; // No começo, a lista está vazia, sem nenhum paciente.
  lista->quantidade = 0; // Nenhum paciente cadastrado inicialmente.
}

/* Cadastra um novo paciente na lista */
void cadastrarPaciente(Lista *lista) {
  ELista *novoNo =
      (ELista *)malloc(sizeof(ELista)); // Cria um novo elo na corrente.
  if (novoNo == NULL) {
    printf("Erro de alocação de memória.\n");
    return; // Se não conseguir criar o elo, para tudo aqui.
  }

  novoNo->dados = (Registro *)malloc(
      sizeof(Registro)); // Reserva espaço para os dados do paciente.
  if (novoNo->dados == NULL) {
    printf("Erro de alocação de memória.\n");
    free(novoNo); // Libera o elo que foi criado, pois não deu para guardar os
                  // dados.
    return;
  }

  /* Coleta os dados do paciente */
  printf("Digite o nome do paciente: ");
  fgets(novoNo->dados->nome, 100, stdin); // Pede para o usuário digitar o nome.
  novoNo->dados->nome[strcspn(novoNo->dados->nome, "\n")] =
      '\0'; // Remove o '\n' que fica no final.

  printf("Digite a idade do paciente: ");
  scanf("%d", &novoNo->dados->idade); // Pede a idade.
  limparBuffer(); // Limpa o balde (buffer) para não bagunçar a próxima entrada.

  printf("Digite o RG do paciente: ");
  fgets(novoNo->dados->rg, 10, stdin); // Pede o RG, que é como um ID.
  novoNo->dados->rg[strcspn(novoNo->dados->rg, "\n")] =
      '\0'; // Remove o '\n' final.

  printf("Digite a data de entrada (dd mm aaaa): ");
  scanf("%d %d %d", &novoNo->dados->entrada.dia, &novoNo->dados->entrada.mes,
        &novoNo->dados->entrada.ano); // Pede a data de entrada.
  limparBuffer();                     // Limpa o buffer novamente.

  /* Adiciona o novo paciente no início da lista */
  novoNo->proximo =
      lista->inicio; // O próximo do novo paciente é o que já estava na lista.
  lista->inicio = novoNo; // O novo paciente passa a ser o primeiro da lista.
  lista->quantidade++;    // Aumenta a contagem de pacientes.

  printf("Paciente cadastrado com sucesso!\n"); // Informa que deu tudo certo.
}

/* Consulta um paciente pelo RG */
void consultarPaciente(Lista *lista, const char *rg) {
  ELista *atual = lista->inicio; // Começa no primeiro paciente da lista.
  while (atual != NULL) {        // Enquanto houver pacientes na lista.
    if (strcmp(atual->dados->rg, rg) ==
        0) { // Compara o RG do paciente atual com o RG procurado.
      /* Se encontrar, mostra os dados do paciente */
      printf("\nPaciente encontrado:\n");
      printf("Nome: %s\n", atual->dados->nome);
      printf("Idade: %d\n", atual->dados->idade);
      printf("RG: %s\n", atual->dados->rg);
      printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados->entrada.dia,
             atual->dados->entrada.mes, atual->dados->entrada.ano);
      return; // Sai da função, já encontrou o paciente.
    }
    atual = atual->proximo; // Vai para o próximo paciente da lista.
  }
  /* Se não encontrar, avisa o usuário */
  printf("Paciente com RG %s não encontrado.\n", rg);
}

/* Atualiza os dados de um paciente */
void atualizarPaciente(Lista *lista, const char *rg) {
  ELista *atual = lista->inicio;             // Começa no primeiro paciente.
  while (atual != NULL) {                    // Percorre a lista inteira.
    if (strcmp(atual->dados->rg, rg) == 0) { // Se encontrar o RG procurado.
      printf("Atualizando dados do paciente %s:\n", atual->dados->nome);

      printf("Digite o novo nome do paciente: ");
      fgets(atual->dados->nome, 100, stdin); // Pede o novo nome.
      atual->dados->nome[strcspn(atual->dados->nome, "\n")] =
          '\0'; // Remove o '\n'.

      printf("Digite a nova idade do paciente: ");
      scanf("%d", &atual->dados->idade); // Pede a nova idade.
      limparBuffer();                    // Limpa o buffer.

      printf("Digite a nova data de entrada (dd mm aaaa): ");
      scanf("%d %d %d", &atual->dados->entrada.dia, &atual->dados->entrada.mes,
            &atual->dados->entrada.ano); // Pede a nova data.
      limparBuffer();                    // Limpa o buffer.

      printf(
          "Paciente atualizado com sucesso!\n"); // Informa que deu tudo certo.
      return;                                    // Sai da função.
    }
    atual = atual->proximo; // Vai para o próximo paciente.
  }
  /* Se não encontrar, avisa o usuário */
  printf("Paciente com RG %s não encontrado.\n", rg);
}

/* Remove um paciente da lista */
void removerPaciente(Lista *lista, const char *rg) {
  ELista *atual = lista->inicio; // Começa no primeiro paciente.
  ELista *anterior =
      NULL; // Guarda o paciente anterior para poder remover o atual.

  while (atual != NULL) {                    // Percorre a lista.
    if (strcmp(atual->dados->rg, rg) == 0) { // Se encontrar o RG.
      if (anterior == NULL) {                // Se for o primeiro da lista.
        lista->inicio = atual->proximo; // O próximo passa a ser o primeiro.
      } else {
        anterior->proximo = atual->proximo; // Liga o anterior ao próximo.
      }
      free(atual->dados);  // Libera a memória dos dados do paciente.
      free(atual);         // Libera o nó da lista.
      lista->quantidade--; // Diminui a contagem de pacientes.
      printf("Paciente removido com sucesso!\n"); // Informa que deu certo.
      return;                                     // Sai da função.
    }
    anterior = atual;       // Atualiza o paciente anterior.
    atual = atual->proximo; // Vai para o próximo paciente.
  }
  /* Se não encontrar, avisa o usuário */
  printf("Paciente com RG %s não encontrado.\n", rg);
}

/* Exibe todos os pacientes cadastrados */
void exibirPacientes(Lista *lista) {
  if (lista->inicio == NULL) { // Se a lista estiver vazia.
    printf("Nenhum paciente cadastrado.\n");
    return;
  }

  ELista *atual = lista->inicio; // Começa no primeiro paciente.
  printf("\nLista de Pacientes:\n");
  while (atual != NULL) { // Percorre a lista inteira.
    printf("------------------------------\n");
    printf("Nome: %s\n", atual->dados->nome);
    printf("Idade: %d\n", atual->dados->idade);
    printf("RG: %s\n", atual->dados->rg);
    printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados->entrada.dia,
           atual->dados->entrada.mes, atual->dados->entrada.ano);
    atual = atual->proximo; // Vai para o próximo paciente.
  }
}

/* ===================== BLOCO 2: Ordem de Atendimento (Fila)
 * ===================== */

/* Inicializa a fila de atendimento */
/* A fila é como uma linha de espera: o primeiro que entra é o primeiro que sai.
 */
void inicializarFila(Fila *fila) {
  fila->head = NULL;    // Começa vazia, sem ninguém na fila.
  fila->tail = NULL;    // O final também está vazio.
  fila->quantidade = 0; // Nenhum paciente na fila inicialmente.
}

/* Enfileira um paciente para atendimento */
void enfileirarPaciente(Fila *fila, Registro *paciente) {
  EFila *novoNo = (EFila *)malloc(sizeof(EFila)); // Cria um novo lugar na fila.
  if (novoNo == NULL) {
    printf("Erro de alocação de memória.\n");
    return; // Se não conseguir, para aqui.
  }
  novoNo->dados = paciente; // Guarda os dados do paciente.
  novoNo->proximo = NULL; // O próximo é NULL porque vai ser o último da fila.

  if (fila->tail == NULL) { // Se a fila estiver vazia.
    fila->head = novoNo;    // O novo paciente é o primeiro.
  } else {
    fila->tail->proximo = novoNo; // Liga o último da fila ao novo paciente.
  }
  fila->tail = novoNo; // Atualiza o final da fila.
  fila->quantidade++;  // Aumenta a contagem de pacientes na fila.

  printf("Paciente %s enfileirado para atendimento.\n",
         paciente->nome); // Informa que o paciente foi enfileirado.
}

/* Desenfileira um paciente */
void desenfileirarPaciente(Fila *fila) {
  if (fila->head == NULL) { // Se a fila estiver vazia.
    printf("Fila de atendimento vazia.\n");
    return;
  }
  EFila *remover = fila->head;      // Pega o primeiro paciente da fila.
  fila->head = fila->head->proximo; // O próximo passa a ser o primeiro.
  if (fila->head == NULL) {         // Se a fila ficou vazia após remover.
    fila->tail = NULL;              // O final também fica vazio.
  }
  printf("Paciente %s foi atendido.\n",
         remover->dados->nome); // Informa que o paciente foi atendido.
  free(remover);                // Libera o lugar na fila.
  fila->quantidade--;           // Diminui a contagem de pacientes na fila.
}

/* Exibe a fila de atendimento */
void exibirFila(Fila *fila) {
  if (fila->head == NULL) { // Se a fila estiver vazia.
    printf("Fila de atendimento vazia.\n");
    return;
  }

  EFila *atual = fila->head; // Começa no primeiro da fila.
  printf("\nFila de Atendimento:\n");
  while (atual != NULL) { // Percorre toda a fila.
    printf("Paciente: %s | RG: %s\n", atual->dados->nome,
           atual->dados->rg); // Mostra o paciente.
    atual = atual->proximo;   // Vai para o próximo paciente.
  }
}

/* ===================== BLOCO 3: Pesquisa e Ordenação (ABB)
 * ===================== */

/* Inicializa uma ABB */
void inicializarABB(ABB *arvore) {
  arvore->raiz = NULL;    // Começa com a árvore vazia.
  arvore->quantidade = 0; // Nenhum paciente na árvore.
}

/* Insere um paciente na ABB ordenada por ano */
EABB *inserirPorAno(EABB *raiz, Registro *paciente) {
  if (raiz == NULL) { // Se a árvore ou sub-árvore estiver vazia.
    EABB *novoNo = (EABB *)malloc(sizeof(EABB)); // Cria um novo nó.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      return NULL; // Se não conseguir, para aqui.
    }
    novoNo->dados = paciente;                   // Guarda os dados do paciente.
    novoNo->FilhoEsq = novoNo->FilhoDir = NULL; // Não tem filhos ainda.
    return novoNo; // Retorna o novo nó para ser ligado na árvore.
  }
  /* Compara o ano de entrada do paciente com o ano do paciente no nó atual */
  if (paciente->entrada.ano < raiz->dados->entrada.ano) {
    raiz->FilhoEsq = inserirPorAno(
        raiz->FilhoEsq, paciente); // Vai para a esquerda se for menor.
  } else {
    raiz->FilhoDir = inserirPorAno(
        raiz->FilhoDir, paciente); // Vai para a direita se for igual ou maior.
  }
  return raiz; // Retorna a raiz atualizada.
}

/* Insere um paciente na ABB ordenada por mês */
EABB *inserirPorMes(EABB *raiz, Registro *paciente) {
  if (raiz == NULL) { // Se a árvore ou sub-árvore estiver vazia.
    EABB *novoNo = (EABB *)malloc(sizeof(EABB)); // Cria um novo nó.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      return NULL; // Se não conseguir, para aqui.
    }
    novoNo->dados = paciente;                   // Guarda os dados do paciente.
    novoNo->FilhoEsq = novoNo->FilhoDir = NULL; // Não tem filhos ainda.
    return novoNo; // Retorna o novo nó para ser ligado na árvore.
  }
  /* Compara o mês de entrada do paciente com o mês do paciente no nó atual */
  if (paciente->entrada.mes < raiz->dados->entrada.mes) {
    raiz->FilhoEsq = inserirPorMes(
        raiz->FilhoEsq, paciente); // Vai para a esquerda se for menor.
  } else {
    raiz->FilhoDir = inserirPorMes(
        raiz->FilhoDir, paciente); // Vai para a direita se for igual ou maior.
  }
  return raiz; // Retorna a raiz atualizada.
}

/* Insere um paciente na ABB ordenada por dia */
EABB *inserirPorDia(EABB *raiz, Registro *paciente) {
  if (raiz == NULL) { // Se a árvore ou sub-árvore estiver vazia.
    EABB *novoNo = (EABB *)malloc(sizeof(EABB)); // Cria um novo nó.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      return NULL; // Se não conseguir, para aqui.
    }
    novoNo->dados = paciente;                   // Guarda os dados do paciente.
    novoNo->FilhoEsq = novoNo->FilhoDir = NULL; // Não tem filhos ainda.
    return novoNo; // Retorna o novo nó para ser ligado na árvore.
  }
  /* Compara o dia de entrada do paciente com o dia do paciente no nó atual */
  if (paciente->entrada.dia < raiz->dados->entrada.dia) {
    raiz->FilhoEsq = inserirPorDia(
        raiz->FilhoEsq, paciente); // Vai para a esquerda se for menor.
  } else {
    raiz->FilhoDir = inserirPorDia(
        raiz->FilhoDir, paciente); // Vai para a direita se for igual ou maior.
  }
  return raiz; // Retorna a raiz atualizada.
}

/* Insere um paciente na ABB ordenada por idade */
EABB *inserirPorIdade(EABB *raiz, Registro *paciente) {
  if (raiz == NULL) { // Se a árvore ou sub-árvore estiver vazia.
    EABB *novoNo = (EABB *)malloc(sizeof(EABB)); // Cria um novo nó.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      return NULL; // Se não conseguir, para aqui.
    }
    novoNo->dados = paciente;                   // Guarda os dados do paciente.
    novoNo->FilhoEsq = novoNo->FilhoDir = NULL; // Não tem filhos ainda.
    return novoNo; // Retorna o novo nó para ser ligado na árvore.
  }
  /* Compara a idade do paciente com a idade do paciente no nó atual */
  if (paciente->idade < raiz->dados->idade) {
    raiz->FilhoEsq = inserirPorIdade(
        raiz->FilhoEsq, paciente); // Vai para a esquerda se for menor.
  } else {
    raiz->FilhoDir = inserirPorIdade(
        raiz->FilhoDir, paciente); // Vai para a direita se for igual ou maior.
  }
  return raiz; // Retorna a raiz atualizada.
}

/* Exibe a ABB em ordem */
/* Percorre a árvore de forma ordenada: primeiro a esquerda, depois o nó, depois
 * a direita */
void exibirABBInOrdem(EABB *raiz) {
  if (raiz != NULL) { // Se o nó não for vazio.
    exibirABBInOrdem(
        raiz->FilhoEsq); // Primeiro, visita toda a sub-árvore da esquerda.
    printf("------------------------------\n");
    printf("Nome: %s\n", raiz->dados->nome);
    printf("Idade: %d\n", raiz->dados->idade);
    printf("RG: %s\n", raiz->dados->rg);
    printf("Data de Entrada: %02d/%02d/%04d\n", raiz->dados->entrada.dia,
           raiz->dados->entrada.mes, raiz->dados->entrada.ano);
    exibirABBInOrdem(
        raiz->FilhoDir); // Depois, visita toda a sub-árvore da direita.
  }
}

/* Insere um paciente na ABB ordenada por ano */
void inserirPorAnoABB(ABB *arvore, Registro *paciente) {
  arvore->raiz = inserirPorAno(
      arvore->raiz, paciente); // Chama a função para inserir na árvore.
  arvore->quantidade++;        // Aumenta a contagem de pacientes na árvore.
}

/* Insere um paciente na ABB ordenada por mês */
void inserirPorMesABB(ABB *arvore, Registro *paciente) {
  arvore->raiz = inserirPorMes(
      arvore->raiz, paciente); // Chama a função para inserir na árvore.
  arvore->quantidade++;        // Aumenta a contagem de pacientes na árvore.
}

/* Insere um paciente na ABB ordenada por dia */
void inserirPorDiaABB(ABB *arvore, Registro *paciente) {
  arvore->raiz = inserirPorDia(
      arvore->raiz, paciente); // Chama a função para inserir na árvore.
  arvore->quantidade++;        // Aumenta a contagem de pacientes na árvore.
}

/* Insere um paciente na ABB ordenada por idade */
void inserirPorIdadeABB(ABB *arvore, Registro *paciente) {
  arvore->raiz = inserirPorIdade(
      arvore->raiz, paciente); // Chama a função para inserir na árvore.
  arvore->quantidade++;        // Aumenta a contagem de pacientes na árvore.
}

/* ===================== BLOCO 4: Desfazer Operações (Pilha)====================
 */

/* Inicializa a pilha */
/* A pilha funciona como uma pilha de pratos: você coloca um prato em cima e, se
 * quiser, remove o último que colocou. */
void inicializarPilha(Pilha *pilha) {
  pilha->topo = NULL; // Começa vazia, sem nenhum prato na pilha.
}

/* Empilha uma operação */
/* Quando você faz uma ação (como cadastrar um paciente), você coloca essa ação
 * no topo da pilha para lembrar o que foi feito. */
void empilharOperacao(Pilha *pilha, Registro *paciente, const char *operacao) {
  EPilha *novoNo =
      (EPilha *)malloc(sizeof(EPilha)); // Cria um novo lugar na pilha.
  if (novoNo == NULL) {
    printf("Erro de alocação de memória.\n");
    return; // Se não conseguir, para aqui.
  }
  novoNo->dados = (Registro *)malloc(
      sizeof(Registro)); // Reserva espaço para os dados do paciente.
  if (novoNo->dados == NULL) {
    printf("Erro de alocação de memória.\n");
    free(novoNo); // Libera o espaço reservado anteriormente.
    return;
  }
  memcpy(novoNo->dados, paciente,
         sizeof(Registro)); // Copia os dados do paciente para a pilha.
  strcpy(novoNo->operacao, operacao); // Guarda qual foi a operação feita.
  novoNo->proximo =
      pilha->topo; // O próximo da nova operação é o que estava no topo.
  pilha->topo = novoNo; // O novo nó passa a ser o topo da pilha.
}

/* Desfaz a última operação */
/* Remove o último prato colocado na pilha e desfaz o que foi feito nessa
 * operação. */
void desfazerOperacao(Pilha *pilha, Lista *lista, ABB *arvoreAno,
                      ABB *arvoreMes, ABB *arvoreDia, ABB *arvoreIdade) {
  if (pilha->topo ==
      NULL) { // Se a pilha estiver vazia, não tem o que desfazer.
    printf("Nenhuma operação para desfazer.\n");
    return;
  }
  EPilha *remover = pilha->topo; // Pega a última operação feita.
  pilha->topo =
      pilha->topo->proximo; // Atualiza o topo da pilha para o próximo.

  if (strcmp(remover->operacao, "CADASTRAR") ==
      0) { // Se a operação foi cadastrar.
    removerPaciente(
        lista, remover->dados->rg); // Remove o paciente que foi cadastrado.
    // Reconstruir as ABBs para refletir a remoção.
    inicializarABB(arvoreAno);
    inicializarABB(arvoreMes);
    inicializarABB(arvoreDia);
    inicializarABB(arvoreIdade);
    ELista *atual = lista->inicio;
    while (atual != NULL) { // Percorre toda a lista de pacientes.
      inserirPorAnoABB(arvoreAno,
                       atual->dados); // Insere na ABB ordenada por ano.
      inserirPorMesABB(arvoreMes,
                       atual->dados); // Insere na ABB ordenada por mês.
      inserirPorDiaABB(arvoreDia,
                       atual->dados); // Insere na ABB ordenada por dia.
      inserirPorIdadeABB(arvoreIdade,
                         atual->dados); // Insere na ABB ordenada por idade.
      atual = atual->proximo;           // Vai para o próximo paciente.
    }
  } else if (strcmp(remover->operacao, "REMOVER") ==
             0) { // Se a operação foi remover.
    /* Reinsere o paciente removido na lista */
    ELista *novoNo =
        (ELista *)malloc(sizeof(ELista)); // Cria um novo nó na lista.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      free(remover->dados); // Libera os dados reservados.
      free(remover);        // Libera o nó da pilha.
      return;
    }
    novoNo->dados = (Registro *)malloc(
        sizeof(Registro)); // Reserva espaço para os dados do paciente.
    if (novoNo->dados == NULL) {
      printf("Erro de alocação de memória.\n");
      free(novoNo);         // Libera o nó da lista.
      free(remover->dados); // Libera os dados.
      free(remover);        // Libera o nó da pilha.
      return;
    }
    memcpy(novoNo->dados, remover->dados,
           sizeof(Registro)); // Copia os dados do paciente para o novo nó.
    novoNo->proximo = lista->inicio; // Liga o novo nó ao início da lista.
    lista->inicio = novoNo; // Atualiza o início da lista para o novo nó.
    lista->quantidade++;    // Aumenta a contagem de pacientes na lista.
    // Reconstruir as ABBs para refletir a inserção.
    inicializarABB(arvoreAno);
    inicializarABB(arvoreMes);
    inicializarABB(arvoreDia);
    inicializarABB(arvoreIdade);
    ELista *atual = lista->inicio;
    while (atual != NULL) { // Percorre toda a lista de pacientes.
      inserirPorAnoABB(arvoreAno,
                       atual->dados); // Insere na ABB ordenada por ano.
      inserirPorMesABB(arvoreMes,
                       atual->dados); // Insere na ABB ordenada por mês.
      inserirPorDiaABB(arvoreDia,
                       atual->dados); // Insere na ABB ordenada por dia.
      inserirPorIdadeABB(arvoreIdade,
                         atual->dados); // Insere na ABB ordenada por idade.
      atual = atual->proximo;           // Vai para o próximo paciente.
    }
    printf("Paciente %s readicionado.\n",
           remover->dados->nome); // Informa que o paciente foi readicionado.
  } else if (strcmp(remover->operacao, "ATUALIZAR") ==
             0) { // Se a operação foi atualizar.
    /* Encontrar o paciente na lista pelo RG */
    ELista *paciente = lista->inicio;
    while (paciente != NULL) {
      if (strcmp(paciente->dados->rg, remover->dados->rg) == 0) {
        /* Restaurar os dados antigos do paciente */
        memcpy(paciente->dados, remover->dados, sizeof(Registro));
        printf("Atualização desfeita para o paciente %s.\n",
               paciente->dados->nome);
        break;
      }
      paciente = paciente->proximo;
    }
    /* Reconstruir as ABBs para refletir a atualização */
    inicializarABB(arvoreAno);
    inicializarABB(arvoreMes);
    inicializarABB(arvoreDia);
    inicializarABB(arvoreIdade);
    ELista *atualLista = lista->inicio;
    while (atualLista != NULL) { // Percorre toda a lista de pacientes.
      inserirPorAnoABB(arvoreAno,
                       atualLista->dados); // Insere na ABB ordenada por ano.
      inserirPorMesABB(arvoreMes,
                       atualLista->dados); // Insere na ABB ordenada por mês.
      inserirPorDiaABB(arvoreDia,
                       atualLista->dados); // Insere na ABB ordenada por dia.
      inserirPorIdadeABB(
          arvoreIdade, atualLista->dados); // Insere na ABB ordenada por idade.
      atualLista = atualLista->proximo;    // Vai para o próximo paciente.
    }
  }

  free(remover->dados); // Libera a memória dos dados do paciente.
  free(remover);        // Libera o nó da pilha.
}

/* ===================== BLOCO 5: Carregar e Salvar Dados =====================
 */

/* Carrega dados de pacientes a partir de um arquivo de texto */
/* Imagine que o arquivo é como um livro onde estão todas as informações dos
 * pacientes. */
void carregarDados(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, ABB *arvoreDia,
                   ABB *arvoreIdade) {
  FILE *arquivo = fopen("pacientes.txt", "r"); // Abre o arquivo para leitura.
  if (arquivo == NULL) {                       // Se não conseguir abrir.
    printf("Arquivo de dados não encontrado.\n");
    return;
  }

  // Reinicializar a lista e as ABBs para começar do zero.
  inicializarLista(lista); // Limpa a lista atual.
  inicializarABB(arvoreAno);
  inicializarABB(arvoreMes);
  inicializarABB(arvoreDia);
  inicializarABB(arvoreIdade);

  char linha[256]; // Espaço para cada linha do arquivo.
  while (fgets(linha, sizeof(linha), arquivo)) { // Lê cada linha do arquivo.
    Registro *paciente =
        (Registro *)malloc(sizeof(Registro)); // Cria um novo paciente.
    if (paciente == NULL) {
      printf("Erro de alocação de memória.\n");
      fclose(arquivo);
      return;
    }

    /* Preenche os dados do paciente a partir da linha lida */
    sscanf(linha, "%[^;];%d;%[^;];%d/%d/%d", paciente->nome, &paciente->idade,
           paciente->rg, &paciente->entrada.dia, &paciente->entrada.mes,
           &paciente->entrada.ano);

    ELista *novoNo =
        (ELista *)malloc(sizeof(ELista)); // Cria um novo elo na lista.
    if (novoNo == NULL) {
      printf("Erro de alocação de memória.\n");
      free(paciente);
      fclose(arquivo);
      return;
    }
    novoNo->dados = paciente;        // Liga os dados ao elo.
    novoNo->proximo = lista->inicio; // O próximo é o que já estava na lista.
    lista->inicio = novoNo; // Atualiza o início da lista para o novo elo.
    lista->quantidade++;    // Aumenta a contagem de pacientes.

    /* Insere o paciente nas ABBs de diferentes critérios */
    inserirPorAnoABB(arvoreAno, paciente);
    inserirPorMesABB(arvoreMes, paciente);
    inserirPorDiaABB(arvoreDia, paciente);
    inserirPorIdadeABB(arvoreIdade, paciente);
  }

  fclose(arquivo);                           // Fecha o arquivo.
  printf("Dados carregados com sucesso!\n"); // Informa que deu tudo certo.
}

/* Salva dados de pacientes em um arquivo de texto */
/* Imagine que salvar é como escrever no livro todas as informações atuais dos
 * pacientes. */
void salvarDados(Lista *lista) {
  FILE *arquivo = fopen("pacientes.txt", "w"); // Abre o arquivo para escrita.
  if (arquivo == NULL) {                       // Se não conseguir abrir.
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  ELista *atual = lista->inicio; // Começa no primeiro paciente.
  while (atual != NULL) {        // Percorre toda a lista.
    /* Escreve os dados do paciente no formato: nome;idade;rg;dia/mês/ano */
    fprintf(arquivo, "%s;%d;%s;%02d/%02d/%04d\n", atual->dados->nome,
            atual->dados->idade, atual->dados->rg, atual->dados->entrada.dia,
            atual->dados->entrada.mes, atual->dados->entrada.ano);
    atual = atual->proximo; // Vai para o próximo paciente.
  }

  fclose(arquivo);                       // Fecha o arquivo.
  printf("Dados salvos com sucesso!\n"); // Informa que deu tudo certo.
}

/* ===================== BLOCO 6: Função main ===================== */

/* Função para liberar a memória da lista */
/* Quando termina o programa, precisamos limpar tudo para não deixar bagunça
 * (vazamentos de memória). */
void liberarLista(Lista *lista) {
  ELista *atual = lista->inicio; // Começa no primeiro paciente.
  while (atual != NULL) {        // Percorre toda a lista.
    ELista *temp = atual;        // Guarda o paciente atual para liberar depois.
    atual = atual->proximo;      // Vai para o próximo paciente.
    free(temp->dados);           // Libera os dados do paciente.
    free(temp);                  // Libera o nó da lista.
  }
  lista->inicio = NULL;  // A lista fica vazia.
  lista->quantidade = 0; // Nenhum paciente na lista.
}

/* Função para liberar a fila */
void liberarFila(Fila *fila) {
  EFila *atual = fila->head; // Começa no primeiro da fila.
  while (atual != NULL) {    // Percorre toda a fila.
    EFila *temp = atual;     // Guarda o paciente atual para liberar depois.
    atual = atual->proximo;  // Vai para o próximo paciente.
    free(temp);              // Libera o nó da fila.
  }
  fila->head = fila->tail = NULL; // A fila fica vazia.
  fila->quantidade = 0;           // Nenhum paciente na fila.
}

/* Função recursiva para liberar ABB */
/* Libera todos os nós da árvore, começando pelas folhas e subindo até a raiz.
 */
void liberarABBRecursivo(EABB *raiz) {
  if (raiz != NULL) {                    // Se o nó não for vazio.
    liberarABBRecursivo(raiz->FilhoEsq); // Libera a sub-árvore esquerda.
    liberarABBRecursivo(raiz->FilhoDir); // Libera a sub-árvore direita.
    free(raiz);                          // Libera o nó atual.
  }
}

/* Função para liberar ABB */
void liberarABB(ABB *arvore) {
  liberarABBRecursivo(arvore->raiz); // Começa a liberar a partir da raiz.
  arvore->raiz = NULL;               // A árvore fica vazia.
  arvore->quantidade = 0;            // Nenhum paciente na árvore.
}

/* Função para liberar a pilha */
void liberarPilha(Pilha *pilha) {
  EPilha *atual = pilha->topo; // Começa no topo da pilha.
  while (atual != NULL) {      // Percorre toda a pilha.
    EPilha *temp = atual;      // Guarda a operação atual para liberar depois.
    atual = atual->proximo;    // Vai para a próxima operação.
    free(temp->dados);         // Libera os dados do paciente.
    free(temp);                // Libera o nó da pilha.
  }
  pilha->topo = NULL; // A pilha fica vazia.
}

/* Função principal do programa */
int main() {
  Lista lista; // Cria a lista de pacientes.
  Fila fila;   // Cria a fila de atendimento.
  ABB arvoreAno, arvoreMes, arvoreDia,
      arvoreIdade; // Cria as árvores para ordenação.
  Pilha pilha;     // Cria a pilha para desfazer operações.

  /* Inicializa todas as estruturas */
  inicializarLista(&lista);
  inicializarFila(&fila);
  inicializarABB(&arvoreAno);
  inicializarABB(&arvoreMes);
  inicializarABB(&arvoreDia);
  inicializarABB(&arvoreIdade);
  inicializarPilha(&pilha);

  int opcao; // Variável para armazenar a escolha do usuário.
  do {
    /* Exibe o menu principal */
    printf("\n========== Menu Principal ==========\n");
    printf("1. Cadastro de Pacientes\n");
    printf("2. Ordem de Atendimento\n");
    printf("3. Pesquisa e Ordenação\n");
    printf("4. Carregar/Salvar Dados\n");
    printf("5. Desfazer Operação\n");
    printf("6. Sobre\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao); // Lê a opção escolhida.
    limparBuffer();      // Limpa o buffer.

    switch (opcao) {
    case 1: { // Cadastro de Pacientes
      int opcaoCadastro;
      do {
        /* Exibe o submenu de cadastro */
        printf("\n--- Menu Cadastro ---\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Consultar Paciente\n");
        printf("3. Atualizar Paciente\n");
        printf("4. Remover Paciente\n");
        printf("5. Exibir Todos os Pacientes\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoCadastro); // Lê a opção do submenu.
        limparBuffer();              // Limpa o buffer.

        char rg[10]; // Variável para armazenar o RG digitado.

        switch (opcaoCadastro) {
        case 1:                      // Cadastrar Paciente
          cadastrarPaciente(&lista); // Chama a função para cadastrar.
          /* Se a lista não estiver vazia após o cadastro, empilha a operação */
          if (lista.inicio != NULL) {
            empilharOperacao(&pilha, lista.inicio->dados, "CADASTRAR");
            /* Insere o paciente nas árvores para ordenação */
            inserirPorAnoABB(&arvoreAno, lista.inicio->dados);
            inserirPorMesABB(&arvoreMes, lista.inicio->dados);
            inserirPorDiaABB(&arvoreDia, lista.inicio->dados);
            inserirPorIdadeABB(&arvoreIdade, lista.inicio->dados);
          }
          break;
        case 2: // Consultar Paciente
          printf("Digite o RG do paciente: ");
          fgets(rg, 10, stdin);          // Pede o RG.
          rg[strcspn(rg, "\n")] = '\0';  // Remove o '\n'.
          consultarPaciente(&lista, rg); // Chama a função para consultar.
          break;
        case 3: { // Atualizar Paciente
          printf("Digite o RG do paciente: ");
          fgets(rg, 10, stdin);         // Pede o RG.
          rg[strcspn(rg, "\n")] = '\0'; // Remove o '\n'.
          /* Antes de atualizar, empilha o estado atual do paciente */
          ELista *pacienteAtualizar = lista.inicio;
          while (pacienteAtualizar != NULL) {
            if (strcmp(pacienteAtualizar->dados->rg, rg) == 0) {
              empilharOperacao(&pilha, pacienteAtualizar->dados, "ATUALIZAR");
              break;
            }
            pacienteAtualizar = pacienteAtualizar->proximo;
          }
          atualizarPaciente(&lista, rg); // Chama a função para atualizar.
          /* Reconstrói as ABBs para refletir a atualização */
          inicializarABB(&arvoreAno);
          inicializarABB(&arvoreMes);
          inicializarABB(&arvoreDia);
          inicializarABB(&arvoreIdade);
          ELista *atualLista = lista.inicio;
          while (atualLista != NULL) { // Percorre a lista.
            inserirPorAnoABB(&arvoreAno,
                             atualLista->dados); // Insere na ABB por ano.
            inserirPorMesABB(&arvoreMes,
                             atualLista->dados); // Insere na ABB por mês.
            inserirPorDiaABB(&arvoreDia,
                             atualLista->dados); // Insere na ABB por dia.
            inserirPorIdadeABB(&arvoreIdade,
                               atualLista->dados); // Insere na ABB por idade.
            atualLista = atualLista->proximo; // Vai para o próximo paciente.
          }
          break;
        }
        case 4: { // Remover Paciente
          printf("Digite o RG do paciente: ");
          fgets(rg, 10, stdin);         // Pede o RG.
          rg[strcspn(rg, "\n")] = '\0'; // Remove o '\n'.
          /* Antes de remover, empilha a operação para possível desfazer */
          ELista *pacienteRemover = lista.inicio;
          while (pacienteRemover != NULL) {
            if (strcmp(pacienteRemover->dados->rg, rg) == 0) {
              empilharOperacao(&pilha, pacienteRemover->dados, "REMOVER");
              break;
            }
            pacienteRemover = pacienteRemover->proximo;
          }
          removerPaciente(&lista, rg); // Chama a função para remover.
          /* Reconstrói as ABBs para refletir a remoção */
          inicializarABB(&arvoreAno);
          inicializarABB(&arvoreMes);
          inicializarABB(&arvoreDia);
          inicializarABB(&arvoreIdade);
          ELista *atualRemover = lista.inicio;
          while (atualRemover != NULL) { // Percorre a lista.
            inserirPorAnoABB(&arvoreAno,
                             atualRemover->dados); // Insere na ABB por ano.
            inserirPorMesABB(&arvoreMes,
                             atualRemover->dados); // Insere na ABB por mês.
            inserirPorDiaABB(&arvoreDia,
                             atualRemover->dados); // Insere na ABB por dia.
            inserirPorIdadeABB(&arvoreIdade,
                               atualRemover->dados); // Insere na ABB por idade.
            atualRemover =
                atualRemover->proximo; // Vai para o próximo paciente.
          }
          break;
        }
        case 5:                    // Exibir Todos os Pacientes
          exibirPacientes(&lista); // Chama a função para exibir.
          break;
        case 0: // Voltar ao Menu Principal
          printf("Voltando ao menu principal...\n");
          break;
        default: // Opção Inválida
          printf("Opção inválida. Tente novamente.\n");
          break;
        }
      } while (opcaoCadastro != 0); // Continua no submenu até escolher voltar.
      break;
    }
    case 2: { // Ordem de Atendimento
      int opcaoFila;
      do {
        /* Exibe o submenu de ordem de atendimento */
        printf("\n--- Menu Ordem de Atendimento ---\n");
        printf("1. Enfileirar Paciente\n");
        printf("2. Atender Paciente\n");
        printf("3. Exibir Fila de Atendimento\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoFila); // Lê a opção do submenu.
        limparBuffer();          // Limpa o buffer.

        switch (opcaoFila) {
        case 1: {      // Enfileirar Paciente
          char rg[10]; // Variável para armazenar o RG digitado.
          printf("Digite o RG do paciente: ");
          fgets(rg, 10, stdin);         // Pede o RG.
          rg[strcspn(rg, "\n")] = '\0'; // Remove o '\n'.
          ELista *atual = lista.inicio; // Começa no primeiro paciente.
          while (atual != NULL) {       // Percorre a lista.
            if (strcmp(atual->dados->rg, rg) == 0) {   // Se encontrar o RG.
              enfileirarPaciente(&fila, atual->dados); // Enfileira o paciente.
              break;                                   // Sai do loop.
            }
            atual = atual->proximo; // Vai para o próximo paciente.
          }
          if (atual == NULL) { // Se não encontrar o paciente.
            printf("Paciente não encontrado.\n");
          }
          break;
        }
        case 2:                         // Atender Paciente
          desenfileirarPaciente(&fila); // Chama a função para atender.
          break;
        case 3:              // Exibir Fila de Atendimento
          exibirFila(&fila); // Chama a função para exibir.
          break;
        case 0: // Voltar ao Menu Principal
          printf("Voltando ao menu principal...\n");
          break;
        default: // Opção Inválida
          printf("Opção inválida. Tente novamente.\n");
          break;
        }
      } while (opcaoFila != 0); // Continua no submenu até escolher voltar.
      break;
    }
    case 3: { // Pesquisa e Ordenação
      int criterio;
      do {
        /* Exibe o submenu de pesquisa e ordenação */
        printf("\n--- Pesquisa e Ordenação ---\n");
        printf("Ordenar por:\n");
        printf("1. Ano de Entrada\n");
        printf("2. Mês de Entrada\n");
        printf("3. Dia de Entrada\n");
        printf("4. Idade\n");
        printf("0. Voltar\n");
        printf("Escolha um critério: ");
        scanf("%d", &criterio); // Lê o critério escolhido.
        limparBuffer();         // Limpa o buffer.

        switch (criterio) {
        case 1: // Ordenar por Ano de Entrada
          printf("Pacientes ordenados por Ano de Entrada:\n");
          exibirABBInOrdem(arvoreAno.raiz); // Exibe a ABB ordenada por ano.
          break;
        case 2: // Ordenar por Mês de Entrada
          printf("Pacientes ordenados por Mês de Entrada:\n");
          exibirABBInOrdem(arvoreMes.raiz); // Exibe a ABB ordenada por mês.
          break;
        case 3: // Ordenar por Dia de Entrada
          printf("Pacientes ordenados por Dia de Entrada:\n");
          exibirABBInOrdem(arvoreDia.raiz); // Exibe a ABB ordenada por dia.
          break;
        case 4: // Ordenar por Idade
          printf("Pacientes ordenados por Idade:\n");
          exibirABBInOrdem(arvoreIdade.raiz); // Exibe a ABB ordenada por idade.
          break;
        case 0: // Voltar ao Menu Principal
          printf("Voltando ao menu principal...\n");
          break;
        default: // Opção Inválida
          printf("Opção inválida. Tente novamente.\n");
          break;
        }
      } while (criterio != 0); // Continua no submenu até escolher voltar.
      break;
    }
    case 4: { // Carregar/Salvar Dados
      int opcaoArquivo;
      do {
        /* Exibe o submenu de carregar/salvar dados */
        printf("\n--- Carregar/Salvar Dados ---\n");
        printf("1. Carregar Dados\n");
        printf("2. Salvar Dados\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoArquivo); // Lê a opção do submenu.
        limparBuffer();             // Limpa o buffer.

        switch (opcaoArquivo) {
        case 1: // Carregar Dados
          carregarDados(&lista, &arvoreAno, &arvoreMes, &arvoreDia,
                        &arvoreIdade); // Chama a função para carregar.
          break;
        case 2:                // Salvar Dados
          salvarDados(&lista); // Chama a função para salvar.
          break;
        case 0: // Voltar ao Menu Principal
          printf("Voltando ao menu principal...\n");
          break;
        default: // Opção Inválida
          printf("Opção inválida. Tente novamente.\n");
          break;
        }
      } while (opcaoArquivo != 0); // Continua no submenu até escolher voltar.
      break;
    }
    case 5: // Desfazer Operação
      desfazerOperacao(&pilha, &lista, &arvoreAno, &arvoreMes, &arvoreDia,
                       &arvoreIdade); // Chama a função para desfazer.
      break;
    case 6:    // Sobre o Programa
      sobre(); // Chama a função que exibe informações sobre o programa.
      break;
    case 0: // Sair do Programa
      printf("Encerrando o programa...\n");
      break;
    default: // Opção Inválida
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  } while (opcao != 0); // Continua exibindo o menu até escolher sair.

  /* Liberar a memória antes de encerrar */
  liberarLista(&lista);     // Libera a lista de pacientes.
  liberarFila(&fila);       // Libera a fila de atendimento.
  liberarABB(&arvoreAno);   // Libera a árvore ordenada por ano.
  liberarABB(&arvoreMes);   // Libera a árvore ordenada por mês.
  liberarABB(&arvoreDia);   // Libera a árvore ordenada por dia.
  liberarABB(&arvoreIdade); // Libera a árvore ordenada por idade.
  liberarPilha(&pilha);     // Libera a pilha de operações.

  return 0; // Termina o programa.
}
