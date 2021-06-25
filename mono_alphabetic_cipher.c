#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void string_encription(char *str,char *key,char *res,int cript)
{
  int i;
	for(i=0;i<strlen(str);i++)
	{
    if(str[i]=='\0')
      break;
    int k=str[i]-97;
    //As a is in 0th position having ascii of 97 we can get the position number directly by subtracting it by 97 
    // For Example : str[i]='a'; then k=97-97=0;

    if(k+cript<126)
      res[i]=key[k+cript];
    else
      res[i]=key[(k+cript)%126];
	}
  res[i]='\0';
}
void string_decription(char *str,char *key,char *let,char *res,int cript)
{
  int i;
	for(i=0;i<strlen(str);i++)
	{
    if(str[i]=='\0')
      break;
    int k=0;
    while(str[i]!=key[k]){
      k++;
    }
    if(k-cript>=0)
     res[i]=let[k-cript];
    else
      res[i]=let[k-cript+126];
	}
  res[i]='\0';
}
int main()
{
  srand(time(NULL)); 
  // The srand(x) function sets the seed of the random number generator algorithm used by the function rand()
  // makes use of the computer's internal clock to control the choice of the seed.
  char key[95];
  for(int k=0,i=32;i<127;i++,k++) 
  {
    // All the print-able ascii charecters are ranged within the value of 32 and 127
    key[k]=i;
  }
  char let[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char str[20];

  printf("\nEnter the string to be encrpyted :");
  scanf("%[^\n]",str);

  int cript;
  int l=strlen(str);
  printf("\nString is of length : %d",l);
  cript = rand() % 95;
  printf("\nRadom key generated :%d",cript);

  char e_cript[l];
	string_encription(str,key,e_cript,cript);

	char d_cript[l];
	string_decription(e_cript,key,let,d_cript,cript);

	printf("\n\nAfter Encrption : %s",e_cript);
	printf("\nAfter Decrption : ");
  for(int k=0;;k++)
  {
    if(d_cript[k]!='\0')
      printf("%c",d_cript[k]);
    else
      break;
  }
  printf("\n");
	return 0;
}