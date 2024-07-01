#include <stdio.h>

double e(double a)
{
    double sum = 1.0, term=1, pow=1; // initialize sum of series
    
    while(sum!=sum+term)
    {
        term*=a/pow;
        pow+=1;
        sum+=term;
    }
    return sum;
}
double natural_log(double x)
{
    double totalValue = 0, z, pow = 1, term;
    z = (x + 1) / (x - 1); 
    //Store step to not have to calculate it each time
    double step = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));
    while (totalValue!=totalValue+term)
    {
        z *= step;
        term = (1 / pow)*z;
        totalValue = totalValue + term;
        pow = pow + 2;
    }
    return 2*totalValue;

}
double power(double x, double y)
{
    double prod=e(natural_log(x)*y);
    return prod;
}
int main()
{
    double x, y;
    printf("Enter x:\n");
    scanf("%lf",&x);
    printf("Enter y:\n");
    scanf("%lf",&y);
    printf("x^y=%lf",power(x,y));

}