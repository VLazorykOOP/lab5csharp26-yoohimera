using System;

namespace ClassHierarchy
{
    // КЛАС "СТУДЕНТ" - Частина 2 (Реалізація)
    public sealed partial class Student
    {
        // Конструктор
        public Student(string name, int age, int course, string major) : base(name, age)
        {
            // Виклик часткового методу
            InitializeStudentData(course, major);
        }

        // Визначення (реалізація) часткового методу
        partial void InitializeStudentData(int course, string major)
        {
            Course = course;
            Major = major;
        }

        // Реалізація абстрактного методу базового класу
        public override void Show()
        {
            Console.WriteLine($"[Студент]   Ім'я: {Name,-15} | Вік: {Age} | Курс: {Course} | Спец: {Major}");
        }
    }
}
