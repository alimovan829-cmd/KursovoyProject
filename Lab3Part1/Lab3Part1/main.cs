using static Lab3Part1.Team;
using static Lab3Part1.Monster;
using static Lab3Part1.Move;
using Lab3Part1;
using System.Runtime.CompilerServices;


Screen currentScreen = Screen.MainMenu;
bool running = true;

Monster m1 = new (0, Monster.Species.dragon, 1), m2 = new (1, Monster.Species.mermaid, 5), m3 = new (2, Monster.Species.gnome, 1), m4 = new (3, Monster.Species.gnome, 10), m5 = new (4, Monster.Species.leshy, 3), m6 = new (5, Monster.Species.imp, 4), m7 = new (6, Monster.Species.leshy, 7);
Team current_team = new Team(new List<Monster> {m1, m2, m3, m4});
List<Monster> collection = new List<Monster> { m1, m2, m3, m4, m5, m6, m7 };

Console.WriteLine("Чудесный мир битв\n");
Console.WriteLine("Добро пожаловать!");

while (running)
{
    switch (currentScreen)
    {
        case Screen.MainMenu:
            Console.WriteLine("\nГлавное Меню");
            Console.WriteLine("1. Настроить отряд");
            Console.WriteLine("2. Демонстрация");
            Console.WriteLine("3. Выход");
            switch (Console.ReadKey(true).KeyChar)
            {
                case '1':
                    currentScreen = Screen.TeamView;
                    break;
                case '2':
                    currentScreen=Screen.Demonstration;
                    break;
                case '3':
                    running = false;
                    break;

            }
            break;

        case Screen.TeamView:
            Console.WriteLine("\nВаш отряд:");
            {
                int n = 0;
                foreach (Monster mon in current_team.List_m)
                {
                    Console.Write($"{++n}. {Monster.SpeciesToString(mon.Specie)}, lvl {mon.Lvl} [ ");

                    List<Move> moves = mon.KnownMoves;

                    for (int i = 0; i < moves.Count(); ++i)
                    {
                        Console.Write($"{Move.MoveToString(moves[i].Type)} ({moves[i].MaxUse}/{moves[i].LeftUse})");

                        if (i < moves.Count() - 1)
                        {
                            Console.Write(", ");
                        }
                        else Console.Write(" ]\n");
                    }
                }
            }

            Console.WriteLine("\nЧто хотите сделать?");
            Console.WriteLine("1. Добавить монстра в отряд");
            Console.WriteLine("2. Убрать монстра из отряда");
            Console.WriteLine("3. Назад");

            switch (Console.ReadKey(true).KeyChar)
            {
                case '1': currentScreen = Screen.Collection; break;
                case '3': currentScreen = Screen.MainMenu; break;
                case '2':
                    {
                        int num;
                        do
                        {
                            Console.WriteLine("Выберите монстра: ");
                            if (!int.TryParse(Console.ReadLine(), out num) || num < 1 || num > current_team.List_m.Count()) Console.WriteLine("Такого монстра нет!");
                        } while (num < 1 || num > current_team.List_m.Count());

                        current_team.RemoveMonster(num - 1);
                        break;
                    }
            }
            break;

        case Screen.Collection:
            Console.WriteLine("\nВаша коллекция:");

            {
                int n = 0;
                foreach (Monster mon in collection)
                {
                    Console.Write($"{++n}. {Monster.SpeciesToString(mon.Specie)}, lvl {mon.Lvl} [ ");

                    List<Move> moves = mon.KnownMoves;

                    for (int i = 0; i < moves.Count(); ++i)
                    {
                        Console.Write($"{Move.MoveToString(moves[i].Type)} ({moves[i].MaxUse}/{moves[i].LeftUse})");

                        if (i < moves.Count() - 1)
                        {
                            Console.Write(", ");
                        }
                        else Console.Write(" ]\n");
                    }
                }
                int num;
                do
                {
                    Console.WriteLine("Выберите монстра: ");
                    if (!int.TryParse(Console.ReadLine(), out num) || num < 1 || num > collection.Count()) Console.WriteLine("Такого монстра нет!");
                } while (num < 1 || num > collection.Count());

                current_team.AddMonster(collection[num - 1]);

                currentScreen = Screen.TeamView;
                break;
            }
        case Screen.Demonstration:
            Console.WriteLine("\nДемонстрация работы ссылки и копии:\n");
            Console.WriteLine("Первоначальный отряд (объект current_team):");
            Console.WriteLine(current_team.ToString());
            Team copy_team = current_team;
            copy_team.AddMonster(new Monster(45, Monster.Species.mermaid, 55));
            Console.WriteLine("\nНовый монстр добавлен через копию ссылки на объект current_team:");
            Console.WriteLine(current_team.ToString());

            Team a = (Team)current_team.Clone();
            a.AddMonster(new Monster(45, Monster.Species.dragon, 5));
            Console.WriteLine("\nНовый монстр добавлен в копию current_team:\n");
            Console.WriteLine($"Копия: {a.ToString()} ");
            Console.WriteLine($"Оригинал: {current_team.ToString()} ");

            Console.WriteLine("\nДемонстрация работы освобождения ресурса:\n");
            var m = new Monster(45, Monster.Species.mermaid, 55);
            Console.WriteLine($"Создаётся объект: {m.ToString()}");
            m.Dispose();
            Console.WriteLine("Ресурс созданного объекта освобождён.\n");

            static WeakReference<Monster> CreateTemporary()
            {
                var temp = new Monster(45, Monster.Species.mermaid, 55);
                return new WeakReference<Monster>(temp);
            }

            Console.WriteLine("Демонстрация работы сборшика мусора:\n");
            var watcher = CreateTemporary();
            GC.Collect();
            GC.WaitForPendingFinalizers();
            Console.WriteLine($"{ watcher.TryGetTarget(out _)} - Объект уничтожен.");

            currentScreen = Screen.MainMenu;
            Console.ReadKey(true);
            break;
    }
}
enum Screen { MainMenu, TeamView, Collection, Demonstration };