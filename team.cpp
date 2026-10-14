#include "team.hpp"
#include "monster.hpp"
#include <iostream>

namespace game
{

    Team::Team(const std::vector<Monster*>& monsters)
        : m_list { monsters }
    {
        if (m_list.size() > 6) {
            m_list.resize(6);
        }
    }

    Team::~Team()
    {
        std::cout << "Объект класса Team (отряд) уничтожен" << std::endl;
    }

    void Team::AddMonster(Monster* monster)
    {
        if (monster != nullptr) {
            auto f = std::find(m_list.begin(), m_list.end(), monster);
            if (f==m_list.end()) {
                if (m_list.size() < 6) {
                    m_list.push_back(monster);
                }
                else std::cout << "Слишком много монстров в отряде!" << std::endl;
            } else  std::cout << "Монстр уже в отряде!" << std::endl;
        }

    }

    void Team::RemoveMonster(int index)
    {
        if (m_list.size() > 1) {
            m_list.erase(m_list.begin() + index);
        }
        else std::cout << "Слишком мало монстров в отряде!" << std::endl;

    }

    void Team::UpdateExp(int exp)
    {
        for (auto& monster : m_list) {
            
        }
    }

} // namespace game