#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int visitado[10]; //revisar columnas, filas o submatriz
//ver que no se repita ningun numero en las filas
  for(int i = 0; i < 9; i++){
    for(int k = 0; k < 10;k++) visitado[k] = 0;
    for(int j = 0; j < 9; j++){ //recorrer cada fila de i
      int valor = n->sudo[i][j];
      if(valor != 0){
        if(visitado[valor]) return 0; //si esta reetido, es invalido
        visitado[valor] = 1; //marcar numero q aparecio en la fila 
      }
    }
  }
//ver que no se repita ningun numero en las columas
  for(int j = 0; j < 9; j++){
    for(int k = 0; k < 10;k++) visitado[k] = 0;
    for(int i = 0; i < 9; i++){ 
      int valor = n->sudo[i][j];
      if(valor != 0){
        if(visitado[valor]) return 0; 
        visitado[valor] = 1;
      }
    }
  }

  for(int columna = 0; columna < 3; columna++){
    for(int fila = 0; fila < 3; fila++){
      for(int k = 0; k < 10;k++) visitado[k] = 0;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          int numero = n->sudo[fila*3 + i][columna*3 + j];
          if(numero !=0){
            if(visitado[numero]) return 0;
            visitado[numero] = 1;
          }
        }
      }
    }
  }
    return 1;
}

List* get_adj_nodes(Node* n){
  List* list = createList();
  for(int i = 0;i < 9;i++){
    for(int j = 0; j < 9;j++){
      if(n->sudo[i][j] == 0){
        for(int k = 1; k <= 9; k++){
          Node* newNodo = copy(n);
          newNodo->sudo[i][j] = k;
          if(is_valid(newNodo)) pushBack(list,newNodo);
          else free(newNodo);
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* pila = createStack();
    push(pila, initial);
    *cont = 0;
    while (!is_empty(pila)) {
        Node* current = top(pila);
        pop(pila);
        (cont)++;

        if (is_final(current)) return current;

        List* adj = get_adj_nodes(current);
        Node* adjNode = first(adj);
        while (adjNode != NULL) {
            push(pila, adjNode);
            adjNode = next(adj);
        }
        free(current);
    }
    return NULL;
}






/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/