#define _CRT_SECURE_NO_WARNINGS
#define BOOL char
#define FALSE 0
#define TRUE 1
#include <string.h>
#include <stdio.h>

//adding procedure
void add() {
    int nums;
    printf("%s", "how many numbers (1000 max)? ");
    scanf("%d", &nums) == 0;
    float numbers[1000];
    for (int i = 0; i < nums; i++)
       {
        printf("%s", "add what number? ");
        scanf("%f", &numbers[i]);
       }

    float sum;
    sum = 0;
    for (int i = 0; i < nums; i++)
    {
        sum = sum + numbers[i];
    }

    printf("the total is %f", sum);
    printf("\n\n\n\n");
    return 0;





}

//multiply procedure
void multiply() {
    int nums;
    printf("%s", "how many numbers (1000 max)? ");
    scanf("%d", &nums) == 0;
    float numbers[1000];
    for (int i = 0; i < nums; i++)
    {
        printf("%s", "multply what number? ");
        scanf("%f", &numbers[i]);
    }

    float sum;
    sum = 1;
    for (int i = 0; i < nums; i++)
    {
        sum = sum * numbers[i];
    }

    printf("the total is %f", sum);
    printf("\n\n\n\n");
    return 0;





}


//subtract procedure
void subtract() {
    int nums;
    printf("%s", "how many numbers (1000 max)? ");
    scanf("%d", &nums) == 0;
    float numbers[1000];
    printf("%s", "what is the first number (#the one that will be taken away from)? ");
    scanf("%f", &numbers[0]);
    for (int i = 1; i < nums; i++)
    {
        printf("%s", "subtract what number? ");
        scanf("%f", &numbers[i]);
    }

    float sum;
    sum = numbers[0];
    for (int i = 1; i < nums; i++)
    {
        sum = sum - numbers[i];
    }

    printf("the total is %f", sum);
    printf("\n\n\n\n");
    return 0;





}
//dividing procedure
void divide()
{
        int nums;
        printf("%s", "how many numbers (1000 max)? ");
        scanf("%d", &nums) == 0;
        float numbers[1000];
        printf("%s", "what is the first number (#the one that will be divided away from)? ");
        scanf("%f", &numbers[0]);
        for (int i = 1; i < nums; i++)
        {
            printf("%s", "divided by what number? ");
            scanf("%f", &numbers[i]);
        }

        float sum;
        sum = numbers[0];
        for (int i = 1; i < nums; i++)
        {
            sum = sum /  numbers[i];
        }

        printf("the total is %f", sum);
        printf("\n\n\n\n");
        return 0;



}


int main()
{
    while (1) {
        char result[200];
        printf("name: ");
        (scanf_s("%s", result, sizeof(result)) == 1);
        printf("hi ");
        printf("%s\n", result);
        printf("%s\n", "welcome to your calculator app");
        char choice[2];
        printf("what would you like to do? ");
        (scanf_s("%s", choice, sizeof(choice)) == 1);
        char* plus = "+";
        char* sub = "-";
        int check, checksub, checkexit, checkdiv, checkmultiply;
        char* multi = "*";
        char* exit = "e";
        char* div = "/";
        check = strcmp(plus, choice);
        checksub = strcmp(sub, choice);
        checkexit = strcmp(exit, choice);
        checkdiv = strcmp(div, choice);
        checkmultiply = strcmp(multi, choice);

        
        if (checkexit == 0)
        {
            break;
        }

        if (check == 0) {
            printf("%s\n", "add mode starting now");
            printf("\n\n");
            add();
        }

        if (checkdiv == 0) {
            printf("%s\n", "starting dividing mode now");
            printf("\n\n");
            divide();
        }

        if (checkmultiply == 0)
        {
            printf("%s\n", "starting multiply mode now");
            printf("\n\n");
            multiply();

        }


        if (checksub == 0) {
            printf("%s\n", "subtract mode starting now");
            printf("\n\n");
            subtract();
        }
        


    }

    return 0;
}
