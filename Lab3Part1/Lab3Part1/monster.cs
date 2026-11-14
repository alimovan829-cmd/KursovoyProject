using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Lab3Part1.Monster;

namespace Lab3Part1
{
    internal class Monster : IDisposable
    {
        public enum Species { dragon, mermaid, gnome, imp, leshy, missing };
        public static string SpeciesToString(Species spiecie)
        {
            switch (spiecie) {
                case Species.dragon: return "Дракон";
                case Species.mermaid: return "Русалка";
                case Species.gnome: return "Гном";
                case Species.imp: return "Имп";
                case Species.leshy: return "Леший";
                default: return "Пропал";
            }
        }

        private int _id;
        private Species _specie;
        private int _lvl;
        private List<Move> _knownMoves;
        public int Id { get => _id ; }
        public Species Specie { get => _specie; }
        public int Lvl { get => _lvl; private set => _lvl+=1 ;}
        public List<Move> KnownMoves { get => _knownMoves; }
        
        public Monster(int id, Species specie, int lvl)
        {
            _id = id;
            _specie = specie;
            _lvl = lvl;
            _knownMoves = PutMoves(specie);
        }

        List<Move> PutMoves(Species specie)
        {
            switch (specie)
            {
                case Species.dragon: return new List<Move> { new (Move.MoveTypes.FireBall, 20) };
                case Species.mermaid: return new List<Move> { new (Move.MoveTypes.Splash, 15), new (Move.MoveTypes.WaterCannon, 10)};
                case Species.gnome: return new List<Move> { new (Move.MoveTypes.Dig, 30) };
                case Species.imp: return new List<Move> { new (Move.MoveTypes.Bite, 20), new (Move.MoveTypes.Dance, 5) };
                case Species.leshy: return new List<Move> { new (Move.MoveTypes.Dig, 30) };
                case Species.missing: return new List<Move> { new (Move.MoveTypes.Struggle, 0) };
                default: return new List<Move> { };
            }
        }

        public void Dispose() => Console.WriteLine($"Монстр {SpeciesToString(_specie)} отпущен");

        public override string ToString()
        {
            string a = $"{SpeciesToString(_specie)} (lvl {_lvl}): ";
            for (int i = 0; i < _knownMoves.Count(); ++i)
            {
                a = a + _knownMoves[i].ToString();
                if (i < _knownMoves.Count() - 1)
                {
                    a = a + " ";
                }
            }
            return a;
        }
    }

}
