#include <stdio.h>

int stack[1000],sp=0;
int op[1000], i = 0, cons[100], j = 0;

void get_op(){
	char c;
	while((c = getchar()) != 0x64);
	//printf("%x\n",c);
	op[i++] = c;
	while((c = getchar()) != 0x53)
		op[i++] = c;//printf("%x\n",c);
	//printf("%x\n\nCONSTANTS\n",c);
}

void get_const(){
	char c;
	while((c = getchar()) !=EOF){
		if( c == 0x69){
			c=getchar();
			cons[j++] = c;//printf("%x\n",c);
			cons[j] = c;
		}
	}
}

void push(int opcode){
	stack[sp++] = opcode;
	//printf("LODED %d at %d \n",opcode,sp);
}

int pop(){
	return(stack[--sp]);
}

void load_cons( int op1){
	//printf("Loading %d constant",op1); 
	push(cons[op1]);
}

void load_name( int op1){ 
	//printf("LOAD_NAME:");
	push(stack[op1]);
}

void print_item(){
	printf("%d",pop());
}

void print_line(){
	printf("\n");
}

void add(){
	int a,b,c;
	a = pop();
	b = pop();
	c = a + b;
        //printf("%d + %d = %d",a,b,c);
	push(c);
}

void sub(){
	 int a,b,c;
	 a = pop();
	 b = pop();
	 c = b - a;
	 //printf("%d + %d = %d",a,b,c);
	 push(c);
}

void div(){
	 int a,b,c;
	 a = pop();
	 b = pop();
	 c = b / a;
	 //printf("%d + %d = %d",a,b,c);
	 push(c);
}

void mod(){
	 int a,b,c;
	 a = pop();
	 b = pop();
	 c = b % a;
	 //printf("%d + %d = %d",a,b,c);
	 push(c);
}

void mul(){
	 int a,b,c;
	 a = pop();
	 b = pop();
	 c = a * b;
	 //printf("%d + %d = %d",a,b,c);
	 push(c);
}

main(){
	get_op();
	get_const();
	int li = 0, lj = 0;
	/*for(li;li<j;li++)
		printf("%x\n",cons[li]);
	li=0;*/

	while(li < i){
		switch ( op[li++] ){
		case 0x64:
			load_cons(op[li++]);
			li++;
			break;
		case 0x5a:
			li+=2;
			break;
		case 0x65:
			load_name(op[li++]);
			li++;
			break;
		case 0x47:
			print_item();
			break;
		case 0x48:
			print_line();
			break;
		case 0x17:
			add();
			break;
		case 0x18:
			sub();
			break;
		case 0x16:
			mod();
			break;
		case 0x15:
			div();
			break;
		case 0x14:
			mul();
			break;
		default :
			printf("UNKNOWN %x\n",op[li]);
		}
	}
}
