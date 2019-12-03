/*****************************************/
/*  			                         */
/*  Frequency Normalization Encrypt Pgm  */
/*  			                         */
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
#define S_start 37
#define T_start 41 // was 52; +1 to start position, incorrect
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

void reverse_otp(unsigned char *in_byte, long int x, int modkey, unsigned char *key){
	int z;unsigned char shingle;unsigned int a;signed int b;
	x--;
	z=x%modkey;
	a=*in_byte;
	b=a;
	if ((x%2)==0) b=b-key[z]; // modulus 2 == even
	if ((x%2)!=0) b=b+key[z];  // modulus 2 == odd
	*in_byte=b;
	//printf("b=%x\n");
	return;
}

main(int argc, char *argv[]){

unsigned char j, shingle, ans;
long int x, file_length;
int y, modkey;
int E,T,O,A,N,I,S;
int e,t,o,a,n,i,s;
int sp;
char erasecmd[20]="erase ";
char filename[13]={'\0'};

unsigned char in_byte, out_byte, key[15];
char * inb_addr;

/* declare file pointer */

FILE *fp_in, *fp_out, *fp_scratch;
/*
strcpy(filename,argv[1]);
fp_in=fopen(filename,"rb");
if (fp_in == NULL) {
	printf("Could not open input file %s",filename);
	getchar();
	exit(1);
	}
strcpy(filename,argv[1]); 
strcat(filename,".tec");  
fp_out=fopen(filename,"wb");
if (fp_out == NULL) {
	printf("Could not open output file %s",filename);
	getchar();
	exit(1);
	}
*/

while(0==0) {
	printf("Please enter filename: \n");
	gets(filename);
	if (filename[0]=='\0') continue;
	break;
}
strcat(filename,".tec");
fp_in=fopen(filename,"rb");
if (fp_in == NULL) {
	printf("Could not open %s.  Not a TEC file\n",filename);
	getchar();
	exit(1);
}
strcat(filename,"-decrypt");
fp_out=fopen(filename,"wb");
if (fp_out == NULL) {
	printf("Could not open output file %s",filename);
	getchar();
	exit(1);
	}


/*  Display Version  */
/*  FNE Version 1.0  */

printf("FNE Version 1.0C\n");
printf("The output file has the same name as the input file with a \"-decrypt\" extension.\n");
printf("Press <enter> to continue");
getchar();

/*** MAIN PROCESS ***/

// get key
inb_addr=&in_byte;
// 15 numbers/characters/symbols
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
//if ((ans=='N') || (ans=='n')) printf("\n");
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


// get date time

// display version #


// set modular key counters
E=T=O=A=N=I=S=0;
//E=0;
//T=0;
//O=0;
//N=0;
//I=0;
//N=0;
//S=0;

e=t=o=a=n=i=s=0;
sp=0;
x=0;
//for(x=0;x<filelength(fileno(fp_in));x++) {
//	if(eof(fp_in)!=0) break;
while(0==0) { // file position pointer
	if(x>=filelength(fileno(fp_in))) break;
	while(1) { // too keep value
		in_byte=getc(fp_in);
		x++;

		printf("before reversal inbyte=%x\n",in_byte);
		//reverse otp
		reverse_otp(inb_addr,x,modkey,key);
		printf("after reversal inbyte=%x\n",in_byte);

//***Decode 
		if((in_byte>=0)&&(in_byte<=4)) {	// 0-4--A
			out_byte='A';
			break;
		} // end in byte == A
/*		if(in_byte=='B' || 'C' || 'D') {
			out_byte=in_byte-61; // 5
			break; 
		}
*/		
		if(in_byte==5) {
			out_byte='B'; // 5--B
			break; 
		}
		if(in_byte==6) {
			out_byte='C'; // 6--C
			break; 
		}
		if(in_byte==7) {
			out_byte='D'; // 7--D
			break; 
		}
		if((in_byte>=8)&&(in_byte<=13)) {  // 8-13--E
			out_byte='E';
			break;
		} // end in byte == E
/*		if(in_byte=='F' || 'G' || 'H') { // 14-16
			out_byte=in_byte-56;
			break;  
		}
*/
		if(in_byte==14) { // 14--F
			out_byte='F';
			break;  
		}
		if(in_byte==15) { // 15--G
			out_byte='G';
			break;  
		}
		if(in_byte==16) { // 16--H
			out_byte='H';
			break;  
		}
		if((in_byte>=17)&&(in_byte<=21)) {  // 17-21
			out_byte='I';
			break;
		} // end in byte == I
/*		if(in_byte=='J' || 'K' || 'L' || 'M') { // 18-21
			out_byte=in_byte-52;
			break;  
		}
*/
		if(in_byte==22) { // 22--J
			out_byte='J';
			break;  
		}
		if(in_byte==23) { // 23--K
			out_byte='K';
			break;  
		}
		if(in_byte==24) { // 24--L
			out_byte='K';
			break;  
		}
		if(in_byte==25) { // 25--M
			out_byte='M';
			break;  
		}
		if((in_byte>=26)&&(in_byte<=29)) {  // 26-29--N
			out_byte='N';
			break;
		} // end in byte == N
		if((in_byte>=30)&&(in_byte<=33)) {  //  30-33--O
			out_byte='O';
			break;
		} // end in byte == O
/*		if(in_byte=='P' || 'Q' || 'R') { // 34-36 
			out_byte=in_byte-46;
			break;  
		}
*/
		if(in_byte==34) { // 34--P
			out_byte='P';
			break;  
		}
		if(in_byte==35) { // 35--Q
			out_byte='Q';
			break;  
		}
		if(in_byte==36) { // 36--R
			out_byte='R';
			break;  
		}
		if((in_byte>=37)&&(in_byte<=40)) {  // 37-40
			out_byte='S';
			break;
		} // end in byte == S
		if((in_byte>=41)&&(in_byte<=46)) {  // 41-46
			out_byte='T';
			break;
		} // end in byte == T
		// if(in_byte=='T') break; didn't change anything.
/*		if(in_byte=='U' || 'V' || 'W' || 'X' || 'Y' || 'Z') {  // 58-63
			out_byte=in_byte-27;
			break;  
		}
*/
		if(in_byte==47) {  // 47--U
			out_byte='U';
			break;  
		}
		if(in_byte==48) {  // 48--V
			out_byte='V';
			break;  
		}
		if(in_byte==49) {  // 49--W
			out_byte='W';
			break;  
		}
		if(in_byte==50) {  // 50--X
			out_byte='X';
			break;  
		}
		if(in_byte==51) {  // 51--Y
			out_byte='Y';
			break;  
		}
		if(in_byte==52) {  // 52--Z
			out_byte='Z';
			break;  
		}
// miniscule
printf("got here a\n");
		if((in_byte>=53)&&(in_byte<=57)) {  // 53-57
			out_byte='a';
			break;
		} // end in byte == a
/*		if(in_byte=='b' || 'c' || 'd') {  // 65-67
			out_byte=in_byte-33;
			break;  
		}
*/
		if(in_byte==58) {  // 58
			out_byte='b';
			break;  
		}
		if(in_byte==59) {  // 59
			out_byte='c';
			break;  
		}
		if(in_byte==60) {  // 60
			out_byte='d';
			break;  
		}
		if((in_byte>=61)&&(in_byte<=66)) {  // 61-66
			out_byte='e';
			break;
		} // end in byte == e
/*		if(in_byte=='f' || 'g' || 'h') {  // 74-76
			out_byte=in_byte-28;
			break;  
		}
*/
		if(in_byte==67) {  // 67
			out_byte='f';
			break;  
		}
		if(in_byte==68) {  // 68
			out_byte='g';
			break;  
		}
		if(in_byte==69) {  // 69
			out_byte='h';
			break;  
		}
		if((in_byte>=70)&&(in_byte<=74)) {  // 70-74
			out_byte='i';
			break;
		} // end in byte == i
/*		if(in_byte=='j' || 'k' || 'l' || 'm') {  // 82-85
			out_byte=in_byte-24;
			break;  
		}
*/
		if(in_byte==75) {  // 75
			out_byte='j';
			break;  
		}
		if(in_byte==76) {  // 76 
			out_byte='k';
			break;  
		}
		if(in_byte==77) {  // 77 
			out_byte='l';
			break;  
		}
		if(in_byte==78) {  // 78 
			out_byte='m';
			break;  
		}
		if((in_byte>=79)&&(in_byte<=82)) {  // 79-82
			out_byte='n';
			break;
		} // end in byte == n
		if((in_byte>=83)&&(in_byte<=86)) {  // 83-86
			out_byte='o';
			break;
		} // end in byte == o
/*		if(in_byte=='p' || 'q' || 'r') {  // 91-93
			out_byte=in_byte-21;
			break; 
		}
*/
		if(in_byte==87) {  // 87--p
			out_byte='p';
			break; 
		}
		if(in_byte==88) {  // 88--q
			out_byte='q';
			break; 
		}
		if(in_byte==89) {  // 89--r
			out_byte='r';
			break; 
		}
		if((in_byte>=90)&&(in_byte<=93)) {  // 90-93
			out_byte='s';
			break;
		} // end in byte == s
		if((in_byte>=94)&&(in_byte<=99)) {  // 94-99
			out_byte='t';
			t++;
			if (t==6) t=0;
			break;
		} // end in byte == I
/*		if(in_byte=='u' || 'v' || 'w' || 'x' || 'y' || 'z') { // 104-109
			out_byte=in_byte-13;
			break;  
		}
*/
		if(in_byte==100) { // 100
			out_byte='u';
			break;  
		}
		if(in_byte==101) { // 101
			out_byte='v';
			break;  
		}
		if(in_byte==102) { // 102
			out_byte='w';
			break;  
		}
		if(in_byte==103) { // 103
			out_byte='x';
			break;  
		}
		if(in_byte==104) { // 104
			out_byte='y';
			break;  
		}
		if(in_byte==105) { // 105
			out_byte='z';
			break;  
		}
		
// other characters

		//if((in_byte>=0) && (in_byte <=31)) {  // 0-31 start @ 110
		if((in_byte>=110) && (in_byte <=141)) {  // 0-31 start @ 110
			out_byte=in_byte-110;
			break;  
		}
		if((in_byte>=142) && (in_byte <=147)) {  // space 32, spread out 142-148
			out_byte=32; // space
			break;
		} // end in byte == space
		//if((in_byte>32) && (in_byte <=64)) {  // 0-13 start @ 110
		//if((in_byte>=148) && (in_byte <=180)) {  // > 148
		if((in_byte>=148) && (in_byte <=180)) {  // > 148
			//out_byte=in_byte-148;
			out_byte=in_byte-116;
			break;  
		}
	} // end while 0=0 setting output value

	// add key
	//otp(inb_addr,x,modkey,key);

	printf("after decode outbyte=%x\n",out_byte);

	// output
	putc(out_byte,fp_out);
	//if(x>=filelength(fileno(fp_in))) break;
} // end for(x=0;x<filelength(fileno(fp_in));x++)
fflush(fp_out);


fclose(fp_out);
fclose(fp_in);

printf("Process Complete");
// test code -- chk output

/*
// will need to adjust to filename as string
strcpy(filename,argv[1]);
strcat(filename,".tec");
fp_in=fopen(filename,"rb");
if (fp_in == NULL) {
	printf("Could not open output for examination\n");
	getchar();
	exit (1);
	}

for (x=0;x<filelength(fileno(fp_in));x++) {
	shingle=getc(fp_in);
printf("\nshingle=%x %d %c",shingle,shingle,shingle);
getchar();
	// shingle<<=8;
}
*/

fclose(fp_in);
/*strcat(erasecmd,argv[1]);*/
/*strcat(erasecmd,".tmp");*/
/*system(erasecmd);*/

// backdoor routine -- embed key
// read in file


exit(0);


}  /* end pgm */