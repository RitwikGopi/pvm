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
	int t1,t2,t3;
	while((c = getchar()) !=EOF){
		if( c == 0x69){
			t1 = getchar();
			t2 = getchar();
			t3 = t2 * 256 + t1;
			cons[j++] = t3;//printf("%x\n",c);
			cons[j] = t3;
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

void comp(int op){
	 int a,b,c;
	 a = pop();
	 b = pop();
	 //printf("%d + %d = %d",a,b,c);
	 switch(op){
		 case 0:
			 c = (b < a);
			 break;
		 case 1:
			 c = (b <= a);
			 break;
		 case 2:
			 c = (b == a);
			 break;
		 case 3:
			 c = (b != a);
			 break;
		 case 4:
			 c = (b > a);
			 break;
		 case 5:
			 c = (b >= a);
			 break;
	 }
	 push(c);
}

int jump_f(int b1,int b2, int y){
	int r = pop();
	if(r!=1)
		return(b2 * 256 + b1);
	else
		return(y + 2);
}

int jump_fwd(int x, int y, int z){
	return(z + y * 256 + x);
}

main(){
	get_op();
	get_const();
	int li = 0, lj = 0, t1 , t2;
	/*for(li;li<j;li++)
		printf("%x\n",cons[li]);
	li=0;*/

	while(li < i){
		switch ( op[li++] ){
		case 0x64:
			t1 = op[li++];
			t2 = op[li++];
			load_cons(t2 * 256 + t1);
			break;
		case 0x5a:
			li+=2;
			break;
		case 0x65:
			t1 = op[li++];
			t2 = op[li++];
			load_name(t2 * 256 + t1);
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
		case 0x6b:
			comp(op[li++]);
			li++;
			break;
		case 0x72:
			li = jump_f(op[li],op[li+1],li);
			break;
		case 0x6e:
			li = jump_fwd(op[li],op[li+1],li+2);
			break;
		default :
			printf("%d\t: UNKNOWN %x\n",li-1,op[li-1]);
		}
	}
}
