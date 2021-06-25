import java.util.Scanner;
public class DES {
	
//	Initial permutation matrix
	static int[] initial_permutation = { 58, 50, 42, 34, 26, 18, 10, 2, 
																			60, 52, 44, 36, 28, 20, 12, 4, 
																			62, 54, 46, 38, 30, 22, 14, 6,
																			64, 56, 48, 40, 32, 24, 16, 8,
																			57, 49, 41, 33, 25, 17, 9, 1, 
																			59, 51, 43, 35, 27, 19, 11, 3, 
																			61, 53, 45, 37, 29, 21, 13, 5, 
																			63, 55, 47, 39, 31, 23, 15, 7 };	// 64
	
	static int[] permuted_choice1 = {57, 49, 41, 33, 25, 17, 9, 1,
																		58, 50, 42, 34, 26, 18, 10, 2,
																		59, 51, 43, 35, 27, 19, 11, 3,
																		60,	52, 44, 36, 63, 55, 47, 39,
																		31, 23, 15, 7, 62, 54, 46, 38,
																		30, 22, 14, 6, 61, 53, 45, 37,
																		29, 21, 13, 5, 28, 20, 12, 4};		// 56
	
	static int[] permuted_choice2 = { 14, 17, 11, 24, 1, 5, 3, 28,
																		15, 6, 21, 10, 23, 19, 12, 4,
																		26, 8, 16, 7, 27, 20, 13, 2,
																		41, 52, 31, 37, 47, 55, 30, 40,
																		51, 45, 33, 48, 44, 49, 39, 56,
																		34, 53, 46, 42, 50, 36, 29, 32 };	// 48
	
	static int[] expansion_permutation = { 32, 1, 2, 3, 4, 5, 4, 5,
																					6, 7, 8, 9, 8, 9, 10, 11,
																				12, 13, 12, 13, 14, 15, 16, 17,
																				16, 17, 18, 19, 20, 21, 20, 21,
																				22, 23, 24, 25, 24, 25, 26, 27,
																				28, 29, 28, 29, 30, 31, 32, 1 };	// 48
	static int[][][] substitution_box = {
																			{ { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
																				{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
																				{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
																				{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } },
														
																			{ { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
																				{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
																				{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
																				{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } },
																			{ { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
																				{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
																				{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
																				{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } },
																			{ { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
																				{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
																				{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
																				{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } },
																			{ { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
																				{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
																				{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
																				{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } },
																			{ { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
																				{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
																				{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
																				{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } },
																			{ { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
																				{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
																				{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
																				{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } },
																			{ { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
																				{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
																				{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
																				{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } }
																	};
			
	static int[] permutation = {16, 7, 20, 21, 29, 12, 28, 17,
															1, 15, 23, 26, 5, 18, 31, 10,
															2, 8, 24, 14, 32, 27, 3, 9,
															19, 13, 30, 6, 22, 11, 4, 25};	// 32

	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		
//		System.out.println("Enter the Hexadesimal String to encript");
//		String plain_text=sc.nextLine();
//		System.out.println("Enter the Hexadesimal String to encript");
//		String initial_key=sc.nextLine();
		
		String plain_text="0123456789ABCDEF";
		String initial_key="0123456789ABCDEF";
		
		if((plain_text.length() % 16) != 0)			// Cheking if the plain text can be divided into 64 bit blocks (16*4=64)
		{
			plain_text=append_dummyBits(plain_text);
			System.out.println("Plain text updated to suit size : "+plain_text);
		}
		if((initial_key.length() % 16) != 0)		// Cheking if the key can be divided into 64 bit blocks (16*4=64)
		{
			initial_key=append_dummyBits(initial_key);
			System.out.println("Key updated to suit size : "+initial_key);
		}
		
		String encripted_text="";
		for(int ctr=0,count=1;ctr<plain_text.length();ctr=ctr+16,count++)
		{
			System.out.println("\n\nBlock "+count);
			encripted_text=DES.encript(plain_text.substring(ctr, ctr+16),initial_key);
		}
		
		// System.out.println("Encripted Text is found to be : "+encripted_text);
	}

	private static String append_dummyBits(String text) {
		// TODO Auto-generated method stub
		while((text.length()%16)!=0)	// Checking if the text can be divided into 64 bit blocks (16*4=64)
		{
			text=text+"0";				// Appending 0 as dummy bits
		}
		return text;
	}
	

	private static String encript(String plain_text, String initial_key) {
		// TODO Auto-generated method stub
		String encripted_text="";
		
//		Initial Permutation
		String perm_pt=permute_text(plain_text,initial_permutation);			
		System.out.println("The value after 1st permutation Plain text : "+perm_pt);
		String l0=perm_pt.substring(0, 32);
		String r0=perm_pt.substring(32, 64);
		System.out.println("The value of L0 : "+l0+" length : "+l0.length());
		System.out.println("The value of R0 : "+r0+" length : "+r0.length());
		
//		Convertion of key from 64 to 56 bits by PC1
		String perm1_key_56=permute_text(initial_key,permuted_choice1);
		System.out.println("The value after PC1 : "+perm1_key_56 + " Length of key : "+perm1_key_56.length());
		String c0=perm1_key_56.substring(0,28);
		String d0=perm1_key_56.substring(28,56);
		System.out.println("The value of C0 : "+c0);
		System.out.println("The value of D0 : "+d0);
		
//		Finding c1 d1
		String c1=c0.substring(1)+c0.charAt(0);
		String d1=d0.substring(1)+d0.charAt(0);
		System.out.println("The value of C1 (C0 Shift to left by 1) : "+c1);
		System.out.println("The value of D1 (D0 Shift to left by 1) : "+d1);
		
//		Applying PC2
		String c1d1=c1+d1;
		System.out.println("Combining c1 d1 we get : "+c1d1+" Length : "+c1d1.length());
		String perm2_key_48=permute_key(c1d1,permuted_choice2);
		System.out.println("The value after PC2 : "+perm2_key_48 + " Length of key : "+perm2_key_48.length());
		
//		Function Module
		String r0_fun_block_op = function_block(r0,perm2_key_48);
		System.out.println("The output of Function Block : "+r0_fun_block_op + " Length of key : "+r0_fun_block_op.length());
		
		String r1 = xor(r0_fun_block_op,l0);	//	XOR the OP of Function block is then XORed with L0 and will be treated as R1
		String l1 = r0;							//	The unchanged value of R0 is then treated as L1
		String round1_bin = l1+r1;					//	Combining the values of L1R1 we get 64 bits that is the output of the first round of DES
		String round1 = bin_hex(round1_bin);
		
		System.out.println("The value of L0 : "+l1+" length : "+l1.length());
		System.out.println("The value of R0 : "+r1+" length : "+r1.length());
		System.out.println("Round 1 Output in Binary : "+round1_bin+" length : "+round1_bin.length());
		System.out.println("Round 1 Output in HexaDecimal : "+round1+" length : "+round1.length());
		
		return encripted_text;
	}

	private static String bin_hex(String txt) {
		// TODO Auto-generated method stub
		String res="";
		for(int i=0;i<txt.length();i+=4)
		{
			String temp = txt.substring(i,i+4);
			int num = Integer.parseInt(temp,2);
			switch(num)
			{
				case 10: res+='A'; break;
				case 11: res+='B'; break;
				case 12: res+='C'; break;
				case 13: res+='D'; break;
				case 14: res+='E'; break;
				case 15: res+='F'; break;
				default: res+=Integer.toString(num);
			}
		}
		return res;
	}

	private static String permute_key(String text, int[] position) {
		// TODO Auto-generated method stub
		String perm_pt="";
		
		for(int i=0;i<position.length;i++)
		{
			perm_pt=perm_pt+text.charAt(position[i]-1);
		}
		
		return perm_pt;
	}
	
	private static String permute_text(String text, int[] position) {
		// TODO Auto-generated method stub
		String perm_pt="";
		
		String bin_pt=hex_bin(text);
		for(int i=0;i<position.length;i++)
		{
			perm_pt=perm_pt+bin_pt.charAt(position[i]-1);
		}
		
		return perm_pt;
	}

	private static String hex_bin(String text) {
		// TODO Auto-generated method stub
		
		String bin_pt="";
//		int size = text.length();
//		while(size!=0)
//		{
//			switch(text.charAt(size-1))
//			{
//				case '0': bin_pt="0000"+bin_pt; break;
//				case '1': bin_pt="0001"+bin_pt; break;
//				case '2': bin_pt="0010"+bin_pt; break;
//				case '3': bin_pt="0011"+bin_pt; break;
//				case '4': bin_pt="0100"+bin_pt; break;
//				case '5': bin_pt="0101"+bin_pt; break;
//				case '6': bin_pt="0110"+bin_pt; break;
//				case '7': bin_pt="0111"+bin_pt; break;
//				case '8': bin_pt="1000"+bin_pt; break;
//				case '9': bin_pt="1001"+bin_pt; break;
//				case 'A': bin_pt="1010"+bin_pt; break;
//				case 'B': bin_pt="1011"+bin_pt; break;
//				case 'C': bin_pt="1100"+bin_pt; break;
//				case 'D': bin_pt="1101"+bin_pt; break;
//				case 'E': bin_pt="1110"+bin_pt; break;
//				case 'F': bin_pt="1111"+bin_pt; break;
//			}
//			size--;
//			
//		}
		
		int ctr=text.length();
		while(ctr!=0)
		{
			String bin=Integer.toBinaryString(Integer.parseUnsignedInt(Character.toString(text.charAt(ctr-1)), 16));
			while(bin.length()<4)
			{
				bin="0"+bin;
			}
			bin_pt=bin+bin_pt;
			ctr--;
		}
		
		return bin_pt;
	}
	

	private static String xor(String str1, String str2) {
		// TODO Auto-generated method stub
		String res= "";
		for(int i=0;i<str1.length();i++)
		{
			if(str1.charAt(i)==str2.charAt(i))
			{
				res=res+"0";
			}
			else
			{
				res=res+"1";
			}
		}
		return res;
	}
	
	private static String function_block(String r, String perm_key_48) {
		// TODO Auto-generated method stub
//		Permutation using Expansion Box
		String r_exp = permute_key(r,expansion_permutation);
		System.out.println("After Expansion(R0) : "+r_exp+" Length : "+r_exp.length());
		
//		XOR op of Expansion box = 48 with 48 bit key generated
		String r_exp_xor = xor(r_exp,perm_key_48);
		System.out.println("Output of Expansion(R0) XOR PC2 key : "+r_exp_xor+" Length : "+r_exp_xor.length());
//		Op is then put in Substitution Box and turned to 32 bits And concatinate them
		String sbox_op = substitution_box_permutation(r_exp_xor);
		System.out.println("Output of Substitution Box : "+sbox_op+" Length : "+sbox_op.length());
//		Which is again permuted by putting into Permutation Box Which is the OP of Function Block
		String res=permute_key(sbox_op,permutation);
		return res;
	}

	private static String substitution_box_permutation(String str) {
		// TODO Auto-generated method stub
		String res="";
		for(int i=0;i<str.length();i=i+6)
		{
			String curr = str.substring(i, i+6);	// Select 6 bits
			int main_ptr=i/6;						// Finding which s-box value of i = 0 , 6 , 12 ..... , 42
													// 0/6 = 0 row1		6/6 = 1		12/6 = 2 ...... 42/6 = 7
			int row = Integer.parseUnsignedInt(Character.toString(curr.charAt(0))+curr.charAt(5), 2);
			int col = Integer.parseUnsignedInt(curr.substring(1, 5),2);
			
			int val = substitution_box[main_ptr][row][col];
			
			if(val==10) {
				res=res+hex_bin("A");
			} else if(val==11) {
				res=res+hex_bin("B");
			} else if(val==12) {
				res=res+hex_bin("C");
			} else if(val==13) {
				res=res+hex_bin("D");
			} else if(val==14) {
				res=res+hex_bin("E");
			} else if(val==15) {
				res=res+hex_bin("F");
			} else {
				res=res+hex_bin(Integer.toString(val));
			}
		}
		return res;
	}


}
