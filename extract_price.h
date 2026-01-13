#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "webscraper.h"
/*
Function: stock_price
----------------------
Calls stock_data_scraper() and then extracts the price of stock from stock_data.txt
Parameters:
    uname: a string containing the user's username
Returns:
    float: price of stock if successful, -1 if failed to open file, -2 if stock_data_scraper()
    failed
*/
float stock_price(char symbol[20])
{
    int web=stock_data_scraper(symbol);
    if(web==1)
        return -2;
    FILE* fp=fopen("stock_data.txt","r");
    if(fp==NULL)
    {
        printf("Error: Unable to open file\n");
        return -1;
    }
    char ch,t[2]="0",str[12]="";
    int f=0;
    // sets file pointer to the estimated position after which price will be found in file
    fseek(fp,300,SEEK_SET); 
    while((ch=fgetc(fp))!=EOF)
    {
        if(isdigit(ch) || ch=='.')
        {
            t[0]=ch;
            strcat(str,t); // stores the price in string format in str
            f=1;
        }
        else if(f==1) // if price is obtained then stops reading
            break; 
    }
    float price=atof(str);
    fclose(fp);
    return price;
}