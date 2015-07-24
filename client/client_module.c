#include <stdio.h>
#include <string.h>
struct data    
{                  
    char name[20];       
    char pass[20];        
    };

int login(char *nm, char *ps)
{
	
   FILE *f;
   struct data elem2,elem;
   int flag;
   flag=0;
   f=fopen("base.dat","r+b");
   while(fread(&elem2, sizeof(elem2), 1, f)!=0);
	{
		if ((strcmp(elem2.name,nm)==0)&&(strcmp(elem2.pass,ps)==0));
		{
		puts("Welcome, You have successfully logged to the server!");
		printf("Type '/exit' to quit the chat\n\n");
		flag=1;
		}
		
	}

	fclose(f);
	return flag;
}

void reg()
{
	
    FILE *f;
    struct data elem;
    char logg[20],pass[20];
    printf("Choose your login:\n");
	scanf("%s",&elem.name);
	printf("Choose your password:\n");
	scanf("%s",&elem.pass);
	f=fopen("base.dat","a+b");
	fwrite(&elem, sizeof(struct data), 1, f);
	puts("You have successfully registered on the server!");
	fclose(f);

}