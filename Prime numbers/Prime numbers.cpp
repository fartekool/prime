#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <random>

unsigned long long ModExp(unsigned long long x, unsigned long long y, unsigned long long N)
{
    if (y == 0)
        return 1;
    unsigned long long z = ModExp(x, y / 2, N);
    z = ((z % N) * (z % N)) % N;
    if (y % 2 == 0)
        return z;
    else
        return ((x % N) * (z % N)) % N;
}

bool Rabin_Primality(unsigned long long N)
{
    if (N <= 1) return false;
    if (N <= 3) return true;
    if (N % 2 == 0) return false;

    //unsigned long long a = 1 + (rand() % (N - 1));
    unsigned long long a = 2;
    if (ModExp(a, N - 1, N) != 1)
        return false;
    else
    {
        unsigned long long K = N - 1;
        int t = 0;
        while (K % 2 == 0)
        {
            K /= 2;
            ++t;
        }
        std::vector<unsigned long long> A;
        for (int i = 0; i <= t; ++i)
        {
            A.push_back(ModExp(a, K * pow(2, i), N));
        }
        if (A[0] == 1) return true;
        for (int i = 1; i <= t; ++i)
        {
            if ((A[i] == 1) && (A[i - 1] != (N - 1)))
            {
                return false;
            }
            else
                return true;
        }

    }

}
bool Ferma_Primality(unsigned long long N)
{   
    if (N <= 1) return false;
    if (N <= 3) return true;
    if (N % 2 == 0) return false;

    //unsigned long long a = 1 + (rand() % (N - 1));
    unsigned long long a = 2;
    if (ModExp(a, N - 1, N) == 1)
        return true;
    else
        return false;
}
bool Default_Primality(unsigned long long N)
{
    if (N <= 1) return false;
    if (N <= 3) return true;
    if (N % 2 == 0) return false;
    for (unsigned long long i = 2; i < sqrt(N) + 1; ++i)
    {
        if (N % i == 0)
            return false;
    }
    return true;
}
int main()
{
    std::srand(time(NULL));

    //int Ferma_count = 0;
    //int default_count = 0;
    //int rabin_count = 0;
    //int X;
    //std::cin >> X;
    //for (int i = 2; i < X; ++i)
    //{
    //    if (Default_Primality(i))
    //        ++default_count;
    //    if (Ferma_Primality(i))
    //        ++Ferma_count;
    //    if (Rabin_Primality(i))
    //    {
    //        //std::cout << i << ' ';
    //        ++rabin_count;
    //    }
    //}
    //std::cout << std::endl;
    //std::cout << "Prime numbers by default_primality from 2 to " << X << " = " << default_count << std::endl;
    //std::cout << "Prime numbers by Ferma_primality from 2 to " << X << " = " << Ferma_count << std::endl;
    //std::cout << "Prime numbers by rabin_primality from 2 to " << X << " = " << rabin_count << std::endl;
    //std::cout << "Ferma_count - default_count = " << Ferma_count - default_count << std::endl;
    //std::cout << "rabin_count - default_count = " << rabin_count - default_count << std::endl;
    /*std::ofstream outputFile("prime10_18.in");
    outputFile.clear();
    if (!outputFile)
        std::cerr << "Error" << std::endl;
    int count = 0;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist(100'000'000'000'000'000, 1'000'000'000'000'000'000);
    while (count < 100)
    {
        unsigned long long i = dist(gen);
        if (Rabin_Primality(i))
        {
            outputFile << i << std::endl;
            ++count;
        }

    }*/



    /*std::ifstream inputFile("prime10_9.in");
    if (!inputFile)
        std::cerr << "Error" << std::endl;
    std::vector<unsigned long long> numbers;
    unsigned long long num;
    while (inputFile >> num)
        numbers.push_back(num);
    inputFile.close();

    std::ofstream outputFile("prime10_9.out");
    outputFile.clear();
    if (!outputFile)
        std::cerr << "Error" << std::endl;
    for (unsigned long long i : numbers)
    {
        outputFile << i << ' ' << Ferma_Primality(i) << ' ' << Rabin_Primality(i) << std::endl;
    }
    outputFile.close();*/
    unsigned long long a = 100000000000000003;
    unsigned long long b = 620401703;
    
    std::cout << Default_Primality(a) << Ferma_Primality(a) << Rabin_Primality(a);
    return 0;
}

