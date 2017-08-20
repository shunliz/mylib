#include<stdio.h>
#include<stdlib.h>
#include "BiTree.h"
#define N 10


void CreateBiTree(BiTree *T, char ch)
{
  /*
        If the very tree is empty, then malloc space for it 
        and initialize the children NULL
        and evaluate the data as ch
   */
  if(!*T)
  {
        *T = (BiTNode*)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return;
  }
  /*
        If the tree is not empty, then compare the tree node value
        with the very value, if the node is bigger, then initalize the 
        left child, the other with the right child
   */
  else
  {
        if((*T)->data == ch)
          return;
        if((*T)->data > ch)
          CreateBiTree(&((*T)->lchild), ch);
        else
          CreateBiTree(&((*T)->rchild), ch);
  }
}

/*
  Print the value according with Previous Order
  is to print the value first, then left child, and last the right child
 */
void MidOrder(BiTree T)
{
  if(T)
  {
        MidOrder(T->lchild);
    printf("%c ", T->data);
        MidOrder(T->rchild);
  }
  return;
}

/*
  Initalize the Root with NULL, and there using the array 
  to provide the values, and this can also get from an extern file
  and even get by inputing
 */
/*
int main()
{
  BiTree T = NULL;
  char a[N] = {'5','2', '3','6', '8', '7', '4', '1', '0', '9'};
  int i = 0;
  for(; i < N; i++)
  {
        CreateBiTree(&T, a[i]);
  }
  MidOrder(T);
  printf("\n");
  system("PAUSE");    
  return 0;

}
*/