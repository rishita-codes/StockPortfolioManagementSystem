#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"holdings_ops.h"
#include "trend.h"
#define DASHES puts("-----------------------------------------------------------------------------------------");
/*
Structure: stock
----------------------
Represents stock transaction data
t_id: transaction id
uname: user's username
symbol: stock symbol
qty: quantity of stock
price: price of each stock
type: type of transaction (BUY or SELL)
dot: date of transaction
*/
typedef struct stock{
    int t_id;
    char uname[48];
    char symbol[20];
    int qty;
    float price;
    char type[5];
    struct date{
        int d,m,y;
    }dot;
}stock;

int remove_trans(char uname[48]);
int update_trans(char uname[48]);
/*
Function: remove_trans
----------------------
Allows user to remove a transaction by accepting transaction id
Parameters: 
    uname: a string containing the user's username
Returns: 
    int: 1 on success, -1 if unable to open file, 0 if user wants to go back
*/
int remove_trans(char uname[48])
{
    stock s;
    FILE* fp=fopen("transaction.dat","r");
    FILE* fp2=fopen("temp.dat","w");
    if(fp==NULL || fp2==NULL)
        return -1;
    int id,f=0,a=1,b=1,c=1;
    char ch;
    printf("ENTER TRANSACTION ID (ENTER 0 TO GO BACK TO MENU AND CHECK TRANSACTION ID): ");
    scanf("%d",&id);
    if(id==0)
        return 0;
    getchar();
    while(fscanf(fp,"%d %s %s %d %f %s %d %d %d",&s.t_id,s.uname,s.symbol,&s.qty,&s.price,s.type,&s.dot.d,&s.dot.m,&s.dot.y)!=EOF)
    {
        if(!strcmp(uname,s.uname) && id==s.t_id)
        {   
            f=1;
            puts("ARE YOU SURE YOU WANT TO DELETE THIS TRANSACTION?");
            DASHES;
            printf("| %9s| %20s| %10s| %12s|  %10s|     %10s|\n","T_ID","SYMBOL","QTY","PRICE","T_TYPE","DOT");
            DASHES;
            printf("|     %05d| %20s| %10d| %12.2f|  %10s|     %02d-%02d-%4d|\n",s.t_id,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
            DASHES;
            printf("ENTER Y FOR YES / ANY OTHER CHARACTER FOR NO: ");
            scanf("%c",&ch);
            if(ch!='y' && ch!='Y')
            {
                f=2;
                break;
            }
            // maintains overall holdings by nullifying the effect of transaction that has to be deleted
            maintain_stock(s.uname, s.symbol, s.qty, s.price, 0); 
            continue;
        }
        fprintf(fp2,"%05d %20s %20s %5d %10.2f %6s  %4d %2d %4d\n",s.t_id,s.uname,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
    }
    fclose(fp);
    fclose(fp2);
    if(f==1)
    {
        a=rename("temp.dat","temp2.dat");
        b=rename("transaction.dat","temp.dat");
        c=rename("temp2.dat","transaction.dat");
    }
    else if(f==0)
        puts("RECORD NOT FOUND. INCORRECT TRANSACTION ID !!!\n");
    if(a==0 && b==0 && c==0)
        puts("TRANSACTION RECORD REMOVED SUCCESSFULLY !!!\n");
    return 1;
}
/*
Function: update_trans
----------------------
Allows user to update a transaction by accepting transaction id
Parameters: 
    uname: a string containing the user's username
Returns: 
    int: 1 on success, -1 if unable to open file, 0 if user wants to go back
*/
int update_trans(char uname[48])
{
    stock s;
    FILE* fp=fopen("transaction.dat","r");
    FILE* fp2=fopen("temp.dat","w");
    if(fp==NULL || fp2==NULL )
        return -1;
    int id,a=1,b=1,c=1,f=0,upd,snum,ch;
    char str[48];
    printf("ENTER TRANSACTION ID (ENTER 0 TO GO BACK TO MENU AND CHECK TRANSACTION ID): ");
    scanf("%d",&id);
    getchar();
    if(id==0)
        return 0;
    while(fscanf(fp,"%d %s %s %d %f %s %d %d %d",&s.t_id,s.uname,s.symbol,&s.qty,&s.price,s.type,&s.dot.d,&s.dot.m,&s.dot.y)!=EOF)
    {
        if(!strcmp(uname,s.uname) && id==s.t_id)
        {   
            puts("THE TRANSACTION RECORD TO BE UPDATED");
            DASHES;
            printf("| %9s| %20s| %10s| %12s|  %10s|     %10s|\n","T_ID","SYMBOL","QTY","PRICE","T_TYPE","DOT");
            DASHES;
            printf("|     %05d| %20s| %10d| %12.2f|  %10s|     %02d-%02d-%4d|\n",s.t_id,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
            DASHES;
            maintain_stock(s.uname, s.symbol, s.qty, s.price, 0);
            f=1;
            char t='\0';
            puts("\nSELECT STOCK SYMBOL FROM THE MENU GIVEN BELOW");
            show_all_symbols();
            puts("***NOTE: HIT ENTER FOR NO CHANGE");
            printf("ENTER STOCK SYMBOL NUMBER : ");
            fgets(str,48,stdin);
            if(str[0]!='\n')
            {
                snum=atoi(str);
                strcpy(s.symbol,symbol_num(snum));
            }
            printf("ENTER QUANTITY : ");
            fgets(str,48,stdin);
            if(str[0]!='\n')
                s.qty=atoi(str);
            printf("ENTER PRICE PER SHARE: ");
            fgets(str,48,stdin);
            if(str[0]!='\n')
                s.price=atof(str);
            while(t!='b'&& t!='B'&& t!='s'&& t!='S'&& t!='\n')
            {
                printf("ENTER TRANSACTION TYPE (B FOR BUY / S FOR SELL): ");
                fgets(str,48,stdin);
                t=str[0];
                if(t!='b'&& t!='B'&& t!='s'&& t!='S'&& t!='\n')
                    printf("!!!INVALID SELECTION!!!\n");
            }
            if(t=='\n')
                t=s.type[0];
            if(t=='b'||t=='B')
            {
                strcpy(s.type,"BUY");
                upd=1;
            }
            else
            {
                strcpy(s.type,"SELL");
                upd=-1;
            }
            printf("ENTER DATE OF TRANSACTION (FORMAT-> DD MM YYYY): ");
            fgets(str,48,stdin);
            if(str[0]!='\n')
                sscanf(str, "%d%d%d",&s.dot.d,&s.dot.m,&s.dot.y);
            fprintf(fp2,"%05d %20s %20s %5d %10.2f %6s  %4d %2d %4d\n",s.t_id,s.uname,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
            maintain_stock(s.uname, s.symbol, s.qty, s.price, upd);
        } 
        else
            fprintf(fp2,"%05d %20s %20s %5d %10.2f %6s  %4d %2d %4d\n",s.t_id,s.uname,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
    }
    fclose(fp);
    fclose(fp2);
    if(f==1)
    {
        a=rename("temp.dat","temp2.dat");
        b=rename("transaction.dat","temp.dat");
        c=rename("temp2.dat","transaction.dat");
    }
    else
        puts("RECORD NOT FOUND. INCORRECT TRANSACTION ID !!!\n");
    if(a==0 && b==0 && c==0)
        puts("TRANSACTION RECORD UPDATED SUCCESSFULLY !!!\n");
    return 1;
}