#include<stdio.h>
#include<string.h>
#include"signup.h"
/*
Function: login
----------------------
Allows users to login to their accounts, by authenticating username and password
Parameters:
    uname: pointer to char array that will store the username of user in case of successful authentication
Returns: 
    int: 1 if authentication successful, 0 if authentication failed, -1 if unable to open the file
*/
int login(char* uname)
{
    int f=0; 
    char t_uname[48],t_pass[16];
    struct user p;
    FILE *fp;
    fp=fopen("users.dat","r");
    if(fp==NULL)
        return -1;
    while(f==0)
    {
        printf("ENTER USERNAME: ");
        fgets(t_uname,48,stdin);
        t_uname[strcspn(t_uname,"\n")]='\0'; // removes the newline char appended by fgets
        printf("ENTER PASSWORD: ");
        hidden_input(t_pass);
        t_pass[strcspn(t_pass,"\n")]='\0';
        rewind(fp);
        while(fscanf(fp,"%s %s %s %s %s",p.uname,p.fname,p.lname,p.email,p.pass)!=EOF)
        {
            if(!strcmp(p.uname,t_uname) && !strcmp(p.pass,t_pass))
            {
                f=1; 
                break;
            }
        }
        if(f==0)
            printf("!!! INCORRECT CREDENTIALS !!!\n");
        else
        {
            strcpy(uname,p.uname);
            puts("LOGIN SUCCESSFUL!");
            printf("\nWELCOME, %s (^v^) !\n",p.fname);
        }
    }
    fclose(fp);
    return f;  
}