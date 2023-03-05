#pragma warning(disable: 4996)
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include "HardCodedData.h"


////////////////////////////////////////////////////////////////////////////////////////////////
/*
Arguments:
1) number that we want to convert it from int to string
2) the function get pointer to the string that we want to write the translation of the integer into it

Return value:
None

Mechanisim of the function: 
it converts the int to char charecters by function itoa(built in function) then at the last chrecter it appends '\0'

*/

void turn_int_into_string(int x, char* the_to_be_written)
{
	int count = 0;
	itoa(x, the_to_be_written, 10);
	the_to_be_written = the_to_be_written + strlen(the_to_be_written);
	*(the_to_be_written) = '\0';
}

////////////////////////////////////////////////////////////////////////////////////////////////








int* factorization_of_int(int the_number , int* number_of_elements)
{

	int counter = 0, i = 3;
	float root;
	int* array_of_factorization = (int*)malloc(1*sizeof(int));

	if (NULL == array_of_factorization)
	{
		printf("Error while allocating memory");

	}
	else
	{
		if (the_number == 1)
		{
			array_of_factorization[0] = 1;
			counter++;

		}

		while ((the_number % 2) == 0)
		{
			the_number = the_number / 2;
			array_of_factorization[counter] = 2;
			counter++;
			array_of_factorization = (int*)realloc(array_of_factorization, ((counter + 1) * sizeof(int)));
			if (NULL == array_of_factorization)
			{
				printf("Error while allocating memory");

			}
		}
		root = (float)sqrt(the_number);
		while (i <= root)
		{
			if ((the_number % i) == 0)
			{
				the_number = the_number / i;
				array_of_factorization[counter] = i;
				counter++;
				array_of_factorization = (int*)realloc(array_of_factorization,((counter + 1) * sizeof(int)));
				if (NULL ==array_of_factorization)
				{
					printf("Error while allocating memory");

				}
			}
			i = i + 2;
		}

		if (the_number > 2)
		{
			array_of_factorization[counter] = the_number;
			counter++;
			*(number_of_elements) = counter;//
		}
		else
		{
			array_of_factorization = (int*)realloc(array_of_factorization, ((counter) * sizeof(int)));//we reallocate the memory to be less one
			*(number_of_elements) = counter;//here we remember the amount of elements 
		}
		
		
		
		/* ********ARRANGE THE FACTORS********* */
		int temp, i, j;

		for (i = 0; i < *(number_of_elements); i++)
		{
			for (j = 0; j < *(number_of_elements - 1); j++)
			{
				if (array_of_factorization[j] > array_of_factorization[j + 1])
				{
					temp = array_of_factorization[j];
					array_of_factorization[j] = array_of_factorization[j + 1];
					array_of_factorization[j + 1] = temp;

				}
			}
		}
		
		//return array_of_factorization;
	}
	return array_of_factorization;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*this function formats te output line as we givven in examples  

Arguments:
1)the number we want to know his factors
2)address of int in order to put in this address how many factors there are for the number

Output :
pointer(array) of the allocated memory for the whole elements

Mechanisim of the function :
It is the implemintation of the method that given in the project, breifly it allocates memory every time we append factor
and in the end we put the number of facors in the adddress that we give in input


*/
char* combine_the_whole_elements(int the_number,int* array_of_factorization,int number_of_elements)
{
	int i;
	char* the_result;
	char the_string_to_write1[30] = { "The prime factors of " };
	char the_string_to_write2[30] = { " are: " };
	int help_integer;
	char help2[5] = {", "};
	char help3[5] = {"\n"};
	char help_string[50];
	char help_string2[50];
	char* result=NULL;
	//int number_of_elements = strlen(array_of_factorization);
	turn_int_into_string(the_number, help_string2);//we get string of the number
	the_result = (char*)malloc((50+strlen(help_string2))*sizeof(char));// 50 because we want to add constant string so it safe to add 50 because they combined are less than 50
	if (NULL == the_result)
	{
		printf("error");
		printf("aa");
		exit(0);
	}
	else
	{


		*(the_result) = '\0';
		the_result = strcat(the_result, the_string_to_write1);//here we add the first section of the output string
		the_result = strcat(the_result, help_string2);//here we add the number in the output string
		the_result = strcat(the_result, the_string_to_write2);//here we add the second section of the output string

		for (i = 0; i < number_of_elements; i++)
		{



			turn_int_into_string(array_of_factorization[i], help_string);//we use the help_string to change the number from int to char form 
			help_integer = strlen(the_result);
			the_result = (char*)realloc(the_result, (help_integer + strlen(help_string) + 4) * sizeof(char));//we allocates memory for the string of the element
			if(NULL==the_result)
			{
				printf("");
				exit(1);
			}
			else
			{
				result = strcat(the_result, help_string);//here we append every time the factor (string form)
				if (i == number_of_elements - 1)
				{
					the_result = strcat(the_result, help3);
				}
				else
				{
					the_result = strcat(result, help2);
				}

			}
		}
		int x = strlen(the_result);
		the_result = the_result + x;//here we put the pointer of the string at the end in order to add '/0'
		*(the_result) = '\0';
		the_result = the_result - x;
		//free(array_of_factorization);
		return the_result;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////











void count_the_number_of_bytes(char* file_path, int* number_of_bytes_in_each_line)
{
	int counter = 0, new_counter = 0;
	char tav = ' ';
	FILE* the_input;
	fopen_s(&the_input, file_path, "r");
	if (NULL == the_input)
	{
		printf("The file FAILED to open\nCheck if the file is EXICTING\n");
		//free_allocated();
		exit(STATUS_CODE_FAILURE);
	}
	else
	{
		while (feof(the_input) == 0)
		{
			new_counter++;
			if (tav == '\n')
			{
				new_counter++;
				*(number_of_bytes_in_each_line) = counter + 1;
				counter = 0;
				number_of_bytes_in_each_line++;
			}

			tav = fgetc(the_input);
			counter++;
		}
		*number_of_bytes_in_each_line = counter - 1;
		fclose(the_input);
	}
	//return new_counter - 1;
}







int string_to_int(char* string)
{
	int key;
	key = atoi(string);
	return key;
}










HANDLE create_file_for_reading_and_chick_if_succeded(char* the_path_of_file)
{
	HANDLE the_handle_of_file;
	the_handle_of_file = CreateFile(the_path_of_file,  // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING ,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);   // no attr. template

	if (the_handle_of_file == INVALID_HANDLE_VALUE)
	{
		printf("Terminal failure: Unable to open file for read %08x \n", GetLastError());
		exit(STATUS_CODE_FAILURE);
	}
	return the_handle_of_file;
}









void reading_file_by_number_of_bytes(HANDLE handle_for_file, char* buffer, DWORD dwBytesToRead, DWORD* ptr)
{
	BOOL read_sign;
	read_sign = ReadFile(handle_for_file, buffer, dwBytesToRead, (LPDWORD)ptr, NULL);
	if (read_sign == 0)
	{
		printf("READING FILE IS NOT SUCCEDED!\n");
		printf("Program failed! Ending program. Last Error = 0x%x\n", GetLastError());
		//free_allocated();
		exit(STATUS_CODE_FAILURE);
	}
	
}








int give_me_the_line(int the_number_of_byte_to_starttt, int* number_of_bytes_in_each_line_tasksss,int num_of_linesss)
{
	int j, sum = 0,line;
	if (the_number_of_byte_to_starttt == 0)
	{
		return 0;
	}
	for (j = 0; j < num_of_linesss; j++)
	{
		sum = sum + number_of_bytes_in_each_line_tasksss[j];
		if (sum == the_number_of_byte_to_starttt)
		{
			line = j + 1;
			return line;
		}
	}
	return -1;
}
