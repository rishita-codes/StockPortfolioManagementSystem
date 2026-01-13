#include<stdio.h>
#include<string.h>
#include<conio.h>
/*
Structure: user
----------------------
Represents user data
uname: stores the user's username
fname: stores the user's first name
lname: stores the user's last name
email: stores the user's email
pass: stores the password of user's account
*/
struct user
{ 
    char uname[48];
    char fname[48];
    char lname[48];
    char email[48];
    char pass[16];
};
int signup(char* uname);
void hidden_input(char* pass);
/*
Function: signup
----------------------
Allows new users to register
Parameters:
    uname: pointer to char array that will store the username of user in case of successful registration
Returns: 
    int: 1 on success, -1 if unable to open the file
*/
int signup(char* uname)
{
    int f=1,t=1;
    struct user person,p;
    char confirm[16];
    FILE *fp;
    fp=fopen("users.dat","a+");
    if(fp==NULL)
        return -1;
    char temp[48];
    printf("ENTER FIRST NAME: ");
    fgets(person.fname,48,stdin);
    printf("ENTER LAST NAME: ");
    fgets(person.lname,48,stdin);
    while(f==1)
    {
        printf("ENTER USERNAME: ");
        fgets(temp,48,stdin);
        temp[strcspn(temp,"\n")]='\0'; // removes the newline char appended by fgets
        f=0;
        rewind(fp);
        while(fscanf(fp,"%s %s %s %s %s",p.uname,p.fname,p.lname,p.email,p.pass)!=EOF)
        {
            if(!strcmp(p.uname,temp))
            {
                f=1; // username found
                printf("!!! THIS USERNAME ALREADY EXISTS !!!\n"); 
                break;
            }
        }
    }
    strcpy(person.uname,temp);
    printf("ENTER EMAIL: ");
    fgets(temp,48,stdin);
    strcpy(person.email,temp);
    while(t)
    {
        printf("ENTER PASSWORD: ");
        hidden_input(person.pass);
        printf("CONFIRM PASSWORD: ");
        hidden_input(confirm);
        if(t=strcmp(person.pass,confirm))
            puts("!!! PASSWORDS DO NOT MATCH !!!");
    }
    fprintf(fp,"%s\n%s%s%s%s\n\n",person.uname,person.fname,person.lname,person.email,person.pass);
    strcpy(uname,person.uname);
    puts("\nCONGRATS! SIGN UP SUCCESSFUL!\n");
    fclose(fp);
    return 1;
}
/*
Function: hidden_input
----------------------
Allows user to enter text without showing eg. password masking
Parameters:
    pass: pointer to char array that will store the input text
Returns: void
*/
void hidden_input(char* pass)
{
    int i=0; // to store length of text
    char ch;
    while((ch=getch())!='\r') // until newline / carriage return char not found
    {
        if(ch=='\b') // if backspace is pressed 
        {
            if(i<=0) // if there's no text to be erased
                continue;
            i--; 
            printf("\b \b"); // takes cursor back, prints space and again takes cursor back
        }
        else
        {
            pass[i++]=ch;
            printf("*"); 
        }
        if(i<0)
            i=0;
    }
    pass[i]='\0';
    puts("");
}