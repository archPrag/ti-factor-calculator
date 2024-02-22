// Program Name:Arthur
// Author(s):
// License:
// Description:

#include <ti/screen.h>
#include<stdlib.h>

int charToInt(char*string,int size){
	int placeHolder=0;
	int index=0;
	while (index<size){
		placeHolder=placeHolder*10+(string[index]-'0');
		index++;
		if (string[index]=='\0'){
			break;
		}
	}
	return placeHolder;
}

int isNextPrime(int*previous,int size,int candidate){
	for(int index=0;index<size;index++){
		if(candidate%previous[index]==0){
			return 0;
		}
	}
	return 1;
}
int exponentIn(int number,int prime){
	int index=0;
	while (number%prime==0){
		number/=prime;
		index++;
	}
	return index;
}
int digitsNeeded(int number){
	int placeHolder=0;
	while (number>=1){
    number/=10;
		placeHolder++;
	}
	return placeHolder;
}
void printNumber(int number){
  int size=digitsNeeded(number);
  char string[size+1];
  for(int i=0;i<size;i++){
		string[size-i-1]='0'+number%10;
		number/=10;
	}
  string[size]='\0';
  os_PutStrFull(string);
}
	
// R/efer to the CE toolchain documentation for help:
// https://ce-programming.github.io/toolchain/libraries/index.html
int main(void) {
	char string[10];
	int*primes=(int*)calloc(1,sizeof(int));
	int size=1;
  os_ClrHome();
	os_GetStringInput("Number",string,10);
	int number=charToInt(string,10);
	primes[0]=2;
	int index=3;
	while (primes[size-1]<=number){
		if (isNextPrime(primes,size,index)){
			size++;
			primes=realloc(primes,size*sizeof(int));
			primes[size-1]=index;
		}
		index++;
	}
	int*exponents=calloc(size,sizeof(int));
	index=0;
	while(index<size){
		exponents[index]=exponentIn(number,primes[index]);
		index++;
	}
	index=0;
  int first=1;
  os_ClrHome();
	while(index<size){
		if (exponents[index]!=0){
      if (first){
      first=0;
      }
      else{
      os_PutStrFull("x");
      }
			printNumber(primes[index]);
			os_PutStrFull("e");
			printNumber(exponents[index]);
      }
		index++;
	}
	free(primes);
	free(exponents);
	os_GetStringInput(".",string,10);
  return 0;
}
