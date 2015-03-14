#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <exception>
#include <sstream>

using namespace std;


class BST{

private:

	struct node{
		string matricula;
		string estado;
		int portagens;
		int altura; // altura do nó
		struct node* pai; // ponteiro para o nó pai
		struct node* left;
		struct node* right;
	};

	BST::node* root; 

public:

	// default constructor
	BST(){
		root = NULL;
	}

	// função que chama a função recursiva rec_insere para inserir um nó na árvore
	void insere(string s, string st);

	// função recursiva para inserir um nó
	BST::node* rec_insere(BST::node** raiz, BST::node* antecessor,string s, string st);

	// função que marca um determinado veículo como regular ou ignora a operação caso não exista
	void unflag(string veiculo);

	// printa o estado de um determinado veiculo
	void status(string veiculo);

	// retorna a altura de um no
	int getAltura(BST::node* no){
		if(no == NULL)
			return 0;
		else
			return 1 + max(getAltura(no->left), getAltura(no->right));
	}

	int getEquilibrio(BST::node* no){
		return getAltura(no->left) - getAltura(no->right);
	}

	/*void Atualiza(BST::node** no, string m);

	void rodaDireita(BST::node** no, string m){
	}

	void rodaEsquerda(BST::node** no, string m){
	}*/

};

void BST::Atualiza(BST::node** no, string m){

	// Rotacao simples para a direita
	
	if(getEquilibrio(*no) > 1 && (*no)->left->matricula > m){
		rodaDireita(&((*no)->left), m);
	}

	// Rotacao simples para a esquerda

	else if(getEquilibrio(*no) < -1 && (*no)->right->matricula < m){

		rodaEsquerda(&((*no)->right), m);
	}

	// Rotação esquerda e depois para a direita

	else if(getEquilibrio(*no) > 1 && (*no)->left->matricula < m){
		rodaEsquerda(&((*no)->left->right), m);
		rodaDireita(&((*no)->left), m);
	}

	// Rotação direita e depois para a esquerda

	else if(getEquilibrio(*no) < -1 && (*no)->right->matricula > m){
		rodaDireita(&((*no)->right->left), m);
		rodaEsquerda(&((*no)->right), m);
	}
}

void BST::insere(string s, string st){
	BST::root = rec_insere(&root, NULL, s, st);
}

BST::node* BST::rec_insere(BST::node** raiz, BST::node* antecessor,string s, string st){
	if (*raiz == NULL){
		*raiz = new BST::node;
		(*raiz)->matricula = s;
		(*raiz)->estado = st;
		(*raiz)->portagens = 1;
		(*raiz)->altura = 1;
		(*raiz)->left = NULL;
		(*raiz)->right = NULL;
		(*raiz)->pai = antecessor;

		return *raiz;
	}

	else if ((*raiz)->matricula > s){
		BST::rec_insere(&((*raiz)->left), *raiz, s, st);
	}

	else if ((*raiz)->matricula < s){
		BST::rec_insere(&((*raiz)->right), *raiz, s, st);
	}

	else{
		(*raiz)->estado = st;
		(*raiz)->portagens++;
	}

	//________________________________ATUALIZAR______________________________________________

	
	BST::node* aux; // aponta para o pai do nó que vai rodar
	BST::node* aux2; // vai apontar para o nó que vai rodar
	BST::node** aux3; //NOVO
	int eq; // NOVO

	aux3 = raiz; // NOVO

	eq = getEquilibrio(*raiz);


	// Rotacao simples para a direita
	
	if(eq > 1 && (*raiz)->left->matricula > s){

		raiz = &((*raiz)->left);
		aux = (*raiz)->pai;
		aux2 = *raiz;
		
		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz; // NOVO
		aux->pai = *raiz;
		aux->left = (*raiz)->right; // raiz == 0
		aux2->right = aux;

		raiz = &(aux->pai);
	}

	// Rotacao simples para a esquerda

	else if(eq < -1 && (*raiz)->right->matricula < s){
		cout << "Rotação esquerda" << endl;

		raiz = &((*raiz)->right);

		aux = (*raiz)->pai;
		aux2 = *raiz;

		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz;

		aux->pai = *raiz;
		aux->right = (*raiz)->left;
		aux2->left = aux;

		raiz = &(aux->pai);

	}

	// Rotação esquerda e depois para a direita

	else if(eq > 1 && (*raiz)->left->matricula < s){

		// RODA ESQUERDA

		raiz = &((*raiz)->left->right);

		aux = (*raiz)->pai;
		aux2 = *raiz;

		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz; // NOVO
		
		aux->pai = *raiz;
		aux->right = (*raiz)->left;
		aux2->left = aux;

		raiz = &(aux->pai);

		// RODA DIREITA

		aux = (*raiz)->pai;
		aux2 = *raiz;

		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz; // NOVO

		aux->pai = *raiz;
		aux->left = (*raiz)->right; // raiz == 0
		aux2->right = aux;

		raiz = &(aux->pai);

	}

	// Rotação direita e depois para a esquerda

	else if(eq < -1 && (*raiz)->right->matricula > s){

		// RODA DIREITA

		raiz = &((*raiz)->right->left);

		aux = (*raiz)->pai;
		aux2 = *raiz;

		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz; // NOVO

		aux->pai = *raiz;
		aux->left = (*raiz)->right; // raiz == 0
		aux2->right = aux;

		raiz = &(aux->pai);

		// RODA ESQUERDA

		aux = (*raiz)->pai;
		aux2 = *raiz;

		(*raiz)->pai = (*raiz)->pai->pai;
		if(*aux3 != NULL)
			*aux3 = *raiz; // NOVO

		aux->pai = *raiz;
		aux->right = (*raiz)->left;
		aux2->left = aux;

		raiz = &(aux->pai);
	}

	//___________________________________________________________________________________

	return *raiz;
}

void BST::unflag(string veiculo){
	BST::node* aux;
	int igual;
				
	aux = root;
	igual = 0;
		
	while (!(aux == NULL || igual == 1)){
		if(veiculo.compare(aux->matricula) < 0)
				aux = aux->left;
		else if (veiculo.compare(aux->matricula) > 0)
			aux = aux->right;
		else
			igual = 1;
			
	}

	if(igual == 1)
		aux->estado = 'R';
}

void BST::status(string veiculo){
	BST::node* aux;
	int igual;
				
	aux = root;
	igual = 0;
		
	while (!(aux == NULL || igual == 1)){
		if(veiculo.compare(aux->matricula) < 0)
			aux = aux->left;
		else if (veiculo.compare(aux->matricula) > 0)
			aux = aux->right;
		else
			igual = 1;
			
	}

	if(igual == 1)
		cout << aux->matricula << " " << aux->portagens << " " << aux->estado << endl;
	else
		cout << veiculo << " NO RECORD" << endl;
}


int main(){
	vector<string> v;
	string buff, comando;
	BST bd = BST();

	do{
		getline(cin, comando);
		stringstream st(comando);

		while(st >> buff)
			v.push_back(buff);

		if(v[0].compare("PASS") == 0){
			bd.insere(v[1], v[2]);
		}
		else if(v[0].compare("STATUS") == 0){
			bd.status(v[1]);
		}
		else
			bd.unflag(v[1]);

		v.clear();

	}while(comando != "\0");

	return 0;
}