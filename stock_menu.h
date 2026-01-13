#include<stdio.h>
#include<string.h>

char* symbol_num(int n);
int show_all_symbols();
/*
Function: show_all_symbols
----------------------
Displays a list of stock symbols to the user
Parameters: void
Returns: void
*/
int show_all_symbols()
{
    FILE* fp=fopen("symbols_menu.txt","r");
    int c=1,i,l,n;
    char t[20];
    if(fp==NULL)
        return -1;
    while(fscanf(fp,"%d%s",&n,t)!=EOF)
    {
        if(c>5)
        {
            printf("\n");
            c=1;
        }
        printf("%02d-%s",n,t);
        for(i=strlen(t);i<=20;i++)
            printf(" ");
        c++;   
    }
    printf("\n\n");
    fclose(fp);
    return 0;
}
/*
Function: symbol_num
----------------------
Returns a pointer to the stock symbol that corresponds to the given number
Parameters: 
    n: an interger that stores the stock symbol number
Returns: 
    char*: m/m address at which stock symbol is stored
*/
char* symbol_num(int n)
{
    static char t[20];
    int i,num;
    FILE* fp=fopen("symbols_menu.txt","r");
    if(fp==NULL)
        return NULL;
    if(n<1 || n>50) // since the list only contains 50 stock symbols
        return NULL;
    for(i=1;i<=n;i++)
        fscanf(fp,"%d%s",&num,t);
    fclose(fp);
    return t;
}