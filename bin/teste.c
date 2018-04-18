#include <stdio.h>

#define PUZZLESIZE 9

struct node{
	
		int *state;
		int cost; 
		int action; 
		int d; 

};
typedef struct node Node; 

Node* createNode(int *state, int depth, int cost, int action){
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
int* createState(int* currentState, int blank, int action){

	int i, aux;
	if (action == 3){
		if(blank % 3 > 0){
			//alocao de memoria do novo estado
			int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
			
			//duplicar estado anterior
			for(i = 0; i < PUZZLESIZE; i++){
				newState[i] = currentState[i];
			}
			aux = newState[blank - 1];
			newState[blank-1] = 0;
			newState[blank] = aux; 
			return newState;

		}
	}else if(action == 4){

		if( blank < PUZZLESIZE-1 && (blank % 3) < 2 ){

			//alocao de memoria do novo estado
			int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
			
			//duplicar estado anterior
			for(i = 0; i < PUZZLESIZE; i++){
				newState[i] = currentState[i];
			}
			aux = newState[blank + 1];
			newState[blank+1] = 0;
			newState[blank] = aux; 
			return newState;
		}

	}else if(action == 1){
	
		if (blank - 3 >= 0){
			//alocao de memoria do novo estado
			int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
			
			//duplicar estado anterior
			for(i = 0; i < PUZZLESIZE; i++){
				newState[i] = currentState[i];
			}
			aux = newState[blank - 3];
			newState[blank-3] = 0;
			newState[blank] = aux; 
			return newState;
	 	}
		
	}else if(action == 2){

		if (blank + 3 < PUZZLESIZE){
			//alocao de memoria do novo estado
			int* newState = (int*) malloc(sizeof(int)*(PUZZLESIZE));
			
			//duplicar estado anterior
			for(i = 0; i < PUZZLESIZE; i++){
				newState[i] = currentState[i];
			}
			aux = newState[blank + 3];
			newState[blank+3] = 0;
			newState[blank] = aux; 
			return newState;
	 	}
	}
}

void printState(int *state){
	int i; 
	for(i = 0; i < PUZZLESIZE; i++){
		printf("%d ", state[i]);
	}
	printf("\n");
}

int bfs(Node *initialNode, int* finalState){

	Node* currentNode;
	deque<Node*> fila;

	vector<Node*> *closeStates; 
	vector<Node*> *filhos; 

	fila.push_back(initialNode);

	if (isFinalState(initialNode, finalState)){
		return 1;
	}

	while(!fila.empty()){

		currentNode = fila.front();
		fila.pop_front();

		filhos = geraFilhos(currentNode, closeStates);

		for(i = 0; i < filhos->size(); i++){
			if(isFinalState(filhos->at(i)->state)){
				return 1;
			}else{
				fila.push_back(filhos->at(i));
			}
		}

	}
	return 0;

}

int main(){

	int initialState[PUZZLESIZE] = {1, 6, 7, 2, 5, 3 ,4 ,0, 8};
	int finalState[PUZZLESIZE] = {0, 1, 2 ,3 , 4, 5, 6 ,7 ,8};
	printState(initialState);
	
	Node *initialNode = createNode(initialState, 0, 0, -1);



}