#include <iostream>
#include <cstring>
#include <limits>
#include <clocale>

struct Dish {
    char* name;
    int portionNumber;
    double price;

    double totalPrice() {
        return portionNumber * price;
    }
};

void sortingDishes(Dish** dishes) {
    int len = 0;
    while (*(dishes + len) != nullptr) {
        len++;
    }

    for (int i = 0; i < len - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < len; j++) {
            if (strcmp((*(dishes + minIndex))->name, (*(dishes + j))->name) > 0) {
                minIndex = j;
            }
        }

        Dish* temp = *(dishes + i);
        *(dishes + i) = *(dishes + minIndex);
        *(dishes + minIndex) = temp;
    }
}

int main() {
    setlocale(LC_ALL, "");

    int n;
    std::cout << "Введите количество заказанных блюд: ";
    while (!(std::cin >> n) || n < 0) {
        std::cout << "Неправильный ввод количества заказанных блюд" << std::endl;
        std::cout << "Введите количество заказанных блюд: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double totalPrice = 0;

    Dish** dishes = new Dish*[n + 1]{};
    Dish** ptr = dishes;

    *(ptr + n) = nullptr;

    for (int i = 1; i <= n; i++) {
        Dish* dish = new Dish();
        char str[100];
        int number;
        double price;

        std::cout << "Введите название блюда " << i << ": ";
        std::cin.ignore();
        std::cin.getline(str, 100);
        std::cout << "Введите количество порций блюда " << i << ": ";
        while (!(std::cin >> number) || number < 0) {
            std::cout << "Неправильный ввод количества порций блюда";
            std::cout << "Введите количество порций блюда " << i << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Введите стоимость за порцию блюда " << i << ": ";  
        while (!(std::cin >> price) || price < 0) {
            std::cout << "Неправильный ввод стоимости за порцию блюда";
            std::cout << "Введите стоимость за порцию блюда " << i << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        char* name = new char[strlen(str) + 1];
        strcpy(name, str);
        dish->name = name;
        dish->portionNumber = number;
        dish->price = price;
        totalPrice += dish->totalPrice();
        
        *ptr = dish;

        std::cout << "Общая стоимость заказа " << i << ": " << dish->totalPrice() << std::endl;

        ptr++;
    }

    sortingDishes(dishes);

    ptr = dishes;
    
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << ". ";
        std::cout << (*(ptr + i))->name << " - ";
        std::cout << "Количество: " << (*(ptr + i))->portionNumber << ", ";
        std::cout << "Стоимость за порцию: " << (*(ptr + i))->price;
        std::cout << std::endl;
    }

    std::cout << "Общая сумма всех заказов: " << totalPrice << std::endl;

    while (*ptr != nullptr) {
        delete[] *ptr;
        ptr++;
    }
    delete[] dishes;

    return 0;
}