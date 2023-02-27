//SOFTWARE DE GERENCIAMENTO DE ESCRITÓRIO PARA ADVOCACIA

//Inclusão das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h> //clrscr
#include <locale.h>

//Definer o buffer como 64
#define BUFFER 64

// Estrutura da array declarada para armazenar nossos dados.
typedef struct lista {
	char *nome;
	int RG;
	int datan;	
	int CEP;
	int processo;
	struct lista *proximo;
}
Dados;

// Protótipo das funções de manuseio dos dados.
Dados *inicia_dados (char *nome, int RG, int datan, int CEP, int processo);
Dados *insere_dados (Dados *dados, char *nome, int RG, int datan, int CEP, int processo);
void exibe_dados (Dados *dados);
void busca_dados (Dados *dados, char *chave);
Dados *deleta_dados (Dados *dados);
int checa_vazio (Dados *dados);

// Protótipo das funções do menu.
void insere(void);
void exibe(void);
void busca(void);
void deleta(void);

// Inicializa a estrutura de dados principal.
Dados *principal = NULL;

// Cria a array apontando o próximo no para NULL.
Dados *inicia_dados (char *nome, int RG, int datan, int CEP, int processo) {
	Dados *novo;
	novo = (Dados *) malloc (sizeof (Dados));
 	novo->nome = (char *) malloc(strlen(nome)+1);
 	strncpy(novo->nome, nome, strlen(nome)+1);
 	novo->RG = RG;
 	novo->datan = datan;
 	novo->CEP = CEP;
 	novo->processo = processo;
 	novo->proximo = NULL;
 	return novo;
}
// Como a array não está mais vazia, apontamos o próximo no para array.
Dados *insere_dados (Dados *dados, char *nome, int RG, int datan, int CEP, int processo) {
 	Dados *novo;
 	novo = (Dados *) malloc (sizeof (Dados));
 	novo->nome = (char *) malloc(strlen(nome)+1);
 	strncpy(novo->nome, nome, strlen(nome)+1);
 	novo->RG = RG;
 	novo->datan = datan;
 	novo->CEP = CEP;
 	novo->processo = processo;
 	novo->proximo = dados;
 	return novo;
}

// Percorre todos os campos da array e imprime até o ponteiro próximo chegar em NULL.
void exibe_dados (Dados *dados) {
	system("cls");
	fprintf (stdout, "Cadastro:\n\n");
	fprintf (stdout, "------------------------\n");
	for (; dados != NULL; dados = dados->proximo) {
 	fprintf (stdout, "Nome: %s\n", dados->nome);
 	fprintf (stdout, "RG: %d\n", dados->RG);
 	fprintf (stdout, "Data de Nascimento: %d\n", dados->datan);
 	fprintf (stdout, "CEP: %d\n", dados->CEP);
 	fprintf (stdout, "Numero do processo: %d\n", dados->processo);
 	fprintf (stdout, "------------------------\n ");
 }
 	printf ("Pressione uma tecla para continuar.");
 	getch ();
}

// Percorre cada array comparando o nome com a chave.
void busca_dados (Dados *dados, char *chave) {
 	int achou = 0;
 	fprintf (stdout, "Cadastro:\n\n");
 	for (; dados != NULL; dados = dados->proximo) {
 		if (strcmp (chave, dados->nome) == 0) {
 			system("cls");
 			fprintf (stdout, "------------------------\n");
 			fprintf (stdout, "Nome: %s\n", dados->nome);
 			fprintf (stdout, "RG: %d\n", dados->RG);
 			fprintf (stdout, "Data de nascimento: %d\n",dados->datan);
 			fprintf (stdout, "CEP: %d\n", dados->CEP);
 			fprintf (stdout, "Numero do Processo: %d\n", dados->processo);
 			fprintf (stdout, "------------------------\n");
 			achou++;
 		}
	}
	if (achou == 0)
 		fprintf (stdout, "Nenhum resultado encontrado.\nPressione uma tecla para continuar.\n");
	else
		fprintf (stdout, "Foram encontrados %d registros.\nPressione uma tecla para continuar.\n", achou);
 		sleep (1);
 		getch ();
}

// Deleta o último registro inserido.
Dados *deleta_dados (Dados *dados) {
 	Dados *novo;
 	novo = dados->proximo;
 	free(dados->nome);
 	free(dados);
 	system("cls");
 	fprintf (stdout, "O ultimo registro foi deletado com sucesso.\n");
 	sleep (1);
 	return novo;
}

// apenas verifica se a array tem valores armazenados ou não.
int checa_vazio (Dados *dados) {
 	if (dados == NULL) {
 		system("cls");
 		fprintf (stdout, "Lista vazia! \n");
 		sleep (1);
 		return 1;
 	} else
 	return 0;
}

// Obtém os dados necessários para chamar as funções de manuseio de dados.
void insere(void) {
 	char *nome;
 	int RG;
 	int datan;
 	int CEP;
 	int processo;
 	nome = (char *) malloc (BUFFER);
 	system("cls");
 	fprintf (stdout, "\n\nDigite o primeiro nome do cliente: \n----> ");
 	scanf ("%s", nome);
 	fprintf (stdout, "\n");
 	fprintf (stdout, "(apenas numeros) \nDigite a RG: \n---->");
 	scanf ("%d", &RG);
 	fprintf (stdout, "\n");
 	fprintf (stdout, "(apenas numeros) \nDigite a data de nascimento: \n----> ");
 	scanf ("%d", &datan);
 	fprintf (stdout, "\n");
 	fprintf (stdout, "(apenas numeros) \nDigite o CEP: \n---->");
 	scanf ("%d", &CEP);
 	fprintf (stdout, "(apenas numeros) \nDigite o numero do processo: \n---->");
 	scanf ("%d", &processo);
 	fprintf (stdout, "\n");
 	if (principal == NULL)
 	principal = inicia_dados (nome, RG, datan, CEP, processo);
 	else
 	principal = insere_dados (principal, nome, RG, datan, CEP, processo);
}

// Verifica se a array tem valores armazenados e chama a void exibe_dados
void exibe(void) {
 	if (! checa_vazio(principal))
 	exibe_dados(principal);
}

// Verifica se a array tem valores armazenados, pede um nome para buscar e chama a void busca_dados
void busca(void) {
 	char *chave;
 	if (! checa_vazio(principal)) {
 		system("cls");
 		chave = (char *) malloc (BUFFER);
 		fprintf (stdout, "Digite o nome para buscar: \n -->");
 		scanf ("%s", chave);
 		busca_dados (principal, chave);
 		getch ();
 	}
}

// Mostra as informações do sistema
void info (void) {
 	system("cls");
 	printf ("Sistema de cadastro de clientes na linguagem C.\n");
 	printf ("Feito para garantir o nosso 10 no PIM!!!\n\n");
 	printf ("\n\nElaborado por:\n\n");
 	printf ("Anderson Tenório Vale\t\t\tF04FAJ3\n");
 	printf ("Fellipe de Azevedo e Vasconcelos\tF298787\n");
 	printf ("Marlon Akio Tochiro\t\t\tT727405\n");
 	printf ("Rychard Mayko Rosado de Araújo\t\tT941709\n");
 	printf ("Vinicus Fernandes U. dos Santos\t\tT109DF0\n\n");
 	printf ("Copyright@2022\n\n\n\n");
 	system("pause");
}
 
// Verifica se a array tem valores armazenados e chama a void deleta_dados
void deleta(void) {
 	if (! checa_vazio(principal))
 		principal = deleta_dados(principal);
}

// Inicio do metodo principal
int main(void) {
 	setlocale (LC_ALL, "portuguese");
 	char escolha;
 	do {
 		system("cls");
 		printf ("--------------------------------------------------------------------------------\n ");
 		printf("\t\t\t\tAdvocacia-SP\n");
 		printf("--------------------------------------------------------------------------------\n\n");
 		printf ("\t\t\t\Cadastro de Pessoas\n");
 		printf ("_______________________________\n ");
 		printf ("1-Cadastrar novo cliente\n ");
 		printf ("2-Exibir Dados\n ");
 		printf ("3-Buscar cliente pelo nome\n ");
 		printf ("4-Excluir o ultimo cadastro\n ");
 		printf ("5-Informacoes do Sistema\n ");
 		printf("6-Sair\n");
 		printf("_______________________________\n\n");
 		printf("--------------------------------------------------------------------------------\n\n");
 		printf ("\nQual opcao você deseja acessar? \n ");
 		scanf ("%c", &escolha);
 		switch(escolha) {
 			case '1':
 				insere ();
				break;
			case '2':
				exibe ();
				break;
			case '3':
 				busca ();
 				break;
 			case '4':
 				deleta ();
				break;
			case '5':
 				info ();
 				break;
 			case '6':
 				exit (0);
 				break;
 			default:
 			fprintf(stderr,"Pronto!");
 			sleep (1);
 			break;
 		}
 	}
// Loop Principal.	
 	while (escolha > 0); 
 	return 0;
}
