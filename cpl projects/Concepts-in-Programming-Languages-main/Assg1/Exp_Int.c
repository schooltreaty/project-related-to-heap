#include <stdio.h>

int power(int x, int y)
{
    int prod, pseq;
    prod=1;
    pseq=x;

    while(y!=0)
    {
        if(y%2==1)
            prod*=pseq;
        y=y/2;
        pseq*=pseq;
    }
    return prod;
}
int main()
{
    int x,y;
    printf("Enter x:\n");
    scanf("%d",&x);
    printf("Enter y:\n");
    scanf("%d",&y);
    printf("x^y=%d",power(x,y));

}