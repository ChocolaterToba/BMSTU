using System;
using System.Collections.Generic;
//using static System.Math;

namespace Лабораторная___1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Aglicheev Mikhail Sergeevich, IU5-31B");
            Console.WriteLine("Quadratic equation: A * x ^ 4 + B * x ^ 2 + C = 0");
 
            string coefficient;  //  Temporary variable for storing input.
            double[] coefficients = new double[3];

            switch(args.Length)
            {
                case 0:
                    string[] coefficientsNames = new string[] { "A", "B", "C" };
                    for (int i = 0; i < 3; ++i)
                    {
                        while (true)
                        {
                            Console.Write($"Please input coefficient {coefficientsNames[i]}:");
                            coefficient = Console.ReadLine();
                            if (double.TryParse(coefficient, out coefficients[i]))
                            {
                                if (i != 0 || coefficients[i] != 0)
                                {
                                    break;
                                }
                                else
                                {
                                    Console.WriteLine("First coefficient ('A') cannot be 0. Please try again.");
                                }
                            }
                            else
                            {
                                Console.WriteLine("That's not a number. Please try again.");
                            }
                        }
                    }
                    break;
                case 3:
                    for (int i = 0; i < 3; ++i)
                    {
                        if (double.TryParse(args[i], out coefficients[i]))
                        {
                            if (i == 0 && coefficients[i] == 0)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("First argument cannot be a 0");
                                Console.ForegroundColor = ConsoleColor.Black;
                                Console.ReadKey();
                                return;
                            }
                        }
                        else
                        {
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine("One of arguments is not a number");
                            Console.ForegroundColor = ConsoleColor.Black;
                            Console.ReadKey();
                            return;
                        }
                    }
                    break;
                default:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"This function needs 3 arguments. You passed {args.Length}.");
                    Console.ForegroundColor = ConsoleColor.Black;
                    Console.ReadKey();
                    return;
            }
            
            var roots = new HashSet<double>();
            double innerExpression = Math.Pow(coefficients[1], 2) - 4 * coefficients[0] * coefficients[2];
            if (innerExpression >= 0)
            {
                double firstOuterExpression = (-coefficients[1] + Math.Sqrt(innerExpression)) / 2 / coefficients[0];
                if (firstOuterExpression >= 0)
                {
                    roots.Add(Math.Sqrt(firstOuterExpression));
                    roots.Add(-Math.Sqrt(firstOuterExpression));
                    double secondOuterExpression = (-coefficients[1] - Math.Sqrt(innerExpression)) / 2 / coefficients[0];
                    if (secondOuterExpression >= 0)
                    {
                        roots.Add(Math.Sqrt(secondOuterExpression));
                        roots.Add(-Math.Sqrt(secondOuterExpression));
                    }
                }
            }
            if (roots.Count == 0)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("No roots have been found");
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine($"{roots.Count} Root{(roots.Count > 1 ? "s" : "")} found:");
                foreach (double root in roots) {
                    Console.Write($"{root} ");
                }
                Console.WriteLine();
            }
            Console.ForegroundColor = ConsoleColor.Black;
            Console.ReadKey();
        }
    }
}
