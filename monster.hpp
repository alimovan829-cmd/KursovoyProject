#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include "move.hpp"
#include <vector>
#include <memory>

namespace game
{
    enum class Species { dragon, mermaid, gnome, imp, leshy, missing };
    std::string SpeciesToString(Species species);
    std::vector<Move> PutMoves(Species species);

    class Monster
    {
    private:
        int m_id;
        Species m_specie;
        int m_lvl;
        int m_exp;
        std::vector<Move> m_knownMoves;

    public:
        Monster(int id, Species specie, int lvl);

        Monster() = delete;
        Monster(const Monster&) = delete;
        Monster(Monster&&) = delete;
        Monster& operator=(const Monster&) = delete;
        Monster& operator=(Monster&&) = delete;
        ~Monster();

        // Unique ID
        [[nodiscard]] auto GetId() const
        {
            return m_id;
        }

        // Monster specie
        [[nodiscard]] auto GetSpecie() const
        {
            return m_specie;
        }

        // Monster lvl
        [[nodiscard]] auto GetLvl() const
        {
            return m_lvl;
        }

        // Monster exp
        [[nodiscard]] auto GetExp() const
        {
            return m_exp;
        }

        // Known moves
        [[nodiscard]] auto GetMoves() const
        {
            return m_knownMoves;
        }


        void SetId( int id)
        {
            m_id = id;
        }

        void SetSpecie(Species specie)
        {
            m_specie = specie;
        }

        void SetLvl(int lvl)
        {
            m_lvl = lvl;
        }

        void SetExp(int exp)
        {
            m_exp = exp;
        }

        void SetMoves() {

        }

        void UpdateExp(int exp);


    };

} // namespace game