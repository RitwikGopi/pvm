#include <stdio.h>

main(){
	char c;
	while((c = getchar()) != 0x64);
	printf("%x\n",c);
	while((c = getchar()) != 0x53)
		printf("%x\n",c);
	printf("%x\n\nCONSTANTS\n",c);
	while((c = getchar()) !=EOF){
		if( c == 0x69)
			printf("%x\n",c=getchar());
	}
}
