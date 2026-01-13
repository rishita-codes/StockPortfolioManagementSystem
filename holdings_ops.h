#include<stdio.h>
#include<string.h>
/*
Structure: holdings
----------------------
Represents a stock holding
uname: username
symbol: stock symbol
qty: stock's quantity
spent: total money invested in that particular stock
*/
struct holdings{
    char uname[48];
    char symbol[20];
    int qty;
    float spent;
};

int check_stock(char uname[48], char symbol[20]);
int maintain_stock(char uname[48], char symbol[20], int qty, int price, int trans_type);

/*
Function: check_stock
----------------------
Checks if the stock already exists in user's portfolio in file stock_holdings.dat
Parameters:
    uname: a string containing the user's username
    symbol: a string containing the stock's symbol
Returns:
    int:  1 if found, 0 if not found and -1 if unable to open file
*/
int check_stock(char uname[48], char symbol[20])
{
    int q=0;
    struct holdings h;
    FILE* fp=fopen("stock_holdings.dat","r");
    if(fp==NULL)
    {
        puts("FAILED TO OPEN THE FILE !");
        return -1;
    }
    while(fscanf(fp,"%s %s %d %f\n",h.uname,h.symbol,&h.qty,&h.spent)!=EOF)
    {
        if(!strcmp(h.uname, uname) && !strcmp(h.symbol, symbol))
        {
            q=1;
            break;
        }
    }
    fclose(fp);
    return q;
}
/*
Function: maintain_stock
----------------------
Maintains the user's stock holdings/portfolio when new purchases are made, stocks are sold, updated or removed
Parameters:
    uname: a string containing the user's username
    symbol: a string containing the stock's symbol
    qty: quantity of stock
    price: price of stock at which transaction was made
    trans_type: 1 for buy, -1 for sell, 0 to nullify the effect of transaction (incase a transaction is deleted/updated)
Returns:
    int: 0 on success and -1 if unable to open the file
*/
int maintain_stock(char uname[48], char symbol[20], int qty, int price, int type_trans)
{
    int f,a,b,c;
    struct holdings h;
    f=check_stock(uname, symbol); 
    FILE* fp=fopen("stock_holdings.dat","r");
    FILE* fp2=fopen("temp3.dat","w"); // file to store the updated holdings
    if(fp==NULL || fp2==NULL)
        return -1;
    if(type_trans==-1 || type_trans==0)
    {
        qty=-qty; // to subtract the quantity from total
    }
    if(f==1)
    {
        while(fscanf(fp,"%s %s %d %f\n",h.uname,h.symbol,&h.qty,&h.spent)!=EOF)
        {
            if(!strcmp(h.uname, uname) && !strcmp(h.symbol, symbol))
            {
                if(type_trans==-1) //sell
                { 
                    h.spent= (h.spent/h.qty)*(h.qty+qty); // maintains avg price of remaining stock
                    h.qty+=qty; // maintains new quantity
                }
                else if(type_trans==1)  //buy
                {
                    h.qty+=qty;
                    h.spent+=price*qty; // records total investment on stock after purchase
                }
                else  //nullify
                {
                    h.spent+=qty*price; // nullifies the effect of previous transaction
                    h.qty+=qty;
                }
                if(h.qty==0) // prevents stock with 0 quantity from being written in file
                    continue;
            }
            fprintf(fp2,"%s %s %d %f\n",h.uname,h.symbol,h.qty,h.spent);
        }
        fclose(fp);
        fclose(fp2);
        // exchanging the names of stock_holdings.dat and temp3.dat
        a=rename("stock_holdings.dat","temp4.dat"); 
        b=rename("temp3.dat","stock_holdings.dat");
        c=rename("temp4.dat","temp3.dat");
        if(a==0 && b==0 && c==0)
            return 0;
    }
    else
    {   // Incase the stock doesn't already exist, makes a new entry for it in overall holdings
        fclose(fp);
        fp=fopen("stock_holdings.dat","a");
        strcpy(h.uname,uname);
        strcpy(h.symbol,symbol);
        h.qty=qty;
        h.spent=price*qty;
        fprintf(fp,"%s %s %d %f\n",h.uname,h.symbol,h.qty,h.spent);
        fclose(fp);
        fclose(fp2);
        return 0;
    }
    return 1;
}
