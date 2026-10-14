#include "monster.hpp"
#include "move.hpp"
#include <iostream>

namespace game
{

    Monster::Monster(int id, Species specie, int lvl)
        : m_id{ id }
        , m_specie{ specie }
        , m_lvl{ lvl }
        , m_exp{ 0 }
        , m_knownMoves {PutMoves(specie)}

    {
        if (m_knownMoves.size() == 0) {
            m_knownMoves = PutMoves(Species::missing);
        }
    }
    
    Monster::~Monster()
    {
        std::cout << "Объект класса Monster (монстр) уничтожен" << std::endl;
    }

    std::string SpeciesToString(Species species) {
        switch (species) {
        case Species::dragon:  return "Дракон";
        case Species::mermaid: return "Русалка";
        case Species::gnome:   return "Гном";
        case Species::imp:     return "Имп";
        case Species::leshy:   return "Леший";
        default:               return "Пропал";
        }
    }
 

    std::vector<Move> PutMoves(Species species) {
        switch (species) {
        case Species::dragon:  return { Move(MoveTypes::FireBall, 20) };
        case Species::mermaid: return { Move (MoveTypes::Splash, 15), Move (MoveTypes::WaterCannon, 10)};
        case Species::gnome:   return { Move(MoveTypes::Dig, 30) };
        case Species::imp:     return { Move(MoveTypes::Bite, 20), Move(MoveTypes::Dance, 5) };
        case Species::leshy:   return { Move(MoveTypes::Dig, 30) };
        case Species::missing: return { Move(MoveTypes::Struggle, 0) };
        default:               return {};
        }
    }

    void Monster::UpdateExp(int exp)
    {
        
    }
    
} // namespace game