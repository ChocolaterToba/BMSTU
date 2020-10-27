using System;
using System.Collections;
using System.Collections.Generic;
using FigureProject;
using SimpleListProject;
using MatrixProject;

namespace Лабораторная___3
{
    class Program
    {
        public enum Options
        {
            SortArrayList = 1,
            SortListFigure = 2,
            DemSparseMatrix = 3,
            DemStack = 4,
            Exit = 5
        }

        static Options Menu()
        {
            Console.WriteLine("Введите номер нужной опции:");
            Console.WriteLine("1: Сортировка на основе ArrayList");
            Console.WriteLine("2: Сортировка на основе List<Figure>");
            Console.WriteLine("3: Демонстрация разряженной матрицы");
            Console.WriteLine("4: Демонстрация стека на основе односвязного списка");
            Console.WriteLine("5: Выход");

            int option = 0;
            while (true)
            {
                if (!int.TryParse(Console.ReadLine(), out option))
                {
                    Console.WriteLine("Неправильный ввод. Повторите ввод");
                }
                else if (!Enum.IsDefined(typeof(Options), option))
                {
                    Console.WriteLine("Неизвестная опция. Повторите ввод");
                }
                else
                {
                    return (Options)option;
                }
            }
        }

        static void Main(string[] args)
        {
            Rectangle rectangle = new Rectangle(2.4, 67);
            Square square = new Square(1);
            Circle circle = new Circle(1);

            Options option = Menu();

            while (option != Options.Exit)
            {
                switch (option)
                {
                    case Options.SortArrayList:
                        {
                            ArrayList nonGenericList = new ArrayList {
                            square,
                            rectangle,
                            circle
                        };

                            Console.WriteLine("До сортировки:");
                            foreach (Figure figure in nonGenericList)
                            {
                                figure.Print();
                            }
                            Console.Write("\n");

                            nonGenericList.Sort();
                            Console.WriteLine("После сортировки (ArrayList):");
                            foreach (Figure figure in nonGenericList)
                            {
                                figure.Print();
                            }
                            Console.Write("\n");
                            break;
                        }

                    case Options.SortListFigure:
                        List<Figure> GenericList = new List<Figure> {
                            square,
                            rectangle,
                            circle
                        };

                        Console.WriteLine("До сортировки:");
                        foreach (Figure figure in GenericList)
                        {
                            figure.Print();
                        }
                        Console.Write("\n");

                        GenericList.Sort();
                        Console.WriteLine("После сортировки (List<Figure>):");
                        foreach (Figure figure in GenericList)
                        {
                            figure.Print();
                        }
                        Console.Write("\n");
                        break;

                    case Options.DemSparseMatrix:
                        Matrix<Figure> matrix = new Matrix<Figure>(2, 2, 2, new FigureMatrixCheckEmpty());
                        matrix[0, 1, 1] = square;
                        matrix[1, 0, 1] = rectangle;
                        matrix[1, 1, 0] = circle;
                        Console.WriteLine(matrix.ToString());
                        break;

                    case Options.DemStack:
                        SimpleStack<Figure> stack = new SimpleStack<Figure>();
                        Console.WriteLine($"Добавляем {square.ToString()} в стэк");
                        stack.Push(square);
                        Console.WriteLine($"Добавляем {rectangle.ToString()} в стэк");
                        stack.Push(rectangle);
                        Console.WriteLine($"Добавляем {circle.ToString()} в стэк");
                        stack.Push(circle);

                        for (int i = 0; i < 3; ++i)
                        {
                            Console.WriteLine($"Производим операцию Pop() и удаляем {stack.Pop().ToString()} из стэка");
                        }
                        break;
                }

                Console.Write('\n');
                option = Menu();
            }
        }
    }
}
