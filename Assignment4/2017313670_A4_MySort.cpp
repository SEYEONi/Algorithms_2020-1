#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////

// Swap
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Quick sort (use randomize array index)
void quick_sort(int *arr,int left,int right)
{
	if (left >= right)
		return;

    int mid = (left + right) /2;
    swap(&arr[left], &arr[mid]); // change mid and left (change pivot to prevent worst case)

	int pivot = left;
	int start = left + 1;
	int end = right;

	while (start<=end)
	{
		while (arr[pivot] >= arr[start] && start <= right)
			start++;
		while (arr[pivot] <= arr[end] && end > left)
			end--;
		if (start > end)
		{
			swap(&arr[pivot], &arr[end]);
		}
		else
			swap(&arr[start], &arr[end]);
	}
	quick_sort(arr, left, end - 1);
	quick_sort(arr, end + 1, right);
}


void MyVeryFastSort(int n, int *d)
{
	quick_sort(d, 0, n-1);
}



/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////


// Utilized to check the correctness
bool Validate(int n, int *d)
{
	for(int i=1;i<n;i++)
	{
		if( d[i-1] > d[i] )
		{
			return false;
		}
	}	
	return true;
}

int main(int argc, char **argv)
{
	if( argc != 3 )
	{
		fprintf( stderr , "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int n, *d;
	FILE *input = fopen( argv[1] , "rb" );
	int e = fread( &n , sizeof(int) , 1 , input );
	d = new int [ n ];
	e = fread( d , sizeof(int) , n , input );
	fclose(input);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your sorting algorithm
	MyVeryFastSort( n , d );

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	bool res_validate = Validate( n , d );

	// Write the results (corretness and time)
	FILE *output = fopen( argv[2] , "w" );
	if( res_validate ) { fprintf( output , "OKAY\n" ); printf("OKAY\n"); }
	else { fprintf( output , "WRONG\n" ); printf("WRONG\n");  }
	fprintf( output , "%d\n" , (int)res_time );
	printf( "%d\n" , (int)res_time );
	fclose(output);

	delete [] d;

	return 1;
}
