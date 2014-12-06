#include <stdio.h>
#include <string.h>
#define MEMORY 2048
#define MAX_COMANDS 2048

char* openFile(char* filename)
{
    FILE *f;
    char* str;
    f = fopen(filename,"r");
    fgets (str, MAX_COMANDS, f);
    fclose(f);
    return str;
}
void interp(char* commands)
{
    char memory[MEMORY]= {0};
    int counter = 0;
    int i;
    for (i = 0; i < strlen(commands); i++ )
    {
        switch (commands[i])
        {
        case '>':
            if(counter<MEMORY)
                counter++;
            else
            {
                printf("Out of memory");
                return 0;
            }
            break;
        case '<':
            if(counter>0)
                counter--;
                        else
            {
                printf("Conter index below zero");
                return 0;
            }
            break;
        case '+':
            memory[counter]++;
            break;
        case '-':
            memory[counter]--;
            break;
        case '.':
            putchar(memory[counter]);
            break;
        case ',':
            memory[counter] = getchar();
            break;
        case '[':
            if (memory[counter] == 0)
            {

                int brackets = 0;
                int j;
                for (j = i + 1; j < strlen(commands); j++)
                {
                    if (commands[j] == '[') brackets++;
                    if (commands[j] == ']' && brackets == 0)
                    {
                        i = j;
                        break;
                    }
                    if (commands[j] == ']' && brackets != 0) brackets--;
                }
            }
            break;
        case ']':
            if (memory[counter] != 0)
            {

                int brackets = 0;
                int j;
                for (j = i-1; j > 0; j--)
                {
                    if (commands[j] == ']') brackets++;
                    if (commands[j] == '[' && brackets == 0)
                    {
                        i = j;
                        break;
                    }
                    if (commands[j] == '[' && brackets != 0) brackets--;
                }

            }
            break;
        }
    }
}
int main(int arc, char **argv)
{
    if(arc<=1) // no parameters - paste and execute code
    {
    char commands[MAX_COMANDS];
    scanf("%s",commands,MAX_COMANDS);
    interp(commands);
    }
    if(arc==2) // parameter - file
    {
        interp(openFile(argv[1]));
    }
    return 0;
}
