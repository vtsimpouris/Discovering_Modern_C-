# Discovering_Modern_Cpp
Selected solution to exercises of the book "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmer" by Peter Gottschlings

### 3.11.3: 
Write a stack implementation for a generic value type. The maximal size of the stack is
defined in the class (hard-wired). Provide the following functions:
• Constructor;
• Destructor if necessary;
• top: show last element;
• pop: remove last element (without returning);
• push: insert new element;
• clear: delete all entries;
• size: number of elements;
• full: whether stack is full;
• empty: whether stack is empty.
Stack over- or underflow must throw an exception.


Note: The solution is implemented using linked lists.

### 3.11.12:
Compute the first and second derivatives for 2 cos x + x ^ 2 with lambda expressions.

### 4.8.3
Requirments:

 1) SDL legacy version 1
 
 2) CUDA capable GPU
 
The Mandelbrot set is the set of complex numbers c for which the function f(z) = z^2 + c does not diverge when iterated from z = 0.

Code description: calculate the amount of iterations needed to examine the divergence of each point. The main.cpp calls a wrapper function which invokes the CUDA
kernel to make the calculations. This code is a CUDA version of the code provided by the book. 

![alt text](https://github.com/vtsimpouris/Discovering_Modern_Cpp/blob/master/Chapter4/Complex_numbers_4.8.3/Mandelbrot_CUDA/mandelbrot.PNG)
