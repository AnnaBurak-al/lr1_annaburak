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

	void ent_repair() {
		if (flag) {
			std::cout << "\nСначала добавьте трубу\n";
			return;
		}
		int izmrepair;
		while (true) {
			std::cout << "\nИзменить признак в ремонте (1 - в ремонте, 0 - не в ремонте): ";
			if (std::cin >> izmrepair && std::cin.peek() == '\n' && (izmrepair == 0 || izmrepair == 1)) {
				repair = (izmrepair == 1);
				break;
			}
			std::cout << "Введите 0 или 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
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

	void work_cs() {
		int work;
		std::cout << "\nЗапуститить или остановить цех КС" << name << ":\n";
		std::cout << "1 - запустить цех\n";
		std::cout << "2 - остановить цех\n";
		while (true) {
			std::cout << "Выберите действие: ";
			if (std::cin >> work && std::cin.peek() == '\n' && (work == 1 || work == 2)) break;
			std::cout << "Введите 1 или 2.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		if (work == 1) {
			if (active_tsex < kol_tsex) {
				active_tsex++;
				std::cout << "Цех запущен, активных цехов: " << active_tsex << "\n";
			}
			else {
				std::cout << "Все цеха уже работают!\n";
			}
		}
		else if (work == 2) {
			if (active_tsex > 0) {
				active_tsex--;
				std::cout << "Цех остановлен, активных цехов: " << active_tsex << "\n";
			}
			else {
				std::cout << "Нет работающих цехов для остановки\n";
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Pipe pipe;
	CS cs;

	pipe.read();
	cs.read();

	pipe.ent_repair();
	cs.work_cs();

	pipe.print();
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
