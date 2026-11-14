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

	std::cout << "�������� ��� ����\n\n";
	std::cout << "����� ����������!\n";

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
				std::cout << "\n������� ����" << std::endl;
				std::cout << "1. ��������� �����" << std::endl;
				std::cout << "2. ������������" << std::endl;
				std::cout << "3. �����" << std::endl;
				switch (_getch()) {
					case '1': currentScreen = Screen::TeamView; break;
					case '2': currentScreen = Screen::Demonstration; break;
					case '3': running = false; break;
				}
				break;

			case Screen::TeamView:

				std::cout << "\n��� �����:\n";
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
			{
				std::cout << "\n���� ���������:\n";

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
					std::cout << "�������� �������: ";
					std::cin >> num;
					if (num < 1 || num > collection.size()) std::cout << "������ ������� ���!" << std::endl;
				} while (num < 1 || num > collection.size());

				current_team.AddMonster(collection[num - 1]);

				currentScreen = Screen::TeamView;

				break;
				}
			case Screen::Demonstration:
				{
				std::cout << "������������ ������ unique_ptr:" << std::endl;
				std::unique_ptr<game::Monster> m1 = std::make_unique<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "�������� ������ ���� ������ � ���������� unique_ptr: " << SpeciesToString(m1->GetSpecie()) << ", lvl " << m1->GetLvl() << std::endl;
				std::cout << "�������� ��������� ������� ���������." << std::endl;
				std::unique_ptr<game::Monster> m2 = std::move(m1);
				std::cout << "�������� ������ ������� ����� ���������: ";
				std::cout << SpeciesToString(m2->GetSpecie()) << ", lvl " << m2->GetLvl() << std::endl;
				std::cout << "����������� ��������� ������ ����: " << m1 << std::endl;
				std::cout << "������ ������������ ��� ������ �� ����� ��� delete:" << std::endl;
				}

				std::cout << "\n������������ ������ shared_ptr:" << std::endl;
				std::cout << "�������� ������ ���� ������ � ���������� shared_ptr:" << std::endl;
				std::shared_ptr<game::Monster> shared1 = std::make_shared<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "������� ���������� �������: " << shared1.use_count() << std::endl;
				std::cout << "�������� ����� ��������� �� ��� �� ������: " << std::endl;
				std::shared_ptr<game::Monster> shared2 = shared1;
				std::cout << "������� ���������� �������: " << shared1.use_count() << std::endl;
				std::cout << "�������� ��������� �������������� � nullptr. ������ ��� ��� ����������." << std::endl;
				shared1 = nullptr;
				std::cout << "������� ���������� �������: " << shared2.use_count() << std::endl;
				std::cout << "�������� ����� ���� �������������� � nullptr. ������� ���������� ���������� ����� 0. ������ ������������:" << std::endl;
				shared2 = nullptr;


				std::cout << "\n������������ ������ weak_ptr:" << std::endl;
				std::cout << "�������� ������ ���� ������ � ���������� shared_ptr:" << std::endl;
				std::shared_ptr<game::Monster> shared = std::make_shared<game::Monster>(49, game::Species::dragon, 77);
				std::cout << "������� ���������� �������: " << shared.use_count() << std::endl;
				std::cout << "�������� ����������� ��� ����� ������� � ���������� weak_ptr" << std::endl;
				std::weak_ptr<game::Monster> weak = shared;
				std::cout << "������� ���������� �� �������������: " << shared.use_count() << std::endl;
				std::cout << "����� weak_ptr ����� ��������� ���������� �� ������: ";
				if (weak.lock()) std::cout << "������ ����������." << std::endl;
				else std::cout << "������ �� ����������." << std::endl;

				std::cout << "�������� shared_ptr �������������� � nullptr, ������ ������������: " << std::endl;
				shared = nullptr;

				std::cout << "����� ��������� ������������� ������� ����� weak_ptr: ";
				if (weak.lock()) std::cout << "������ ����������." << std::endl;
				else std::cout << "������ �� ����������." << std::endl;

				currentScreen = Screen::MainMenu;
				break;
		}
		
	}


	return 0;
}
