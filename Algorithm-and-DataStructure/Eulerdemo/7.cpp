#include<stdio.h>
#define MAX 10000
int main(){
    int prem[MAX]={0};
    for(int i = 2;i<MAX;i++){
        for(int j=i*2;j<MAX;j+=i){
            prem[j] = 1;
        }
    }
    for(int i = 2;i<30;i++){
        if(!prem[i]){
            printf("%d",i);
        }
    }
}
