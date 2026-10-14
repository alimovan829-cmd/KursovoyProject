#include <iostream>
#include <format>
#include <conio.h>
#include "move.hpp"
#include "monster.hpp"
#include "team.hpp"

enum class Screen { MainMenu, TeamView, Collection};

int main() {
	setlocale(LC_ALL, "");

	Screen currentScreen = Screen::MainMenu;
	bool running = true;

	std::cout << "�������� ��� ����\n\n";
	std::cout << "����� ����������!\n";

	game::Monster m1(0, game::Species::dragon, 1), m2(1, game::Species::mermaid, 5), m3(2, game::Species::gnome, 1), m4(3, game::Species::gnome, 10), m5(4, game::Species::leshy, 3), m6(5, game::Species::imp, 4), m7(4, game::Species::leshy, 7);
	std::vector<game::Monster *> collection ({ &m1, &m2, &m3, &m4, &m5, &m6, &m7 });
	game::Team current_team({ &m1, &m2, &m3, &m4});


	while (running) {
		switch (currentScreen) {
			case Screen::MainMenu:
				std::cout << "\n������� ����" << std::endl;
				std::cout << "1. ��������� �����" << std::endl;
				std::cout << "2. �����" << std::endl;
				switch (_getch()) {
					case '1': currentScreen = Screen::TeamView; break;
					case '2': running = false; break;
				}
				break;

			case Screen::TeamView:

				std::cout << "\n��� �����:\n";
				{
					int n = 0;
					for (game::Monster* mon : current_team.GetList()) {
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

				std::cout << "��� ������ �������?" << std::endl;
				std::cout << "1. �������� ������� � �����" << std::endl;
				std::cout << "2. ������ ������� �� ������" << std::endl;
				std::cout << "3. �����" << std::endl;

				switch (_getch()) {
					case '1': currentScreen = Screen::Collection; break;
					case '3': currentScreen = Screen::MainMenu; break;
					case '2':
						int num = 0;
						do {
							std::cout << "�������� �������: ";
							std::cin >> num;
							if (num < 1 || num > current_team.GetList().size()) std::cout << "������ ������� ���!" << std::endl;
						} while (num < 1 || num > current_team.GetList().size());

						current_team.RemoveMonster(num - 1);
						break;
				}

				break;
			case Screen::Collection:
				
				std::cout << "\n���� ���������:\n";

				int n = 0;
				for (game::Monster* mon : collection) {
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
					std::cout << "�������� �������: ";
					std::cin >> num;
					if (num < 1 || num > collection.size()) std::cout << "������ ������� ���!" << std::endl;
				} while (num < 1 || num > collection.size());
				
				current_team.AddMonster(collection[num - 1]);

				currentScreen = Screen::TeamView;

				break;
		}
		
	}


	return 0;
}
