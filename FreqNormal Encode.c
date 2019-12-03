/*****************************************/
/*  			                 */
/*  Frequency Normalization Encrypt Pgm  */
/*                by Givon Zirkind       */
/*  			                 */
/*****************************************/

/*  Frequency Normalization Encryption Version 1.0  */

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <math.h>
#include <process.h>
#include <conio.h>

#define A_start 0
#define E_start 8
#define I_start 17
#define N_start 26
#define O_start 30
#define S_start 37 // was 49
#define T_start 41 // was 52
#define a_start 53 // was 64
#define e_start 61 // was 68
#define i_start 70 // was 77
#define n_start 79 // was 83
#define o_start 83 // was 87
#define s_start 90 // was 94
#define t_start 94 // was 98
#define sp_start 142 // was 141

void otp(unsigned char *in_byte, long int x, int modkey, unsigned char *key){
	int z;unsigned char shingle;unsigned int a;signed int b;
	x--;
	z=x%modkey;
	a=*in_byte;
	b=a;
	if ((x%2)==0) b=b+key[z]; // modulus 2 == even
	if ((x%2)!=0) b=b-key[z];  // modulus 2 == odd
	*in_byte=b;
	return;
}

main(int argc, char *argv[]){

unsigned char j, shingle, ans;
long int x, file_length;
int modkey;
unsigned int y;
signed int z;
int E,T,O,A,N,I,S;
int e,t,o,a,n,i,s;
int sp;
char erasecmd[20]="erase ";
char filename[13]={'\0'};

unsigned char in_byte, out_byte, key[15];
char * inb_addr;

/* declare file pointer */

FILE *fp_in, *fp_out, *fp_scratch;

while(0==0) {
	printf("Please enter filename: \n");
	gets(filename);
	if (filename[0]=='\0') continue;
	break;
}
fp_in=fopen(filename,"rb");
if (fp_in == NULL) {
	printf("Could not open input file %s",filename);
	getchar();
	exit(1);
}
strcat(filename,".tec");  
fp_out=fopen(filename,"wb");
if (fp_out == NULL) {
	printf("Could not open output file %s",filename);
	getchar();
	exit(1);
	}


/*  Display Version  */
/*  FNE Version 1.0  */

printf("FNE Version 1.0\n");
printf("The output file has the same name as the input file with a \"TEC\" extension.\n");
printf("Press <enter> to continue");
getchar();

/*** MAIN PROCESS ***/

inb_addr=&out_byte;
REENTERKEY: 
for (x=0;x<15;x++) key[x]='\0';
printf("Enter a key.  Minimum 1 Character.  Maximum 15 Characters\n");
printf("All characters that can be typed at a keyboard are valid.\n");
printf("Some systems may require a Caps Lock to enter small letters (miniscule).\n");
printf("Null keys are permitted.\n");
printf("Using a null key will not provide \"uncrackable\" encryption.\n");
printf("Please enter a key:\n");
for (x=0;x<15;x++) { // enter key
	key[x]=getche();
	if (key[x]==13) break;
} // end key entry
printf("\nYour Key is: %s",key);
if (key[0]==13)  printf("Your key is a null key.\n");
else printf("\n");
printf("Correct? (Y/N) \n");
ans=getche();
printf("\n");
if ((ans=='N') || (ans=='n')) goto REENTERKEY;
if (key[0]==13) { // <enter> null key
	printf("Your key is a null key.\n");
	printf("A null key is permitted.  However, a null key gives less security.\n");
	printf("Using a null key will not provide \"uncrackable\" encryption.\n");
	printf("Re-enter a key? (Y/N)\n");
	ans=getche();
	//if ((ans=='Y') || (ans=='y')) printf("\n");
	printf("\n");
	if ((ans=='Y') || (ans=='y')) goto REENTERKEY;
} // end entered null key
if ((ans!='Y') && (ans!='y')) goto REENTERKEY;
modkey=strlen(key)-1; // remove enter key

// display version #

// set modular key counters
//E=T=O=A=N=I=S=0;
E=0;
T=0;
O=0;
A=0;
N=0;
I=0;
S=0;

e=t=o=a=n=i=s=0;
sp=0;
x=0;
while(0==0) { // file position pointer
	if(x>=filelength(fileno(fp_in))) break;
	while(1) { // too keep value
		in_byte=getc(fp_in);
		x++;
		if(in_byte=='A') {	// 0-4
			out_byte=A_start+A;
			//y=A_start+A;
			A++;
			if (A==5) A=0;
			break;
		} // end in byte == A
		if(in_byte=='B') {
			out_byte=in_byte;
			out_byte=out_byte-61;  // 5
			break; 
		}
		if(in_byte=='C') {
			out_byte=in_byte-61; // 6
			break; 
		}
		if(in_byte=='D') {
			out_byte=in_byte-61; // 7
			break; 
		}
		if(in_byte=='E') {  // 8-13
			out_byte=E_start+E;
			E++;
			if (E==6) E=0;
			break;
		} // end in byte == E
		if(in_byte=='F') { // 14
			out_byte=in_byte-56;
			break;  
		}
		if(in_byte=='G') { // 15
			out_byte=in_byte-56;
			break;  
		}
		if(in_byte=='H') { // 16
			out_byte=in_byte-56;
			break;  
		}
		if(in_byte=='I') {  // 17-21
			out_byte=I_start+I;
			I++;
			if (I==5) I=0;
			break;
		} // end in byte == I
		if(in_byte=='J') { // 22
			out_byte=in_byte-52;
			break;  
		}
		if(in_byte=='K') { // 23
			out_byte=in_byte-52;
			break;  
		}
		if(in_byte=='L') { // 24
			out_byte=in_byte-52;
			break;  
		}
		if(in_byte=='M') { // 25
			out_byte=in_byte-52;
			break;  
		}
		if(in_byte=='N') {  // 26-29
			out_byte=N_start+N;
			N++;
			if (N==4) N=0;
			break;
		} // end in byte == N
		if(in_byte=='O') {  //  30-33
			out_byte=O_start+O;
			O++;
			if (O==4) O=0;
			break;
		} // end in byte == I
		if(in_byte=='P') { // 34 
			out_byte=in_byte-46;
			break;  
		}
		if(in_byte=='Q') { // 35 
			out_byte=in_byte-46;
			break;  
		}
		if(in_byte=='R') { // 36 
			out_byte=in_byte-46;
			break;  
		}
		if(in_byte=='S') {  // 37-40
			out_byte=S_start+S;
			S++;
			if (S==4) S=0;
			break;
		} // end in byte == S
		if(in_byte=='T') {  // 41-46
			out_byte=T_start+T;
			T++;
			if (T==6) T=0;
			break;
		} // end in byte == T
		// if(in_byte=='T') break; didn't change anything.
		if(in_byte=='U') {  // 47
			out_byte=in_byte-38;
			break;  
		}
		if(in_byte=='V') {  // 48
			out_byte=in_byte-38;
			break;  
		}
		if(in_byte=='W') {  // 49
			out_byte=in_byte-38;
			break;  
		}
		if(in_byte=='X') {  // 50
			out_byte=in_byte-38;
			break;  
		}
		if(in_byte=='Y') {  // 51
			out_byte=in_byte-38;
			break;  
		}
		if(in_byte=='Z') {  // 52
			out_byte=in_byte-38;
			break;  
		}
// miniscule
printf("got here a\n");
		if(in_byte=='a') {  // 53-57
			out_byte=a_start+a;
			a++;
			if (a==5) a=0;	
			break;
		} // end in byte == a
		if(in_byte=='b') {  // 58
			out_byte=in_byte-40;
			break;  
		}
		if(in_byte=='c') {  // 59
			out_byte=in_byte-40;
			break;  
		}
		if(in_byte=='d') {  // 60
			out_byte=in_byte-40;
			break;  
		}

		if(in_byte=='e') {  // 61-66
			out_byte=e_start+e;
			e++;
			if (e==6) e=0;
			break;
		} // end in byte == e
		if(in_byte=='f') {  // 67
			out_byte=in_byte-35;
			//z=in_byte-35;
			break;  
		}
		if(in_byte=='g') {  // 68
			out_byte=in_byte-35;
			break;  
		}
		if(in_byte=='h') {  // 69
			out_byte=in_byte-35;
			break;  
		}
		if(in_byte=='i') {  // 70-74
			out_byte=i_start+i;
			i++;
			if (i==5) i=0;
			break;
		} // end in byte == i
		if(in_byte=='j') {  // 75
			out_byte=in_byte-31;
			break;  
		}
		if(in_byte=='k') {  // 76 
			out_byte=in_byte-31;
			break;  
		}
		if(in_byte=='l') {  // 77 
			out_byte=in_byte-31;
			break;  
		}
		if(in_byte=='m') {  // 78 
			out_byte=in_byte-31;
			break;  
		}
		if(in_byte=='n') {  // 79-82
			out_byte=n_start+n;
			n++;
			if (n==4) n=0;
			break;
		} // end in byte == n
		if(in_byte=='o') {  // 83-86
			out_byte=o_start+o;
			o++;
			if (o==4) o=0;
			break;
		} // end in byte == o
		if(in_byte=='p') {  // 87
			out_byte=in_byte-25;
			break; 
		}
		if(in_byte=='q') {  // 88
			out_byte=in_byte-25;
			break; 
		}
		if(in_byte=='r') {  // 89
			out_byte=in_byte-25;
			break; 
		}
		if(in_byte=='s') {  // 90-93
			out_byte=s_start+s;
			s++;
			if (s==4) s=0;
			break;
		} // end in byte == s
		if(in_byte=='t') {  // 94-99
			out_byte=t_start+t;
			t++;
			if (t==6) t=0;
			break;
		} // end in byte == I
		if(in_byte=='u') { // 100
			out_byte=in_byte-17;
			break;  
		}
		if(in_byte=='v') { // 101
			out_byte=in_byte-17;
			break;  
		}
		if(in_byte=='w') { // 102
			out_byte=in_byte-17;
			break;  
		}
		if(in_byte=='x') { // 103
			out_byte=in_byte-17;
			break;  
		}
		if(in_byte=='y') { // 104
			out_byte=in_byte-17;
			break;  
		}
		if(in_byte=='z') { // 105
			out_byte=in_byte-17;
			break;  
		}
		
// other characters

		if((in_byte>=0) && (in_byte <=31)) {  // 0-31 start @ 110
			out_byte=in_byte+110;
			break;  
		}
		if(in_byte==32) {  // space 32, spread out 142-147
			out_byte=sp_start+sp;
			sp++;
			if (sp==6) sp=0;
			break;
		} // end in byte == space
		if((in_byte>32) && (in_byte <=64)) {  // 0-13 start @ 110
			//out_byte=in_byte+148;
			out_byte=in_byte+116;
			break;  
		}
	} // end while 0=0 setting output value

	printf("before key outbyte=%x\n",out_byte);

	// add key
	otp(inb_addr,x,modkey,key);

	printf("after key outbyte=%x\n",out_byte);
	// output
	putc(out_byte,fp_out);
	getch();
} // end for(x=0;x<filelength(fileno(fp_in));x++)
fflush(fp_out);


fclose(fp_out);
fclose(fp_in);

printf("Process Complete");

fclose(fp_in);

exit(0);

}  /* end pgm */
