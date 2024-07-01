## Write a program to perform efficient exponentiation operation, i.e. x^y. 

Assume that x is an integer. Consider two cases, one where y is an integer and another where y
is a real number.

### Case 1
``Exp_Int.c``

X and y are int

Example:  
Binary expansion of 39= 34 + 4 + 2 + 1
x^39 = x^34 * x^4 * x^2 * x^1

* Obs 1: x^16 and x^8 are not considered
* Obs 2: It is easier to generate powers of 2 as exponents of x in the order x^1, x^2,
x^4, x^8, x^16 etc by multiplying the current power by itself.

#### Algorithm

~~~C
while( y!=0)
{
    1. Divide y successively by 2, also keep on generating powers of 2 in the order x^1, x^2, x^4, x^8 etc
    2. If the reminder (bit) is 1
        consider the current power of x in the partial answer
    Else
        Ignore
}
~~~

**Time complexity** : O(log y)

### Case 2
``Exp_Real.c``

X and y are real

**Formula used**: exp( log(x)*y )

#### Functions

``double natural_log( double x)``  

##### Algorithm

``z= ( x - 1) / ( x + 1)``  
We can generate the next term by using the current term  
Multiply the previous term with the step  

~~~C
step = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));
z*=step;
term = (1/pow)*z;
~~~

Add the term to the current sum  
The loop will go on till old sum!=current sum, so that we get accurate results  
In the end multiply 2 with the total value

``double e( double x)``

Sum =1 (initialise sum of series)  
Term = x, power =1  
next_term= (term*x)/power+1  
Add term to the previous sum
