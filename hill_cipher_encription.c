#include<stdio.h>
#include<string.h>
int main()
{
  char plain_text[100],key[50],pt[100];
  //keep the string , key matrix , a string to enter
  int k=0,l;
  printf("Enter the string to encrypt: \n");
  scanf("%[^\n]",pt);
  
  for(l=0;l<strlen(pt);l++)
  {
    if(pt[l]<97 || pt[l]>122)
      continue;
    plain_text[k++]=pt[l];  //abc def ghi. kmh
  }
  // if(k%2!=0) // Dont do this because all sq matrix no of elements are not divisible by 2 Ex. 3 X 3 mat with elements = 9
    // plain_text[k+1]=97; //If odd add an extra letter
  plain_text[k+1]='\0';

  printf("Enter the key: \n"); 
  scanf("%s",key);

  int pl=strlen(plain_text);
  int kl=strlen(key);
  int flag=0,i;     // To check if key is a perfect sq and to store the value of the size in i

  for(i=0;i<=100;i++)
  {
    if(i*i==kl) // Checking if the key can form a square matrix
    {
      flag=1;
      break;
    }
  }
  if(flag==0) // if the key can not form a square matrix show error and exit
  {
    printf("Invalid key Please try again!\n");
    return 1;
  }
  else 
  {
    printf("Valid key entered! \n");
  }

  int check_bit=k%i;
  printf("k = %d \t i = %d\n",k,i);
  if(check_bit!=0)    // Checking if the plain text needs to append more strings to it
  { 
    check_bit=i-check_bit;    // Finding how many bits I need to append
    printf("Adding Extra bits as the plain text is not enough to form matrix\n");
    while(check_bit!=0)
    {
      plain_text[k++]=check_bit+97;     // Adding a charecter value to it
      check_bit--;
      printf("Plain text Added : %c\n",plain_text[k-1]);
    }
    printf("k = %d \t i = %d\n",k,i);
  }
  
  pl=k;
  int key_mat[i][i];           // Key matrix to store the key in matrix form
  int plain_mat[pl/i][i][1];      // Plain Text matrix to store the plain text in matrix form

  int r=0,c=0; // row and coloumn of key

  printf("\nKey matrix :\n");
  for(int j=0;j<kl;j++)   // kl-key length ; loop - to get all the key values to place in matrix
  {
    int a=key[j]-97;      // The ascii value of a=97  =>  a=ascii_value_of_key - ascii_value_of_a
    key_mat[r][c]=a;      // Storing the value foundin key

    printf("%3d : %c ",key_mat[r][c],key_mat[r][c]+97);
    // printf("%d %d   ",a,key_mat[r][c]);  // Just for checking if the op is comming right or not

    if(c==i-1)    // As max col size is i-1 (as we start the counting from 0)
    {
      c=0;      // Reinitialize key to 0
      r++;      // And increment the row size
      printf("\n");
      continue;   //Don't increase the value of col and jump to next iteration
    }
    c++;  // Else increase the coloumn to the next value
  }

  int pm=0,pr=0,pc=0;   // Main, Row, Coloumn Counter 
  
  for(int j=0;j<pl;j++)
  {
    if(plain_text[j]<97 || plain_text[j]>122)
      break;
    int a=plain_text[j]-97;
    plain_mat[pm][pr][pc]=a;

    if(pr==i-1)   // As the no of rows have max value of i-1 (as we are starting from 0)
    {
      pr=0;       // Reinitialize the value of row to 0
      pm++;       //Increment the main pointer pointing to each smaller matrix
      continue; //Don't increase the value of row and jump to next iteration
    }
    pr++;
  }

  printf("\nPlain Text :\n");
  for(int p=0;p<pm;p++)
  {
    for(int q=0;q<r;q++)
    {
      printf("%3d : %c   ",plain_mat[p][q][0],(plain_mat[p][q][0]+97));
    }
    printf("\n");
  }

  // Calculation Part C = KP mod 26 :
  int cipher_mat[pl/i][i][1];

  for(int ctr=0;ctr<pm;ctr++) 
  {
    for(int p=0;p<r;p++) // row=cololumn same for key using row because c is reinitialized to 0
    {
      cipher_mat[ctr][p][0]=0;
      for(int r=0;r<i;r++)
      {
        cipher_mat[ctr][p][0]+=(key_mat[p][r]*plain_mat[ctr][r][0]);
      }
      if(cipher_mat[ctr][p][0]>26)
      {
        cipher_mat[ctr][p][0]%=26;    // To find the index of the number since the value currently stored is very large
      }

      cipher_mat[ctr][p][0]+=97;  //1+97=98='b'  //Storing the alphabet Ex. id cipher_mat[][][]=0 then 0+97='a'
      if(cipher_mat[ctr][p][0]>122)
      {
        cipher_mat[ctr][p][0]=(cipher_mat[ctr][p][0]-122)+96; //'e'->123 =>   1+96=97
        // suppose the value that we found is > 122 then revert its direction back to 'a'
      }
    }
  }

  printf("\nCipher Text Obtained :\n");
  for(int p=0;p<pm;p++)
  {
    for(int q=0;q<r;q++)
    {
      printf("%3d : %c   ",cipher_mat[p][q][0],cipher_mat[p][q][0]);
    }
    printf("\n");
  }

  printf("\n\n\nPlain Text to Cipher Text Mapping :\n");
  printf("\n==============================================================================================\n");
  for(int p=0;p<pm;p++)
  {
    for(int q=0;q<r;q++)
    {
      printf("%4d : %c   ->   %4d : %c   |   ",plain_mat[p][q][0],(plain_mat[p][q][0]+97),cipher_mat[p][q][0],cipher_mat[p][q][0]);
    }
    printf("\n==============================================================================================\n");
  }
  return 0;
  
}

/*
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-2$ gcc hill_cipher.c
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-2$ ./a.out
Enter the string to encrypt: 
safe messages
Enter the key: 
ciphering
Valid key entered! 
k = 12   i = 3

Key matrix :
  2 : c   8 : i  15 : p 
  7 : h   4 : e  17 : r 
  8 : i  13 : n   6 : g   

Plain Text :
 18 : s     0 : a     5 : f   
  4 : e    12 : m     4 : e   
 18 : s    18 : s     0 : a   
  6 : g     4 : e    18 : s   

Cipher Text Obtained :
104 : h   100 : d   115 : s   
105 : i   111 : o   101 : e   
121 : y   113 : q   111 : o   
 99 : c    97 : a    97 : a   



Plain Text to Cipher Text Mapping :

==============================================================================================
  18 : s   ->    104 : h   |      0 : a   ->    100 : d   |      5 : f   ->    115 : s   |   
==============================================================================================
   4 : e   ->    105 : i   |     12 : m   ->    111 : o   |      4 : e   ->    101 : e   |   
==============================================================================================
  18 : s   ->    121 : y   |     18 : s   ->    113 : q   |      0 : a   ->    111 : o   |   
==============================================================================================
   6 : g   ->     99 : c   |      4 : e   ->     97 : a   |     18 : s   ->     97 : a   |   
==============================================================================================
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-2$ 
*/