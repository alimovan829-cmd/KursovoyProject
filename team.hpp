#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <memory>
#include "monster.hpp"


namespace game
{

    class Team
    {

    private:
        std::vector<std::shared_ptr<Monster>> m_list;
    public:
        Team(const std::vector<std::shared_ptr<Monster>> monsters);
        ~Team();

        Team() = delete;
        Team(const Team&) = delete;
        Team(Team&&) = delete;
        Team& operator=(const Team&) = delete;
        Team& operator=(Team&&) = delete;

        [[nodiscard]] auto GetList() const
        {
            return m_list;
        }


        void UpdateExp(int exp);
        void AddMonster(std::shared_ptr<Monster>& monster);
        void RemoveMonster(int index);
    };

} // namespace game