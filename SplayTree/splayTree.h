#pragma once

typedef struct tag_SplayTreeNode{
  struct tag_SplayTreeNode *left;
  struct tag_SplayTreeNode *right;
  struct tag_SplayTreeNode *parent;
  int data;
}SplayTreeNode;

typedef struct tag_SplayTree{
  SplayTreeNode *root;
}SplayTree;

SplayTree *CreateTree();
void PrintTree(FILE *F, SplayTree *tree);
void AddElement(SplayTree *tree, int data);
SplayTreeNode *SearchElement(SplayTree *tree, int data);
void DeleteTree(SplayTree *tree);
void Split(SplayTree *tree, int board, SplayTree **tree1 /* out */, SplayTree **tree2 /* out */);
SplayTree *Join(SplayTree *tree1, SplayTree *tree2, int data);