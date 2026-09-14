// lab1_burak.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <clocale>
struct Pipe {
	std::string name;
	double length;
	double diametr;
	bool repair;
	void read() {
		std::cout << "введите название трубы: ";
		std::cin >> name;
		std::cout << "введите длину в км: ";
		std::cin >> length;
		std::cout << "введите диаметр в мм: ";
		std::cin >> diametr;
		std::cout << "в ремонте? (1 - да, 0 - нет):";
		std::cin >> repair;
	}
	void print() {
		std::cout << "\nитоговая информация о трубе\n";
		std::cout << "название: " << name << "\n";
		std::cout << "длина: " << length << " км\n";
		std::cout << "диаметр: " << diametr << " мм\n";
		std::cout << "в ремонте?: " << (repair ? "да" : "нет") << "\n";
	}
	void ent_repair() {
		std::cout << "\nизменить признак в ремонте (1 - в ремонте, 0 - не в ремонте): ";
		std::cin >> repair;
	}
};

struct CS {
	std::string name;
	int kol_tsex;
	int active_tsex;
	int class_stan;
	void read() {
		std::cout << "\nвведите название КС: ";
		std::cin >> name;
		std::cout << "введите количество цехов (всего): ";
		std::cin >> kol_tsex;
		std::cout << "введите количество цехов в работе: ";
		std::cin >> active_tsex;
		std::cout << "введите класс станции: ";
		std::cin >> class_stan;
	}
	void print() {
		std::cout << "\nитоговая информация о КС\n";
		std::cout << "название: " << name << "\n";
		std::cout << "количество цехов: " << kol_tsex << "\n";
		std::cout << "количество активных цехов: " << active_tsex << "\n";
		std::cout << "класс станции: " << class_stan << "\n";
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	Pipe pipe;
	pipe.read();
	pipe.print();
	pipe.ent_repair();
	pipe.print();
	CS cs;
	cs.read();
	cs.print();
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
