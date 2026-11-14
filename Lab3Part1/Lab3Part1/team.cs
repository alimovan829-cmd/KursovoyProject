using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Lab3Part1
{
    internal class Team : ICloneable
    {
        private List<Monster> _list_m;
        public List<Monster> List_m
        {
            get { return _list_m; }
            set { _list_m = value; }
        }

        public Team(List<Monster> list)
        {
            _list_m = list;
        }
        public void AddMonster(Monster monster)
        {
            if (monster != null)
            {
                if (!_list_m.Contains(monster))
                {
                    if (_list_m.Count() < 6) 
                    {
                        _list_m.Add(monster);
                    } else Console.WriteLine("Слишком много монстров в отряде!");
                }
                else Console.WriteLine("Монстр уже в отряде!");
            }
        }
        public void RemoveMonster(int index)
        {
            if (_list_m.Count > 1)
            {
                if (_list_m.Count > index && index >= 0) {
                    _list_m.RemoveAt(index);
                }
                else Console.WriteLine("Такого монстра нет!");
            }
            else Console.WriteLine("Слишком мало монстров в отряде!");
        }
        public override string ToString()
        {
            string a = "Отряд: ";
            for (int i = 0; i < _list_m.Count(); ++i)
            {
                a = a + _list_m[i].ToString();
                if (i < _list_m.Count() - 1)
                {
                    a = a + ", ";
                }
            }
            return a;
        }
        
        public object Clone()
        {
            List<Monster> list = new List<Monster> (_list_m);
            return new Team(list);  
        }
    }
}
