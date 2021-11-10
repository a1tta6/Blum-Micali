#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Возведение в степень по модулю
long int exponentiationModulo(long long int x, long long int y, long long int N)
{
    if (y == 0) return 1;
    int z = exponentiationModulo(x, y / 2, N);
    if (y % 2 == 0)
        return (z * z) % N;
    else
        return (x * z * z) % N;
}
//Находит первообразный корень по простому модулю р
int primitiveRoot(long long p)
{
    vector<int> fact; //динамический массив для факториала
    int phi = p - 1, n = phi; //функция пробегающая по всем числам от 1 до n-1
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            fact.push_back(i);//помещает факториал в конец
            while (n % i == 0)
                n /= i;

        }
    if (n > 1)
        fact.push_back(n);
    for (int res = 2; res <= p; ++res)
    {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= exponentiationModulo(res, phi / fact[i], p) != 1;
        if (ok) return res;

    }
    return -1;//если нет первообразного корня, передает в результат -1
}

// Взятие случайного большого простого числа из файла
long int generateP()
{
	ifstream f;
	f.open("primes1.txt");
	long long int p = 0;
    long long int r = time(0)%10000;
	for (long long int i = 0; i < r; i++)
		f >> p;
	f.close();
	return p;
}
int blumMicaliGenerator(long long int p, long long int g, long long int x, long long int &xNext)
{

    xNext = exponentiationModulo(g, x, p);
    if (xNext < (p - 1) / 2)
        return 1;
    else return 0;

}
bool pearsonCsTest(int numbers[], int n) {
    int fr1 = 0, fr2 = 0, tF1 = n / 2, tF2 = n / 2;
    for (int i = 0; i < n; i++)
        if (numbers[i])
            fr1++;
        else fr2++;
    double hi = pow((abs(fr1 - tF1) - 0.5), 2) / tF1 + pow((abs(fr2 - tF2) - 0.5), 2) / tF2;
    cout <<"Хи-квадрат "<< hi << endl;
    if (hi < 3.841)
        return true;
    else return false;
}
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "RUS");
    const int n = 20;
    long long int p, g, x, xNext;
    int* numbers = new int[n];
    bool norm = false;
    while (!norm)
    {
        p = generateP();
        cout << "p= " << p << endl;
        g = primitiveRoot(p);
        cout << "g= " << g << endl;
        x = time(0) % 100;
        numbers[0] = blumMicaliGenerator(p, g, x, xNext);
        cout << numbers[0] << ' ';

        for (int i = 1; i < n; i++)
        {
            x = xNext;
            numbers[i] = blumMicaliGenerator(p, g, x, xNext);
            cout << numbers[i] << ' ';
        }
        cout << endl;
        norm = pearsonCsTest(numbers, n);
        cout << "Нормальное распределение? : " << norm << endl;

    }
   
}