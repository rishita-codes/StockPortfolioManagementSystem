#include<stdio.h>
#include<string.h>
#include "view_price.h"
#include "login.h"

void pretty_print(char* s, char ch); // displays text with symbols printed around it 
 
int main()
{   
    int ch, t;
    char uname[48];
    page1:
    pretty_print("TRADING SHARES PORTFOLIO MANAGEMENT SYSTEM",'%');
    rep: 
    puts("ENTER 1-SIGNUP\n      2-LOGIN\n      3-Exit\n"); // displays authentication menu
    printf("YOUR CHOICE: ");
    scanf("%d",&ch); // accepts user's choice
    switch(ch) // handles user authentication choices
    {
        case 1: 
            pretty_print("SIGN UP",'*');
            getchar();
            // collects user's information and creates new account
            t=signup(uname);
            break;
        case 2:
            pretty_print("LOGIN",'*');
            getchar();
            // collects username & password and authenticates user
            t=login(uname);
            break;
        case 3:
            exit(0);
        default:
            puts("INVALID CHOICE!\n");
            goto rep; // redirects user to the authentication menu
    }
    if(t==1) // In case of successful authentication
    {
        page2:
        pretty_print("MAIN MENU",'*');
        rep2:
        // displays main menu to perform various portfolio operations
        puts("ENTER 1-VIEW TRANSACTION RECORDS\n      2-ADD A TRANSACTION\n      3-REMOVE A TRANSACTION\n      4-UPDATE A TRANSACTION\n      5-ANALYSE PORTFOLIO\n      6-TRACK STOCK PERFORMANCE\n      7-CHECK CURRENT PRICES\n      8-TO LOG OUT\n");
        printf("YOUR CHOICE: ");
        scanf("%d",&ch);
        getchar();
        switch(ch) // handles portfolio operation choices
        {
            case 1:
                pretty_print("VIEW TRANSACTION RECORDS",'*'); 
                // displays user's transaction records
                view_recs(uname);
                break;
            case 2:
                pretty_print("ADD A TRANSACTION",'*');
                /* seeds the random number generator with current time to ensure different 
                   random numbers are generated each time when rand() is called */
                srand(time(0));
                // collects transaction details and adds the new record to file
                add_trans(uname);
                getchar();
                break;
            case 3:
                pretty_print("REMOVE A TRANSACTION",'*');
                /* collects transaction id from user and 
                   removes the corresponding transaction from file */
                t=remove_trans(uname);
                if(t==0)
                    goto page2; // redirects the user to main menu
                getchar();
                break;
            case 4:
                pretty_print("UPDATE A TRANSACTION",'*');
                /* collects transaction id and updates the corresponding transaction
                   by reading the fields to be updated from user */
                t=update_trans(uname);
                if(t==0)
                    goto page2;
                break;
            case 5:
                pretty_print("ANALYSE PORTFOLIO",'*');
                // analyses portfolio and displays performance metrics
                assess_port(uname);
                break;
            case 6:
                pretty_print("TRACK STOCK PERFORMANCE",'*');
                /* collects stock symbol number from the user and displays its
                   performance of the last 15 days in graphical format */
                track_stock();
                break;
            case 7:
                pretty_print("CHECK CURRENT PRICES",'*');
                // collects stock symbol numbers from user and displays their current prices
                check_stock_price();
                break;
            case 8:
                goto page1; // redirects to authentication menu
            default:
                puts("INVALID CHOICE!\n");
                goto rep2; // redirects to read user's choice again
        }
        printf("HIT ENTER TO GO BACK ");
        getchar();
        goto page2; // redirects to main menu
    }
}
/*
Function: pretty_print
----------------------
displays styled text to console
Parameters:
    s: s is a pointer to the string which is to be printed
    ch: ch is a character containing the decorative symbol which will enclose the
        text to be printed
Returns: void
*/
void pretty_print(char* s, char ch)
{
    int i,j=0,l;
    char s2[100], s3[100], sym[47];
    l=strlen(s);
    for(i=0;i<l/2;i++,j++) // copies half the characters of s to s2
        s2[j]=s[i];
    s2[j]='\0'; 
    j=0;
    for(;i<l;i++,j++) // copies the other half of s to s3
        s3[j]=s[i];
    s3[j]='\0';
    // makes a string of the decorative symbols
    for(i=0;i<46;i++) 
        sym[i]=ch;
    sym[i]='\0';
    // prints text to the console in decorative mannner
    printf("\n%s%s%s\n%s%23s%-23s%46s\n%s%s%s\n\n",sym,sym,sym,sym,s2,s3,sym,sym,sym,sym);
}
