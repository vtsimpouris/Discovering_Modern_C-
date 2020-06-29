#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <cuda_runtime.h>


__global__ void kernel(int* iter,float xdim,float ydim,int max_iter)
{
	
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	float x = (float)blockIdx.x;
	float y = (float)threadIdx.x;
	x *= 2.4f / ydim;
	y *= 2.4f / ydim;
	x -= 1.2 * (xdim / ydim) + 0.5;
	y -= 1.2;
	float z_x = x;
	float z_y = y;
	float temp;
	for (int j = 0; j < max_iter; j++) {
		if ((z_x * z_x + z_y * z_y) > 4.0f) { break; }
		iter[i]++;
		temp = z_x;
		z_x = z_x * z_x - z_y * z_y + x;
		z_y = 2 * z_y * temp + y;
	}
}


void compute_iterations(int* iter,int xdim,int ydim, int max_iter) {

	int N = xdim * ydim;
	int* a;
	cudaMalloc(&a, N * sizeof(int));
	for (int i = 0; i < N; i++) {
		iter[i] = 0;
	}
	cudaMemcpy(a, iter, N * sizeof(int), cudaMemcpyHostToDevice);

	kernel << < 1200, 800 >> > (a, static_cast<float>(xdim), static_cast<float>(ydim), max_iter);
	cudaDeviceSynchronize();

	cudaError_t error = cudaGetLastError();
	if (error != cudaSuccess)
	{
		fprintf(stderr, "ERROR: %s\n", cudaGetErrorString(error));
		exit(-1);
	}

	cudaMemcpy(iter, a, N * sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(a);
}