/*
FELIPE HOMRICH MELCHIOR
UNIPAMPA - 161150758
*/

#include <iostream>
#include <deque> //Biblioteca da fila
#include <stack> //Biblioteca da pilha
#include <vector> //Biblioteca do vector

#define PUZZLESIZE 9 //Definido o tamanho do desafio

using namespace std;

struct node { //Nodo da árvore
	int *state;
	int cost;
	int action;
	int d;
};
typedef struct node Node;

Node* createNode(int *state, int depth, int cost, int action) { // Função de criação de um nodo
	Node *g = (Node*) malloc(sizeof(Node));
	g->state = state;
	g->cost = cost;
	g->action = action;
	g->d = depth;

	return g;
}

void printState(int *state) { // Funcao que printa o estado que foi recebido via parametro
	for(int i = 0; i < PUZZLESIZE; i++) {
		cout << state[i] << " ";
	}

	cout << endl;
}

/*
1: cima
2: baixo
3: esquerda
4: direita
*/

int* createState(int* currentState, int blank, int action) { // Funcao que movimenta o indice vazio (0)
	int aux;
	int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));

	//duplicar estado anterior
	for(int i = 0; i < PUZZLESIZE; i++) {
			newState[i] = currentState[i];
	}

	//cima
	if(action == 1) {
		if(blank - 3 >= 0) {
			aux = newState[blank-3];
			newState[blank-3] = 0;
			newState[blank] = aux;
			//printState(newState);
			return newState;
		}
	}
	//baixo
	else if(action == 2) {
		if(blank + 3 < PUZZLESIZE) {
			aux = newState[blank+3];
			newState[blank+3] = 0;
			newState[blank] = aux;
			//printState(newState);
			return newState;
		}
	}
	//esquerda
	else if(action == 3) {
		if(blank % 3 > 0) {
			aux = newState[blank - 1];
			newState[blank-1] = 0;
			newState[blank] = aux;
			//printState(newState);
			return newState;
		}
	}
	//direita
	else if(action == 4) {
		if(blank < PUZZLESIZE-1 && (blank % 3) < 2) {
			aux = newState[blank + 1];
			newState[blank+1] = 0;
			newState[blank] = aux;
			//printState(newState);
			return newState;
		}
	}

	return newState;
}

int compareStates(int* newState, int* closeStates) { //Compara dois estados recebidos
	int count = 0;

	for(int i = 0; i < PUZZLESIZE-1; i++) {
		if(newState[i] == closeStates[i]) count++;
	}

	if(count == PUZZLESIZE-1) return 1;	
	else return 0;
}

int nodeExisting(int* newState, vector<int*>*closeStates) { // Compara um estado recebido com todos os estados que ja foram percorridos, para verificar existencia
	for(int i = 0; i < closeStates->size(); i++) {
		int count = 0;
		for(int j = 0; j < PUZZLESIZE; j++) {
			if(newState[j] == closeStates->at(i)[j]) {
				count++;
				if(count == PUZZLESIZE-1) return 1;
			}
			else break;
 		}
	}

	return 0;
}

vector<Node*> geraFilhos(Node* currentNode, vector<int*>*closeStates) { //Funcao que gera os estados-filhos atraves do estado-pai
	int blank;
	int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
	Node* nodo_filho = new Node;
	vector<Node*> filhos;

	for(int i = 0; i < PUZZLESIZE; i++) {
		if(currentNode->state[i] == 0) blank = i;
	}

	for(int i = 0; i < 4; i++) {
		newState = createState(currentNode->state, blank, i+1);

		if(!(compareStates(currentNode->state, newState)) && !(nodeExisting(newState, closeStates))) {
			nodo_filho = createNode(newState, currentNode->d+1, currentNode->cost+1, i);

			filhos.push_back(nodo_filho);
		}
	}

	return filhos;

}

int bfs(Node *initialNode, int* finalState) { //Busca em largura com fila
	Node* currentNode;
	deque<Node*> fila;

	vector<int*> closeStates;
	vector<Node*> filhos;

	fila.push_back(initialNode);
	closeStates.push_back(initialNode->state);

	if(compareStates(initialNode->state, finalState)) {
		return 1;
	}

	while(!fila.empty()) {
		currentNode = fila.front();
		fila.pop_front();

		if(!closeStates.empty()) {		
			filhos = geraFilhos(currentNode, &closeStates);
		}

		for(int i = 0; i < filhos.size(); i++) {
			if(compareStates(filhos.at(i)->state, finalState)) {
				printState(filhos.at(i)->state);
				cout << "BFS -> Solução encontrada com " << filhos.at(i)->cost << " Movimentos" << endl;
				return 1;
			}else{
				fila.push_back(filhos.at(i));
				closeStates.push_back(filhos.at(i)->state);
			}
		}
	}

	cout << "BFS -> Solução não encontrada" << endl;
	return 0;
}

int dfs(Node *initialNode, int* finalState) { //busca em profundidade com pilha
	Node* currentNode;
	stack<Node*> pilha;

	vector<int*> closeStates;
	vector<Node*> filhos;

	pilha.push(initialNode);
	closeStates.push_back(initialNode->state);

	if(compareStates(initialNode->state, finalState)) {
		return 1;
	}

	while(!pilha.empty()) {
		currentNode = pilha.top();
		pilha.pop();

		if(!closeStates.empty()) {		
			filhos = geraFilhos(currentNode, &closeStates);
		}

		for(int i = 0; i < filhos.size(); i++) {
			if(compareStates(filhos.at(i)->state, finalState)) {
				printState(filhos.at(i)->state);
				cout << "DFS -> Solução encontrada com " << filhos.at(i)->cost << " Movimentos" << endl;
				return 1;
			}else{
				pilha.push(filhos.at(i));
				closeStates.push_back(filhos.at(i)->state);
			}
		}
	}

	cout << "DFS-> Solução não encontrada" << endl;
	return 0;
}


int main(void) {
	/*Declaração do estado inicial, com um exemplo ja comentado
	{4, 3, 0, 6, 7, 2, 8, 1, 5}; -> BFS-> Cerca de 0.2s :: DFS-> Cerca de 17s
	*/
	int initialState[PUZZLESIZE] =  {1, 6, 7, 2, 5, 3, 4, 0, 8}; //{4, 3, 0, 6, 7, 2, 8, 1, 5};
 	int finalState[PUZZLESIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	Node *initialNode = createNode(initialState, 0, 0, -1); //Criacao do nodo inicial

	printState(initialNode->state); //Imprime o estado inicial

	bfs(initialNode, finalState); //Faz a busca em largura
	dfs(initialNode, finalState); //Faz a busca em profundidade
}