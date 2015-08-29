#include <stdio.h>

main(){
	char c, i = 0;
	while((c = getchar()) != 0x64);
	printf("%d : %x\n",i++,c);
	while((c = getchar()) != 0x53)
		printf("%d : %x\n",i++,c);
	printf("%d : %x\n\nCONSTANTS\n",i++,c);
	i = 0;
	while((c = getchar()) !=EOF){
		if( c == 0x69){
			int t1,t2;
			t1 = getchar();
			t2 = getchar();
			printf("%d : %x\n",i,t1+t2*256);
		}
	}
}
