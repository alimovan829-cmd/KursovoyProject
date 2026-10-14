#include "move.hpp"
#include <iostream>

namespace game
{
    Move::Move(MoveTypes type, int maxUse)
        : m_type{ type }
        , m_maxUse{ maxUse }
        , m_leftUse{ maxUse }
    {
    }

    Move::~Move()
    {
        std::cout << "Объект класса Move (действие) уничтожен" << std::endl;
    }

    std::string MovesToString(MoveTypes move) {
        switch (move) {
        case MoveTypes::FireBall:  return "Огненный шар";
        case MoveTypes::Splash: return "Плеск";
        case MoveTypes::WaterCannon:   return "Водяная пушка";
        case MoveTypes::Song:     return "Песня";
        case MoveTypes::Dig:   return "Копать";
        case MoveTypes::RockThrow:  return "Бросок камня";
        case MoveTypes::Dance: return "Танец";
        case MoveTypes::Poison:   return "Отравить";
        case MoveTypes::Bite:     return "Укус";
        case MoveTypes::Scratch:     return "Царапать";
        case MoveTypes::SadFace:     return "Грустный взгляд";
        default:               return "missing";
        }
    }

} // namespace game