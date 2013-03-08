#include <stdio.h>

#define PARENT(i)  (i / 2)	// floor
#define LEFT(i)		(i * 2)
#define RIGHT(i)	((i * 2) + 1)

const int LENGTH = 16;
int A[LENGTH + 1] = {0};
int heap_size = 0;

void
exchange(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

// root index as i
void
max_heapify(int *a, int i)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	if (l <= heap_size && a[l] > a[i])
		largest = l;
	else
		largest = i;
	if (r <= heap_size && a[r] > a[largest])
		largest = r;
	if (largest != i) {
		exchange(&a[i], &a[largest]);
		max_heapify(a, largest);
	}
}

void
build_max_heap(int *a)
{
	heap_size = LENGTH; // init heap
	for (int i = LENGTH / 2/*floor*/; i >= 1; i--)
		max_heapify(a, i);
}

void
heapsort(int *a)
{
	build_max_heap(a);
	for (int i = LENGTH; i >= 2; i--)
		exchange(&a[1], &a[i]),
		heap_size--,
		max_heapify(a, 1);
}

int
main(int c, char** v)
{
	for (int i = 1; i <= LENGTH; i++)
		A[i] = i;

	exchange(&A[1], &A[2]);
	exchange(&A[3], &A[5]);
	exchange(&A[7], &A[11]);
	exchange(&A[9], &A[8]);
	exchange(&A[4], &A[6]);

	for (int i = 1; i <= LENGTH; i++)
		printf("%d ", A[i]);

	printf("\n");

	heapsort(&A[0]);

	for (int i = 1; i <= LENGTH; i++)
		printf("%d ", A[i]);

	printf("\n");

	return 0;
}
