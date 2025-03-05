// Function to find the median of three values
int medianOfThree(int a, int b, int c)
{
    if ((a > b) != (a > c))
        return a; // a is median
    else if ((b > a) != (b > c))
        return b; // b is median
    else
        return c; // c is median
}

int partition(int arr[], int low, int high, int pivot)
{
    int pivotValue = arr[pivot];
    int temp = arr[pivot];
    arr[pivot] = arr[high];
    arr[high] = temp;

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivotValue)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// QuickSort with Median of Three Pivot
void quickSort3(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        int median = medianOfThree(arr[low], arr[mid], arr[high]);

        // Find the index of the median value in the array
        int pivotIndex = (arr[low] == median) ? low : (arr[mid] == median) ? mid
                                                                           : high;

        int pi = partition(arr, low, high, pivotIndex);
        quickSort3(arr, low, pi - 1);
        quickSort3(arr, pi + 1, high);
    }
}
void quickSort1(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, low);
        quickSort1(arr, low, pi - 1);
        quickSort1(arr, pi + 1, high);
    }
}

// Pivot Strategy 2: Random element
void quickSort2(int arr[], int low, int high)
{
    if (low < high)
    {
        int randomPivot = low + rand() % (high - low);
        int pi = partition(arr, low, high, randomPivot);
        quickSort2(arr, low, pi - 1);
        quickSort2(arr, pi + 1, high);
    }
}