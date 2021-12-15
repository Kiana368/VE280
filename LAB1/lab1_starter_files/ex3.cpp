#include <iostream>
using namespace std;

// Modify the matrix. There is no need to return a new image here.
void flipAndInvertImage(int **image, int size)
{
    // TODO: Implement this function.
}

int main()
{
    int size;
    cin >> size;
    int **image = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        image[i] = new int[size];
        for (int j = 0; j < size; ++j)
        {
            cin >> image[i][j];
        }
    }
    flipAndInvertImage(image, size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << image[i][j];
            cout << ((j == size - 1) ? "\n" : " ");
        }
        delete[](image[i]);
    }
    delete[](image);
    return 0;
}
