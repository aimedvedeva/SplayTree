#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <crtdbg.h>
#include "splayTree.h"


int main(void){
  FILE *F;
  if ((F = fopen("input.txt", "r")) == NULL){
    return;
  }

  int numOfNodes;
  fscanf(F, "%i", &numOfNodes);

  SplayTree *tree = CreateTree();

  for (int i = 0; i < numOfNodes; i++){
    int data;
    fscanf(F, "%i", &data);
    AddElement(tree, data);
  }

  fclose(F);

  FILE *Output = NULL;

  if ((Output = fopen("output.txt", "w")) == NULL){
    return;
  }


  SplayTree *tree1 = CreateTree();
  SplayTree *tree2 = CreateTree();
  PrintTree(F, tree);
  Split(tree, 39, &tree1, &tree2);
  PrintTree(F, tree1);
  PrintTree(F, tree2);
  tree = Join(tree1, tree2, 7);
  PrintTree(F, tree);
  DeleteTree(tree);
  //DeleteTree(tree1);
  //DeleteTree(tree2);
  fclose(Output);
  _CrtDumpMemoryLeaks();
}