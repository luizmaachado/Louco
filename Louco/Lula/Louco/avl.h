struct bancodedados {
	
	char projeto[40];
	char classe[20];
	char email[40];
	char telefone[15];
	char ferramentas[100];
	char descricao[1000];
	char keyword[20];
	int finalizado;

	int altura;
	int tamanho;
	
	struct bancodedados* esquerda;
	struct bancodedados* direita;

};

typedef struct bancodedados* BD;


//LIB FUNCTIONS:


// cria a árvore
BD createTree(void); 

// monta a árvore a partir do arquivo binário
BD montar_struct(BD root);

//adiciona um novo projeto na árvore
BD novoProjeto(BD root,char* projeto,char* email,char* telefone,int finalizado,char* ferramentas,char* descricao,char* classe,char* keyword);

//printa todas as informações do arquivo passado como parametro
BD buscarProjeto(BD root,char* projeto);

//printa todos projetos
void listarprojetos(BD root);

// faz o backup da árvore no arquivo
void escrever(BD root);


//AUX AVL FUNCTIONS

// Funções relacionadas à árvore AVL

//cria um novo node na árvore
BD criaprojeto(char* projeto,char* email,char* telefone,int finalizado,char* ferramentas,char* descricao,char* classe,char* keyword);

//Percorre a árvore até achar a posição correta para adicionar os novos valores
BD addprojeto(BD root,char* projeto,char* email,char* telefone,int finalizado,char* ferramentas,char* descricao,char* classe,char* keyword);

//Verifica se já existe um projeto cadastrado com o mesmo nome
int verifierProjeto(BD root,char* projeto);

//Printa todos os valores referentes ao node passado como argumento
void printaprojeto(BD root);

// Funções que fazem a rotação da árvore AVL
BD SRotLeft(BD root);
BD SRotRight(BD root);
BD DRotLeft(BD root);
BD DRotRight(BD root);

//Retorna a altura do node
int getaltura(BD node);

//Retorna o tamanho do node
int gettamanho(BD node);

//retorna a maior altura entre as duas comparadas
int max(int altura1,int altura2);

//Faz o update da altura do node após a rotação
void updateAltura(BD node);

//Faz o uptade do tamanho do node após a rotação
void updatetamanho(BD node);


//AUX FILE FUNCTIONS

//Aloca espaço na memória e copia um node de um arquivo para a árvore
BD recriarNo(BD noAntigo);

//Escreve a árvore AVL em um arquivo binário
void escreve(BD root);


//STR functions

int compararStrings(char* string1,char* string2);

//<><><><><><><>   [LIST]   <><><><><><><>//

struct list {

	struct bancodedados* index;
	struct list* next;

};

typedef struct list *NODE;


//Seta uma variável para Nulo
NODE createList(void);

//Adiciona um node à lista linkada
NODE addList(NODE head,BD projeto);

//Cria uma lista linkada a partir de uma árvore AVL
NODE makelist(BD root,NODE head);

//Passa para o próximo valor da lista
NODE next(NODE head);

//Printa em ordem alfabética todos os projetos na lista 
void printl(NODE head);