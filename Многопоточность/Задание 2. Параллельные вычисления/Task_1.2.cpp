#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <Windows.h>

void sum_vec(std::vector<int> vec1, std::vector<int> vec2) 
{
	for (int i = 0; i < vec1.size(); ++i) 
	{
		double sum{0};
		sum += vec1.at(i) + vec2.at(i);
	}
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> vec1;
	std::vector<int> vec2;
	std::vector<int> vec_size{ 1000, 10000, 100000, 1000000 };
	std::vector<int> number_thread{ 1, 2, 4, 8, 16 };

	std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;
	std::cout << "\t\t" << 1000 << "\t\t" << 10000 << "\t\t" << 100000 << "\t\t" << 1000000 << std::endl;

	for (const auto& count : number_thread)
	{
		std::cout << count << " потоков\t";

		for (const auto& x : vec_size)
		{
			vec1.resize(x, 1);
			vec2.resize(x, 2);
			std::vector<std::thread> vectorThreads;
			int vectorsSize = x / count;
			
			auto start = std::chrono::steady_clock::now();
			
			for (int i = 0; i < count; i++) 
			{
				std::vector<int> new_vec1;
				std::vector<int> new_vec2;
				int rightBorder = (i != count - 1) ? vectorsSize * (i + 1) : x;
				for (int j = vectorsSize * i; j < rightBorder; ++j) 
				{
					new_vec1.push_back(vec1.at(j));
					new_vec2.push_back(vec2.at(j));
				}
				vectorThreads.push_back(std::thread(sum_vec, new_vec1, new_vec2));
			}
			for (auto& y : vectorThreads) 
			{
				y.join();
			}
			auto stop = std::chrono::steady_clock::now(); 
			auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
			std::cout << static_cast<double>(duration.count()) / 1e6 << "s\t";
		}
		std::cout << std::endl;
	}
	
	std::cout << "\n";
    system("pause");
	return 0;
}