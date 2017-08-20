
#ifndef BITREE_H
#define BITREE_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct BiTNode{
        char data;
        struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *T, char ch);
void MidOrder(BiTree T);

#ifdef __cplusplus
}
#endif

#endif
