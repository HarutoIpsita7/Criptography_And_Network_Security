#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL)); 

  char pt[100];
  int depth,l,k=0;

  printf("\nEnter the plaintext : ");
  scanf("%[^\n]",pt);

  char plain_text[100];
  printf("\npt : %ld",strlen(pt));

  printf("\nEnter depth : ");
  scanf("%d",&depth);

  for(l=0;l<strlen(pt);l++)
  {
    if(pt[l]<97 || pt[l]>122)
      continue;
    plain_text[k++]=pt[l];  //abc def ghi. kmh
  }

  int rem=k%depth,cript;  //all the bes tax 3
  rem=depth-rem;
  if(rem!=0)
  {
    while(rem!=0)
    {
      cript = (rand() % 26)+97; // 0-25=> 3+97=100
      if(cript>122)
      {
        cript=97;
      }
      // printf("crypt : %d",cript);
      plain_text[k++]=cript;
      rem--;
    }
  }

  plain_text[k+1]='\0';
  printf("\nPlain Text : %s k=%d",plain_text,k);

  int col=k/depth;
  char ciph_mat[depth][col],plain_mat[depth][col]; 
  //alh
  //lte
  char cip_text[k],pl_txt[k];
  int m=0;
  for(int i=0;i<col;i++)
  {
    for(int j=0;j<depth;j++)
    {
      if(m>k)
        break;
      ciph_mat[j][i]=plain_text[m++];
    }

    if(m>k)
        break;
  }

  printf("\n\nPosition of ciph_mat: \n");
  for(int i=0;i<depth;i++)
  {
    for(int j=0;j<col;j++)
    {
      printf("%c %d %d | ",ciph_mat[i][j],i,j);
    }
    printf("\n");
  }

  m=0;
  printf("\nEncrypted Plain text (Cipher Text): \n");
  for(int i=0;i<depth;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(m>k)
        break;
      cip_text[m++]=ciph_mat[i][j];
      printf("%c",cip_text[m-1]);
    }
    if(m>k)
        break;
  }
  printf("\n");

  // DECRYPTION
  m=0;
  for(int i=0;i<depth;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(m>k)
        break;
      plain_mat[i][j]=cip_text[m++];
    }
    if(m>k)
        break;
  }

  printf("\n\nPosition of plain_mat: \n");
  for(int i=0;i<depth;i++)
  {
    for(int j=0;j<col;j++)
    {
      printf("%c %d %d | ",plain_mat[i][j],i,j);
    }
    printf("\n");
  }

  m=0;
  printf("\nDe-Ciphered Plain text : \n");
  for(int i=0;i<col;i++)
  {
    for(int j=0;j<depth;j++)
    {
      if(m>k)
        break;
      pl_txt[m++]=plain_mat[j][i];
      printf("%c",pl_txt[m-1]);
    }
    if(m>k)
        break;
  }
  printf("\n\n");
  
  return 0;
}
/*
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ gcc rail_fence.c 
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ ./a.out

Enter the plaintext : all the best for exams

pt : 22
Enter depth : 3

Plain Text : allthebestforexamseed k=21

Position of ciph_mat: 
a 0 0 | t 0 1 | b 0 2 | t 0 3 | r 0 4 | a 0 5 | e 0 6 | 
l 1 0 | h 1 1 | e 1 2 | f 1 3 | e 1 4 | m 1 5 | e 1 6 | 
l 2 0 | e 2 1 | s 2 2 | o 2 3 | x 2 4 | s 2 5 | d 2 6 | 

Encrypted Plain text (Cipher Text): 
atbtraelhefemelesoxsd


Position of plain_mat: 
a 0 0 | t 0 1 | b 0 2 | t 0 3 | r 0 4 | a 0 5 | e 0 6 | 
l 1 0 | h 1 1 | e 1 2 | f 1 3 | e 1 4 | m 1 5 | e 1 6 | 
l 2 0 | e 2 1 | s 2 2 | o 2 3 | x 2 4 | s 2 5 | d 2 6 | 

De-Ciphered Plain text : 
allthebestforexamseed

haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ 
*/