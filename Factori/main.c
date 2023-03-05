#pragma once 
#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include "HardCodedData.h"
#include"function.h"
#include"ThreadManage.h"
#include"Queue.h"

extern int size;
int main(int argc, char* argv[])
{
	thread_manage(argv[1], argv[2],argv[3], argv[4]);	
	
	
}
