#include <stdio.h>
#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[])
{
	int ProcNum, ProcRank, RecvRank;
	int M = 10;
	int message = 7;
	int getmessage;
	double t1, t2, dt;
	
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	if (ProcRank == 0)
		t1 = MPI_Wtime();
	for (int j = 0; j < M; j++)
	{
		if (ProcRank == 0) {
			// Действия, выполняемые только процессом с рангом 0
			for (int i = 1; i < ProcNum; i++)
			{
				MPI_Send(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			for (int i = 1; i < ProcNum; i++) {
				MPI_Recv(&getmessage, 1, MPI_INT, i,
					MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				//cout << getmessage << endl;
			}
		}
		else { // Сообщение, отправляемое всеми процессами, 
		// кроме процесса с рангом 0 
			MPI_Recv(&getmessage, 1, MPI_INT, 0,
				MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			MPI_Send(&getmessage, 1, MPI_INT, 0,0, MPI_COMM_WORLD);
		}
	}
	if (ProcRank == 0) {
		t2 = MPI_Wtime();
		dt = t2 - t1;
		cout << "time - " << dt;
	}
	MPI_Finalize();
	return 0;
}