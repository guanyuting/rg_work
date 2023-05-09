#include<stdio.h>
#define MAX 1002
int main(){
    int n,a[MAX];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    int D[n],max=a[0];
    D[0]=a[0];
    for(int i=1;i<n;i++){
        if(D[i-1]>0)
            D[i]=a[i]+D[i-1];
        else
            D[i]=a[i];
        if(D[i]>max)
            max=D[i];
    }
    for(int i=0;i<n;i++)
        printf("%d ",D[i]);
    printf("\nmax is %d\n",max);
    D[n-1]=a[n-1];
    max=a[0];
    for(int i=n-2;i>=0;i--){
        if(D[i+1]>0)
            D[i]=a[i]+D[i+1];
        else
            D[i]=a[i];
        if(D[i]>max)
            max=D[i];
    }
    for(int i=0;i<n;i++)
        printf("%d ",D[i]);
    printf("\nmax is %d\n",max);
}
