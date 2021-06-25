#include<stdio.h>
#include <string.h>
void string_encription(char *str,int key,char *res,char *pos)
{
	for(int i=0;i<strlen(str);i++)
	{
    int k=str[i]-97; 
    //a=0=97-97; c=99-97=2
    //As a is in 0th position having ascii of 97 we can get the position number directly by subtracting it by 97 
    // For Example : str[i]='a'; then k=97-97=0;

    // Or u can calculate using a while loop:
    // int k=0;
		// while(str[i]!=pos[k]){
    //   k++;
    // }
    
    if(k>=0 && k<=25) {
      int check=(k+key)%26;
      res[i]=pos[check];
    } else {
      printf("\nPlease enter charecter values\n");
      return;
    }
	}
}
void string_decription(char *str,int key,char *res,char *pos)
{
	for(int i=0;i<strlen(str);i++)
	{
    int k=str[i]-97;
    if(k>=0 && k<=25) {
      int check=(k-key)%26;
      if(check<0) {
        check=check+26;
      }
      res[i]=pos[check];
    } else {
      printf("\nPlease enter charecter values\n");
      return;
    }
	}
}
int main()
{
  char position[26];
	char str[]="hello";
	int key;
  printf("\nEnter the key: ");
  scanf("%d",&key);
	for(int i=0;i<26;i++) {
    position[i]='a'+i;
  }

  char e_cript[strlen(str)];
	string_encription(str,key,e_cript,position);

	char d_cript[strlen(str)];
	string_decription(e_cript,key,d_cript,position);

	printf("After Encrption : %s",e_cript);
	printf("\nAfter Decrption : %s\n",d_cript);

	return 0;
}


