#include <stdio.h>
#include "iostream"
using namespace std;
int main(){
	 int sum = 0;
         for(int i = 2;i<1000;i++){
	     if(i%3==0){
		   sum += i;
		    printf("%d\n",i);
         }
         if(i%5==0){
	       sum += i;
	      printf("%d\n",i);
         }
         if(i%3==0&&i%5==0){
	       sum -= i;
	    printf("%d\n",i);
         }
}
       printf("%d",sum);  
}
