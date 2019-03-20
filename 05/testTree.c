#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"


void mirror(TreeNode **t) {
    if (*t) {
        mirror(&((*t)->r));
        mirror(&((*t)->l));
        TreeNode * aux = (*t)->r;
        (*t)->r = (*t)->l;
        (*t)->l = aux;
    }
}

int sameTree(TreeNode *t1, TreeNode *t2) {
    return (t1 && t2 ? t1->elem == t2->elem && sameTree(t1->l, t2->l) && sameTree(t2->r, t2->r) : t1 != t2);
}

int main()
{
    TreeNode *t1=NULL, *t2=NULL;
    Insert(&t1, 1); Insert(&t1, 2);
    Insert(&t1, 3); Insert(&t1, 4);

    Insert(&t2, 1); Insert(&t2, 2);
    Insert(&t2, 3); Insert(&t2, 5);


    printf("Preorder should be: 1 2 3 4 \nPreorder = ");
    PrintPreorder(t1);
    printf("\n\n");

    printf("Inorder should be: 1 2 3 4 \nInorder = ");
    PrintInorder(t1);
    printf("\n\n");

    printf("Postorder should be: 4 3 2 1 \nPostorder = ");
    PrintPostorder(t1);
    printf("\n\n");

    printf("Size should be: 4 \n");
    printf("Size = %d \n \n", Size(t1));

    printf("MaxDepth should be: 4 \n");
    printf("MaxDepth = %d \n \n", maxDepth(t1));

    printf("Same tree should be: 0 \n");
    printf("Same tree = %d \n\n", sameTree(t1,t2));

    printf("Before swap (mirror). Inorder should be: 1 2 3 5 \n"); PrintInorder(t2);
    printf("\n");
    mirror(&t2);
    printf("After swap (mirror). Inorder should be: 5 3 2 1 \n"); PrintInorder(t2);
    printf("\n");

    Free(&t1);
    Free(&t2);

    return 0;
}
