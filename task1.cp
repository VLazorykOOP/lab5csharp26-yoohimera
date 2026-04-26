using System;

namespace ClassHierarchy
{
    // 1. Абстрактний базовий клас "Персона"
    abstract class Person
    {
        // Поля базового класу
        public string Name { get; set; }
        public int Age { get; set; }

        public Person(string name, int age)
        {
            Name = name;
            Age = age;
        }

        // Абстрактний метод, який обов'язково мають реалізувати похідні класи
        public abstract void Show();
    }

    // 2. Похідний клас "Студент"
    class Student : Person
    {
        public int Course { get; set; }
        public string Major { get; set; }

        public Student(string name, int age, int course, string major) : base(name, age)
        {
            Course = course;
            Major = major;
        }

        public override void Show()
        {
            Console.WriteLine($"[Студент] Ім'я: {Name, -15} | Вік: {Age} | Курс: {Course} | Спеціальність: {Major}");
        }
    }

    // 3. Похідний клас "Викладач"
    class Teacher : Person
    {
        public string Subject { get; set; }
        public int Experience { get; set; }

        public Teacher(string name, int age, string subject, int experience) : base(name, age)
        {
            Subject = subject;
            Experience = experience;
        }

        public override void Show()
        {
            Console.WriteLine($"[Викладач] Ім'я: {Name, -14} | Вік: {Age} | Стаж: {Experience} р. | Дисципліна: {Subject}");
        }
    }

    // 4. Похідний клас "Завідувач кафедри" (успадковує Викладача)
    class DepartmentHead : Teacher
    {
        public string DepartmentName { get; set; }

        public DepartmentHead(string name, int age, string subject, int experience, string departmentName) 
            : base(name, age, subject, experience)
        {
            DepartmentName = departmentName;
        }

        public override void Show()
        {
            Console.WriteLine($"[Зав. каф.] Ім'я: {Name, -13} | Вік: {Age} | Стаж: {Experience} р. | Дисципліна: {Subject} | Кафедра: {DepartmentName}");
        }
    }

    class Program
    {
        static void Main()
        {
            // Для коректного відображення української мови в консолі
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            // Створення масиву об'єктів з представниками кожного типу
            Person[] people = new Person[]
            {
                new Student("Олександр", 19, 2, "Комп'ютерні науки"),
                new Student("Марія", 20, 3, "Інженерія ПЗ"),
                new Teacher("Іван Петрович", 45, "Алгоритми", 20),
                new Teacher("Олена Василівна", 38, "Бази даних", 12),
                new DepartmentHead("Микола Іванович", 55, "Архітектура ПК", 30, "Кафедра ІТ"),
                new DepartmentHead("Анна Сергіївна", 50, "Кібербезпека", 25, "Кафедра БІ")
            };

            Console.WriteLine("=== Дані ДО сортування ===");
            foreach (var person in people)
            {
                person.Show();
            }

            // Впорядкування масиву за полем базового класу (за віком - Age)
            // Використовуємо метод Array.Sort з лямбда-виразом для порівняння
            Array.Sort(people, (p1, p2) => p1.Age.CompareTo(p2.Age));

            Console.WriteLine("\n=== Дані ПІСЛЯ сортування (за зростанням віку) ===");
            
            // Виклик методу Show() для всіх елементів масиву в циклі
            foreach (var person in people)
            {
                person.Show();
            }
            
            Console.ReadLine();
        }
    }
}
