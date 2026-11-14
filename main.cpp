#include <iostream>
#include <format>
#include <conio.h>
#include "move.hpp"
#include "monster.hpp"
#include "team.hpp"
#include <memory>

enum class Screen { MainMenu, TeamView, Collection, Demonstration};

int main() {
	setlocale(LC_ALL, "");

	Screen currentScreen = Screen::MainMenu;
	bool running = true;

	std::cout << "Чудесный мир битв\n\n";
	std::cout << "Добро пожаловать!\n";

	std::shared_ptr<game::Monster> m1 = std::make_shared<game::Monster>(0, game::Species::dragon, 1); 
	std::shared_ptr<game::Monster> m2 = std::make_shared<game::Monster>(1, game::Species::mermaid, 5);
	std::shared_ptr<game::Monster>m3 = std::make_shared<game::Monster>(2, game::Species::gnome, 1);
	std::shared_ptr<game::Monster>m4 = std::make_shared<game::Monster>(3, game::Species::gnome, 10);
	std::shared_ptr<game::Monster>m5 = std::make_shared<game::Monster>(4, game::Species::leshy, 3);
	std::shared_ptr<game::Monster>m6 = std::make_shared<game::Monster>(5, game::Species::imp, 4);
	std::shared_ptr<game::Monster>m7 = std::make_shared<game::Monster>(4, game::Species::leshy, 7);
	std::vector<std::shared_ptr<game::Monster>> collection({ m1, m2, m3, m4, m5, m6, m7});
	game::Team current_team({ m1, m2, m3, m4 });


	while (running) {
		switch (currentScreen) {
			case Screen::MainMenu:
				std::cout << "\nГлавное Меню" << std::endl;
				std::cout << "1. Настроить отряд" << std::endl;
				std::cout << "2. Демонстрация" << std::endl;
				std::cout << "3. Выход" << std::endl;
				switch (_getch()) {
					case '1': currentScreen = Screen::TeamView; break;
					case '2': currentScreen = Screen::Demonstration; break;
					case '3': running = false; break;
				}
				break;

			case Screen::TeamView:

				std::cout << "\nВаш отряд:\n";
				{
					int n = 0;
					for (std::shared_ptr<game::Monster> mon : current_team.GetList()) {
						std::cout << ++n << ". " << SpeciesToString(mon->GetSpecie()) << ", lvl " << mon->GetLvl() << " { ";

						const auto& moves = mon->GetMoves();

						for (size_t i = 0; i < moves.size(); ++i) {
							std::cout << std::format("{} ({}/{})", game::MovesToString(moves[i].GetType()), moves[i].GetLeftUse(), moves[i].GetMaxUse());

							if (i < moves.size() - 1) {
								std::cout << ", ";
							}
							else std::cout << " }";
						}

						std::cout << std::endl << std::endl;
					}
				}

				std::cout << "Что хотите сделать?" << std::endl;
				std::cout << "1. Добавить монстра в отряд" << std::endl;
				std::cout << "2. Убрать монстра из отряда" << std::endl;
				std::cout << "3. Назад" << std::endl;

				switch (_getch()) {
					case '1': currentScreen = Screen::Collection; break;
					case '3': currentScreen = Screen::MainMenu; break;
					case '2':
						int num = 0;
						do {
							std::cout << "Выберите монстра: ";
							std::cin >> num;
							if (num < 1 || num > current_team.GetList().size()) std::cout << "Такого монстра нет!" << std::endl;
						} while (num < 1 || num > current_team.GetList().size());

						current_team.RemoveMonster(num - 1);
						break;
				}

				break;
			case Screen::Collection:
			{
				std::cout << "\nВаша коллекция:\n";

				int n = 0;
				for (std::shared_ptr<game::Monster> mon : collection) {
					std::cout << ++n << ". " << SpeciesToString(mon->GetSpecie()) << ", lvl " << mon->GetLvl() << " { ";

					const auto& moves = mon->GetMoves();

					for (size_t i = 0; i < moves.size(); ++i) {
						std::cout << std::format("{} ({}/{})", game::MovesToString(moves[i].GetType()), moves[i].GetLeftUse(), moves[i].GetMaxUse());

						if (i < moves.size() - 1) {
							std::cout << ", ";
						}
						else std::cout << " }";
					}

					std::cout << std::endl;
				}
				int num = 0;
				do {
					std::cout << "Выберите монстра: ";
					std::cin >> num;
					if (num < 1 || num > collection.size()) std::cout << "Такого монстра нет!" << std::endl;
				} while (num < 1 || num > collection.size());

				current_team.AddMonster(collection[num - 1]);

				currentScreen = Screen::TeamView;

				break;
				}
			case Screen::Demonstration:
				{
				std::cout << "Демонстрация работы unique_ptr:" << std::endl;
				std::unique_ptr<game::Monster> m1 = std::make_unique<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "Создаётся объект типа Монстр с указателем unique_ptr: " << SpeciesToString(m1->GetSpecie()) << ", lvl " << m1->GetLvl() << std::endl;
				std::cout << "Владение передаётся другому указателю." << std::endl;
				std::unique_ptr<game::Monster> m2 = std::move(m1);
				std::cout << "Объектом теперь владеет новый указатель: ";
				std::cout << SpeciesToString(m2->GetSpecie()) << ", lvl " << m2->GetLvl() << std::endl;
				std::cout << "Изначальный указатель теперь пуст: " << m1 << std::endl;
				std::cout << "Объект уничтожается при выходе из блока без delete:" << std::endl;
				}

				std::cout << "\nДемонстрация работы shared_ptr:" << std::endl;
				std::cout << "Создаётся объект типа Монстр с указателем shared_ptr:" << std::endl;
				std::shared_ptr<game::Monster> shared1 = std::make_shared<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "Счётчик владельцев объекта: " << shared1.use_count() << std::endl;
				std::cout << "Создаётся копия указателя на тот же объект: " << std::endl;
				std::shared_ptr<game::Monster> shared2 = shared1;
				std::cout << "Счётчик владельцев объекта: " << shared1.use_count() << std::endl;
				std::cout << "Значение оригинала приравнивается к nullptr. Объект все еще существует." << std::endl;
				shared1 = nullptr;
				std::cout << "Счётчик владельцев объекта: " << shared2.use_count() << std::endl;
				std::cout << "Значение копии тоже приравнивается к nullptr. Счётчик владельцев становится равен 0. Объект уничтожается:" << std::endl;
				shared2 = nullptr;


				std::cout << "\nДемонстрация работы weak_ptr:" << std::endl;
				std::cout << "Создаётся объект типа Монстр с указателем shared_ptr:" << std::endl;
				std::shared_ptr<game::Monster> shared = std::make_shared<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "Счётчик владельцев объекта: " << shared.use_count() << std::endl;
				std::cout << "Создаётся наблюдатель для этого объекта с указателем weak_ptr" << std::endl;
				std::weak_ptr<game::Monster> weak = shared;
				std::cout << "Счётчик владельцев не увеличивается: " << shared.use_count() << std::endl;
				std::cout << "Через weak_ptr можно проверить существует ли объект: ";
				if (weak.lock()) std::cout << "Объект существует." << std::endl;
				else std::cout << "Объект не существует." << std::endl;

				std::cout << "Значение shared_ptr приравнивается к nullptr, объект уничтожается: " << std::endl;
				shared = nullptr;

				std::cout << "Снова проверяем существование объекта через weak_ptr: ";
				if (weak.lock()) std::cout << "Объект существует." << std::endl;
				else std::cout << "Объект не существует." << std::endl;

				currentScreen = Screen::MainMenu;
				break;
		}
		
	}


	return 0;
}
