#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include "HardCodedData.h"
#include"function.h"
#include "ThreadManage.h"
#include "Queue.h"
#include <tchar.h>

/* ***** GLOBAL VARIABLES ***** */
HANDLE* p_threads_handles = NULL;
int* number_of_bytes_in_each_line_tasks;
int* number_of_bytes_in_each_line_priority;
THREAD_Arguments* Thread;
LPDWORD thread_id;

/* ***** STATIC ******* */
static LPCTSTR P_COUNT_MUTEX_NAME = _T("Excercise_Named_Mutex__MutexForWriteToTasksFile");








/***** FUNCTIONS *****/
DWORD WINAPI Factorization(THREAD_Arguments* Thread)
{
	DWORD ptr;
	HANDLE tasks_handle = NULL;
	char* buffer;
	int the_number;
	int elements_number;
	char* the_final_string;
	int* factorized;
	int start_byte = Thread->start_byte_number_to_read;
	char* tasks_path_string = Thread->tasks_path;
	int number_of_bytes_to_read = Thread->number_of_bytes_to_read;
	printf("aaaa");
	tasks_handle = create_file_for_reading_and_chick_if_succeded(tasks_path_string);
	buffer = (char*)malloc(number_of_bytes_to_read* sizeof(char));
	ptr = SetFilePointer(tasks_handle, start_byte, NULL, FILE_BEGIN);
	reading_file_by_number_of_bytes(tasks_handle, buffer, number_of_bytes_to_read, &ptr);
	the_number = string_to_int(buffer);
	factorized=factorization_of_int(the_number,&elements_number);
	the_final_string = combine_the_whole_elements(the_number, factorized,elements_number);
	printf("%s", the_final_string);		
	
	return STATUS_CODE_SUCCESS;
}








int thread_manage(char* Path_of_tasks, char* Path_of_priority, char* Num_lines, char* threads)
{
	Queue_struct* Queue;
	int num_of_lines, i, number_of_byte_in_Tasks, number_of_byte_in_priority;
	HANDLE file_priority_handler;
	DWORD ptr;
	int sum = 0, line;
	char* buffer;
	int priority, thread_number, number_of_bytes_to_read;
	thread_number = string_to_int(threads);
	num_of_lines = string_to_int(Num_lines);
	int	num_thread_available;
	HANDLE mutex_handle = NULL;
	
	if (thread_number <= 0) // Check if number of threads is positive
	{
		printf("Number Of Thread is NOT positive!\n");
		return STATUS_CODE_FAILURE;
	}
	else
	{
		number_of_bytes_in_each_line_priority = (int*)malloc(num_of_lines* sizeof(int));
		number_of_bytes_in_each_line_tasks = (int*)malloc(num_of_lines* sizeof(int));
		if ((NULL == number_of_bytes_in_each_line_priority) || (NULL == number_of_bytes_in_each_line_tasks))
		{
			printf("ALLOCATION FAILED");
			return STATUS_CODE_FAILURE;
		}
		p_threads_handles = (HANDLE*)malloc((thread_number) * sizeof(HANDLE)); // array of thread handles with size of number threads given
		Thread = (THREAD_Arguments*)malloc((thread_number) * sizeof(THREAD_Arguments)); // array of threads with size of number threads 
		thread_id = (LPDWORD)malloc((thread_number) * sizeof(LPDWORD));
		if ((NULL == Thread) || (NULL == p_threads_handles) || (NULL == thread_id) || (NULL == number_of_bytes_in_each_line_priority)) // check if memory allocation is done 
		{
			printf("Fatal error: Memory Allocation FAILED!\n");
			return STATUS_CODE_FAILURE;
		}
		else
		{
			count_the_number_of_bytes(Path_of_tasks, number_of_bytes_in_each_line_tasks);
			count_the_number_of_bytes(Path_of_priority, number_of_bytes_in_each_line_priority);//
			file_priority_handler = create_file_for_reading_and_chick_if_succeded(Path_of_priority);
			Queue = InitializeQueue(num_of_lines);
			for (i = 0; i < num_of_lines; i++)
			{
				buffer = (char*)malloc((number_of_bytes_in_each_line_priority[i] + 1) * sizeof(char));//+1 for '\0'
				reading_file_by_number_of_bytes(file_priority_handler, buffer, (number_of_bytes_in_each_line_priority[i]), &ptr);
				priority = string_to_int(buffer);//3 parameter of thread
				Push(Queue, priority);
	
			}
			
			mutex_handle = CreateMutex(
				NULL,					/* default security attributes */
				FALSE,					/* initially not owned */
				P_COUNT_MUTEX_NAME);	/* named mutex */

			if (NULL == mutex_handle)
			{
				printf("Error when creating mutex: %d\n", GetLastError());
				return ERROR_CODE;
			}
			for (i = 0; i < thread_number; i++)
			{
				if (Empty(Queue) == 1) /// when thread num > size of queue
				{
					// ????? wait for whaaatttt
					break;
				}

				line = give_me_the_line(Top(Queue), number_of_bytes_in_each_line_tasks, num_of_lines);// 5 parameterof thread
				number_of_bytes_to_read = (number_of_bytes_in_each_line_tasks[line]);
				Thread[i].tasks_path = Path_of_tasks;
				Thread[i].number_of_bytes_to_read = number_of_bytes_to_read;
				Thread[i].start_byte_number_to_read = Top(Queue);
				printf("Top is : %d\n", Top(Queue));
				Pop(Queue);
				p_threads_handles[i] = CreateThreadSimple(Factorization, &thread_id[i], &Thread[i], i);
			}
			while (!Empty(Queue))
			{
				num_thread_available =available_thread(p_threads_handles,thread_number);
				line = give_me_the_line(Top(Queue), number_of_bytes_in_each_line_tasks, num_of_lines);// 5 parameterof thread
				number_of_bytes_to_read = (number_of_bytes_in_each_line_tasks[line]);
				Thread[num_thread_available].tasks_path = Path_of_tasks;
				Thread[num_thread_available].number_of_bytes_to_read = number_of_bytes_to_read;
				Thread[num_thread_available].start_byte_number_to_read = Top(Queue);
				Pop(Queue);
				p_threads_handles[num_thread_available] = CreateThreadSimple(Factorization, &thread_id[num_thread_available], &Thread[num_thread_available], 1);
			}
			//close_threads(thread_number);	/* Close thread handles and check if closing succeeded */
		}
	}
	return STATUS_CODE_FAILURE;
}



int available_thread(HANDLE* p_threads_handles,int threads_number) 
{
	int i;
	for (i = 0; i < threads_number; i++)
	{
		
		if (WaitForSingleObject(p_threads_handles[i], 0) == WAIT_OBJECT_0) //The state of the specified object is signaled.
		{
			return i;
		}
		if (i == threads_number - 1)
		{
			i = 0;
		}
	}
	return 0;
}






void close_threads(int thread_num) {
	int ret_status = STATUS_CODE_SUCCESS;
	for (int i = 0; i < thread_num; i++)
	{
		if (CloseHandle(p_threads_handles[i]) == FALSE)/*closing all handles of threads*/
		{
			ret_status = STATUS_CODE_FAILURE;
		}
	}
	if (ret_status == STATUS_CODE_FAILURE)
	{
		printf("Error while closing Threads%d\n", GetLastError());
		exit(ERROR_CODE);
	}
}






static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPDWORD p_thread_id, THREAD_Arguments* thread_arg_p, int thread_idx)
{
	HANDLE thread_handle = NULL;
	if (NULL == p_start_routine)
	{
		// Should not get here
		// freee threads !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
		printf("Error when creating a Thread\n");
		printf("Received null routine pointer\n");
		exit(ERROR_CODE);
	}
	if (NULL == p_thread_id)
	{
		// Should not get here
		printf("Error when creating a Thread\n");
		printf("Received null id pointer\n");
		exit(ERROR_CODE);
	}
	thread_handle = CreateThread(
		NULL,            /*  default security attributes */
		0,               /*  use default stack size */
		p_start_routine, /*  thread function */
		thread_arg_p,    /*  argument to thread function */
		0,               /*  use default creation flags */
		p_thread_id);    /*  returns the thread identifier */

	if (NULL == thread_handle)
	{
		printf("Couldn't create Thread\n");
		
		exit(ERROR_CODE);
	}
	
	return thread_handle;
}
