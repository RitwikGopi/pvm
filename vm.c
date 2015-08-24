#include <stdio.h>

int stack[1000],si=0;
char c;

void print(){
	printf("%d\n",stack[si-1]);
}

void push(){
	stack[si++] = getnumber();
}

void add(){
	stack[si-2] = stack[si-2] + stack[--si];
}

void sub(){
	stack[si-2] = stack[si-2] - stack[--si];
}

void div(){
	stack[si-2] = stack[si-2]/ stack[--si];
}

void mul(){
	stack[si-2] = stack[si-2] * stack[--si];
}

void great(){
	stack[si-2] = stack[si-2] > stack[--si];
}

void less(){
	stack[si-2] = stack[si-2] < stack[--si];
}

void equal(){
	stack[si-2] = stack[si-2] == stack[--si];
}

void notequal(){
	stack[si-2] = stack[si-2] != stack[--si];
}

int getnumber(){
	int n = 0;
	while(c != '\n' && c != EOF && c!=' '){
		n = n*10 + ( c - '0');
		c=getchar();
	}
	if(c != EOF)
		c = getchar();
	return n;
}

void execute(){
	while(c != EOF){
		switch(getnumber()){
		case 90 :
			push(getnumber);
			break;
		case 91 :
			add();
			break;
		case 92 :
			sub();
			break;
		case 93 :
			div();
			break;
		case 94 :
			mul();
			break;
		case 95 :
			print();
			break;
		case 96 :
			great();
			break;
		case 97 :
			less();
			break;
		case 98 :
			equal();
			break;
		case 99 :
			notequal();
			break;
		case 89 :
			condition();
			break;
		}
	}
}

main(){
	c = getchar();
	execute();
}
