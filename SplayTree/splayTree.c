#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "splayTree.h"
#define SIZE 15

void f_DelRoot(SplayTree *tree, SplayTreeNode *delElement);
SplayTreeNode *f_CreateNode(int data){
  SplayTreeNode *node = (SplayTreeNode*)malloc(sizeof(SplayTreeNode));
  node->left = node->right = node->parent = NULL;
  node->data = data;
  return node;
}
void f_DestroyNode(SplayTreeNode *node){
  free(node);
}
void f_SplayTreeRightRotate(SplayTree *tree, SplayTreeNode *nodeParent){
  SplayTreeNode *nodeGrany = nodeParent->parent;
  SplayTreeNode *child = nodeParent->left;

  if (nodeGrany != NULL){
    if (nodeGrany->left == nodeParent){
      nodeGrany->left = child;
    }
    else if (nodeGrany->right == nodeParent){
      nodeGrany->right = child;
    }
  }
  else{
    tree->root = child;
  }
  child->parent = nodeGrany;

  nodeParent->left = child->right;
  if (child->right != NULL){
    child->right->parent = nodeParent;
  }

  child->right = nodeParent;
  nodeParent->parent = child;
}
void f_SplayTreeLeftRotate(SplayTree *tree, SplayTreeNode *nodeParent){
  SplayTreeNode *nodeGrany = nodeParent->parent;
  SplayTreeNode *child = nodeParent->right;

  if (nodeGrany != NULL){
    if (nodeGrany->left == nodeParent){
      nodeGrany->left = child;
    }
    else if (nodeGrany->right == nodeParent){
      nodeGrany->right = child;
    }
  }
  else{
    tree->root = child;
  }
  child->parent = nodeGrany;

  nodeParent->right = child->left;
  if (child->left != NULL){
    child->left->parent = nodeParent;
  }
  
  child->left = nodeParent;
  nodeParent->parent = child;
}
void f_SplayTree(SplayTree *tree, SplayTreeNode *node){
  while (node->parent != NULL){
    if (node->parent == tree->root){
      if (node->parent->left == node){
        f_SplayTreeRightRotate(tree, node->parent);
      }
      else if (node->parent->right == node){
        f_SplayTreeLeftRotate(tree, node->parent);
      }
    }
    else if (node->parent->left == node && node->parent->parent->left == node->parent){
      f_SplayTreeRightRotate(tree, node->parent->parent);
      f_SplayTreeRightRotate(tree, node->parent);
    }
    else if (node->parent->right == node && node->parent->parent->right == node->parent){
      f_SplayTreeLeftRotate(tree, node->parent->parent);
      f_SplayTreeLeftRotate(tree, node->parent);
    }
    else if (node->parent->right == node && node->parent->parent->left == node->parent){
      f_SplayTreeLeftRotate(tree, node->parent);
      f_SplayTreeRightRotate(tree, node->parent);
    }
    else if (node->parent->left == node && node->parent->parent->right == node->parent){
      f_SplayTreeRightRotate(tree, node->parent);
      f_SplayTreeLeftRotate(tree, node->parent);
    }
  }
}


SplayTree *CreateTree(){
  SplayTree *tree = (SplayTree*)malloc(sizeof(SplayTree));
  tree->root = NULL;
  return tree;
}

SplayTreeNode *f_SearchPlaceForAdd(SplayTree *tree, int data){
  SplayTreeNode *tmp = tree->root;
  SplayTreeNode *prevElement = NULL;
  while (tmp != NULL){
    prevElement = tmp;
    if (data > tmp->data){
      tmp = tmp->right;
    }
    else if (data < tmp->data){
      tmp = tmp->left;
    }
    else{
      return;
    }
  }
  return prevElement;
}

void AddElement(SplayTree *tree, int data){
  if (tree->root == NULL){
    SplayTreeNode *newNode = f_CreateNode(data);
    tree->root = newNode;
  }
  else{
    SplayTreeNode *parent = f_SearchPlaceForAdd(tree, data);
    if (parent == NULL){
      return;
    }
    SplayTreeNode *newNode = f_CreateNode(data);
    if (data > parent->data){
      parent->right = newNode;
    }
    else{
      parent->left = newNode;
    }
    newNode->parent = parent;
    f_SplayTree(tree, newNode);
  }
}

SplayTreeNode *SearchElement(SplayTree *tree, int data){
  SplayTreeNode *tmp = tree->root;
  while (tmp != NULL){
    if (data > tmp->data){
      tmp = tmp->right;
    }
    else if (data < tmp->data){
      tmp = tmp->left;
    }
    else if (data == tmp->data){
      return tmp;
    }
  }
  return NULL;
}

SplayTree *Join(SplayTree *tree1, SplayTree *tree2, int data){
  SplayTree *resultTree = CreateTree();
  resultTree->root = f_CreateNode(data);
  resultTree->root->left = tree1->root;
  resultTree->root->right = tree2->root;

  f_DelRoot(resultTree, resultTree->root);
  free(tree1);
  free(tree2);
  return resultTree;
}

void f_DelRoot(SplayTree *tree, SplayTreeNode *delElement){
  if (tree->root == NULL || delElement == NULL){
    return;
  }
  SplayTreeNode *instead = delElement->right;
  while (instead->left != NULL){
    instead = instead->left;
  }
  delElement->data = instead->data;

  if (instead->right != NULL){
    delElement->right = instead->right;
    instead->right->parent = delElement;
  }

  f_DestroyNode(instead);
}

void Split(SplayTree *tree, int board, SplayTree **tree1 /* out */, SplayTree **tree2 /* out */){
  AddElement(tree, board);

  (*tree1)->root = tree->root->left;
  (*tree2)->root = tree->root->right;
  tree->root->left = NULL;
  tree->root->right = NULL;

  DeleteTree(tree);
}

void PostOrder(SplayTreeNode *CurEl, void(*Function) (SplayTreeNode *Node)){
  if (CurEl != NULL)
  {
    PostOrder(CurEl->left, Function);
    PostOrder(CurEl->right, Function);
    Function(CurEl);
  }
}

void DeleteTree(SplayTree *tree){
  if (tree == NULL){
    return;
  }
  if (tree->root != NULL){
    PostOrder(tree->root, &(f_DestroyNode));
  }
  free(tree);
}


void f_InitMatrixForPrint(int y, int *x, SplayTreeNode *node, int **matrixForPrint){
  if (node != NULL){
    f_InitMatrixForPrint(y + 1, x, node->left, matrixForPrint);

    (*x)++;
    matrixForPrint[y][*x] = node->data;

    f_InitMatrixForPrint(y + 1, x, node->right, matrixForPrint);
  }
}

void f_PrintTreeMatrix(FILE *Output, int **matrixForPrint){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (matrixForPrint[i][j] == 0){
        fprintf(Output, "  ");
      }
      else{
        fprintf(Output, "%i", matrixForPrint[i][j]);
      }
    }
    fprintf(Output, "\n");
  }
  fprintf(Output, "\n------------------------------\n");
}

void f_InitMatrixByZero(int **matrixForPrint){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      matrixForPrint[i][j] = 0;
    }
  }
}

int **f_CreateMatrix(){
  int **MatrixForPrint = (int**)malloc(sizeof(int*) * SIZE);
  for (int i = 0; i < SIZE; i++){
    MatrixForPrint[i] = (int*)malloc(sizeof(int) * SIZE);
  }
  return MatrixForPrint;
}

void f_DeleteMatrix(int **Matrix){
  for (int i = 0; i < SIZE; i++){
    free(Matrix[i]);
  }
  free(Matrix);
}

void PrintTree(FILE *F, SplayTree *tree){
  int **MatrixForPrint = f_CreateMatrix();
  f_InitMatrixByZero(MatrixForPrint);

  int x = 0;
  f_InitMatrixForPrint(0, &x, tree->root, MatrixForPrint);
  f_PrintTreeMatrix(F, MatrixForPrint);
  f_DeleteMatrix(MatrixForPrint);
}
