Requirments:

 1) SDL legacy version 1
 
 2) CUDA capable GPU
 
The Mandelbrot set is the set of complex numbers c for which the function f(z) = z^2 + c does not diverge when iterated from z = 0.

Code description: calculate the amount of iterations needed to examine the divergence of each point. The main.cpp calls a wrapper function which invokes the CUDA
kernel to make the calculations. This code is a CUDA version of the code provided by the book. 

![alt text](https://github.com/vtsimpouris/Discovering_Modern_Cpp/blob/master/Chapter4/Complex_numbers_4.8.3/Mandelbrot_CUDA/mandelbrot.PNG)
