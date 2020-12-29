using System;

namespace Лабораторная___5
{
    public class Distance
    {
        static public int Levenshtain(string first, string second)
        {
            int[,] d = new int[first.Length + 1, second.Length + 1];
            
            for (int i = 1; i <= first.Length; ++i)
            {
                d[i, 0] = i;
            }

            for (int j = 1; j <= second.Length; ++j)
            {
                d[0, j] = j;
            }

            for (int j = 1; j <= second.Length; ++j)
            {
                for (int i = 1; i <= first.Length; ++i)
                {
                    int substitutionCost = 0;
                    if (first[i - 1] != second[j - 1])
                    {
                        substitutionCost = 1;
                    }

                    d[i, j] = Math.Min(Math.Min(d[i - 1, j] + 1,  // deletion
                                                d[i, j - 1] + 1),  // insertion
                                       d[i - 1, j - 1] + substitutionCost);  // substitution
                }
            }

            return d[first.Length, second.Length];
        }

        static public int DamerauLevenshtain(string first, string second)
        {
            int[] alphabet = new int[255];
            int[,] d = new int[first.Length + 2, second.Length + 2];

            int maxDistance = first.Length + second.Length;
            d[0, 0] = maxDistance;

            for (int i = 0; i <= first.Length; ++i)
            {
                d[i + 1, 0] = maxDistance;
                d[i + 1, 1] = i;
            }

            for (int j = 0; j <= second.Length; ++j)
            {
                d[0, j + 1] = maxDistance;
                d[1, j + 1] = j;
            }

            for (int i = 1; i <= first.Length; ++i)
            {
                int db = 0;
                for (int j = 1; j <= second.Length; ++j)
                {
                    int k = alphabet[second[j - 1] - 0];  // -0 converts char to int
                    int l = db;

                    int substitutionCost;
                    if (first[i - 1] == second[j - 1])
                    {
                        substitutionCost = 0;
                        db = j;
                    }
                    else
                    {
                        substitutionCost = 1;
                    }

                    d[i + 1, j + 1] = Math.Min(Math.Min(d[i, j + 1] + 1,  // deletion
                                                        d[i + 1, j] + 1),  // insertion
                                               Math.Min(d[i, j] + substitutionCost,  // substitution
                                                        d[k, l] + (i - k - 1) + 1 + (j - l - 1)));  // transposition
                }

                alphabet[first[i - 1] - 0] = i;
            }

            return d[first.Length, second.Length];
        }
    }
}
