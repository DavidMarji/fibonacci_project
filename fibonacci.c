#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//NOTE: at the default state, the max fibonacci number this program can calculate is the 4883rd number. To change that change the size of the num array (default size is 1024).


//using a struct because after around the 80th number the long long data type isn't large enough to hold the values
typedef struct largest_num {
	//1024 digit number
	char num[1024];
       	//length of the number to reduce iterations when adding numbers	
	short length;
} largest;
largest placeHolder;

int add(largest *first, largest *second, largest *final);
void print_largest_num(largest *num);
void set_num(largest *num);

int main(int argc, char *argv[]){
	if(argc!=2){
		puts("wrong number of inputs, please only include 1 input");
		return 1;
	}
	int num=0;
	
	int s=0;
	while(argv[1][s]!='\0'){
		s++;
	}

	for(int i=0; i<s; i++){
		
		int pos=1;
		for(int k=0; k< s - i - 1 ; k++){
			pos*=10;
		}
		num += (((int)argv[1][i])-48)*pos;
	}	
	


	if(num==0){ printf("the %d number of the sequence is %d\n", num, 0); return 0;}
	if(num==1 || num==2){printf("the %d number of the sequence is %d\n", num, 1); return 0;}


	largest *final= (largest * ) malloc(sizeof(placeHolder));
	largest *k= (largest * ) malloc(sizeof(placeHolder));
	largest *j = (largest * )  malloc(sizeof(placeHolder));

	if(j==NULL || k==NULL || j==NULL) return 2;
	(*j).length = 1;
	set_num(j);
	//(*j).num[((int) sizeof(placeHolder.num))-1]= '0'; //already 0
	
	(*k).length = 1;
	set_num(k);
	(*k).num[((int) sizeof(placeHolder.num))-1]= '1';

	(*final).length = 1;
	set_num(final);
	//(*final).num[((int) sizeof(placeHolder.num))-1]= '0'; //already 0

	for(int i=0; i<num-1; i++){

			    //final = k + j
		int error = add(j, k, final);
		if(error == 1){
			return 1;
		}

		//j=k
		strcpy((*j).num, (*k).num);
		(*j).length = (*k).length;

		//k=final
		strcpy((*k).num, (*final).num);
		(*k).length = (*final).length;
	}

	printf("the %d number of the sequence is ", num);
	print_largest_num(final);

	free(final);
	free(j);
	free(k);

	return 0;
}

int add(largest *first, largest *second, largest *to_change){
	int c_out=0;
	short largest_length=0;

	if((*first).length > (*second).length){
		largest_length = (*first).length;	
	}
	else{
		largest_length = (*second).length;
	}
	
	
	//i= right most digit to make printing easier
	for(int i = ((int) sizeof(placeHolder.num)) - 1; i > ((int) sizeof(placeHolder.num)) - 1 - largest_length - c_out; i--){ 
		//c_out is to account for cases like 9 + 9 where after the addition is done and c_out = 1, when the loop checks the condition it'll iterate one more time 
		
		
		short addition = (short)((*first).num[i]) + (short)((*second).num[i]) + c_out;		
		(*to_change).length = largest_length + c_out;

		if((*to_change).length >= ((int) sizeof(placeHolder.num)) - 1){
			puts("the numbers are too large");
			return 1;
		}

		//current digit could be a maximum of 9, 48*2 because of char conversion
		if(addition > 9 + (48*2)){

			//for any digit the maximum addition with a carry in can be 9 + 9 + 1 which is 19, to store the 9 we just do addition(19) - 10
			//the -48 comes from adding 48 to 2*-48 convert back to char
			(*to_change).num[i] = addition - 10 - 48;
			
			//since we already got this digit we still need to store the 10 from the 2 digit added number
			c_out = 1;			
		}
		else{
			(*to_change).num[i] = addition - 48;
			c_out = 0;
		}
		
	}
	return 0;
}

void print_largest_num(largest *number){
	
	short first_non_zero = 0;
	
	for(int i = ((int) sizeof(placeHolder.num)) - 1 - (*number).length; i < sizeof(placeHolder.num); i++){

		if((*number).num[i] != '0'){
			first_non_zero=1;
		}
		

		//to avoid confusion I did first_non_zero != 0 instead of !first_non_zero
		if(first_non_zero != 0){
			printf("%c",(*number).num[i]);
		}	
	}
	printf("\n");
}

void set_num(largest *number){
	
	for(int i = 0; i < (int) sizeof(placeHolder.num); i++){
		(*number).num[i]='0';
	}

}
