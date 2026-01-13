#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "graphs.h"
#include "trendscraper.h"
#include "stock_menu.h"

int extract_stock_trend(int n, data* close);
int track_stock();
/*
Function: extract_stock_trend
----------------------
Extracts stock prices of last 15 days which are stored in trend_data.txt and stores them into an array of data (structure for graph)
Parameters: 
    n: number of stock prices to be extracted
    close: pointer to an array of struct data that will store prices
Returns: 
    int: 0 on success, -1 if unable to open file
*/
int extract_stock_trend(int n, data* close)
{
    char ch, str[200*2], t[10];
    FILE* fp=fopen("trend_data.txt","r");
    if(fp==NULL)
        return -1;
    // estimated place where prices would be in file
    fseek(fp,-150*2,2); 
    fscanf(fp,"%s",str); 
    fclose(fp);
    int i=0, j=0, f=0, k, m=0;
    while(str[i]!='\0')
    {
        if(str[i]==':' && str[i+1]=='[' && isdigit(str[i+2]))
        {
            f=1;
            i+=2;
            break;
        }
        i++;
    }
    if(f==1)
    {
        while(str[i]!='\0')
        {
            j=0;
            while(str[i]!='.')
                t[j++]=str[i++];
            t[j++]=str[i++];
            k=1;
            while(k<=4 && isdigit(str[i]))
            {
                t[j++]=str[i++];
                k++;
            }
            t[j]='\0';
            sprintf(close[m].label,"%d",m+1);
            close[m++].y=atof(t);
            while(str[i]!=',' && str[i]!=']')
                i++;
            if(str[i]==']')
                break;
            i++;
        }
    }
    return 0;
}
/*
Function: track_stock
----------------------
Allows user to select a stock symbol and displays its trend using graphical representaion
Parameters: void
Returns: 
    int: 0 on success, 1 if invalid selection is made by user
*/
int track_stock()
{
    int n=15, snum;
    char* symbol;
    data close[n];
    puts("\nSELECT STOCK SYMBOL FROM THE MENU GIVEN BELOW");
    show_all_symbols();
    printf("ENTER STOCK SYMBOL NUMBER: ");
    scanf("%d",&snum);
    getchar();
    if(!(snum>=1 && snum<=50))
    {
        printf("INVALID SELECTION !\n");
        return 1;
    }
    symbol=symbol_num(snum);
    stock_trend_scraper(symbol);
    extract_stock_trend(n,close);
    printf("\n%40s*** %s STOCK- 15-DAY TREND ***\n\n","",symbol);
    graphical(close,n);
    return 0;
}