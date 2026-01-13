#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"transaction_ops.h"

int add_trans(char uname[48]); 
int view_recs(char* uname); 
/*
Function: add_trans
----------------------
Adds a record of stock transaction under the given username 
Parameters:
    uname: a string containing the user's username
Returns:
    int: 1 if unable to open "transaction.dat" file, 0 if file opened and record added successfully
*/
int add_trans(char uname[48])
{
    char ch='y'; // intialized with 'y' to make loop run atleast once
    FILE* fp;
    fp=fopen("transaction.dat","a"); // opens file containing transaction records of users
    if(fp==NULL)
    {
        puts("FAILED TO OPEN THE FILE.\n");
        return 1;
    }
    int upd, snum; // upd: parameter for maintain_stock function, snum: stock symbol number
    while(ch=='y'|| ch=='Y')
    {
        char t=0;
        stock s;
        strcpy(s.uname, uname); 
        s.t_id=rand(); // generates a random no. for transaction id
        puts("\nSELECT STOCK SYMBOL FROM THE MENU GIVEN BELOW"); 
        show_all_symbols(); // displays a list of stock symbols to select from
        printf("ENTER STOCK SYMBOL NUMBER: ");
        scanf("%d",&snum);
        strcpy(s.symbol,symbol_num(snum));
        printf("ENTER QUANTITY: ");
        scanf("%d",&s.qty);
        printf("ENTER PRICE PER SHARE: ");
        scanf("%f",&s.price);
        while(t!='b'&& t!='B'&& t!='s'&& t!='S') // until a valid choice is not made
        {
            getchar(); // to consume newline char
            printf("ENTER TRANSACTION TYPE (B FOR BUY / S FOR SELL): ");
            scanf("%c",&t);
            if(t!='b'&& t!='B'&& t!='s'&& t!='S')
                printf("!!!INCORRECT SELECTION!!!\n");
        }
        if(t=='b'||t=='B')
        {
            strcpy(s.type,"BUY");
            upd=1; // sets to 1 to add the stocks to stock_holdings.dat file through maintain_stock function
        } 
        else
        {
            strcpy(s.type,"SELL");
            upd=-1; // sets to -1 to remove the stocks from stock_holdings.dat file through maintain_stock function
        }
        printf("ENTER DATE OF TRANSACTION (FORMAT-> DD MM YYYY): ");
        scanf("%d%d%d",&s.dot.d,&s.dot.m,&s.dot.y);
        fprintf(fp,"%05d %20s %20s %5d %10.2f %6s  %4d %2d %4d\n",s.t_id,s.uname,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
        getchar();
        maintain_stock(s.uname, s.symbol, s.qty, s.price, upd); // maintains holdings of user in file stock_holdings.dat
        printf("RECORD OF TRANSACTION ADDED SUCCESSFULLY!\n");
        printf("MORE ENTRIES? (ENTER Y FOR YES / ANY OTHER CHARACTER FOR NO ): ");
        scanf("%c",&ch);
        printf("\n");
    }
    fclose(fp);
    return 0;
}

/*
Function: view_recs
----------------------
Displays the transaction records of user 
Parameters:
    uname: a string containing the user's username
Returns:
    int:  -1 if unable to open "transaction.dat" file, 0 if file opened and read successfully
*/
int view_recs(char* uname)
{
    stock s;
    FILE* fp=fopen("transaction.dat","r");
    if(fp==NULL)
    {
        puts("FAILED TO OPEN THE FILE.\n");
        return -1;
    }
    DASHES;
    printf("| %9s| %18s| %9s| %14s|  %10s|  %14s|\n","T_ID","SYMBOL","QTY","PRICE","T_TYPE","DOT");
    DASHES;
    while(fscanf(fp,"%d %s %s %d %f %s %d %d %d",&s.t_id,s.uname,s.symbol,&s.qty,&s.price,s.type,&s.dot.d,&s.dot.m,&s.dot.y)!=EOF)
    {
        if(!strcmp(uname,s.uname))
        {
            printf("|     %05d| %18s| %9d| %14.2f|  %10s|      %02d-%02d-%4d|\n",s.t_id,s.symbol,s.qty,s.price,s.type,s.dot.d,s.dot.m,s.dot.y);
            DASHES;
        }
    }
    puts("");
    fclose(fp);
    return 0;
}