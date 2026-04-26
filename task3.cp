using System;
using System.Collections.Generic;

namespace GoodsHierarchy
{
    // 1. Абстрактний базовий клас "Товар"
    abstract class Item
    {
        public string Name { get; set; }
        public decimal Price { get; set; }

        public Item(string name, decimal price)
        {
            Name = name;
            Price = price;
        }

        // Абстрактні методи для виводу інформації та перевірки на простроченість
        public abstract void ShowInfo();
        public abstract bool IsExpired();
    }

    // 2. Похідний клас "Продукт"
    class Product : Item
    {
        public DateTime ProductionDate { get; set; }
        public int ExpirationDays { get; set; } // Строк придатності у днях

        public Product(string name, decimal price, DateTime productionDate, int expirationDays) 
            : base(name, price)
        {
            ProductionDate = productionDate;
            ExpirationDays = expirationDays;
        }

        public override void ShowInfo()
        {
            Console.WriteLine($"[Продукт] {Name,-15} | Ціна: {Price,5} грн | Вироблено: {ProductionDate:dd.MM.yyyy} | Придатний (днів): {ExpirationDays}");
        }

        public override bool IsExpired()
        {
            // Якщо поточна дата більша за (Дата виробництва + дні придатності)
            return DateTime.Now > ProductionDate.AddDays(ExpirationDays);
        }
    }

    // 3. Похідний клас "Партія"
    class Batch : Item
    {
        public int Quantity { get; set; }
        public DateTime ProductionDate { get; set; }
        public int ExpirationDays { get; set; }

        public Batch(string name, decimal price, int quantity, DateTime productionDate, int expirationDays) 
            : base(name, price)
        {
            Quantity = quantity;
            ProductionDate = productionDate;
            ExpirationDays = expirationDays;
        }

        public override void ShowInfo()
        {
            Console.WriteLine($"[Партія]  {Name,-15} | Ціна за шт: {Price,5} грн | К-сть: {Quantity} шт | Вироблено: {ProductionDate:dd.MM.yyyy} | Придатний (днів): {ExpirationDays}");
        }

        public override bool IsExpired()
        {
            return DateTime.Now > ProductionDate.AddDays(ExpirationDays);
        }
    }

    // 4. Похідний клас "Комплект"
    class ProductSet : Item
    {
        public List<Product> Products { get; set; }

        public ProductSet(string name, decimal price, List<Product> products) 
            : base(name, price)
        {
            Products = products;
        }

        public override void ShowInfo()
        {
            Console.WriteLine($"[Комплект]{Name,-15} | Загальна ціна: {Price} грн | Складається з:");
            foreach (var product in Products)
            {
                Console.WriteLine($"          - {product.Name} (Вироблено: {product.ProductionDate:dd.MM.yyyy})");
            }
        }

        public override bool IsExpired()
        {
            // Комплект прострочений, якщо прострочений хоча б один продукт у ньому
            foreach (var product in Products)
            {
                if (product.IsExpired())
                {
                    return true;
                }
            }
            return false;
        }
    }

    class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            // Створюємо продукти для використання окремо і в комплектах
            Product milkGood = new Product("Молоко", 35.50m, DateTime.Now.AddDays(-2), 7);       // Свіже
            Product milkExpired = new Product("Молоко старе", 30.00m, DateTime.Now.AddDays(-10), 7); // Прострочене
            Product cookies = new Product("Печиво", 45.00m, DateTime.Now.AddDays(-30), 180);     // Свіже

            // Створюємо масив товарів (базу)
            Item[] inventory = new Item[]
            {
                milkGood,
                cookies,
                new Batch("Йогурти (упаковка)", 25.00m, 20, DateTime.Now.AddDays(-15), 14),      // Прострочена партія
                new Batch("Вода мінеральна", 15.00m, 100, DateTime.Now.AddDays(-100), 365),      // Свіжа партія
                new ProductSet("Новорічний", 250.00m, new List<Product> { cookies, milkGood }),  // Свіжий комплект
                new ProductSet("Сніданок", 150.00m, new List<Product> { cookies, milkExpired })  // Прострочений комплект (через молоко)
            };

            // 1. Виведення повної інформації з бази
            Console.WriteLine("=== ПОВНА ІНФОРМАЦІЯ ПРО ТОВАРИ НА СКЛАДІ ===");
            foreach (var item in inventory)
            {
                item.ShowInfo();
            }

            // 2. Пошук простроченого товару на момент поточної дати
            Console.WriteLine("\n=== УВАГА! ЗНАЙДЕНО ПРОСТРОЧЕНІ ТОВАРИ ===");
            bool hasExpired = false;

            foreach (var item in inventory)
            {
                if (item.IsExpired())
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    item.ShowInfo();
                    Console.ResetColor();
                    hasExpired = true;
                }
            }

            if (!hasExpired)
            {
                Console.WriteLine("Прострочених товарів не виявлено.");
            }

            Console.ReadLine();
        }
    }
}
