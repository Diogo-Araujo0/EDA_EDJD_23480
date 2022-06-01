/**
 * @file main.c
 * @author Diogo Araújo
 * @email a23480@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 2)
 * @bug bugs desconhecidos.
*/

#include "header.h";
#pragma warning disable 

int main() {
	Node* raiz;
	raiz = NULL;
	ProcessPlan* p = NULL;
	MachinesList* machinesOp1 = NULL, * machinesOp2 = NULL, * machinesOp3 = NULL;
	OperationsList* OperationsJob1 = NULL;
	OperationsMath x;
	float y;

	Job* e;

	e = CreateJob(1,NULL);
	raiz = AddNode(raiz, e);

	e = CreateJob(2, NULL);
	raiz = AddNode(raiz, e);

	e = CreateJob(3, NULL);
	raiz = AddNode(raiz, e);
	raiz = Balance(raiz);

	PreOrder(raiz);
	
	DeleteNode(raiz,e);
	Machine* M1 = CreateMachine(1, 4);
	machinesOp1 = InsertMachineInMachinesList(machinesOp1, M1);
	Operation* O1 = CreateOperation(1, machinesOp1);
	Operation* O2 = CreateOperation(2, NULL);
	raiz = AddNewOperationToJob(raiz, 1, O1);
	raiz = AddNewOperationToJob(raiz, 1, O2);
	raiz = ChangeOperationInJob(raiz, 1, 1, 1, 5, 20);
	raiz = RemoveOperationFromJob(raiz, 1, 1);
	
	
	
	


	

	


	


	

	
	/*
	x = GetMinTimeToCompleteJob(p, 1);
	ListOperations(x.operations);
	puts(" ");
	x = GetMaxTimeToCompleteJob(p, 1);
	ListOperations(x.operations);

	y = GetAverageOperationTime(p, 1, 3);*/

	return 0;
}


