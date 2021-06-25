#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void string_encription(char *str,char *key,char *res,int cript[])
{
	for(int i=0;i<strlen(str);i++)
	{
    int k=str[i]-97;
    //As a is in 0th position having ascii of 97 we can get the position number directly by subtracting it by 97 
    // For Example : str[i]='a'; then k=97-97=0;

    if(k+cript[i]<26)
      res[i]=key[k+cript[i]];
    else
      res[i]=key[(k+cript[i])%26];
	}
}
void string_decription(char *str,char *key,char *let,char *res,int cript[])
{
	for(int i=0;i<strlen(str);i++)
	{
    int k=0;
    while(str[i]!=key[k]){
      k++;
    }
    if(k-cript[i]>=0)
     res[i]=let[k-cript[i]];
    else
      res[i]=let[k-cript[i]+26];
	}
}
int main()
{
  srand(time(NULL)); 
  // The srand(x) function sets the seed of the random number generator algorithm used by the function rand()
  // makes use of the computer's internal clock to control the choice of the seed.
  char key[]={'j','a','k','b','l','m','c','n','o','d','p','q','e','r','s','f','t','u','g','v','w','h','x','y','i','z'};
  char let[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char str[10];
	printf("\nEnter the string to be encrpyted :");
  scanf("%s",str);
  int cript[strlen(str)];
  int l=strlen(str);
  printf("\nRandom key generated : ");
  for(int i=0;i<l;i++)
  {
    cript[i] = rand() % 26;
    printf("%d ",cript[i]);
  }

  char e_cript[l];
	string_encription(str,key,e_cript,cript);

	char d_cript[l];
	string_decription(e_cript,key,let,d_cript,cript);

	printf("\n\nAfter Encrption : %s",e_cript);
	printf("\nAfter Decrption : %s\n",d_cript);
	return 0;
}


