using System;

namespace ClassHierarchy
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Console.WriteLine("=== Тестування Завдання 4 (Уся ієрархія класів) ===\n");

            // Створюємо масив базового типу Person, який містить ВСІ похідні класи
            Person[] universityPeople = new Person[]
            {
                new Student("Олександр", 20, 3, "Інженерія ПЗ"),
                new Student("Марія", 19, 2, "Кібербезпека"),
                new Teacher("Іван Петрович", 45, "Алгоритми", 20),
                new DepartmentHead("Микола Іванович", 55, "Архітектура ПК", 30, "Кафедра ІТ")
            };

            // Викликаємо метод Show() для кожного об'єкта
            // Завдяки поліморфізму, для кожного об'єкта відпрацює його власна реалізація
            foreach (var person in universityPeople)
            {
                person.Show();
            }

            Console.WriteLine("\nНатисніть Enter для виходу...");
            Console.ReadLine();
        }
    }
}
