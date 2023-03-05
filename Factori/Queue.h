#pragma once

#ifndef _QUEUE_H_
#define _QUEUE_H_



// ** STRUCTS **
typedef struct {
	int front,rear,priority;
} Queue_struct;

// ** QUEUE FUNCTIONS **

Queue_struct* InitializeQueue(int tasks_num);

int Top(Queue_struct* queue);

void Pop(Queue_struct* queue);

void Push(Queue_struct* queue,int priority);

int Empty(Queue_struct* queue);

void DestroyQueue(Queue_struct** pointer_queue);

#endif // _QUEUE_H