# Big_Int.c

## Implement ‘BigInt’ data type with operations (+, -, *) for supporting 1024 bit ints

In C/C++ the number of digits a long long int can have is a maximum of 20. And we want to store the
22 digit number which is not easy to store in any kind of primitive type. So to deal with this type of problem we design a new data type called **BigInt**.

We are going to store our numbers in the form of characters as using strings we can store very big numbers also.

### ALGORITHM

We create a struct for BigInt and store num pointer, signed bit and length in it

~~~C
stringToBigInt()
{
    Size of the number= length of the string (subtract signed bit from the length)
    If the first character is ‘-’ set the signed bit as 1
    Else set signed bit as 0
    Allocate memory for the number in heap
    Using a while loop convert each character to int by subtracting 48 from it.
}
~~~

Now for the addition/subtraction operation of two big integers, use the basic math for addition which says that add the corresponding two digits and if some carry is generated add it to the sum of the next digits and repeat this process until all digits are added/subtracted.

~~~C
addBigInts()
{
    Check which number(among n1 and n2) is longer and allocate sizeof(int)*(n+1) memory to the sum->num
    If both numbers are of same sign
        Have 3 while loops to get the final sum, add carry to the digit if it is generated
    If the carry is not equal to 0 in the end
        Have another while loop taking that into consideration.
    If both numbers have different sign
        If b1->signedBit==1
        {
            b1->signedBit = 0
            sum = subtractBigInts(b2, b1)
            b1->signedBit = 1
        }
        else
        {
            b2->signedBit = 0;
            sum = subtractBigInts(b1, b2);
            b2->signedBit = 1;
        }
    return sum;
}
~~~

~~~C
subtractBigInts()
{
    Create a “diff” struct pointer and allocate memory of sizeoof(BigInt)
    Check which number(among n1 and n2) is longer and allocate sizeof(int)*(n) memory to the diff->num
    If the signed bits are not equal
        If the signed bit of second number is 1    
            make it 0 add the numbers and then set the signed bit of diff to 0.
        Else
            Set the signed bit of second number to 1 add it and set the signed bit of diff to 1
    If the signed bits are equal
        Compare the magnitude of two numbers using the compare(b1,b2) function
        If b1>b2
            Call subtraction(b1,b2)
            Diff will have the signed bit of b1
        Else
            Call subtraction(b2,b1)
            Diff will have the signed bit of b2
    return diff
}
~~~

~~~C
multBigInts()
{
    Create mult struct pointer
    mult->length = b1->length+b2->length;
    Initialise all mult->num[i] to 0
    We use the basic mathematics approach which states that multiply every digit of one number with the other complete number and at last add all the numbers we get in multiplication.
    We use nested loops to do that
}
~~~
