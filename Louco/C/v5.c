#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//<><><><><><><><><>   [TREE]   <><><><><><><><><>//

struct bancodedados {
	
	char projeto[30];
	char email[30];
	int telefone;
	int finalizado;

	int altura;
	int tamanho;
	
	struct bancodedados* esquerda;
	struct bancodedados* direita;

};

typedef struct bancodedados* BD;


//<><><><><><><><><>   [HEAD]   <><><><><><><><><><><>//

//System Functions

BD montar_struct(BD root);

int escolheAcao(void);

BD cadastraProjeto(BD root,char* projeto,char* email,int telefone,int finalizado);
void buscarProjeto(BD root);
void listarProjeto(BD root);
void escrever(BD root);

//BD functions

BD criaprojeto(char* projeto,char* email,int telefone,int finalizado);
BD addprojeto(BD root,char* projeto,char* email,int telefone,int finalizado);
BD findproject(BD root,char* projeto);
void printaprojeto(BD root);
void printatodosprojetos(BD root);

//Rotation functions

BD SRotLeft(BD root);
BD SRotRight(BD root);
BD DRotLeft(BD root);
BD DRotRight(BD root);

int getaltura(BD node);
int gettamanho(BD node);
int max(int altura1,int altura2);

void updateAltura(BD node);
void updatetamanho(BD node);

//STR functions

int isstrbigger(char* novoprojeto,char* projeto);
int isequal(char* procurado,char* projeto);

BD recriarNo(BD noAntigo);

void escreve(BD root);

void gotoxy(int x,int y);

//<><><><><><><><><>   [GLOBAL]   <><><><><><><><><>//

FILE *fp; //ponteiro para o arquivo

//<><><><><><><><><>   [MAIN]   <><><><><><><><><>//

int main() {

	BD root = NULL;

	char projeto[30];
	char email[30];
	int telefone;
	int finalizado;

	int ligado = 1;
	int escolha;

	root = montar_struct(root);

	system("clear");

	while (ligado) {

		escolha = escolheAcao();

		if(escolha == 1) root = cadastraProjeto(root,projeto,email,telefone,finalizado);

		if(escolha == 2) buscarProjeto(root);

		if(escolha == 3) listarProjeto(root);

		if(escolha == 4) escrever(root);

		printf("\nProcesso executado com sucesso!\n\n");
	}
	return 0;
}


//<><><><><><><><><>  [BD FUNCTIONS]  <><><><><><><><>//

BD criaprojeto(char* projeto,char* email,int telefone,int finalizado) {

	//cria uma subroot;

	BD newprojeto;
	newprojeto = malloc(sizeof(struct bancodedados));
	newprojeto->esquerda = NULL;
	newprojeto->direita = NULL;
	strcpy(newprojeto->projeto,projeto);
	strcpy(newprojeto->email,email);
	newprojeto->telefone = telefone;
	newprojeto->finalizado = finalizado;
	newprojeto->altura = 1;
	newprojeto->tamanho = 1;

	return newprojeto;
}

BD addprojeto(BD root,char* projeto,char* email,int telefone,int finalizado) {

	//Encontra a posição correta para a folha e anexa;

	if (root == NULL) root = criaprojeto(projeto,email,telefone,finalizado);
	
	else {

		root->tamanho++; //vai dando update no tamanho de cada node.

		if(isstrbigger(projeto,root->projeto)) {
		root->direita = addprojeto(root->direita,
		projeto,email,telefone,finalizado);

			if(getaltura(root->direita) - getaltura(root->esquerda) == 2) {
				if (isstrbigger(projeto,root->direita->projeto)) root = SRotLeft(root);
				else root = DRotLeft(root);
			}
		}

		else {
			
			root->esquerda = addprojeto(root->esquerda,
				projeto,email,telefone,finalizado);

			if (getaltura(root->esquerda) - getaltura(root->direita) == 2) {
				
				if (isstrbigger(root->esquerda->projeto,projeto))  root = SRotRight(root);
				else root = DRotRight(root);
			}
		}
	}
	updateAltura(root);
	return root;
}


//<><><><><><><>   [ROTATION FUNCTIONS]   <><><><><><><><>//


BD SRotLeft(BD root) {

	BD aux = malloc(sizeof(struct bancodedados));
	aux = root->direita;
	root->direita = aux->esquerda;
	aux->esquerda = root;
	
	updateAltura(root->esquerda);
	updateAltura(root);
	updatetamanho(aux->esquerda);
	updatetamanho(aux);

	return aux;
}


BD SRotRight(BD root) {
	
	BD aux = malloc(sizeof(struct bancodedados));
	aux = root->esquerda;
	root->esquerda = aux->direita;
	aux->direita = root;
	
	updateAltura(root->direita);
	updateAltura(root);
	updatetamanho(aux->direita);
	updatetamanho(aux);

	return aux;
}


BD DRotLeft(BD root) {

	BD rotation = malloc(sizeof(struct bancodedados));
	root->direita = SRotRight(root->direita);
	rotation = SRotLeft(root);
	return rotation;
}


BD DRotRight(BD root) {

	BD rotation = malloc(sizeof(struct bancodedados));
	root->esquerda = SRotLeft(root->esquerda);
	rotation = SRotRight(root);
	return rotation;
}


//=====================   [Altura functions]   ===============//


int getaltura(BD node) {

	if (node == NULL) return 0;
	else return node->altura;
}


void updateAltura(BD node) {

	int altura_direita;
	int altura_esquerda;

	if (node != NULL) {
		altura_direita = getaltura(node->direita);
		altura_esquerda = getaltura(node->esquerda);
		node->altura = max(altura_direita,altura_esquerda) + 1;
	}
}


int max(int altura1,int altura2) {

	if(altura1 > altura2) return altura1;
	else return altura2;
}


//=============   [SIZE FUNCTIONS]   ==================//

int gettamanho(BD node) {

	if (node == NULL) return 0;
	else return node->tamanho;
}


void updatetamanho(BD node) {

	int tamanho_direita;
	int tamanho_esquerda;

	if (node != NULL) {
		tamanho_direita = gettamanho(node->direita);
		tamanho_esquerda = gettamanho(node->esquerda);
		node->tamanho = tamanho_direita + tamanho_esquerda + 1;
	}
}

//<><><><><><><><>  [UX FUNCTIONS]  <><><><><><><><><>//

BD findproject(BD root,char* projeto) {

	//encontra o projeto pelo seu nome;

	if(isequal(projeto,root->projeto)) {
		printaprojeto(root);
	}

	else {

		if(isstrbigger(projeto,root->projeto)) {
		root->direita = findproject(root->direita,
		projeto);
	}
		else 
			root->esquerda = findproject(root->esquerda,
				projeto);
	}
	return root;
}


void printaprojeto(BD root) {

	//printa todas as informações do projeto;

	printf("Projeto: %s\n",root->projeto);
	printf("E-mail: %s\n",root->email);
	printf("Telefone: %d\n",root->telefone);
	if(root->finalizado) printf("Status: finalizado\n");
	else printf("Status: em andamento\n");
}


void printatodosprojetos(BD root) {
	
	//printa todos os nomes de projetos em ordem alfabetica;

	if(root != NULL) {
		printatodosprojetos(root->esquerda);
		printf("%s\n",root->projeto);
		printatodosprojetos(root->direita);
	}
}


//<><><><><><><><>   [STR FUNCTION]   <><><><><><><><>//

int isstrbigger(char* novoprojeto,char* projeto) {

	//Compara duas strings para verificar qual é a maior;
	//0 novoprojeto é menor e 1 é maior;

	int i = 0;
	while(novoprojeto[i] != '\0' && projeto[i] != '\0') {
		if(novoprojeto[i] < projeto[i]) return 0;
		if(novoprojeto[i] > projeto[i]) return 1;
		i++;
	}
	if(novoprojeto[i] == '\0') return 0;
	if(novoprojeto[i] != '\0') return 1;
}

int isequal(char* procurado,char* projeto) {

	//compara se as strings são iguais;
	//0 não é igual 1 é igual;

	int i = 0;
	while(procurado[i] != '\0' && projeto[i] != '\0') {
		if(procurado[i] != projeto[i]) return 0;
		i++;
	}
	return 1;
}


//<><><><><><><>   [FILES]   <><><><><><><><>

BD recriarNo(BD make){

	//Cria uma nova struct a partir do arquivo

	BD noNovo = malloc(sizeof(struct bancodedados));
	*noNovo = *make;
	return noNovo;
}

void escreve(BD root) {

	//Escreve em um arquivo as estruturas 

	if(root != NULL) {
		fwrite(root,sizeof(struct bancodedados),1,fp);
		escreve(root->esquerda);
		escreve(root->direita);
	}
}


//<><><><><><><><><>   [System Op]   <><><><><><><><>//

int escolheAcao(void) {

	//Printa menu de opções e retorna a ação desejada
	
	int escolha;

	printf("Selecione uma ação:\n\n");
	printf("1 - Novo Projeto\n");
	printf("2 - Buscar Projeto\n");
	printf("3 - Listar Projetos\n");
	printf("4 - Backup\n\n");

	scanf("%d",&escolha);
	system("clear");
	return escolha;
}

BD cadastraProjeto(BD root,char* projeto,char* email,int telefone,int finalizado) {

	// Cadastra um novo projeto

	printf("Qual o nome do projeto?\n");
	scanf("%s",projeto);
	printf("Informe um e-mail para contato:\n");
	scanf("%s",email);
	printf("Informe um telefone para contato:\n");
	scanf("%d",&telefone);
	printf("O projeto está finalizado?\n");
	scanf("%d",&finalizado);
	system("clear");
	root = addprojeto(root,projeto,email,telefone,finalizado);
	return root;
}

void buscarProjeto(BD root) {

	//Busca um projeto pelo nome

	char projeto[30];

	printf("Qual projeto você gostaria de visualizar?\n");
	scanf("%s",&projeto);
	findproject(root,projeto);
}

void listarProjeto(BD root) {

	//Lista em ordem alfabética os projetos

	printf("Segue a lista de projetos realizados no L.O.U.Co:\n");
	printatodosprojetos(root);
}


void escrever(BD root) {

	//Escreve em um arquivo binário os projetos

	fp = fopen("teste.txt","wb");
	if(fp==NULL) {
		printf("Error\n");
		exit(1);
	}
	else {
		fp = fopen("teste.txt","wb");
		rewind(fp);
		escreve(root);
		pclose(fp);
	}
}

BD montar_struct(BD root) {

	//Lê do arquivo e recria a árvore

	struct bancodedados make;
	BD aux;

	fp = fopen("teste.txt","rb");
	while(fread(&make,sizeof(struct bancodedados),1,fp)) {
		aux = recriarNo(&make);
		root = addprojeto(root,aux->projeto,aux->email,aux->telefone,aux->finalizado);
	}
	rewind(fp);
	fclose(fp);

	return root;
}


void gotoxy(int x,int y) {
	printf("%c[%d;%df",0x1B,y,x);
}
