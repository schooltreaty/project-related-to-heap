Assignment 1
Write a program to perform efficient exponentiation operation, i.e. xy. Assume that x is an integer. Consider two cases, one where y is an integer and another where y is a real number.

Assignment 2
Implement ‘BigInt’ data type with operations (+, -, *) for supporting 1024 bit ints.

Assignment 3
Write a program to implement heap management scheme. Implement the ‘allocate’ and ‘free’ functions. Ensure that adjacent free blocks are merged together.



assignment 1

Assume that x is an integer. Consider two cases, one where y is an integer and another where y is a real number.

Case 1
Exp_Int.c

X and y are int

Example:
Binary expansion of 39= 34 + 4 + 2 + 1 x^39 = x^34 * x^4 * x^2 * x^1

Obs 1: x^16 and x^8 are not considered
Obs 2: It is easier to generate powers of 2 as exponents of x in the order x^1, x^2, x^4, x^8, x^16 etc by multiplying the current power by itself.
Algorithm
while( y!=0)
{
    1. Divide y successively by 2, also keep on generating powers of 2 in the order x^1, x^2, x^4, x^8 etc
    2. If the reminder (bit) is 1
        consider the current power of x in the partial answer
    Else
        Ignore
}
Time complexity : O(log y)

Case 2
Exp_Real.c

X and y are real

Formula used: exp( log(x)*y )

Functions
double natural_log( double x)

Algorithm
z= ( x - 1) / ( x + 1)
We can generate the next term by using the current term
Multiply the previous term with the step

step = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));
z*=step;
term = (1/pow)*z;
Add the term to the current sum
The loop will go on till old sum!=current sum, so that we get accurate results
In the end multiply 2 with the total value

double e( double x)

Sum =1 (initialise sum of series)
Term = x, power =1
next_term= (term*x)/power+1
Add term to the previous sum


assign 2 


Big_Int.c
Implement ‘BigInt’ data type with operations (+, -, *) for supporting 1024 bit ints
In C/C++ the number of digits a long long int can have is a maximum of 20. And we want to store the 22 digit number which is not easy to store in any kind of primitive type. So to deal with this type of problem we design a new data type called BigInt.

We are going to store our numbers in the form of characters as using strings we can store very big numbers also.

ALGORITHM
We create a struct for BigInt and store num pointer, signed bit and length in it

stringToBigInt()
{
    Size of the number= length of the string (subtract signed bit from the length)
    If the first character is ‘-’ set the signed bit as 1
    Else set signed bit as 0
    Allocate memory for the number in heap
    Using a while loop convert each character to int by subtracting 48 from it.
}
Now for the addition/subtraction operation of two big integers, use the basic math for addition which says that add the corresponding two digits and if some carry is generated add it to the sum of the next digits and repeat this process until all digits are added/subtracted.

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
multBigInts()
{
    Create mult struct pointer
    mult->length = b1->length+b2->length;
    Initialise all mult->num[i] to 0
    We use the basic mathematics approach which states that multiply every digit of one number with the other complete number and at last add all the numbers we get in multiplication.
    We use nested loops to do that
}



assignment 3

Implements the “allocate” and “free” functions. It also ensures that adjacent free blacks are merged together.

#include<stddef.h>
stddef.h is required because the definition for size_t datatype is found there.

char memory[20000];
This is the declaration of the array which is considered as our memory. We get a contiguous allocation of memory by using an array. Here, I assumed a block of memory of size 20,000 bytes char memory[20000]; (assuming that the storage for a character is 1 byte in the machine) and all the data structures and the allocated memory blocks reside in this same chunk of memory.

struct block freeList=(void)memory;
Here we initialize a pointer of type "meta_block", named freeList pointing to the starting address of the chunk of memory we created before. This freeList pointer will point to the start of the linked list of metadata blocks.The starting address of the array (memory) should be casted to type void so that we are able to allocate blocks of memory which are of different datatypes.(int, char, float etc.)

/Initializing the block of memory/
void initialize()
{
 freeList->size=20000-sizeof(struct block); 
 freeList->free=1;
 freeList->next=NULL;
}
This is where we initialize the first metadata block, update it to refer to the next block of memory. The size of the block that it refers to is (20000 bytes- the_size_of_one_metadata_block) To indicate that the block is not yet allocated, we set the free flag to 1. And the first metadata block has no next metadata block yet. So we set next to NULL.

/Making way for a new block allocation by splitting a free block -- (Assume first fit algorithm)/
void split(struct block *fitting_slot,size_t size)
{
 struct block new=(void)((void*)fitting_slot+size+sizeof(struct block));
 new->size=(fitting_slot->size)-size-sizeof(struct block);
 new->free=1;
 new->next=fitting_slot->next;
 fitting_slot->size=size;
 fitting_slot->free=0;
 fitting_slot->next=new;
}
We use the First-fit-algorithm to find a free block to allocate memory. Assume that we get a request to allocate a block of memory of size 500 bytes. Starting from the first metadata block we can go on searching for the first block which has enough space to allocate. If we get the free block sizes to be 250, 130 and 750 in order, we will allocate the block of size 750.

If we find a free block which exactly fits the required size, we don't need to do the splitting. So this function is only required if we have what is more than required.

The arguments accepted by this function are --- A pointer to the metadata block which refers to the block of memory whose size is more than required.(fitting_slot) and the required size of the memory chunk to be allocated.

Here we create a new metadata block pointer called "new". And it should point to the location provided by passing(setting aside) a block of memory which is equal to the_size_of_the_metadata_block_we_considered + the_size_requested_to_be_allocated

Then this new pointer points to the metadata block referring to the next free chunk. As you can see from the code, I have set the attributes of both the new and fitting_slot metadata blocks accordingly.

The malloc and free functions are named here as MyAlloc() and MyFree().

if(!(freeList->size))
{ 
 initialize();
 printf("Memory initialized\n");
}
This condition will initialize the memory if it is not initialized at the beginning. This set of statements will be executed only if the size of the first metadata block is not set yet. That means, if the memory is still not initialized.

while(((curr->size<noOfBytes)||(curr->free==0))&&(curr->next!=NULL))
If this condition is met, the metadata block we checked cannot be used for the allocation. So we execute the following statements. That is you go on checking one metadata block at a time

if(curr->size==noOfBytes)
If this condition is met, the metadata block we checked refers to a chunk of memory that exactly fits the required size. So set the free flag to 0, indicating that it is allocated. Then return the starting address of the block of allocated memory.

else if(curr->size>(noOfBytes+sizeof(struct block)))
If this condition is met, the metadata block we checked refers to a chunk of memory that is of size greater than what is required. So invoke the split() function to allocate only the block which is required and then return the starting address of the block of allocated memory.

There can be a situation where you have consecutive blocks that are set free by deallocating after they were previously allocated. This results in external fragmentation which will cause the MyAlloc() function to return a NULL pointer although we have enough memory to allocate. Therefore we use a function called merge() to join the consecutive free blocks by removing the metadata blocks lying in between.

After we allocate memory for some purpose, it is a really good practice to deallocate that memory if you have finished using it, so that it can be used by another person for his memory requirement. We use the MyFree() function for that.

It takes the pointer to a block of memory previously allocated as a parameter.

if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+20000)))
Here we check whether the address to which the pointer given as an argument to the function actually lies within the address range of the memory array that we used for the purpose. If yes,we simply set the free flag in the metadata block to 1 indicating that it is free and scan through and merge the consecutive blocks that are free, if any.
