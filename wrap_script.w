{{fn foo MPI_Init MPI_Send MPI_Recv MPI_Isend MPI_Irecv MPI_Wait MPI_Barrier MPI_Alltoall MPI_Scatter MPI_Gather MPI_Reduce MPI_Allreduce MPI_Finalize}} {
int count;
double start_time = MPI_Wtime(); 
{{callfn}} 
double end_time = MPI_Wtime();
printf("Starttime - endtime = %f\n", end_time-start_time);
} 
{{endfn}} 

