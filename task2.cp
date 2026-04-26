using System;

namespace ClassHierarchyTask2
{
    // 1. Абстрактний базовий клас "Персона"
    abstract class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }

        // Конструктор 1: За замовчуванням
        protected Person()
        {
            Name = "Невідомо";
            Age = 0;
            Console.WriteLine("-> Виклик конструктора Person (за замовчуванням)");
        }

        // Конструктор 2: Параметризований
        protected Person(string name, int age)
        {
            Name = name;
            Age = age;
            Console.WriteLine($"-> Виклик конструктора Person (параметризований: {Name})");
        }

        // Конструктор 3: Частковий (тільки ім'я)
        protected Person(string name) : this(name, 18) 
        {
            Console.WriteLine($"-> Виклик конструктора Person (частковий: {Name})");
        }

        // Деструктор
        ~Person()
        {
            Console.WriteLine($"<- Виклик деструктора Person для {Name}");
        }

        public abstract void Show();
    }

    // 2. Клас "Студент"
    class Student : Person
    {
        public string Major { get; set; }

        // Конструктор 1
        public Student() : base()
        {
            Major = "Не визначено";
            Console.WriteLine("   -> Виклик конструктора Student (за замовчуванням)");
        }

        // Конструктор 2
        public Student(string name, int age, string major) : base(name, age)
        {
            Major = major;
            Console.WriteLine("   -> Виклик конструктора Student (параметризований)");
        }

        // Конструктор 3
        public Student(string name, string major) : base(name)
        {
            Major = major;
            Console.WriteLine("   -> Виклик конструктора Student (ім'я + спеціальність)");
        }

        ~Student()
        {
            Console.WriteLine($"   <- Виклик деструктора Student для {Name}");
        }

        public override void Show() => Console.WriteLine($"[Студент] {Name}, Вік: {Age}, Спец: {Major}");
    }

    // 3. Клас "Викладач"
    class Teacher : Person
    {
        public string Subject { get; set; }

        // Конструктор 1
        public Teacher() : base()
        {
            Subject = "Загальний предмет";
            Console.WriteLine("   -> Виклик конструктора Teacher (за замовчуванням)");
        }

        // Конструктор 2
        public Teacher(string name, int age, string subject) : base(name, age)
        {
            Subject = subject;
            Console.WriteLine("   -> Виклик конструктора Teacher (параметризований)");
        }

        // Конструктор 3
        public Teacher(string name, string subject) : base(name)
        {
            Subject = subject;
            Console.WriteLine("   -> Виклик конструктора Teacher (ім'я + предмет)");
        }

        ~Teacher()
        {
            Console.WriteLine($"   <- Виклик деструктора Teacher для {Name}");
        }

        public override void Show() => Console.WriteLine($"[Викладач] {Name}, Вік: {Age}, Предмет: {Subject}");
    }

    // 4. Клас "Завідувач кафедри"
    class DepartmentHead : Teacher
    {
        public string Department { get; set; }

        // Конструктор 1
        public DepartmentHead() : base()
        {
            Department = "Загальна кафедра";
            Console.WriteLine("      -> Виклик конструктора DepartmentHead (за замовчуванням)");
        }

        // Конструктор 2
        public DepartmentHead(string name, int age, string subject, string dept) : base(name, age, subject)
        {
            Department = dept;
            Console.WriteLine("      -> Виклик конструктора DepartmentHead (параметризований)");
        }

        // Конструктор 3
        public DepartmentHead(string name, string dept) : base(name, "Менеджмент")
        {
            Department = dept;
            Console.WriteLine("      -> Виклик конструктора DepartmentHead (ім'я + кафедра)");
        }

        ~DepartmentHead()
        {
            Console.WriteLine($"      <- Виклик деструктора DepartmentHead для {Name}");
        }

        public override void Show() => Console.WriteLine($"[Зав. каф.] {Name}, Кафедра: {Department}");
    }

    class Program
    {
        // Метод для створення об'єктів у окремій області видимості
        static void CreateObjects()
        {
            Console.WriteLine("--- Створення об'єктів та виклик конструкторів ---\n");

            Person[] array = new Person[3];

            Console.WriteLine("Створення Студента (Конструктор 2):");
            array[0] = new Student("Олексій", 19, "Кібербезпека");
            
            Console.WriteLine("\nСтворення Викладача (Конструктор 3):");
            array[1] = new Teacher("Дмитро", "Математика");

            Console.WriteLine("\nСтворення Завідувача (Конструктор 1):");
            array[2] = new DepartmentHead();

            Console.WriteLine("\n--- Список створених об'єктів ---");
            foreach (var p in array) p.Show();
            
            Console.WriteLine("\n--- Область видимості завершується, об'єкти готові до видалення ---");
        }

        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            CreateObjects();

            // Явний виклик збирача сміття для демонстрації деструкторів
            Console.WriteLine("\nОчікування запуску Garbage Collector...");
            GC.Collect(); 
            GC.WaitForPendingFinalizers(); 

            Console.WriteLine("\nПрограма завершена. Натисніть Enter.");
            Console.ReadLine();
        }
    }
}
