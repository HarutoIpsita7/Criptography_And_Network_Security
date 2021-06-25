#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  char pt[100],plain_text[100],str_key[50],str_key_orig[50],key[25];
  int k=0,check_repeat=0;
  printf("\nEnter PalinText:\n");
  scanf("%[^\n]",pt);
  for(int l=0;l<strlen(pt);l++)
  {
    if(pt[l]<97 || pt[l]>122)
      continue;
    plain_text[k++]=pt[l];  //abc def ghi. kmh
  }
  plain_text[k+1]='\0';
  printf("\nPlain Text : %s  with k : %d\n",plain_text,k);

  // Taking input of key
  printf("\nEnter key:\n");
  scanf("%s",str_key_orig);

  for(int ptr=0;ptr<strlen(str_key_orig);ptr++)
  {
    str_key[ptr]=str_key_orig[ptr];
  }

  // Removing Duplicates if any
  for(int i=0;i<strlen(str_key);i++) 
  {
    for(int j=i+1;j<strlen(str_key);j++) 
    {
      if(str_key[i]==str_key[j])
      {
        str_key[j]='0'; // If duplicate element is found I am replacing it with 0
        check_repeat=1;
      }
    }
  } 
  if(check_repeat==1)
  {
    printf("***************************************************************************************************************************\nSolving with NONE REPEATED KEY\n***************************************************************************************************************************");
  }
  int l=0;
  for(int i=0;i<strlen(str_key);i++) 
  {
    if(str_key[i]!='0')
    {
      key[l++]=str_key[i]; // If not duplicate enter the key
    }
  } 

  printf("\n\n=====================================================================================\nENCRIPTION\n=====================================================================================\n\n");
  printf("\nKey : %s  with l = %d\n",key,l);

  printf("\nValue for each key : \n");
  int no_key[l],ctr=1;
  for(int i=97;i<123;i++)
  {
    for(int j=0;j<l;j++)
    {
      if(key[j]==i)
      {
        no_key[j]=ctr++; // math = 3  1  4  2
        printf("For %c => %d\n",key[j],ctr-1);
      }
    }
  }

  printf("\nFinal Key with Allocated Value :\n");
  for(int i=0;i<l;i++)
  {
    printf("For %c => %d | ",key[i],no_key[i]);
  }

  int row=0;
  if(k%(ctr-1)!=0)
  {
    row=(k/(ctr-1))+1;  // (no_of_alph_to_encript/no_of_columns_in_transposition_mat) + 1 => (25/7)+1 => 3+1 = 4
  }
  else
  {
    row=(k/(ctr-1));  // (no_of_alph_to_encript/no_of_columns_in_transposition_mat)        => (21/7)  => 3
  }
  char encryp_mat[row][ctr-1];

  int p,q,sz=0;
  for(p=0;p<row;p++)
  {
    for(q=0;q<ctr-1;q++)
    {
      if(plain_text[sz]<97 || plain_text[sz]>122)
        plain_text[sz]='a'+q;
      encryp_mat[p][q]=plain_text[sz++];
      // printf("\nPT : %2c at %d %d\n",plain_text[s-1],p,q);
    }
    
  }

  printf("\n\nPosition Allocated : \n");
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<ctr-1;j++)
    {
      printf("  %d %d %c   |  ",i,j,encryp_mat[i][j]);
    }
    printf("\n");
  }

  char cipher_text[sz];
  int curr_col=1,r,s=0;
  for(p=0;p<ctr-1;p++)
  {
    if(curr_col==ctr)
      break;
    for(r=0;r<l;r++)    // l=ctr-1
    {
      if(no_key[r]==curr_col)
      {
        break;
      }
    }
    for(q=0;q<row;q++)
    {
      cipher_text[s++]=encryp_mat[q][r];
      // printf("\nEach ciph_text : %c at position %d",cipher_text[s-1],s-1);
    }
    curr_col++;
  }

  printf("\nCipher Text obtained :\n");
  for(int z=0;z<s;z++)
  {
    // printf("\n z=%d =>",z); // z=27
    printf("%c",cipher_text[z]);
  }

  // printf("\n And size of sz=%d, s=%d and cipher text is : %s\n",sz,s,cipher_text); 
  // And size of sz=28, s=28 and cipher text is : ttnaaptmtsuoaodwcoiaknlapetap

  printf("\n\n=====================================================================================\nDECRIPTION\n=====================================================================================\n\n");

  char decripted_mat[row][ctr-1],decripted_pt[sz];
  curr_col=1,r,s=0;
  for(p=0;p<ctr-1;p++)
  {
    if(curr_col==ctr)
      break;
    for(r=0;r<l;r++)
    {
      if(no_key[r]==curr_col)
      {
        break;
      }
    }
    for(q=0;q<row;q++)
    {
      decripted_mat[q][r]=cipher_text[s++];
    }
    curr_col++;
  }

  p,q,s=0;
  for(p=0;p<row;p++)
  {
    for(q=0;q<ctr-1;q++)
    {
      decripted_pt[s++]=decripted_mat[p][q];
    }
  }

  printf("\n\nPosition Allocated : \n");
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<ctr-1;j++)
    {
      printf("  %d %d %c   |  ",i,j,decripted_mat[i][j]);
    }
    printf("\n");
  }

  printf("\nPlain Text obtained :\n");
  for(int z=0;z<s;z++)
  {
    printf("%c",decripted_pt[z]);
  }

  printf("\n\n");

  if(check_repeat==1)
  {
    printf("***************************************************************************************************************************\nSolving with REPEATED KEY\n***************************************************************************************************************************");
  

    l=0;
    for(int i=0;i<strlen(str_key_orig);i++) 
    {
      if(str_key_orig[i]!='0')
      {
        key[l++]=str_key_orig[i]; // If not duplicate enter the key
      }
    } 

    printf("\n\n=====================================================================================\nENCRIPTION\n=====================================================================================\n\n");
    printf("\nKey : %s  with l = %d\n",key,l);

    printf("\nValue for each key : \n");
    ctr=1;
    for(int i=97;i<123;i++)
    {
      for(int j=0;j<l;j++)
      {
        if(key[j]==i)
        {
          no_key[j]=ctr++;
          printf("For %c => %d\n",key[j],ctr-1);  
          // mathematics
          //  1  4 2  3
          // matheics
        }
      }
    }

    printf("\nFinal Key with Allocated Value :\n");
    for(int i=0;i<l;i++)
    {
      printf("For %c => %d | ",key[i],no_key[i]);
    }

    row=0;
    if(k%(ctr-1)!=0)
    {
      row=(k/(ctr-1))+1;  // (no_of_alph_to_encript/no_of_columns_in_transposition_mat) + 1 => (25/7)+1 => 3+1 = 4
    }
    else
    {
      row=(k/(ctr-1));  // (no_of_alph_to_encript/no_of_columns_in_transposition_mat)        => (21/7)  => 3
    }
    encryp_mat[row][ctr-1];

    sz=0;
    for(p=0;p<row;p++)
    {
      for(q=0;q<ctr-1;q++)
      {
        if(plain_text[sz]<97 || plain_text[sz]>122)
          plain_text[sz]='a'+q;
        encryp_mat[p][q]=plain_text[sz++];
        // printf("\nPT : %2c at %d %d\n",plain_text[s-1],p,q);
      }
      
    }

    printf("\n\nPosition Allocated : \n");
    for(int i=0;i<row;i++)
    {
      for(int j=0;j<ctr-1;j++)
      {
        printf("  %d %d %c   |  ",i,j,encryp_mat[i][j]);
      }
      printf("\n");
    }

    // char cipher_text[sz];
    curr_col=1,s=0;
    for(p=0;p<ctr-1;p++)
    {
      if(curr_col==ctr)
        break;
      for(r=0;r<l;r++)    // l=ctr-1
      {
        if(no_key[r]==curr_col)
        {
          break;
        }
      }
      for(q=0;q<row;q++)
      {
        cipher_text[s++]=encryp_mat[q][r];
        // printf("\nEach ciph_text : %c at position %d",cipher_text[s-1],s-1);
      }
      curr_col++;
    }

    printf("\nCipher Text obtained :\n");
    for(int z=0;z<s;z++)
    {
      // printf("\n z=%d =>",z); // z=27
      printf("%c",cipher_text[z]);
    }

    // printf("\n And size of sz=%d, s=%d and cipher text is : %s\n",sz,s,cipher_text); 
    // And size of sz=28, s=28 and cipher text is : ttnaaptmtsuoaodwcoiaknlapetap

    printf("\n\n=====================================================================================\nDECRIPTION\n=====================================================================================\n\n");

    // char decripted_mat[row][ctr-1],decripted_pt[sz];
    curr_col=1,s=0;
    for(p=0;p<ctr-1;p++)
    {
      if(curr_col==ctr)
        break;
      for(r=0;r<l;r++)
      {
        if(no_key[r]==curr_col)
        {
          break;
        }
      }
      for(q=0;q<row;q++)
      {
        decripted_mat[q][r]=cipher_text[s++];
      }
      curr_col++;
    }

    s=0;
    for(p=0;p<row;p++)
    {
      for(q=0;q<ctr-1;q++)
      {
        decripted_pt[s++]=decripted_mat[p][q];
      }
    }

    printf("\n\nPosition Allocated : \n");
    for(int i=0;i<row;i++)
    {
      for(int j=0;j<ctr-1;j++)
      {
        printf("  %d %d %c   |  ",i,j,decripted_mat[i][j]);
      }
      printf("\n");
    }

    printf("\nPlain Text obtained :\n");
    for(int z=0;z<s;z++)
    {
      printf("%c",decripted_pt[z]);
    }
  }
  printf("\n\n");
  
  return 0;
}

/*
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem$ cd CNS/Assignment-4
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ gcc columnar_transposition.c
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ ./a.out

Enter PalinText:
hello world

Plain Text : helloworld  with k : 10

Enter key:
adhi


=====================================================================================
ENCRIPTION
=====================================================================================


Key : adhi  with l = 4

Value for each key : 
For a => 1
For d => 2
For h => 3
For i => 4

Final Key with Allocated Value :
For a => 1 | For d => 2 | For h => 3 | For i => 4 | 

Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |    0 3 l   |  
  1 0 o   |    1 1 w   |    1 2 o   |    1 3 r   |  
  2 0 l   |    2 1 d   |    2 2 c   |    2 3 d   |  

Cipher Text obtained :
holewdloclrd

=====================================================================================
DECRIPTION
=====================================================================================



Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |    0 3 l   |  
  1 0 o   |    1 1 w   |    1 2 o   |    1 3 r   |  
  2 0 l   |    2 1 d   |    2 2 c   |    2 3 d   |  

Plain Text obtained :
helloworldcd



haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ ./a.out

Enter PalinText:
hello world 

Plain Text : helloworld  with k : 10

Enter key:
aabca
***************************************************************************************************************************
Solving with NONE REPEATED KEY
***************************************************************************************************************************

=====================================================================================
ENCRIPTION
=====================================================================================


Key : abc  with l = 3

Value for each key : 
For a => 1
For b => 2
For c => 3

Final Key with Allocated Value :
For a => 1 | For b => 2 | For c => 3 | 

Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |  
  1 0 l   |    1 1 o   |    1 2 w   |  
  2 0 o   |    2 1 r   |    2 2 l   |  
  3 0 d   |    3 1 b   |    3 2 c   |  

Cipher Text obtained :
hlodeorblwlc

=====================================================================================
DECRIPTION
=====================================================================================



Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |  
  1 0 l   |    1 1 o   |    1 2 w   |  
  2 0 o   |    2 1 r   |    2 2 l   |  
  3 0 d   |    3 1 b   |    3 2 c   |  

Plain Text obtained :
helloworldbc

***************************************************************************************************************************
Solving with REPEATED KEY
***************************************************************************************************************************

=====================================================================================
ENCRIPTION
=====================================================================================


Key : aabca  with l = 5

Value for each key : 
For a => 1
For a => 2
For a => 3
For b => 4
For c => 5

Final Key with Allocated Value :
For a => 1 | For a => 2 | For b => 4 | For c => 5 | For a => 3 | 

Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |    0 3 w   |    0 4 o   |  
  1 0 w   |    1 1 o   |    1 2 r   |    1 3 l   |    1 4 d   |  

Cipher Text obtained :
hweoodlrwl

=====================================================================================
DECRIPTION
=====================================================================================



Position Allocated : 
  0 0 h   |    0 1 e   |    0 2 l   |    0 3 w   |    0 4 o   |  
  1 0 w   |    1 1 o   |    1 2 r   |    1 3 l   |    1 4 d   |  

Plain Text obtained :
helwoworld

haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-4$ 
*/