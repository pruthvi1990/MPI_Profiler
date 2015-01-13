/*
		 "// ------------------------------------------------------------------------------------------------- 
		 "// Copyright (c) 2014 Pruthvi and Rachana Raj Sunku , University of Arizona" 
		 "// Permission to copy is granted provided that this header remains" 
		 "// intact. This software is provided with no warranties" 
		 "// -------------------------------------------------------------------------------------------------
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _EXTERN_C_
#ifdef __cplusplus
#define _EXTERN_C_ extern "C"
#else /* __cplusplus */
#define _EXTERN_C_
#endif /* __cplusplus */
#endif /* _EXTERN_C_ */

#ifdef MPICH_HAS_C2F
_EXTERN_C_ void *MPIR_ToPointer(int);
#endif // MPICH_HAS_C2F

#ifdef PIC
/* For shared libraries, declare these weak and figure out which one was linked
   based on which init wrapper was called.  See mpi_init wrappers.  */
#pragma weak pmpi_init
#pragma weak PMPI_INIT
#pragma weak pmpi_init_
#pragma weak pmpi_init__
#endif /* PIC */

struct node 
{
	char func_name[50];
      int proc_rank;
	int dest;
      int tag;
      int source;
	int num_bytes; //to determine the data send for MPI_Send/MPI_Isend 
	double s_time;
	double e_time;
	int unique_id;
};
char file_name[20]; 
char file_lines[1000][500];
struct node **array;
int *count_all;
int count=0;
int MPI_rank;
int num_procs;
int **adj_matrix;
//MPI_Comm_size(MPI_COMM_WORLD,&MPI_rank);
_EXTERN_C_ void pmpi_init(MPI_Fint *ierr);
_EXTERN_C_ void PMPI_INIT(MPI_Fint *ierr);
_EXTERN_C_ void pmpi_init_(MPI_Fint *ierr);
_EXTERN_C_ void pmpi_init__(MPI_Fint *ierr);

	
/* ================== C Wrappers for MPI_Init ================== */
_EXTERN_C_ int PMPI_Init(int *argc, char ***argv);
_EXTERN_C_ int MPI_Init(int *argc, char ***argv) { 
    int _wrap_py_return_val = 0;
 {
//struct node = {0,0,0};
//struct node node_instance;
//node_instance =(struct node) (NULL,0,0,0,0,0.0,0.0);
array=(struct node**)malloc(100*sizeof(struct node*));
int i;
for(i=0;i<100;i++)
{
	array[i]=(struct node*)malloc(400*sizeof(struct node));
}


//MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
double start_time = MPI_Wtime();
_wrap_py_return_val = PMPI_Init(argc, argv);
//struct node node_instance;
//node_instance =(struct node) (NULL,0,0,0,0,0.0,0.0);
MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
count_all=(int *)malloc(num_procs*sizeof(int));


 

MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Init";
int source=0;
int dest=0;
int tag=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t ",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
sleep(1);
printf("MPI_Init took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp,"0\n");
fclose(fp);

//printf("Trying to get num_workers %d\n", MPI_rank);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Send ================== */
_EXTERN_C_ int PMPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
_EXTERN_C_ int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {

double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Send(buf, count, datatype, dest, tag, comm);
MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Send";
int source=0;


sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t ",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Send took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
MPI_Datatype name1=MPI_INT;
MPI_Datatype name2=MPI_FLOAT;
MPI_Datatype name3=MPI_DOUBLE;

if ((datatype==name1) || ((datatype==name2))) {
	        fprintf(fp, "%d\n", count*4);
}
else if ((datatype==name3)) {
	 fprintf(fp, "%d\n", count*8);
}

fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Recv ================== */
_EXTERN_C_ int PMPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
_EXTERN_C_ int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { 
    int _wrap_py_return_val = 0;
 {

double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Recv(buf, count, datatype, source, tag, comm, status);
MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Recv";
int dest=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t ",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Recv took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t ",start_time,end_time);
MPI_Datatype name1=MPI_INT;
MPI_Datatype name2=MPI_FLOAT;
MPI_Datatype name3=MPI_DOUBLE;
if ((datatype==name1) || ((datatype==name2))) {
	        fprintf(fp, "0\n");
}
else if ((datatype==name3)) {
	 fprintf(fp, "0\n");
}


fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Barrier ================== */
_EXTERN_C_ int PMPI_Barrier(MPI_Comm comm);
_EXTERN_C_ int MPI_Barrier(MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Barrier(comm);
char rank[20];
int source=0;
int dest=0;
int tag=0;
char func_name[20]="MPI_Barrier";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Barrier took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");


fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Alltoall ================== */
_EXTERN_C_ int PMPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
_EXTERN_C_ int MPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
char rank[20];
int source=0;
int dest=0;
int tag=0;
char func_name[20]="MPI_Alltoall";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Alltoall took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");

fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Scatter ================== */
_EXTERN_C_ int PMPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
_EXTERN_C_ int MPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
char rank[20];
int source=root;
int dest=0;
int tag=0;
char func_name[20]="MPI_Scatter";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Scatter took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");
fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Gather ================== */
_EXTERN_C_ int PMPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
_EXTERN_C_ int MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
char rank[20];
int source=0;
int dest=root;
int tag=0;
char func_name[20]="MPI_Scatter";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Gather took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");
fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Reduce ================== */
_EXTERN_C_ int PMPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
_EXTERN_C_ int MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
char rank[20];
int source=0;
int dest=root;
int tag=0;
char func_name[20]="MPI_Reduce";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Reduce took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");

fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Allreduce ================== */
_EXTERN_C_ int PMPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
_EXTERN_C_ int MPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
char rank[20];
int source=0;
int dest=0;
int tag=0;
char func_name[20]="MPI_Allreduce";
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s %d %d %d %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Allreduce took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);   
fprintf(fp, "0\n");
fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Isend ================== */
_EXTERN_C_ int PMPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
_EXTERN_C_ int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Isend(buf, count, datatype, dest, tag, comm, request);
MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Isend";
int source=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t ",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Isend took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
MPI_Datatype name1=MPI_INT;
MPI_Datatype name2=MPI_FLOAT;
MPI_Datatype name3=MPI_DOUBLE;
if ((datatype==name1) || ((datatype==name2))) {
	        fprintf(fp, "%d\n", count*4);
}
else if ((datatype==name3)) {
	 fprintf(fp, "%d\n", count*8);
}

fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Irecv ================== */
_EXTERN_C_ int PMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
_EXTERN_C_ int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Irecv(buf, count, datatype, source, tag, comm, request);
MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Irecv";
int dest=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Irecv took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
MPI_Datatype name1=MPI_INT;
MPI_Datatype name2=MPI_FLOAT;
MPI_Datatype name3=MPI_DOUBLE;
if ((datatype==name1) || ((datatype==name2))) {
	        fprintf(fp, "0\n");
}
else if ((datatype==name3)) {
	 fprintf(fp, "0\n");
}

fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Wait ================== */
_EXTERN_C_ int PMPI_Wait(MPI_Request *request, MPI_Status *status);
_EXTERN_C_ int MPI_Wait(MPI_Request *request, MPI_Status *status) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Wait(request, status);
char rank[20];
char func_name[20]="MPI_Wait";
int source=status->MPI_SOURCE;
int dest=0;
int tag=status->MPI_TAG;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Wait took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fprintf(fp, "0\n");
fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Waitall ================== */
_EXTERN_C_ int PMPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses);
_EXTERN_C_ int MPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses) { 
    int _wrap_py_return_val = 0;
 {
double start_time = MPI_Wtime();
 sleep(1);
_wrap_py_return_val = PMPI_Waitall(count, array_of_requests, array_of_statuses);
char rank[20];
char func_name[20]="MPI_Waitall";
int source=array_of_statuses->MPI_SOURCE;
int dest=0;
int tag=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t %d\t %d\t %d\t %d\t",func_name,MPI_rank,source,dest,tag);
double end_time = MPI_Wtime();
printf("MPI_Waitall took %f nanoseconds to run!\n", (end_time - start_time));
fprintf(fp,"%f\t %f\t",start_time,end_time);
fclose(fp);
}
    return _wrap_py_return_val;
}

/* ================== C Wrappers for MPI_Finalize ================== */
_EXTERN_C_ int PMPI_Finalize();
_EXTERN_C_ int MPI_Finalize() { 
    int _wrap_py_return_val = 0;
 {
sleep(1);
double start_time = MPI_Wtime();

MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
_wrap_py_return_val = PMPI_Finalize();
//MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
char rank[20];
char func_name[20]="MPI_Finalize";
int source=0;
int dest=0;
int tag=0;
double end=0;
sprintf(rank,"%d",MPI_rank);
strcpy(file_name,"file");
strcat(file_name,rank);
strcat(file_name,".txt");
printf("Filename is: %s \n",file_name);
FILE *fp;
fp=fopen(file_name,"a");
fprintf(fp,"%s\t  %d\t  %d\t  %d\t  %d\t %f\t %f\t",func_name,MPI_rank,source,dest,tag,start_time,end);
fprintf(fp, "0");


fclose(fp);
if(MPI_rank==0)
{
	int count=0;
	int uniq_cnt=0;
	int j,k,l;
	//FILE *ptr;
	//fopen("file.txt","w");
	for(j=0;j<num_procs;j++)
	{
		char num[20];
		char line[1000];
		int num_lines=0;
		char *temp;
		sprintf(num,"%d",j);
		strcpy(file_name,"file");
		strcat(file_name,num);
		strcat(file_name,".txt");
		printf("Opening filename %s \n",file_name);
		FILE *fp;
		fp=fopen(file_name,"r");
		while(!feof(fp))
		{
			int i=0;
			fgets(line,1000,fp);
			while(isspace(line[i]))
				i++;
			if(!line[i])
				continue;
			else if(strlen(line)==1)
				continue;
			else
			{
				strcpy(file_lines[num_lines],line);
				//printf("%s",file_lines[num_lines]);
				num_lines=num_lines+1;
			}
		}
		for(k=0;k<num_lines;k++)
		{
			temp=(char *)calloc(1,20);
			while(temp != NULL)
			{
				temp=strtok(file_lines[k]," \t\n");
				strcpy((array[j][count].func_name),temp);
				temp=strtok(NULL," \t\n");
				int tmp1=0;
				int len1=strlen(temp);
				for(l=0;l<len1;l++)
				{
					tmp1=tmp1*10+(temp[l]-'0');
				}
				array[j][count].proc_rank=tmp1;
				temp=strtok(NULL," \t\n");
				int tmp2=0;
                                int len2=strlen(temp);
                                for(l=0;l<len2;l++)
                                {
                                        tmp2=tmp2*10+(temp[l]-'0');
                                }
				array[j][count].source=tmp2;
				temp=strtok(NULL," \t\n");
				int tmp3=0;
                                int len3=strlen(temp);
                                for(l=0;l<len3;l++)
                                {
                                        tmp3=tmp3*10+(temp[l]-'0');
                                }
				array[j][count].dest=tmp3;
				temp=strtok(NULL," \t\n");
                		int tmp4=0;
                                int len4=strlen(temp);
                                for(l=0;l<len4;l++)
                                {
                                        tmp4=tmp4*10+(temp[l]-'0');
                                }
				array[j][count].tag=tmp4;
				temp=strtok(NULL," \t\n");
				sscanf(temp,"%lf",&array[j][count].s_time);
				//array[count].s_time=strtof(temp,NULL);
				temp=strtok(NULL," \t\n");
				sscanf(temp,"%lf",&array[j][count].e_time);
				//array[count].e_time=strtof(temp,NULL);
                                temp=strtok(NULL," \t\n");
				int tmp5=0;
				int len5=strlen(temp);
				for(l=0;l<len5;l++)
				{
					tmp5=tmp5*10+(temp[l]-'0');
				}
				array[j][count].num_bytes=tmp5;
				temp=strtok(NULL," \t\n");
			}
			array[j][count].unique_id = uniq_cnt;
			count=count+1;
			uniq_cnt++;
		}
		fclose(fp);
		count_all[j]=count;
		count=0;
	}
	int x,y,x1=0,y1;	
	//sum is the sum of all lines of files
	int sum=0;
	for(x=0;x<num_procs;x++)
	{
		sum=sum+count_all[x];
	}

//allocate matrix for adjacency matrix

	adj_matrix = (int **)malloc( sizeof(int *)* (sum-num_procs*2+2));
	//int x,y;

	for(x=0;x<sum;x++)
	{
			adj_matrix[x]=(int  *)malloc(sizeof(int)*(sum-num_procs*2+2));
	}

	for(x=0;x<(sum-num_procs*2+2);x++)
	{
		for(y=0;y<(sum-num_procs*2+2);y++)
		{
			adj_matrix[x][y]=0;
		}
	}

	for(x=0;x<(sum-num_procs*2+2);x++)
        {
                for(y=0;y<(sum-num_procs*2+2);y++)
                {
                        printf("%d",adj_matrix[x][y]);
                }
		printf("\n");
        }


	// Find the dependency matrix
	int index=0;
	int count_dep;
	int count_x =0;
	int count_y=0;
	 for(x=0;x<num_procs;x++)
        {

   		for(x1=0; x1<count_all[index];x1++){

			if (!strcmp (array[x][x1].func_name ,"MPI_Init") && x!=0){
			printf("I am mpi_int\n");
			continue;		
			}
			if (!strcmp (array[x][x1].func_name ,"MPI_Finalize") && x!=num_procs-1){
				printf("I am mpi_finalize\n");
				break;
			}
   			//loop through all the matrix elements for each row 
			/**********************************/
               	 for(y=0; y<num_procs;y++)
                	{
			
		   	for (y1=0;y1<count_all[y]; y1++){

			if (!strcmp (array[y][y1].func_name ,"MPI_Init") && y!=0){
			//	printf ("hmmm!!!"); 
				continue; 
			}
			if (!strcmp (array[y][y1].func_name ,"MPI_Finalize") && y!=num_procs-1){
				    //  printf ("hmmm!!!, I am done") ;
				      break;
			}
			
				//form a dependency for all the immediate nodes
     if((array[y][y1].proc_rank ==array[x][x1].proc_rank && (!strcmp (array[y][y1].func_name ,"MPI_Send")) && array[y][y1].tag == array[x][x1].tag )){
						if((array[y][y1].dest == array[x][x1].dest)){
							printf("yaaaaaaaaaaay!!! %d%d %s\n", x1, count_y,array[y][y1].func_name );
							if (x1<count_all[index]-2 )
								adj_matrix[count_x][count_y+1]= abs(ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time)) ;
							 if (x1==count_all[index]-2 )
			adj_matrix[count_x][(sum-num_procs*2+2)-1]= abs(ceil(array[num_procs-1][count_all[num_procs-1]].s_time) - ceil(array[x][x1].e_time));
						}
		}
     
     if((array[y][y1].proc_rank ==array[x][x1].proc_rank && (!strcmp (array[y][y1].func_name ,"MPI_Recv")) && array[y][y1].tag == array[x][x1].tag )){
						if((array[y][y1].source == array[x][x1].source)){
						 if (x1<count_all[index]-2 )
							adj_matrix[count_x][count_y+1]= abs(ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time));
						  if (x1==count_all[index]-2 )
		adj_matrix[count_x][(sum-num_procs*2+2)-1]= abs(ceil(array[num_procs-1][count_all[num_procs-1]].s_time) - ceil(array[x][x1].e_time));
							
						}
				
					}
				
     if((array[y][y1].proc_rank ==array[x][x1].proc_rank && (!strcmp (array[y][y1].func_name ,"MPI_Wait")) && array[y][y1].tag == array[x][x1].tag )){
	       if((array[y][y1].unique_id == array[x][x1].unique_id)){
		       if (x1<count_all[index]-2 )
			        adj_matrix[count_x][count_y+1]= (ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time));
		}
      }	
					
       if((array[y][y1].proc_rank ==array[x][x1].proc_rank && (!strcmp (array[y][y1].func_name ,"MPI_Isend")) && array[y][y1].tag == array[x][x1].tag )){
	       if((array[y][y1].unique_id == array[x][x1].unique_id)){
		       if (x1<count_all[index]-2 )
			        adj_matrix[count_x][count_y+1]= abs(ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time)) ;
	       }
	}

	if((array[y][y1].proc_rank ==array[x][x1].proc_rank && (!strcmp (array[y][y1].func_name ,"MPI_Irecv")) && array[y][y1].tag == array[x][x1].tag )){
		 if((array[y][y1].unique_id == array[x][x1].unique_id)){
			 if (x1<count_all[index]-2 )
				 adj_matrix[count_x][count_y+1]= abs(ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time));
		}
	} 

					//end of formaing dependency to all the immediate nodes


					//dependency for MPI_Send
			 if (!strcmp (array[y][y1].func_name ,"MPI_Recv") && (!strcmp (array[x][x1].func_name , "MPI_Send"))){
			if ((array[y][y1].source  == array[x][x1].proc_rank) &&(array[y][y1].tag ==  array[x][x1].tag)&& array[x][x1].dest == array[y][y1].proc_rank )
						adj_matrix[count_x][count_y]=ceil((1.387759*pow(2.718281828,-8)*array[x][x1].num_bytes) + (0.000117252));
					}	

					//dependency for MPI_Isend

		 if (!strcmp (array[y][y1].func_name ,"MPI_Irecv") && (!strcmp (array[x][x1].func_name , "MPI_Isend"))){
		if ((array[y][y1].source  == array[x][x1].proc_rank) &&(array[y][y1].tag ==  array[x][x1].tag)&& array[x][x1].dest == array[y][y1].proc_rank )
						 adj_matrix[count_x][count_y]= ceil((1.387759*pow(2.718281828,-8)*array[x][x1].num_bytes) + (0.000117252));
					}
					

							
				 //find the dependecy from Init to all the MPI functions
				 if (!strcmp (array[x][x1].func_name , "MPI_Init" ) && y1==1 ){
					adj_matrix[count_x][count_y]= abs(ceil(array[y][y1].s_time) - ceil(array[x][x1].e_time));
					
				}
				 if (!strcmp (array[x][x1].func_name , "MPI_Finalize" ) && y1==count_all[y]-2 ){
					 adj_matrix[count_x][count_y]= abs(ceil(array[y][y1].e_time) - ceil(array[x][x1].s_time));
				} 
					
   	 
				
				 	count_y++;
	          	 }	
			  		  
						   
			}/*******************************/
	count_y=0;
	count_x++;
	} // Covers for each process
	index++;
		
	} //End of Dependency matrix

	index=0;
	count_x =0;
	count_y=0;
	//function to find the critical path
	struct node* crit_node_array;
	crit_node_array = (struct node *)malloc(sizeof(struct node)*sum);
	int citical_path(struct node* mpi_node ){

	for(x=0;x<num_procs;x++){
		for(x1=0; x1<count_all[index];x1++){
			if (!strcmp (array[x][x1].func_name ,"MPI_Init") && x!=0){
				continue;
			}
			if (!strcmp (array[x][x1].func_name ,"MPI_Finalize") && x!=num_procs-1){
				break;
			}
			for(y=0; y<num_procs;y++){
				for (y1=0;y1<count_all[y]; y1++){
					if (!strcmp (array[y][y1].func_name ,"MPI_Init") && y!=0){
						continue;
					}
					if (!strcmp (array[y][y1].func_name ,"MPI_Finalize") && y!=num_procs-1)
						break;
			
						if (array[x][x1].func_name == "MPI_Finalize")
							return;
							
						if (adj_matrix[count_x][count_y])
						citical_path(&array[y][y1]);	
				

				count_y++;
				} 
			}
			count_y=0;
			count_x++;
		}
		index++;
	} 
	} //end of critical path


//function to find the critical path

	int *nodes;
	int array_size=0;
        nodes=(int *)calloc((sum-num_procs*2+2),sizeof(int));
	
	int *max_array;
	max_array=(int *)calloc((sum-num_procs*2+2),sizeof(int));
	//x=(sum-num_procs*2+2);
	void critical_path(int x)
	{
		if(x==((sum-num_procs*2+2)-1))
		{
			//int maximum=0;
			nodes[index]=x;
			int w;
			for(w=0;w<(sum-num_procs*2+2);w++)
			{
				maximum=maximum+max_array[w];
			}
		}
		else
		{
		max=adj_matrix[x][0];
                for(x1=0; x1<(sum-num_procs*2+2);x1++)
		{	
			if(adj_matrix[x][x1]>max)
			{
				max=adj_matrix[x][x1];
				column=x1;
				printf("Maximum is= %d\n",max);
			}
		}
		nodes[index]=x;
		array_size++;
		max_array[index]=max;
		index++;
		critical_path(column);
		}
	}
	x=0;
	critical_path(x);
	printf("Critical path value is %d\n",maximum);
	
	
	
	// Create the task graph from the dependency matrix
	FILE *dot_fp;
	dot_fp = fopen("taskgraph.dot", "w");
	int i;
	index=0;
	char rank[20];
	char string[20];
	char string1[20];
	count_x=0;
	count_y=0;
	fprintf(dot_fp, "digraph taskgraph {\n");
	
	
	for(x=0;x<num_procs;x++)
    	{
	
	   for(x1=0; x1<count_all[index];x1++){
		
		if (!strcmp (array[x][x1].func_name ,"MPI_Init") && x!=0){
			continue;		
			}
			if (!strcmp (array[x][x1].func_name ,"MPI_Finalize") && x!=num_procs-1){
				break;
			}
   			
			//loop through all the matrix elements for each row 
			
       	        	 for(y=0; y<num_procs;y++)
                	{
				for (y1=0;y1<count_all[y]; y1++){
				     if (!strcmp (array[y][y1].func_name ,"MPI_Init") && y!=0){
					continue; 
					}
					if (!strcmp (array[y][y1].func_name ,"MPI_Finalize") && y!=num_procs-1){
					break;
					}
						
						if(adj_matrix[count_x][count_y]){
						
							sprintf(rank, "%d",count_x);
							strcpy(string1, array[x][x1].func_name );
							strcat(string1, rank );
							fprintf( dot_fp, "%s" ,string1);
				       		fprintf( dot_fp, "[label=\"");
							fprintf( dot_fp, "%s", array[x][x1].func_name);
							fprintf(dot_fp, "\"]\n");
							fprintf(dot_fp ,"\n");
							sprintf(rank, "%d",count_y);
							strcpy(string, array[y][y1].func_name );
							strcat(string, rank );
							fprintf( dot_fp, "%s" ,string);
							fprintf( dot_fp, "[label=\"");
							fprintf( dot_fp, "%s", array[y][y1].func_name);
							fprintf(dot_fp, "\"]\n");
							fprintf(dot_fp ,"\n"); 
													
					
							//create an edge
if (strcmp(array[x][x1].func_name, "MPI_Finalize" ) && !(!strcmp(array[x][x1].func_name, "MPI_Send") &&(!strcmp(array[y][y1].func_name, "MPI_Recv")))  && !(!strcmp(array[x][x1].func_name, "MPI_Isend") &&(!strcmp(array[y][y1].func_name, "MPI_Irecv")))){ 
							
							fprintf( dot_fp, "%s",string1 );
							fprintf(dot_fp, " -> ");
							fprintf( dot_fp, "%s",string );
							fprintf( dot_fp, "[label=\"");
							sprintf(rank, "%d",adj_matrix[count_x][count_y]);
							fprintf(dot_fp, "%s", rank);
							fprintf(dot_fp, "\"]\n");
							}
if ((!strcmp(array[x][x1].func_name, "MPI_Send") &&(!strcmp(array[y][y1].func_name, "MPI_Recv"))) || ((!strcmp(array[x][x1].func_name, "MPI_Isend"))&&(!strcmp(array[y][y1].func_name, "MPI_Irecv"))) )        
                            {                           
								fprintf( dot_fp, "%s",string1 );
								fprintf(dot_fp, " -> ");
								fprintf( dot_fp, "%s",string );								
								fprintf( dot_fp, "[label=\"");
        				        sprintf(rank, "%d",adj_matrix[count_x][count_y]);
                                fprintf(dot_fp, "%s", rank);
                                fprintf(dot_fp, "(");
                                sprintf(rank, "%d",array[x][x1].num_bytes);
                                fprintf(dot_fp, "%s", rank);
                                fprintf(dot_fp, ")", rank);
                                fprintf(dot_fp, "\"]\n");	
		
							}
						
						if (!strcmp(array[x][x1].func_name, "MPI_Finalize" ) ){
								printf("hmmmmmm!!");
								 fprintf( dot_fp, "%s",string );
								 fprintf(dot_fp, " -> ");
								 fprintf( dot_fp, "%s",string1 );
								 fprintf( dot_fp, "[label=\"");
								 sprintf(rank, "%d",adj_matrix[count_x][count_y]);
								 fprintf(dot_fp, "%s", rank);
								 fprintf(dot_fp, "\"]\n");
								 
							}

						} 
						count_y++;
					}	
		}
		count_y=0;
		count_x++;
	}
		index++;
	   
   }
	
	fprintf(dot_fp,"}\n");
	fclose(dot_fp);	
	
	fprintf(dot_fp,"}\n");
	fclose(dot_fp);	
	
	
	//create a file to output critical path
	FILE *crit_fp;
	crit_fp = fopen("critical_path.txt", "w");
	index=0;
	int node_cnt=0;

	for(x=0;x<num_procs;x++){
		for(x1=0; x1<count_all[index];x1++){

		if (!strcmp (array[x][x1].func_name ,"MPI_Init") && x!=0){
			printf("I am mpi_int\n");
			continue;		
			}
			if (!strcmp (array[x][x1].func_name ,"MPI_Finalize") && x!=num_procs-1){
				printf("I am mpi_finalize\n");
				break;
			}
			
			for(y=0; y<num_procs;y++){
		   		for (y1=0;y1<count_all[y]; y1++){

				if (!strcmp (array[y][y1].func_name ,"MPI_Init") && y!=0){
				continue; 
				}
				if (!strcmp (array[y][y1].func_name ,"MPI_Finalize") && y!=num_procs-1){
				break;
				}

				if (array[y][y1].unique_id == nodes[node_cnt] && array_size>=0){
				fprintf(crit_fp, "%s\t", array[y][y1].func_name);	
				sprintf(rank, "%d",array[y][y1].proc_rank);
                                fprintf(dot_fp, "%s\t", rank);
				sprintf(rank, "%d",ceil(array[y][y1].e_time - array[y][y1].s_time));
				fprintf(dot_fp, "%s\n", rank);
				node_cnt++;
				array_size--;
				}
	
			}

		}
		index++;
	}

  }
	fclose(crit_fp);
	//print adjacent matrix again

	printf("\n\n\n");
	for(x=0;x<(sum-num_procs*2+2);x++)
	{
		 for(y=0;y<(sum-num_procs*2+2);y++)
		{
			 printf("%d",adj_matrix[x][y]);
		}
		 printf("\n");
	}
	
	 
	// print all the MPI funx from array of structures
	int a,b;
	int m,n;
	for(a=0;a<num_procs;a++)
	{
		for(b=0;b<count_all[a];b++)
		{
			printf("Name is %s\t",array[a][b].func_name);
			printf("Rank is %d\t",array[a][b].proc_rank);
			printf("Source is %d\t",array[a][b].source);
			printf("Destination is %d\t",array[a][b].dest);
			printf("Tag is %d\t",array[a][b].tag);
			m = ceil(array[a][b].s_time);
			n = ceil(array[a][b].e_time);
			printf("Start time is %d\t",m);
			printf("End time is %d\n",n);
		}
	}
	
}


double end_time = MPI_Wtime();
//printf("MPI_Finalize took %d nanoseconds to run!\n", ceil(end_time - start_time));
}
    return _wrap_py_return_val;
}
