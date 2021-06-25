#include<stdio.h>
#include <string.h>
#define N 5
#define SZ 100

int main()
{
  char position[N][N]; //Key matrix
  int ctr=0,ctc=0,c=0; //Counter for key matrix
  char str_key[SZ]; //Key Input
  char plain_txt[SZ],pt[SZ]; //Plain text input

  // Taking input of the plaintext
  printf("\nEnter PalinText:\n");
  scanf("%[^\n]",pt);
  for(int i=0;i<strlen(pt);i++)
  {
    if(pt[i]!=' ' && pt[i]!='.' && pt[i]!='\0')
    {
      plain_txt[c++]=pt[i];
    }
  }

  // Taking input of key
  printf("\nEnter key:\n");
  scanf("%s",str_key);

  // Removing Duplicates if any
  for(int i=0;i<strlen(str_key);i++) 
  {
    for(int j=i+1;j<strlen(str_key);j++) 
    {
      if(str_key[i]==str_key[j])
        str_key[j]='0'; // If duplicate element is found I am replacing it with 0
    }
  } 

  // Filling the key to the matrix
	for(int i=0;i<strlen(str_key);i++) 
  {
    if(str_key[i]=='0')
      continue; //Sikip to next itteration
    position[ctr][ctc]=str_key[i];
    if(ctc==4)
    {
      ctr++;
      ctc=0;
      continue; //Sikip to next itteration
    }
    ctc++;
  }

  // Filling the remaning alphabets to the matrix
  for(int i=0;i<26;i++) 
  {

    // As i comes before j it must already be present in the matrix so skip j
    char check='a'+i; //97+1
    if(check=='j')
      continue;

    int flag=0; //Checking if the alphabet is already present in the array
    for(int i=0;i<strlen(str_key);i++) 
    {
      if(check==str_key[i])
      {
        flag=1;
        break; //If the alphabet is already present then incrementing the value of flag to 1 and comming out of the loop
      }
    }

    //Cheiking if the element is duplicate or not if duplicate goes to increment part of i loop
    if(flag==1)
      continue; 

    // else part
    position[ctr][ctc]='a'+i;
    if(ctc==4)
    {
      ctr++; // Increamenting row value
      ctc=0; // Updating coloumn to 0 again for the new row
      continue;
    }
    // else part
    ctc++;
  }

  // Printing the final Matrix key i.e. position
  printf("\nFinal Matrix Key Position:\n");
  for(int p=0;p<N;p++)
  {
    for(int q=0;q<N;q++)
    {
      printf("%c ",position[p][q]);
    }
    printf("\n");
  }
  
  // Making Pairs for of the plain text
  char pairs[strlen(plain_txt)*2][2];
  int counter=0,count=0,i;
  for(i=0;i+1<strlen(plain_txt); ) // No incrementation here as it would be variable might be 1 or 2    helow =5 4+1<5
  {
    if(plain_txt[i+1]<97 || plain_txt[i+1]>122)
    {
      break;
    }
    if(plain_txt[i]==plain_txt[i+1]) // If there are 2 continious letters
    {
      if(plain_txt[i]!='x') // If there are 2 continious letters that are not 'x'
      {
        pairs[counter][0]=plain_txt[i];
        pairs[counter][1]='x'; 
        i=i+1;
        counter++;
        count=count+1;
      } 
      else // If there are 2 continious letters that are 'x'
      {
        pairs[counter][0]='x';
        pairs[counter][1]='z';
        i=i+1;
        counter++;
        count=count+1;
      }
    }
    else // If there are 2 letters that are not contious
    {
      pairs[counter][0]=plain_txt[i];
      pairs[counter][1]=plain_txt[i+1];
      counter++;
      i=i+2;
      count=count+2;
    }
  }
  // printf("\nletters completed: %d total length:%ld",count,strlen(plain_txt)-2);
  int k;
  // if(count<(strlen(plain_txt)-1) && plain_txt[i]!='\0') 
  // check_bit==1 // Not working for even numbers so didn't use added ascii conditions to the previous condition
  if(count<(strlen(plain_txt)-1) && plain_txt[i]!='\0' && plain_txt[i]>=97 && plain_txt[i]<=122) // If there is a single remaining alpahabet
  {
    pairs[counter][0]=plain_txt[i];
    pairs[counter][1]='z';
    count++;
    counter++;
  }
  for(int p=0;p<counter;p++)
  {
    for(int q=0;q<2;q++)
    {
      if(pairs[p][q]=='j') // If there is a j in the plain text convert it to i
        pairs[p][q]='i';
    }
  }

  // Printing the pairs
  printf("\nPlain Text Pairing:\n");
  for(int p=0;p<counter;p++)
  {
    for(int q=0;q<2;q++)
    {
      printf("%c ",pairs[p][q]);
    }
    printf("\n");
  }

  // Finding cipher text
  char cipher_txt[counter][2];
  for(int p=0;p<counter;p++)
  {
    int one_r,two_r,one_c,two_c;
    for(int r=0;r<N;r++)
    {
      for(int s=0;s<N;s++)
      {
        //Storing the values of pairs when found
        if(pairs[p][0]==position[r][s]) 
        {
          one_r=r;
          one_c=s;
        }
        if(pairs[p][1]==position[r][s])
        {
          two_r=r;
          two_c=s;
        }
      }
    }

    if(one_r==two_r) // If the pair is present in the same row
    {
      if(one_c==4) //If the element is found in the extreem right then updating it to 0 (left most)
      {
        one_c=0;
      }
      else // If not then Updating the index value to their immidiate right
      {
        one_c++;
      }
      if(two_c==4)
      {
        two_c=0;
      }
      else
      {
        two_c++;
      }
    }
    else if(one_c==two_c) // If the pair is present in the same coloumn
    {
      if(one_r==4) //If the element is found in the bottom then updating it to 0 (top most)
      {
        one_r=0;
      }
      else // If not then Updating the index value to their immidiate bottom
      {
        one_r++;
      }
      if(two_r==4)
      {
        two_r=0;
      }
      else
      {
        two_r++;
      }
    }
    else // If the pair is present nither in the same row or coloumn
    {
      // replacing them with the alphabets in the same row respectively but at other pair of corner
      int temp_c=one_c;
      one_c=two_c;
      two_c=temp_c;
    }

    // Storing the cipher text
    cipher_txt[p][0]=position[one_r][one_c];
    cipher_txt[p][1]=position[two_r][two_c];
  }

  // Printing the cipher text found
  printf("\nPlayfair Cipher Found:\n");
  for(int p=0;p<counter;p++)
  {
    for(int q=0;q<2;q++)
    {
      printf("%c",cipher_txt[p][q]);
    }
  }
  printf("\n");

	return 0;
}

// Output:
/*
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-2$ ./a.out

Enter PalinText:
must see you over cadogan west.coming at once.

Enter key:
largest

Final Matrix Key Position:
l a r g e 
s t b c d 
f h i k m 
n o p q u 
v w x y z 

letters completed: 36 total length:36
Plain Text Pairing:
m u 
s t 
s e 
e y 
o u 
o v 
e r 
c a 
d o 
g a 
n w 
e s 
t c 
o m 
i n 
g a 
t o 
n c 
e z 

Playfair Cipher Found:
uztbdlgzpnnwlgtgtuerovldbduhfperhwqsde
haruto@DESKTOP-E1O75P0:/mnt/d/6thSem/CNS/Assignment-2$ 
*/