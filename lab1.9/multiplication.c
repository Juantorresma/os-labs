#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_BUFFERS 40

long **buffers[NUM_BUFFERS];
pthread_mutex_t mutexes[NUM_BUFFERS];
pthread_t threads[200];
long *result;
long *matA;
long *matB;

struct MatStruct {
	long row;
	long *matA_pt;
	long *matB_pt;
	long *result;
};

long *readMatrix(char *filename);
void printMatrix(long *mat_pt);
long *getColumn(int col, long *matrix);
void printColumn(long *col);
void printRow(long *row);
long *getRow(int row, long *matrix);
int getLock(void);
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2);
int saveResultMatrix(long *result);
long *multiply(long* matA, long* matB);
void *row_mul(void *args);
long *test(void);

int main(void) {
	matA = readMatrix("matA.dat");
	matB = readMatrix("matB.dat");
	long *result;
	result = multiply(matA, matB);
	saveResultMatrix(result);
	return EXIT_SUCCESS;
}

long *multiply(long *matA, long *matB) {
	int i;
	int j;
	int index;
	int rv;
	static long *result;
	long *row_result_pt;
	result = malloc(SIZE * sizeof(long));
	for (i = 0; i < 200; i++) {
		rv = pthread_create(&threads[i], NULL, &row_mul, (void *) i);
		if (rv != 0) {
			perror("error");
			return 0;
		}
	}
	for (j = 0; j < 200; j++) {
		pthread_join(threads[j], (long *) &row_result_pt);
		for (index = 0; index < 200; index++) {
			*(result + ((j * 200) + index)) = *(row_result_pt + index);
		}

	}
	return result;
}

void *row_mul(void *args) {
	long *row;
	long *col;
	long *result_vec;
	int row_n = (int) args;
	int lock;
	int i;
	result_vec = malloc(200 * sizeof(long));
	row = getRow(row_n, matA);
	lock = getLock();
	while (lock == -1) {
		lock = getLock();
	}
	buffers[lock] = &result_vec;
	for (i = 0; i < 200; i++) {
		col = getColumn(i, matB);
		*(*buffers[lock] + i) = dotProduct(row, col);
	}
	buffers[lock] = 0;
	releaseLock(lock);
	return (void *) result_vec;
}

long *test(void) {
	long *row;
	long *col;
	int i;
	long *pt;
	pt = malloc(200 * sizeof(long));
	buffers[0] = &pt;
	row = getRow(0, matA);
	for (i = 0; i < 200; i++) {
		col = getColumn(i, matB);
		*(*buffers[0] + i) = dotProduct(row, col);
	}
	return pt;
}

void printMatrix(long *mat_pt) {
	int i;
	int j;
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 200; j++) {
			printf("[%d][%d] = %ld\n", i, j, *(mat_pt + (i * 200) + j));
		}
	}
}

void printColumn(long *col) {
	int j;
	printf("[");
	for (j = 0; j < COL; j++) {
		printf("%d:%ld, ", j, *(col + j));
	}
	printf("]\n");
}

void printRow(long *row) {
	int j;
	printf("[");
	for (j = 0; j < 200; j++) {
		printf("%d:%ld, ", j, *(row + j));
	}
	printf("]\n");
}

long *readMatrix(char *filename) {
	FILE *file;
	int i;
	long *matrix;
	matrix = malloc(40000 * sizeof(long));
	file = fopen(filename, "r");
	if (file) {
		for (i = 0; i < 40000; i++) {
			fscanf(file, "%ld\n", &matrix[i]);
		}
		fclose(file);
	} else {
		return 0;
	}
	return matrix;
}

long *getColumn(int col, long *matrix) {
	static long *column;
	column = malloc(COL * sizeof(long));
	int j;
	for (j = 0; j < 200; j++) {
		column[j] = matrix[(j * 200) + col];
	}
	return column;
}

long *getRow(int row, long *matrix) {
	long *row_list;
	row_list = malloc(200 * sizeof(long));
	int i;
	for (i = 0; i < 200; i++) {
		row_list[i] = matrix[(row * 200) + i];
	}
	return row_list;
}

int getLock(void) {
	int lock;
	int i;
	for (i = 0; i < NUM_BUFFERS; i++) {
		lock = pthread_mutex_trylock(&mutexes[i]);
		if (lock == 0) {
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock) {
	return pthread_mutex_unlock(&mutexes[lock]);
}

long dotProduct(long *vec1, long *vec2) {
	int i;
	int result;
	result = 0;
	for (i = 0; i < 200; i++) {
		result += vec1[i] * vec2[i];
	}
	return result;
}

int saveResultMatrix(long *result) {
	FILE *f = fopen("resultado.dat", "w+");
	for (int i = 0; i < 40000; i++) {
		fprintf(f, "%ld\n", *(result + i));
	}
	fclose(f);

	return 0;
}
