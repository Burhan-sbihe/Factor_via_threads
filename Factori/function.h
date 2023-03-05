
#ifndef __FUNCTION_H__   
#define __FUNCTION_H__






////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


/*
Arguments:
1)the number we want to know his factors
2)address of int in order to put in  how many factors there are for the number

Output:
pointer(array) of the allocated memory for the whole elements

Mechanisim of the function:
It is the implemintation of the method that given in the project ,breifly it allocates memory every time we append factor
and in the end we put the number of facors in the adddress that we give in input.
and we arrange the factors by value

*/
int* factorization_of_int(int the_number,int* number_of_elements);




/////////////////////////////////////////////////////////////////////////////////////////////////
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


void turn_int_into_string(int x, char* the_to_be_written);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////







/*this function formats the output line as we givven in examples

Arguments:
1)the number we want to know his factors
2)address of int in order to put in this address how many factors there are for the number

Output :
pointer(array) of the allocated memory for the whole elements

Mechanisim of the function :
It is the implemintation of the method that given in the project, breifly it allocates memory every time we append factor
and in the end we put the number of facors in the adddress that we give in input


*/


char* combine_the_whole_elements(int the_number, int* array_of_factorization, int number_of_elements);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*


Arguments:
1)the path to the file that we want to open and count the number of each line 
2)pointer to array that we want to fill in each cell the number of bytes in each line at the file ,
as example line one is in the first place in the array  

Output :
none 

Mechanisim of the function:
we open the file then we run a counetr  as we get information if the tav is \n we keep this for the line 
and then set counter to 0  repeating until we finish the file  \n w









*/

void count_the_number_of_bytes(char* file_path, int* number_of_bytes_in_each_line);













////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
/*
Arguments:
1)the pointer of sting hat we want to convert to integer

Output :
the number that the string holds no matter how bytes we use the function atoi() 


Mechanisim of the function :
we convert then return the number 




*/

int string_to_int(char* string);




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
This function creates file for reading with function CreateFile()
Argument:
the path of file to be created for reading


Return value:
HANDLE for the File , if not secceded we send an appropiate error messege



Mechanisim of the function:
we use winapi function to open the file and getting handle to this file and if faild we stop the function 

*/

HANDLE create_file_for_reading_and_chick_if_succeded(char* the_path_of_file);




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

This function  gets the specified bytes from the file and put it into buffer


Arguments:
1)handle  of the file to be readed
2)the buffer that we want to put the data that we readed
3)variable that stores how many bytes that have been readed
4)Address that pointer to the line to be readed from the file


Return value:
none.

Mechanisim of the function:
we use winapi function to open the file and getting the number of bytes specified from  this file and if faild we stop the function



*/


void reading_file_by_number_of_bytes(HANDLE handle_for_file, char* buffer, DWORD dwBytesToRead, DWORD* ptr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int give_me_the_line(int the_number_of_byte_to_starttt, int* number_of_bytesss_in_each_line_tasksss, int num_of_linesss);


#endif // __FUNCTION_H__