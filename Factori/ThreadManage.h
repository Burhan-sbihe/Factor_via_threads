

#ifndef __THREADMANAGE_H__   
#define __THREADMANAG_H__



int thread_manage(char* argv_1, char* argv_2, char* argv_3, char* argv_4);
static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPDWORD p_thread_id, THREAD_Arguments* thread_arg_p, int thread_idx);
DWORD WINAPI Factorization(THREAD_Arguments* Thread);

void close_threads(int thread_num);
int available_thread(HANDLE* p_threads_handles, int threads_number);

#endif // ____THREADMANAG_H____