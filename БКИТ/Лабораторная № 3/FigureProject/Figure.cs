using System;
using static System.Math;

namespace FigureProject
{
    public abstract class Figure : IPrint, IComparable
    {
        protected string Type { get; set; }

        public abstract double Area();

        public override string ToString()
        {
            return this.Type + " площадью " + this.Area();
        }

        public void Print()
        {
            Console.WriteLine(this.ToString());
        }

        public int CompareTo(object other)
        {
            if (other == null)
            {
                return 1;
            }
            return this.Area().CompareTo(((Figure)other).Area());
        }
    }

    interface IPrint
    {
        void Print();
    }

    public class Rectangle : Figure
    {
        protected double _Length;
        public virtual double Length
        {
            get { return _Length; }
            set
            {
                if (value >= 0)
                {
                    _Length = value;
                }
                else
                {
                    throw new Exception("Длина не может быть отрицательной");
                }
            }
        }
        protected double _Width;
        public virtual double Width
        {
            get { return _Width; }
            set
            {
                if (value >= 0)
                {
                    _Width = value;
                }
                else
                {
                    throw new Exception("Ширина не может быть отрицательной");
                }
            }
        }

        public Rectangle(double Length = 0, double Width = 0)
        {
            this.Length = Length;
            this.Width = Width;
        }

        public override double Area()
        {
            return this.Length * this.Width;
        }

        public override string ToString()
        {
            return $"Прямоугольник со сторонами {this.Length} и {this.Width} и площадью {this.Area():G3}";
        }
    }

    public class Square : Rectangle
    {
        public Square(double side = 0) : base(side, side) {; }

        public override double Length
        {
            get { return _Length; }
            set
            {
                if (value >= 0)
                {
                    _Width = value;
                    _Length = value;
                }
                else
                {
                    throw new Exception("Сторона не может быть отрицательной");
                }
            }
        }

        public override double Width
        {
            get { return _Length; }
            set
            {
                if (value >= 0)
                {
                    _Width = value;
                    _Length = value;
                }
                else
                {
                    throw new Exception("Сторона не может быть отрицательной");
                }
            }
        }

        public override string ToString()
        {
            return $"Квадрат со стороной {this.Length} и площадью {this.Area():G3}";
        }
    }

    public class Circle : Figure
    {
        private double _Radius;
        public double Radius
        {
            get { return _Radius; }
            set
            {
                if (value >= 0)
                {
                    _Radius = value;
                }
                else
                {
                    throw new Exception("Радиус не может быть отрицательным");
                }
            }
        }

        public Circle(double Radius = 0)
        {
            this.Radius = Radius;
        }

        public override double Area()
        {
            return PI * Pow(Radius, 2);
        }

        public override string ToString()
        {
            return $"Круг с радиусом {this.Radius} и площадью {this.Area():G3}";
        }
    }
}
