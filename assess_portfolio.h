#include<stdio.h>
#include<string.h>
#include "extract_price.h"
#define DASHES_2 puts("-------------------------------------------------------------------------------------------------------------------");
/*
Function: assess_port
----------------------
Assesses the user's portfolio and displays performance metrics
Parameters:
    uname: a string containing the user's username
Returns:
    int:  -1 if unable to open "stock_holdings.dat" file, 0 if successful
*/
int assess_port(char uname[48])
{
    struct holdings h;
    FILE*fp=fopen("stock_holdings.dat","r");
    if(fp==NULL)
    {
        return -1;
    }
    double gainloss, roi, p_value=0, investment=0 ,cur_price, avg_p, s_value;
    while(fscanf(fp,"%s %s %d %f",h.uname,h.symbol,&h.qty,&h.spent)!=EOF)
    {   
        if(!strcmp(uname,h.uname))
        {
            cur_price=stock_price(h.symbol); // fetches the current price of stock
            p_value+=cur_price*h.qty; // calculates portfolio value
            investment+=h.spent; // calculates investment
        }
    }
    gainloss=p_value-investment;
    roi=(p_value-investment)*100/investment; // calculates return on investment
    printf("%-40s%s %.2lf\n%-40s%s %.2lf%s\n%-40s%s %.2lf\n%-40s%s %.2lf\n","INVESTMENT",":",investment,"RETURN ON INVESTMENT (ROI)",":",roi,"%", "GAIN/LOSS",":",gainloss,"PORTFOLIO VALUE",":",p_value);
    rewind(fp);
    DASHES_2;
    printf("| %15s| %10s| %15s| %15s| %15s| %15s| %15s|\n","SYMBOL","QUANTITY","AVERAGE PRICE","CURRENT PRICE","TOTAL VALUE","GAIN/LOSS","PORTFOLIO %AGE");
    DASHES_2;
    while(fscanf(fp,"%s %s %d %f\n",h.uname,h.symbol,&h.qty,&h.spent)!=EOF)
    {
        if(!strcmp(uname,h.uname))
        {
            cur_price=stock_price(h.symbol);
            s_value=cur_price*h.qty; // calculates stock value
            avg_p=h.spent/h.qty; // calculates average buying price of stock
            printf("| %15s| %10d| %15.2lf| %15.2lf| %15.2lf| %15.2lf| %15.2lf|\n", h.symbol, h.qty, avg_p, cur_price, s_value, s_value-h.spent, s_value*100/p_value);
            DASHES_2;
        }
    }
    puts("");
    fclose(fp);
    return 0;
}

