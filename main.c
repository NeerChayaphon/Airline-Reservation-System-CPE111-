#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char number[64];
    char input[64];
    int i = 0;
    
    while (1)
    {
        number[i] = 0;
        printf("\nPlease enter your fight number(1-20): ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",number);
        
        printf("%lu\n",strlen(number));
        if (strlen(number) == 2)
        {
            for (i = 0; i <= 2; i++)
            {
                if ((isdigit(number[0]) == 1))
                {
                    if (number[0] == '1')
                    {
                        if (isdigit(number[1]) == 1)
                        {
                            exit(1);
                        }
                        else
                        {
                            printf("1 Sorry you should input fight number 1 to 20\n");
                            break;
                        }
                    }
                    else if (number[0] == '2')
                    {
                        if((number[1] == '0') || (number[1] == '\0'))
                        {
                            exit(2);
                        }
                        else
                        {
                            printf("2 Sorry you should input fight number 1 to 20\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("3 Sorry you should input fight number 1 to 20\n");
                        break;
                    }
                }
                else
                {
                    printf("4 Sorry you should input fight number 1 to 20\n");
                    break;
                }
            }
        }
        else if (strlen(number) == 1)
        {
            if (number[0] == '0')
            {
                printf("5 Sorry you should input fight number 1 to 20\n");
            }
            else
            {
                if (isdigit(number[0]) == 1)
                {
                    exit(4);
                }
                else
                {
                    printf("6 Sorry you should input fight number 1 to 20\n");
                }
            }
        }
        else
        {
            printf("7 Sorry you should input fight number 1 to 20\n");
        }
    }
    return 0;
}


