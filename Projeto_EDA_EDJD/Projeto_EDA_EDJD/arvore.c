/**
 * @file arvore.c
 * @author Diogo Araújo
 * @email a23480@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 2)
 * Metodos para manipular as árvores e os process plans
 *
 * @bug bugs desconhecidos.
*/
#include <stdio.h>
#include "header.h"

/**
* @brief Cria um node caso a lista não contenha nada
* @param [in] e Inicio da lista Job		
* @return	node
*/
Node* NewNode(Job* e) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;	//problemas ao criar espaço em memória	
    node->job.cod = e->cod;
    node->job.operations = e->operations;
    node->leftTree = NULL;
    node->rightTree = NULL;
    return node;
}

/**
* @brief Mostra o código do que está contido na árvore
* @param [in] root Lista da arvore
* @return	
*/
void PreOrder(Node* root) {
    if (root == NULL) return;
    printf("Cod=%d\n", root->job.cod);
    PreOrder(root->leftTree);
    PreOrder(root->rightTree);
}

/**
* @brief Adiciona um node á lista da arvore com o codJob
* @param [in] root Lista da arvore
* @param [in] e Lista de Jobs
* @return
*/

Node* AddNode(Node* root, Job* e) {
    if (root == NULL)        //arvore vazia
    {
        root = NewNode(e);
    }
    else
    {
        if (root->job.cod > e->cod) {        //Insere à esquerda
            root->leftTree = AddNode(root->leftTree, e);
        }
        else
            if (root->job.cod < e->cod)        //Insere à direita
                root->rightTree = AddNode(root->rightTree, e);

    }
    return root;
}
/**
* @brief Remove um node da lista de arvores
* @param [in] root Lista da arvore
* @param [in] e Lista de Jobs
* @return
*/


PtrNode DeleteNode(PtrNode root, Job* e) {
    //árvore vazia ou enexistente
    if (root == NULL) return NULL;

    if (root->job.cod > e->cod)
        root->leftTree = DeleteNode(root->leftTree, e);
    else
        if (root->job.cod < e->cod) {
            root->rightTree = DeleteNode(root->rightTree, e);
        }
        else    
        {
            root = DeleteCurrentNode(root);
        }
    return root;

}

/**
* @brief Remove o último elemento da lista da arvore
* @param [in] root Lista da arvore
* @return
*/
PtrNode DeleteCurrentNode(PtrNode root) {
    PtrNode aux;
    if (root == NULL) return NULL;	//Nada para apagar!

    if (root->leftTree == NULL && root->rightTree == NULL) {	//único nodo
        DestroyNode(&root);
        return NULL;
    }
    else
        if (root->leftTree == NULL) {		//só tem sub-arvore direita...ligar à direita
            aux = root;
            root = root->rightTree;
            DestroyNode(&aux);
        }
        else
        {
            if (root->rightTree == NULL) {	//só com sub-arvore esquerda
                aux = root;
                root = root->leftTree;
                DestroyNode(&aux);
            }
            else       //com sub-arvores esquerda e direita
            {
                //substitui pelo menor da sub-arvore direita
                root->job = FindMin(root->rightTree)->job;
                //elimina o menor da sub-arvore direita
                root->rightTree = DeleteNode(root->rightTree, &root->job);
            }
        }
    return root;
}

/**
* @brief Apaga o node
* @param [in] p recebe um apontado da lista de nodes
* @return
*/
void DestroyNode(Node** p) {		//DestroyNode(PtrNode *p)	
    //Fazer varias coisas...
    if (*p != NULL) {
        free(*p);
        *p = NULL;
        //H2
        //free((*p)->element);
        //*p = NULL;
    }
}
/**
* @brief Encontra o valor mais pequeno na arvore
* @param [in] root Lista da arvore
* @return
*/
PtrNode FindMin(PtrNode root) {
    if (root->leftTree == NULL) return root;
    else
        return(FindMin(root->leftTree));
}
/**
* @brief Devolve o tamanho da árvore
* @param [in] r Lista da arvore
* @return
*/

int TreeSize(PtrNode r) {

    if (r == NULL) return 0;
    else
        return (1 + TreeSize(r->leftTree) + TreeSize(r->rightTree));
}
// =========== Balanceamento ============

/*
Prepara Balanceamento da arvore
*/

PtrNode Balance(PtrNode root) {
    PtrNode newRoot = NULL;
    if (root == NULL) return NULL;

    int tot = TreeSize(root); //quantos nodos tem a arvore?
    int count = 0;

    //criar estrutura dinâmica auxiliar
    Node *listNode;

    if ((listNode = (Node *)malloc(sizeof(Node)*tot)) == NULL) return NULL;
    //preenche lista a partir da arvore
    BST2List(root, &count, listNode);   
    //balanceia arvore
    newRoot = BSTBalance(newRoot, listNode, 0, tot - 1);
    free(listNode);
    return newRoot;
}

/*
Balanceia árvore. Travessia Binária de um array!
*/
PtrNode BSTBalance(PtrNode root, Node* list, int ini, int end) {
    unsigned int m;

    if (ini <= end) {
        m = (ini + end) / 2;
        root = AddNode(root, &list[m].job);
        root = BSTBalance(root, list, ini, m - 1);
        root = BSTBalance(root, list, m + 1, end);
    }
    return root;
}

/*
Cria uma "Lista" a partir dos elementos de uma arvore
*/
void BST2List(PtrNode root, unsigned int *count, Node *list) {
    if (root != NULL) {
        BST2List(root->leftTree, count, list);
        list[(*count)++].job = root->job;
        BST2List(root->rightTree, count, list);
    }
}


