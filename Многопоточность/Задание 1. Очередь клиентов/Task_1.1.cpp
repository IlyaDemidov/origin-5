#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

 int counter_client{0};

void client(int x)
{
    while (counter_client != x)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter_client++;
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << counter_client;
    }
}

void operators(int x)
{
    while (counter_client >= 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << counter_client;
        counter_client--;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Введите максимальное количество клиентов: ";
    int max_client{0};
    std::cin >> max_client;
    
    std::thread t1(client, max_client);
    std::thread t2(operators, max_client);

    t1.join();
    t2.join();
    
    std::cout << "\n";
    system("pause");
    return 0;
}