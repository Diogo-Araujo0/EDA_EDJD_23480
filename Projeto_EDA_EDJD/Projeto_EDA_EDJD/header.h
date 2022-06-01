/**
 * @file header.h
 * @author Diogo Araújo
 * @email a23480@alunos.ipca.pt
 * @date 2022
 * @brief Definicoes Globais para o Trabalho pratico da UC EDA (versao 2)
 *
 *	Structs e Assinaturas de Funcoes
 * @bug bugs desconhecidos.
*/
#ifndef BTREE
#define BTREE




#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura para armazenar uma maquina
 *
 * Uma maquina contem um codigo (@@cod) e tempo (@@time).
 */
typedef struct Machine {
	int cod;	/**< Codigo da Maquina*/
	int time;	/**< Tempo para executar a operacao*/
}Machine;

/**
 * @brief Estrutura para armazenar as maquinas
 *
 * Uma lista de maquinas contem a estrutura do tipo Machine (@@machine) e o apontador para a proxima maquina (@@nextMachine).
 */
typedef struct MachinesList {
	struct Machine machine;					/**< toda a informacao da Maquina */
	struct MachinesList* nextMachine;		/**< Ligacao a outra Maquina*/
}MachinesList;

/**
 * @brief Estrutura para armazenar uma operacao
 *
 * Uma operacao contem um codigo (@@cod) e uma lista de maquinas (@@machines).
 */
typedef struct Operation {
	int cod;							/**< Codigo da Operacao*/
	struct MachinesList* machines;		/**< Todas as Maquinas da Operacao*/
}Operation;

/**
 * @brief Estrutura para armazenar as operacoes
 *
 * Uma lista de operacoes contem a estrutura do tipo Operation (@@operation) e o apontador para a proxima operacao (@@nextOperation).
 */
typedef struct OperationsList {
	struct Operation operation;					/**< toda a informacao da Operacao */
	struct OperationsList* nextOperation;		/**< Ligacao a outra Operacao*/
}OperationsList;

/**
 * @brief Estrutura para armazenar um trabalho
 *
 * Um trabalho contem um codigo (@@cod) e uma lista de operacoes (@@operations).
 */
typedef struct Job {
	int cod;								/**< Codigo do Job*/
	struct OperationsList* operations;		/**< Todas as Operacoes do Job*/
}Job;

/**
 * @brief Estrutura para armazenar os trabalhos
 *
 * Uma lista de trabalhos contem a estrutura do tipo Job (@@job) e o apontador para o proximo trabalho (@@nextJob).
 */
typedef struct ProcessPlan {
	struct Job job;						/**< toda a informacao do Job */
	struct ProcessPlan* nextJob;		/**< Ligacao o outro Job*/
}ProcessPlan;

/**
 * @brief Estrutura utilizada para resultados em calculos com Operacoes
 *
 * Um OperationsMath contem o resultado dos calculos (@@res) e o apontador para a lista de operacoes utilizadas para obter o resultado (@@operations).
 */
typedef struct OperationsMath {
	int res;								/**< resultado dos calculos */
	struct OperationsList* operations;		/**< Todas as Operacoes utilizadas para obter o resultado*/
}OperationsMath;

typedef struct Node {
	Job job;
	struct Node* leftTree;
	struct Node* rightTree;
}Node, *PtrNode;



//Assinaturas de funcoes
#pragma region Machine Functions
	Machine* CreateMachine(int cod, int time);
	MachinesList* CreateMachineListNode(Machine* m);
	MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine);
	bool CheckMachineExists(MachinesList* h, int cod);
	Machine* SearchMachine(MachinesList* h, int cod);
	int SumMachineTime(MachinesList* h);
	int CountMachines(MachinesList* h);
	Machine* ChangeMachine(Machine* h, int newMacCod, int newTime);
	Machine* GetMachineWithLowerTime(MachinesList* h);
	Machine* GetMachineWithHigherTime(MachinesList* h);
	void ListMachines(MachinesList* h);
#pragma endregion

#pragma region Operation Functions
	Operation* CreateOperation(int cod, MachinesList* m);
	OperationsList* CreateOperationListNode(Operation* o);
	OperationsList* InsertOperationInOperationsList(OperationsList* h, Operation* newOperation);
	bool CheckOperationExists(OperationsList* h, int cod);
	Operation* SearchOperation(OperationsList* h, int cod);
	float GetAverageOperationTime(ProcessPlan* h, int jobCod, int opCod);
	Node* ChangeOperationInJob(Node* h, int jobCod, int opCod, int macCod, int newMacCod, int newTime);
	OperationsMath GetMinTimeToCompleteOperations(OperationsList* h);
	OperationsMath GetMaxTimeToCompleteOperations(OperationsList* h);
	void ListOperations(OperationsList* h);
#pragma endregion

#pragma region Job Functions
	Job* CreateJob(int cod, OperationsList* o);
	bool CheckJobExists(ProcessPlan* h, int cod);
	Node* AddNewOperationToJob(Node* h, int jobCod, Operation* o);
	Node* RemoveOperationFromJob(Node* h, int jobCod, int opCod);
	Job* SearchJob(Node* h, int cod);
	OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod);
	OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod);
#pragma endregion







//================= Assinatura de métodos ===================

//Inicializa uma àrvore
PtrNode InitTree();

//Cria novo nodo de uma árvore binária
PtrNode NewNode(Job* e);

//Destroi um nodo de uma árvore
void DestroyNode(PtrNode* p);

//Calcula o Número de Nodos de uma Árvore
int TreeSize(PtrNode r);

//Calcula a Altura de uma Árvore
int TreeHeight(PtrNode r);


// =========== Operações de procura ============

PtrNode FindNode(Job e, PtrNode root);



PtrNode GetMax(PtrNode root);

PtrNode GetMin(PtrNode root);


// =========== Operações de Manipulação ============

PtrNode AddNode(PtrNode root, Job* e);
//PtrNode AddNodeII(PtrNode root, Node e);
PtrNode DeleteNode(PtrNode root, Job* e);
PtrNode DeleteCurrentNode(PtrNode root);
PtrNode FindMin(PtrNode root);




// =========== Balanceamento ============

PtrNode Balance(PtrNode root);
PtrNode BSTBalance(PtrNode root, Node *list, int ini, int end);
void BST2List(PtrNode root, unsigned int tot, Node *list);




#endif