#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void
exchange(int *a, int *b)
{
  int t;
	t = *a;
	*a = *b;
	*b = t;
}

// x of [p, r]
int
random(int p, int r)
{
	assert(p < r);
	return p + rand() % (r - p);
}

int
partition(int *a, int p, int r)
{
	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
		if (a[j] <= x)
			i++, exchange(&a[i], &a[j]);
	exchange(&a[i + 1], &a[r]);
	return i + 1;
}

int
randomized_partition(int *a, int p, int r)
{
	int i = random(p, r);
	exchange(&a[r], &a[i]);
	return partition(a, p, r);
}

int
randomized_select(int *a, int p, int r, int i)
{
	if (p == r)
		return a[p];

	int q = randomized_partition(a, p, r);
	int k = q - p + 1;
	if (i == k) // the pivot value is the answer.
		return a[q];
	else if (i < k)
		return randomized_select(a, p, q - 1, i);
	else
		return randomized_select(a, q + 1, r, i - k);
}

//int arr[] = { 11, 7, 2, 5, 32, 1, 13, 4, 8, 6 };
//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
int arr[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

int
main(int c, char **v)
{
	// set the seed for rand()
	srand((uint)time(0));

	for (int i = 1; i <= 13; i++) {
		int res = randomized_select(arr, 0, 12, i);
		printf("res of %d: %d\n", i, res);
	}

	return 0;
}
