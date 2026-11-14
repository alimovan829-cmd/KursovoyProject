using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Lab3Part1.Monster;

namespace Lab3Part1
{
    internal class Move
    {
        public enum MoveTypes { FireBall, Splash, WaterCannon, Song, Dig, RockThrow, Dance, Poison, Bite, Scratch, SadFace, Struggle }
        public static string MoveToString(MoveTypes move)
        {
            switch (move)
            {
                case MoveTypes.FireBall: return "Огненный шар";
                case MoveTypes.Splash: return "Плеск";
                case MoveTypes.WaterCannon: return "Водяная пушка";
                case MoveTypes.Song: return "Песня";
                case MoveTypes.Dig: return "Копать";
                case MoveTypes.RockThrow: return "Бросок камня";
                case MoveTypes.Dance: return "Танец";
                case MoveTypes.Poison: return "Отравить";
                case MoveTypes.Bite: return "Укус";
                case MoveTypes.Scratch: return "Царапать";
                case MoveTypes.SadFace: return "Грустный взгляд";
                default: return "missing";
            }
        }

        private MoveTypes _type;
        private int _maxUse;
        private int _leftUse;
        public MoveTypes Type
        {
            get => _type;
        }
        public int MaxUse
        {
            get => _maxUse;
        }
        public int LeftUse
        {
            get => _leftUse;
        }
        public Move(MoveTypes type, int maxUse)
        {
            _type = type;
            _maxUse = maxUse;
            _leftUse = maxUse;
        }

        public override string ToString()
        {
            return $"{MoveToString(_type)} ({_maxUse}/{_leftUse})";
        }
    }
}
