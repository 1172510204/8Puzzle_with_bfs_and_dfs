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

void printState(int *state) {
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

int compareStates(int* newState, int* closeStates) {
	int count = 0;

	for(int i = 0; i < PUZZLESIZE-1; i++) {
		if(newState[i] == closeStates[i]) count++;
	}

	if(count == PUZZLESIZE-1) return 1;	
	else return 0;

}

vector<Node*> *geraFilhos(Node* currentNode, vector<Node*>*closeStates) {
	int blank;
	int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
	int action[4] = { 0, 0, 0, 0 };
	int size = closeStates->size();
	Node* nodo_filho = new Node;
	vector<Node*> *filhos = new vector<Node*>;

	for(int i = 0; i < PUZZLESIZE; i++) {
		if(currentNode->state[i] == 0) blank = i;
	}

	//cout << closeStates->size() << endl;

	if(blank - 3 >= 0) action[0] = 1;
	if(blank + 3 < PUZZLESIZE) action[1] = 2;
	if(blank % 3 > 0) action[2] = 3;
	if(blank < PUZZLESIZE-1 && (blank % 3) < 2) action[3] = 4;

	for(int i = 0; i < 4; i++) {

		if(action[i] != 0) {
			newState = createState(currentNode->state, blank, action[i]);
			
			for(int j = 0; j < size; j++) {
				if(!compareStates(newState, closeStates->at(j)->state)) {
					nodo_filho = createNode(newState, 0, currentNode->cost+1, action[i]);

					filhos->push_back(nodo_filho);
					closeStates->push_back(nodo_filho);
				}
			}
		}
	}

	return filhos;

}

int bfs(Node *initialNode, int* finalState) {
	Node* currentNode;
	deque<Node*> fila;

	vector<Node*> *closeStates = new vector<Node*>;
	vector<Node*> *filhos = new vector<Node*>;

	fila.push_back(initialNode);
	closeStates->push_back(initialNode);

	if(compareStates(initialNode->state, finalState)) {
		return 1;
	}

	while(!fila.empty()) {
		currentNode = fila.front();
		fila.pop_front();

		if(!closeStates->empty()) {		
			filhos = geraFilhos(currentNode, closeStates);
		}

		for(int i = 0; i < filhos->size(); i++) {
			if(compareStates(filhos->at(i)->state, finalState)) {
				cout << filhos->at(i)->cost << endl;
				return 1;
			}else{
				fila.push_back(filhos->at(i));
			}
		}
	}
	return 0;
}

int main() {
	//int initialState[PUZZLESIZE] = {1, 6, 7, 2, 5, 3, 4, 0, 8};
	int initialState[PUZZLESIZE] = {3, 1, 2,
									6, 4, 5,
									7, 0, 8};
	int finalState[PUZZLESIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	Node *initialNode = createNode(initialState, 0, 0, -1);

	if(bfs(initialNode, finalState)) cout << "Encontrei o finalState" << endl;
	else cout << "Não encontrei o finalState" << endl;

}