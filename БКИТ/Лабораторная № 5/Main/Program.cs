using System;
using static Лабораторная___5.Distance;

namespace Main
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Input 2 string for comparison, each from new line");
            string first = Console.ReadLine();
            string second = Console.ReadLine();
            Console.WriteLine("Resulting Levensthtein distance: {0}", Levenshtain(first, second));
            Console.WriteLine("Resulting Damerau-Levensthtein distance: {0}", DamerauLevenshtain(first, second));
        }
    }
}
