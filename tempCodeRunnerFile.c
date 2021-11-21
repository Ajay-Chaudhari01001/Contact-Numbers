#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void addcontact();    //function decleration
void showcontact();   //function decleration
void editcontact();  //function declearation
void deletcontac();  //function decleration

struct Book     //store all details in structure Book type 
{
    char name[20];
    long int number;
}p;

FILE *fp;             // create file pointer , using global variable 
int main()
{
    int choice;
    while(1)
    {
        system("cls");       //clear screen
        system("COLOR 70");   // change foreground and background color
        printf("\n\t\t\t\t CONSOLE PHONE BOOK \n\n");
        printf("\n\t\t1 Add New Contact \n");
        printf("\n\t\t2 View Contacts Details \n");
        printf("\n\t\t3 Edit Contact Details \n");
        printf("\n\t\t4 Delete Contact \n");
        printf("\n\t\t0 Exit\n");
        printf("\n\t\t\t Enter Your Choice :");
        scanf("%d",&choice);

        switch(choice)
        {
        case 0:
            exit(1);
            break;
        case 1:
            addcontact();    //function calling
            break;
        case 2:
            showcontact();   //function calling
            break;
        case 3:
            editcontact();
            break;
        case 4:
            deletcontact();
            break;
        default:
            printf("\n Invalid Choice Number ");   
            break;
        }
    }
    return 0;
}
void addcontact()   //function defination
{
    system("cls");
    system("COLOR 7e");
    printf("\t*********************************************************");
    printf("\n\t\t ADD NEW PHONE NUMBER RECORD \n");
    printf("\t*********************************************************\n");
    fp = fopen("PhoneBook.txt","ab");

    printf("\n\t\t Enter Person Name :");
    fflush(stdin);
    gets(p.name);
    printf("\n\t\t Enter Person Number :");
    scanf("%ld",&p.number);

    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    printf("\n\n\t\t\t Record Save Successfully...");
    getch();
}
void showcontact()
{
    system("cls");
    system("COLOR 70");
    printf("\t %-30s %-10s","NAME","NUMBER");
    printf("\t\t\n------------------------------------------------------\n");
    fp = fopen("PhoneBook.txt","rb");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
         printf("\t %-30s %-10d\n",p.name, p.number);
    }
    fclose(fp);
    printf("\n\n\t\t Press Any Key To Continue... ");
    getch();
}
void editcontact()
{
    char na[20];
    int flag = 0;
    system("cls");
    system("COLOR 7e");
    printf("\n\n\n\t\t Enter Contact Name You Want to Edit :");
    fflush(stdin);
    gets(na);
    fp = fopen("PhoneBook.txt","rb+");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
         if(strcmpi(na , p.name)==0)
          {
             flag = 1;
             printf("\n\t\t Enter New Contact Name :");
             gets(p.name);
             printf("\n\t\t Enter New Contact Number :");
             scanf("%ld",&p.number); 
             fseek(fp,-sizeof(p),1);
             fwrite(&p,sizeof(p),1,fp);
             break;
          }
    }
    fclose(fp);
    if(flag==0)
    printf("\n\t\t Record Not Found ");
    else
    printf("\n\t\t Record Save Successfully ");

    getch();
}
void deletcontact()
{
    system("cls");
    system("COLOR 0e");
    char na[40];
    int flag = 0;
    FILE *tf;
   fp = fopen("PhoneBook.txt","rb");
   tf = fopen("temp.txt","wb");
   printf("\n\t\t Enter contact name you want to delete :");
   fflush(stdin);
   gets(na);
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmpi(na, p.name))
         flag = 1;
        else
        {
            fwrite(&p,sizeof(p),1,tf);
        }
        
    }
        fclose(fp);
        fclose(tf);
        remove("PhoneBook.txt");
        rename("temp.txt","PhoneBook.txt");
        if(flag==0)
        printf("\n\t\t Record Not Found ");
        else
        printf("\n\t\t Record Delete Successfully \n");

        getch();
}
