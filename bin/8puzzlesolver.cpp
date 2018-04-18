#include <iostream>
#include <deque>
#include <queue>
#include <vector>

#define PUZZLESIZE 9

using namespace std;

struct node {
	int *state;
	int cost;
	int action;
	int d;
};
typedef struct node Node;

Node* createNode(int *state, int depth, int cost, int action) {
	Node *g = (Node*) malloc(sizeof(Node));
	g->state = state;
	g->cost = cost;
	g->action = action;
	g->d = depth;

	return g;
}

/*
1: cima
2: baixo
3: esquerda
4: direita
*/

int* createState(int* currentState, int blank, int action) {
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
			return newState;
		}
	}
	//baixo
	else if(action == 2) {
		if(blank + 3 < PUZZLESIZE) {
			aux = newState[blank+3];
			newState[blank+3] = 0;
			newState[blank] = aux;
			return newState;
		}
	}
	//esquerda
	else if(action == 3) {
		if(blank % 3 > 0) {
			aux = newState[blank - 1];
			newState[blank-1] = 0;
			newState[blank] = aux;
			return newState;
		}
	}
	//direita
	else if(action == 4) {
		if(blank < PUZZLESIZE-1 && (blank % 3) < 2) {
			aux = newState[blank + 1];
			newState[blank+1] = 0;
			newState[blank] = aux;
			return newState;
		}
	}

	return newState;
}

void printState(int *state) {
	for(int i = 0; i < PUZZLESIZE; i++) {
		cout << state[i] << " ";
	}

	cout << endl;
}

int isFinalState(Node* initialNode, int* finalState) {
	int count=0;
	for(int i = 0; i < PUZZLESIZE; i++) {
		if(initialNode->state[i] == finalState[i]) count++;
	}

	if(count == PUZZLESIZE) return 1;
	else return 0;
}
/*
int bfs(Node *initialNode, int* finalState) {
	Node* currentState;
	deque<Node*> fila;

	vector<Node*> *closeStates;
	vector<Node*> *filhos;

	fila.push_back(initialNode);

	if(isFinalState(initialNode, finalState)) {
		return 1;
	}

	while(!fila.empty()) {
		currentNode = fila.front();
		fila.pop_front();

		filhos = geraFilhos(currentNode, closeStates);

		for(int i = 0; i < filhos->size(); i++) {
			if(isFinalState(filhos->at(i)->state, finalState)) {
				return 1;
			}else{
				fila.push_back(filhos->at(i));
			}
		}
	}
	return 0;
}*/

int main() {
	int initialState[PUZZLESIZE] = {1, 6, 7, 2, 5, 3, 4, 0, 8};
	int finalState[PUZZLESIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	printState(initialState);

	Node *initialNode = createNode(initialState, 0, 0, -1);

	int *newState = createState(initialState, 7, 1);
	printState(newState);
}