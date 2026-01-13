#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "add_stock_transaction.h"
#define DASHES_3 puts("---------------------------------------------");
/*
Function: check_stock_price
----------------------
Allows user to check current stock prices
Parameters: void
Returns: 
    int: 0 on success
*/
int check_stock_price()
{
    int n,f=0,i;
    char str[5], symbol[20],ch;
    double cur_price;
    puts("\nSELECT STOCK SYMBOL FROM THE MENU GIVEN BELOW");
    show_all_symbols();
    puts("ENTER THE STOCK SYMBOLS NUMBERS SEPARATED BY SPACES:");
    while(1)
    {
        i=0;
        while((ch=getchar())!=' ' && ch!='\n')
        {
            str[i++]=ch;
        }
        str[i]='\0';
        if(isdigit(str[0]))
        {
            if(f==0)
            {
                DASHES_3;
                printf("| %20s| %20s|\n","STOCK SYMBOL","CURRENT PRICE");
                DASHES_3
                f=1;
            }
            n=atoi(str);
            if(n>=0 && n<=50)
            {
                strcpy(symbol,symbol_num(n));
                cur_price=stock_price(symbol);
                printf("| %20s| %20.2lf|\n",symbol,cur_price);
                DASHES_3;
            }
        }
        if(ch=='\n' && f==1)
                break;
    }
    puts("");
    return 0;
}