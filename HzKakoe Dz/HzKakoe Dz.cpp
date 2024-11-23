#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

struct Product {
    std::string name;
    int quantity;
    double price;
};

void displayMenu() {
    std::cout << "Выберите файл для работы:\n";
    std::cout << "1) products1.txt\n";
    std::cout << "2) products2.txt\n";
    std::cout << "3) products3.txt\n";
    std::cout << "0) Выход\n";
}

void writeToFile(const std::string& filename, const std::vector<Product>& products) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    for (const auto& product : products) {
        file << product.name << "\n" << product.quantity << "\n" << product.price << "\n";
    }
    file.close();
}

std::vector<Product> readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Product> products;
    Product product;

    while (std::getline(file, product.name) && file >> product.quantity >> product.price) {
        file.ignore(); 
        products.push_back(product);
    }
    file.close();
    return products;
}

void displayProducts(const std::vector<Product>& products) {
    std::cout << std::setw(5) << "Id" << std::setw(20) << "Название" << std::setw(10) << "Кол-во" << std::setw(10) << "Цена" << std::endl;
    for (size_t i = 0; i < products.size(); ++i) {
        std::cout << std::setw(5) << (i + 1) << std::setw(20) << products[i].name << std::setw(10) << products[i].quantity << std::setw(10) << products[i].price << std::endl;
    }
}

void addProducts(std::vector<Product>& products) {
    for (int i = 0; i < 3; ++i) {
        Product product;
        std::cout << "Введите название товара: ";
        std::getline(std::cin, product.name);
        std::cout << "Введите количество: ";
        std::cin >> product.quantity;
        std::cout << "Введите цену: ";
        std::cin >> product.price;
        std::cin.ignore(); 
        products.push_back(product);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    std::vector<Product> products;
    std::string filename;
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
        case 1:
            filename = "products1.txt";
            break;
        case 2:
            filename = "products2.txt";
            break;
        case 3:
            filename = "products3.txt";
            break;
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            continue;
        }

        products = readFromFile(filename);
        if (!products.empty()) {
            std::cout << "Файл уже содержит данные. Выберите действие:\n";
            std::cout << "1) Дополнить существующие данные\n";
            std::cout << "2) Стереть и заполнить заново\n";
            int action;
            std::cin >> action;
            std::cin.ignore();

            if (action == 2) {
                products.clear();
            }
        }

        addProducts(products);
        writeToFile(filename, products);
        displayProducts(products);
    }

    return 0;
}
