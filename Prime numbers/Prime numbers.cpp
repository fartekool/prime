#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>


unsigned long long ModMul(unsigned long long a, unsigned long long b, unsigned long long N) {
    unsigned long long result = 0;
    a = a % N;

    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result + a) % N;
        }
        a = (a * 2) % N;
        b /= 2;
    }
    return result;
}
unsigned long long ModExp(unsigned long long base, unsigned long long exp, unsigned long long N) {
    unsigned long long result = 1;
    base = base % N;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = ModMul(result, base, N);
        }
        exp = exp >> 1;
        base = ModMul(base, base, N);
    }
    return result;
}
bool Rabin_Primality(unsigned long long N)
{
    if (N <= 1) return false;
    if (N <= 3) return true;
    if (N % 2 == 0) return false;

    unsigned long long a = 1 + (rand() % (N - 1));
    
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

    unsigned long long a = 1 + (rand() % (N - 1));
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


unsigned long long GenRandomPrime(int len)
{
    unsigned long long min = pow(10, len - 1);
    unsigned long long max = pow(10, len) - 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(min, max);

    unsigned long long RandomPrime;
    do
    {
        RandomPrime = dis(gen);
    } while (!Rabin_Primality(RandomPrime));
    return RandomPrime;
}

unsigned long long GCD(unsigned long long a, unsigned long long b)
{
    while (b != 0)
    {
        unsigned long long tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

unsigned long long ModInverse(long long e, long long N) {
    long long d = 0, new_d = 1;
    long long r = N, new_r = e;

    while (new_r != 0) {
        long long quotient = r / new_r;

        long long temp_d = d;
        d = new_d;
        new_d = temp_d - quotient * new_d;

        long long temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    if (r > 1) return 0;
    if (d < 0) d += N;
    return d;
}

unsigned long long Encrypt(unsigned long long message, unsigned long long e, unsigned long long N)
{
    return ModExp(message, e, N);
}
unsigned long long Decrypt(unsigned long long ciphermessage, unsigned long long d, unsigned long long N)
{
    return ModExp(ciphermessage, d, N);
}

void RSA(const std::string& input_file, const std::string& middle_file, const std::string& output_file)
{
    unsigned long long message;
    std::ifstream inputFile(input_file);
    if (!inputFile)
        std::cerr << "Error" << std::endl;
    inputFile >> message;
    int len;
    inputFile >> len;
    inputFile.close();
    

    unsigned long long p = GenRandomPrime(len);
    unsigned long long q = GenRandomPrime(len);
    unsigned long long N = p * q;
    unsigned long long n = (p - 1) * (q - 1);

    unsigned long long e = 3;
    while (GCD(e, n) != 1)
    {
        e = 2 + rand() % (n - 2);
    }


    unsigned long long d = ModInverse(e, n);
    unsigned long long encrypted_message = Encrypt(message, e, N);
    std::ofstream middleFile(middle_file);
    if (!middleFile)
        std::cerr << "Error" << std::endl;
    middleFile.clear();
    middleFile << "Encrypted message: " << encrypted_message << std::endl;
    middleFile << "Public key (e, N): " << '(' << e << ", " << N << ')' << std::endl;
    middleFile << "Private key (d, N): " << '(' << d << ", " << N << ')' << std::endl;
    middleFile.close();


    unsigned long long decrypted_message = Decrypt(encrypted_message, d, N);
    std::ofstream outputFile(output_file);
    if (!outputFile)
        std::cerr << "Error" << std::endl;
    outputFile.clear();
    outputFile << "Original message: " << message << std::endl;
    outputFile << "Decrypted message: " << decrypted_message << std::endl;
    outputFile << message << " == " << decrypted_message << " = " << (message == decrypted_message) << std::endl;
    outputFile.close();


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
    /*std::ofstream outputFile("composite10_18.in");
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
        while (i % 2 == 0)
            i = dist(gen);
        if (!Rabin_Primality(i) && !Ferma_Primality(i))
        {
            outputFile << i << std::endl;
            ++count;
        }

    }*/



    /*std::ifstream inputFile("carlmichael.in");
    if (!inputFile)
        std::cerr << "Error" << std::endl;
    std::vector<unsigned long long> numbers;
    unsigned long long num;
    while (inputFile >> num)
        numbers.push_back(num);
    inputFile.close();

    std::ofstream outputFile("carlmichael.out");
    outputFile.clear();
    if (!outputFile)
        std::cerr << "Error" << std::endl;
    int count = 1;
    for (unsigned long long i : numbers)
    {
        outputFile << count << ") " << i << std::endl;
        outputFile << "  " << "Default test: ";
        auto start = std::chrono::steady_clock::now();
        bool def = Default_Primality(i);
        auto end = std::chrono::steady_clock::now();
        outputFile << def << "   (" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds)" << std::endl;

        outputFile << "  " << "Ferma test:   ";
        start = std::chrono::steady_clock::now();
        bool ferma = Ferma_Primality(i);
        end = std::chrono::steady_clock::now();
        outputFile << ferma << "   (" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds)" << std::endl;

        outputFile << "  " << "Rabin test:   ";
        start = std::chrono::steady_clock::now();
        bool rabin = Rabin_Primality(i);
        end = std::chrono::steady_clock::now();
        outputFile << rabin << "   (" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds)" << std::endl;
        ++count;
        std::cout << count;
    }
    outputFile.close();*/




    /*unsigned long long a = GenRandomPrime(9);
    std::cout << a << std::endl;
    std::cout << Default_Primality(a) << std::endl;*/
    
    RSA("RSA.in", "RSA.middle", "RSA.out");

    return 0;
}

