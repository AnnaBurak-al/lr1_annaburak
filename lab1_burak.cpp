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
	bool flag = true;

	void read() {
		std::cout << "Введите название трубы: ";
		std::cin >> name;

		while (true) {
			std::cout << "Введите длину в км: ";
			if (std::cin >> length && std::cin.peek() == '\n' && length > 0) break;
			std::cout << "Введите положительное число.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		while (true) {
			std::cout << "Введите диаметр в мм: ";
			if (std::cin >> diametr && std::cin.peek() == '\n' && diametr > 0) break;
			std::cout << "Введите положительное число.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		int tempRepair;
		while (true) {
			std::cout << "В ремонте? (1 - да, 0 - нет): ";
			if (std::cin >> tempRepair && std::cin.peek() == '\n' && (tempRepair == 0 || tempRepair == 1)) {
				repair = (tempRepair == 1);
				break;
			}
			std::cout << "Введите 0 или 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		flag = false;
	}

	void print() const {
		if (flag) {
			std::cout << "\nТруба еще не добавлена!\n";
			return;
		}
		std::cout << "\nИтоговая информация о трубе\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Длина: " << length << " км\n";
		std::cout << "Диаметр: " << diametr << " мм\n";
		std::cout << "В ремонте?: " << (repair ? "да" : "нет") << "\n";
	}
};

struct CS {
	std::string name;
	int kol_tsex;
	int active_tsex;
	int class_stan;
	bool flag = true;

	void read() {
		std::cout << "\nВведите название КС: ";
		std::cin >> name;
		while (true) {
			std::cout << "Введите количество цехов (всего): ";
			if (std::cin >> kol_tsex && std::cin.peek() == '\n' && kol_tsex > 0) break;
			std::cout << "Введите положительное целое число.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		while (true) {
			std::cout << "Введите количество цехов в работе: ";
			if (std::cin >> active_tsex && std::cin.peek() == '\n' && active_tsex >= 0 && active_tsex <= kol_tsex) break;
			std::cout << "Введите число от 0 до " << kol_tsex << ".\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		while (true) {
			std::cout << "Введите класс станции: ";
			if (std::cin >> class_stan && std::cin.peek() == '\n' && class_stan > 0) break;
			std::cout << "Введите положительное целое число.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		flag = false;
	}

	void print() const {
		if (flag) {
			std::cout << "\nКомпрессорная станция еще не добавлена\n";
			return;
		}
		std::cout << "\nИтоговая информация о КС\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Количество цехов: " << kol_tsex << "\n";
		std::cout << "Количество активных цехов: " << active_tsex << "\n";
		std::cout << "Класс станции: " << class_stan << "\n";
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	// На этом этапе мы просто проверяем, что структуры работают
	Pipe pipe;
	CS cs;
	pipe.read();
	pipe.print();

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
