#include <iostream>
#include <vector>
#include <string>
#include <memory> // Додано для використання smart pointers

using namespace std;

// Базовий клас "Транспорт"
class Transport {
protected:
    string brand;
    int speed;
public:
    Transport(string b, int s) : brand(b), speed(s) {}
    virtual void showInfo() const {
        cout << "Транспорт: " << brand << ", швидкість: " << speed << " км/год" << endl;
    }
    virtual int getSpeed() const { return speed; }
    virtual ~Transport() {}
};

// Клас "Автомобіль", успадкований від "Транспорт"
class Car : public Transport {
protected:
    int doors;
public:
    Car(string b, int s, int d) : Transport(b, s), doors(d) {}
    void showInfo() const override {
        cout << "Автомобіль: " << brand << ", швидкість: " << speed << " км/год, двері: " << doors << endl;
    }
};

// Клас "Мотоцикл", успадкований від "Транспорт"
class Motorcycle : public Transport {
protected:
    bool hasSidecar;
public:
    Motorcycle(string b, int s, bool hs) : Transport(b, s), hasSidecar(hs) {}
    void showInfo() const override {
        cout << "Мотоцикл: " << brand << ", швидкість: " << speed << " км/год, коляска: " << (hasSidecar ? "так" : "ні") << endl;
    }
};

// Клас для демонстрації статичного поліморфізму (шаблони)
template<typename T>
class Garage {
private:
    vector<T> vehicles;
public:
    void addVehicle(const T& vehicle) { // Приймаємо за посиланням
        vehicles.push_back(vehicle);
    }

    void showAllVehicles() const {
        for (const auto& vehicle : vehicles) {
            vehicle.showInfo();
        }
    }
};

int main() {
    // Динамічний поліморфізм
    unique_ptr<Transport> car = make_unique<Car>("BMW", 240, 4);
    unique_ptr<Transport> motorcycle = make_unique<Motorcycle>("Harley Davidson", 180, true);

    car->showInfo();
    motorcycle->showInfo();

    // Статичний поліморфізм
    Garage<Car> carGarage;
    carGarage.addVehicle(Car("Audi", 220, 4));
    carGarage.addVehicle(Car("Tesla", 260, 4));

    cout << "\nАвтомобілі в гаражі:\n";
    carGarage.showAllVehicles();

    return 0;
}
