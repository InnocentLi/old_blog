#include "stdio.h"
int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b,a%b);
}
int main(){
	int ans = 1;
	for(int i = 1;i <= 20; ++i){
		ans *= i / gcd (i,ans);
	}
	printf("%d",ans);
	
}
