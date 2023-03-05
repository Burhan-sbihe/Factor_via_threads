#pragma warning(disable: 4996)
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include "HardCodedData.h"
#include"function.h"
#include"Queue.h"

int size;

Queue_struct* InitializeQueue(int tasks_num)
{
	Queue_struct* queue;
	size=0;
	queue = malloc(tasks_num*sizeof(Queue_struct)); // allocate for one element in queue and return its pointer
	if (NULL == queue)
	{
		printf(" MEMORY ALLOCATION FALIED\n");
		exit(ERROR_CODE);
	}
	return queue;
}

void Push(Queue_struct* queue,int priority)
{

	size++;
	if (size == 1)
	{
		queue[size - 1].front = 1;
		queue[size - 1].rear = 1;
		queue[size - 1].priority = priority;
		
	}
	else 
	{
			queue[size - 2].rear = 0;
			queue[size - 1].front = 0;
			queue[size - 1].rear = 1;
			queue[size - 1].priority = priority;
	}

}

int Top(Queue_struct* queue)
{
	return queue->priority; 
}

void Pop(Queue_struct* queue)
{	
	int i;
	if (size > 1)
	{
		for (i = 0; i < size - 1; i++)
		{
			queue[i].front = queue[i + 1].front;
			queue[i].rear = queue[i + 1].rear;
			queue[i].priority = queue[i + 1].priority;
		}
		queue[0].front = 1;
		queue[size - 2].rear = 1;
	}

	queue[size - 1].front = 0;
	queue[size - 1].rear = 0;
	queue[size - 1].priority = 0;
	size--;
}
void DestroyQueue(Queue_struct** pointer_queue)
{
	free(*(pointer_queue));
	*pointer_queue = NULL;
}


int Empty(Queue_struct* queue)
{
	if (size == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}