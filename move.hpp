#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace game
{
    enum class MoveTypes { FireBall, Splash, WaterCannon, Song, Dig, RockThrow, Dance, Poison, Bite, Scratch, SadFace, Struggle };
    std::string MovesToString(MoveTypes move);
    

    class Move
    {

    private:
        MoveTypes m_type;
        int m_maxUse;
        int m_leftUse;

    public:
        Move(MoveTypes type, int maxUse);

        Move() = delete;
        Move(const Move&) = default;
        Move(Move&&) = default;
        Move& operator=(const Move&) = delete;
        Move& operator=(Move&&) = delete;
        ~Move();

        [[nodiscard]] auto GetType() const
        {
            return m_type;
        }

        [[nodiscard]] auto GetMaxUse() const
        {
            return m_maxUse;
        }

        [[nodiscard]] auto GetLeftUse() const
        {
            return m_leftUse;
        }

        void SetType(MoveTypes type)
        {
            m_type = type;
        }

        void SetSpecie(int maxUse)
        {
            m_maxUse = maxUse;
        }

        void SetLvl(int leftUse)
        {
            m_leftUse = leftUse;
        }

    };

} // namespace game