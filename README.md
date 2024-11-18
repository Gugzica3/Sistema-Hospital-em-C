# 🏥 Sistema de Hospital em C

> Um sistema simples para gerenciamento de pacientes em um hospital, utilizando estruturas de dados em C.

<p align="center">
  <img src="https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow" alt="Status">
  <img src="https://img.shields.io/badge/Linguagem-C-%23007ACC" alt="Linguagem">
  <img src="https://img.shields.io/github/license/usuario/projeto" alt="Licença">
</p>

## 🚀 Sobre o Projeto

Este projeto é um sistema de gerenciamento de hospital desenvolvido em C, como parte de um trabalho acadêmico na disciplina de Estrutura de Dados. O sistema permite o cadastro, consulta, atualização e remoção de pacientes, além de gerenciar a ordem de atendimento e realizar buscas utilizando uma Árvore Binária de Busca (ABB).

### 📝 Funcionalidades

- 📝 **Cadastro de Pacientes** - Cadastre novos pacientes na lista.
- 🔍 **Consulta de Pacientes** - Consulte os dados de um paciente pelo RG.
- ✏️ **Atualização de Dados** - Atualize as informações de um paciente já cadastrado.
- ❌ **Remoção de Pacientes** - Remova pacientes da lista.
- 🚑 **Gerenciamento da Fila de Atendimento** - Organize a ordem de atendimento dos pacientes.
- 🌳 **Pesquisa e Ordenação com ABB** - Ordene pacientes por diferentes critérios, como data de entrada ou idade.
- 🔄 **Desfazer Operações** - Utilize a pilha para desfazer ações como cadastro, remoção ou atualização de pacientes.

## 🌟 Momentos Importantes do Código

Aqui estão algumas partes do código que são fundamentais para o funcionamento do sistema e que merecem destaque:

1. **Cadastro de Pacientes na Lista**
   ```c
   void cadastrarPaciente(Lista *lista) {
       // Código responsável por cadastrar um novo paciente
       // Alocação de memória, coleta de dados e inserção na lista
   }
   ```

2. **Gerenciamento da Fila de Atendimento**
   ```c
   void enfileirarPaciente(Fila *fila, Registro *paciente) {
       // Código responsável por adicionar um paciente à fila de atendimento
       // Implementa a lógica FIFO (First In, First Out)
   }
   ```

3. **Desfazer Operações com Pilha**
   ```c
   void desfazerOperacao(Pilha *pilha, Lista *lista, ABB *arvoreAno, ABB *arvoreMes, ABB *arvoreDia, ABB *arvoreIdade) {
       // Código responsável por desfazer a última operação realizada
       // Utiliza uma pilha para gerenciar as operações que podem ser desfeitas
   }
   ```

4. **Ordenação com Árvore Binária de Busca (ABB)**
   ```c
   EABB *inserirPorAno(EABB *raiz, Registro *paciente) {
       // Código responsável por inserir um paciente na ABB ordenado pelo ano de entrada
       // Garante a eficiência nas buscas e ordenações
   }
   ```

## 🌈 Demonstração

<p align="center">
  
  ![image](https://github.com/user-attachments/assets/84d657c6-a12a-4c0a-bd97-9049321c106c)

  ![image](https://github.com/user-attachments/assets/30d7e427-e9f5-4cb4-9bc7-1c69064104de)

  ![image](https://github.com/user-attachments/assets/3ac4acd2-7280-445c-95e9-aed1a0175d20)

  ![image](https://github.com/user-attachments/assets/f2ea9789-b6f2-4d53-9341-5acd8ed0efeb)

  
</p>

## 🛠️ Tecnologias Utilizadas

- 💻 **Linguagem:** C
- 📚 **Estruturas de Dados:** Lista Encadeada, Fila, Pilha, Árvore Binária de Busca (ABB)

## 📦 Como Compilar e Executar o Projeto

Clone o repositório e siga os seguintes passos:

```bash
# Clone este repositório
git clone https://github.com/usuario/nome-do-projeto.git

# Acesse a pasta do projeto
cd nome-do-projeto

# Compile o código
gcc -o sistema_hospital sistema_hospital.c

# Execute a aplicação
./sistema_hospital
```

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.


---

<p align="center">Feito com 💖 por Gustavo Bertoluzzi e Isabella Rosseto </p>

