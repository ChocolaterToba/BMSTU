using System;
using System.Text;
using System.Collections.Generic;
using FigureProject;

namespace MatrixProject
{
    public class Matrix<T>
    {
        /// <summary>
        /// Словарь для хранения значений
        /// </summary>
        Dictionary<string, T> _matrix = new Dictionary<string, T>();
        /// <summary>
        /// Количество элементов по горизонтали (максимальное количество столбцов)
        /// </summary>
        int maxX;
        /// <summary>
        /// Количество элементов по вертикали (максимальное количество строк)
        /// </summary>
        int maxY;
        /// <summary>
        /// Количество элементов по оси Z
        /// </summary>
        int maxZ;
        /// <summary>
        /// Реализация интерфейса для проверки пустого элемента
        /// </summary>
        IMatrixCheckEmpty<T> сheckEmpty;
        /// <summary>
        /// Конструктор
        /// </summary>
        public Matrix(int px, int py, int pz,
        IMatrixCheckEmpty<T> сheckEmptyParam)
        {
            this.maxX = px;
            this.maxY = py;
            this.maxZ = pz;
            this.сheckEmpty = сheckEmptyParam;
        }
        /// <summary>
        /// Индексатор для доступа к данных
        /// </summary>
        public T this[int x, int y, int z]
        {
            set
            {
                CheckBounds(x, y, z);
                string key = DictKey(x, y, z);
                this._matrix.Add(key, value);
            }
            get
            {
                CheckBounds(x, y, z);
                string key = DictKey(x, y, z);
                if (this._matrix.ContainsKey(key))
                {
                    return this._matrix[key];
                }
                else
                {
                    return this.сheckEmpty.getEmptyElement();
                }
            }
        }
        /// <summary>
        /// Проверка границ
        /// </summary>
        void CheckBounds(int x, int y, int z)
        {
            if (x < 0 || x >= this.maxX)
            {
                throw new ArgumentOutOfRangeException("x",
                "x=" + x + " выходит за границы");
            }
            if (y < 0 || y >= this.maxY)
            {
                throw new ArgumentOutOfRangeException("y",
                "y=" + y + " выходит за границы");
            }
            if (z < 0 || z >= this.maxZ)
            {
                throw new ArgumentOutOfRangeException("z",
                "z=" + z + " выходит за границы");
            }
        }
        /// <summary>
        /// Формирование ключа
        /// </summary>
        string DictKey(int x, int y, int z)
        {
            return x.ToString() + "_" + y.ToString() + "_" + z.ToString();
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            for (int k = 0; k < maxZ; ++k)
            {
                result.Append(k);
                result.Append("-й слой матрицы:\n");
                for (int i = 0; i < maxX; ++i)
                {
                    result.Append('[');
                    for (int j = 0; j < maxY; ++j)
                    {
                        if (!сheckEmpty.checkEmptyElement(this[i, j, k]))
                        {
                            result.Append(this[i, j, k].ToString());
                        }
                        else
                        {
                            result.Append("     -     ");
                        }
                        if (j < maxY - 1)
                        {
                            result.Append("; ");
                        }
                    }
                    result.Append("]\n");

                }
                result.Append('\n');
            }

            return result.ToString();
        }
    }

    /// <summary>
    /// Проверка пустого элемента матрицы
    /// </summary>
    public interface IMatrixCheckEmpty<T>
    {
        /// <summary>
        /// Возвращает пустой элемент
        /// </summary>
        T getEmptyElement();
        /// <summary>
        /// Проверка что элемент является пустым
        /// </summary>
        bool checkEmptyElement(T element);
    }

    public class FigureMatrixCheckEmpty : IMatrixCheckEmpty<Figure>
    {
        /// <summary>
        /// В качестве пустого элемента возвращается null
        /// </summary>
        public Figure getEmptyElement()
        {
            return null;
        }
        /// <summary>
        /// Проверка что переданный параметр равен null
        /// </summary>
        public bool checkEmptyElement(Figure element)
        {
            return element == null;
            //bool Result = false;
            //if (element == null)
            //{
            //   Result = true;
            //}
            //return Result;
        }
    }
}
