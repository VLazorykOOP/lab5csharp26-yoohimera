using System;

namespace ClassHierarchy
{
    // 1. Абстрактний базовий клас "Персона"
    public abstract class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }

        protected Person(string name, int age)
        {
            Name = name;
            Age = age;
        }

        public abstract void Show();
    }

    // 2. Клас "Викладач"
    public class Teacher : Person
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
            Console.WriteLine($"[Викладач]  Ім'я: {Name,-15} | Вік: {Age} | Стаж: {Experience} р. | Предмет: {Subject}");
        }
    }

    // 3. Клас "Завідувач кафедри"
    public class DepartmentHead : Teacher
    {
        public string DepartmentName { get; set; }

        public DepartmentHead(string name, int age, string subject, int experience, string departmentName) 
            : base(name, age, subject, experience)
        {
            DepartmentName = departmentName;
        }

        public override void Show()
        {
            Console.WriteLine($"[Зав. каф.] Ім'я: {Name,-15} | Вік: {Age} | Стаж: {Experience} р. | Кафедра: {DepartmentName}");
        }
    }

    // 4. КЛАС "СТУДЕНТ" - Частина 1 (Оголошення)
    // sealed - забороняє успадкування від Студента
    // partial - дозволяє розділити клас
    public sealed partial class Student : Person
    {
        public int Course { get; set; }
        public string Major { get; set; } = string.Empty; // Уникнення попередження CS8618

        // Оголошення часткового методу
        partial void InitializeStudentData(int course, string major);
    }
}
