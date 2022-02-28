#include <iostream>
#include <string>

unsigned int count_set_bit(int x)
{
    unsigned int count = 0;
    while (x)
    {
        count += (x & 1);
        x >>= 1;
    }
    return count;
}

unsigned int hamming_distance(std::string A, std::string B)
{
    if (A.size() != B.size())
    {
        std::cout << "String sizes are different"
                  << "\n";
        exit(1);
    }

    unsigned int distance = 0;
    for (int i = 0; i < A.size(); i++)
    {
        distance += count_set_bit(A[i] ^ B[i]);
    }

    return distance;
}