#include <stdio.h>

int get_index(int arr[5], int val) //Function that returns if a value is in an array of intigers
{
    
    for (int i = 0; i < 5; i++) 
    {
        if (arr[i] == val) 
        {
            return i;
        }
    }
    return -1;
}

int main() 
{

    char file_name[50];
    FILE *pFile;

    printf("Enter a file name: ");
    scanf("%s", file_name);

    pFile = fopen(file_name, "r");

    char ch;

    int row = 0, col = 0;//Declare two integer variables to keep track of the current row and column in the input file

    int programmers_pref[5][5];//Declare a two-dimensional array to hold the preference list of the programmers

    int departments_pref[5][5];//Declare a two-dimensional array to hold the preference list of the departments

    while ((ch = fgetc(pFile)) != EOF) 
    {
        if ('0' <= ch && ch <= '9') 
        {
            if (col < 5) 
            {
                departments_pref[row][col] = ch - '0';//Assign the current digit to the department preference list at the current row and column
            } else {
                programmers_pref[row][col - 5] = ch - '0';//Assign the current digit to the programmer preference list at the current row and column offset by 5
            }
            if (++row == 5) //If the end of the row is reached
            {
                row = 0;
                col++;
                //Move to the next column and reset the row counter
            }
        }
    }

    int programmer_index, department_index;

    int indeces[5][5];

    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            programmer_index = 5 - get_index(programmers_pref[j], i + 1);//Find index of programmer in preference list
            department_index = 5 - get_index(departments_pref[i], j + 1);//Find index of department in preference list
            indeces[i][j] = programmer_index + department_index;//Assigns both elements to current element
        }
    }
    int matches[5] = {-1, -1, -1, -1, -1};

    int maxPoint = 10, totalMatches = 0;

    while (totalMatches < 5) 
    {

        for (int i = 0; i < 5; i++) 
        {

            for (int j = 0; j < 5; j++) 
            {

                if (indeces[i][j] == maxPoint && matches[i] == -1 && get_index(matches, j) == -1) 
                {
                    matches[i] = j;
                    totalMatches++;
                }
            }
        }
        maxPoint--;
    }

    for (int i = 0; i < 5; i++) 
    {
        printf("Department #%d will get Programmer #%d\n", i + 1, matches[i] + 1);
    }
    fclose(pFile);
    return 0;
}
