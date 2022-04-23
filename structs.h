#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <set>
#include <memory>

// Интерфейс "Геометрическая фигура".
class IGeoFig {
public:
// Площадь.
    virtual double square() = 0;

// Периметр.
    virtual double perimeter() = 0;
};

// Вектор
class CVector2D {
public:
    double x, y;
};


// Интерфейс "Физический объект".
class IPhysObject {
public:
// Масса, кг.
    virtual double mass() const = 0;

// Координаты центра масс, м.
    virtual CVector2D position() = 0;

// Сравнение по массе.
    virtual bool operator==(const IPhysObject &ob) const = 0;

// Сравнение по массе.
    virtual bool operator<(const IPhysObject &ob) const = 0;
};

// Интерфейс "Отображаемый"
class IPrintable {
public:
// Отобразить на экране
// (выводить в текстовом виде параметры фигуры).
    virtual void draw() = 0;
};

// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
// Задать параметры объекта с помощью диалога с пользователем.
    virtual void initFromDialog() = 0;
};

// Интерфейс "Класс"
class BaseCObject {
public:
// Имя класса (типа данных).
    virtual const char *classname() = 0;

// Размер занимаемой памяти.
    virtual unsigned int size() = 0;
};

class RightTriangle: IGeoFig, public IPhysObject, IPrintable, IDialogInitiable, public BaseCObject{
private:
    CVector2D points[3]{};
    CVector2D center{};
    double mass_value{};
    constexpr static const auto name = "RightTriangle" ;


public:
    double mass() const override {
        return mass_value;
    }

    CVector2D position() override{
        return center;
    }
    bool operator== (const IPhysObject &ob) const override{
        return mass() == ob.mass();
    }

    bool operator< (const IPhysObject &ob) const override{
        return mass() < ob.mass();
    }

    void draw() override{
        std::cout << name;
        std::cout << "Cords:\n" <<
        points[0].x << ", " << points[0].y << '\n' <<
        points[1].x << ", " << points[1].y << '\n' <<
        points[2].x << ", " << points[2].y << '\n' <<
        "Center:\n" << center.x << ", " << center.y <<
        "\nMass:\n" << mass();
    }

    double side(){
        return std::sqrt((points[1].x - points[0].x) * (points[1].x - points[0].x) +
                         (points[1].y - points[0].y) * (points[1].y - points[0].y));
    }

    double square() override{
        double a = side();
        return (a * a * sqrt(3)) / 4;
    }

    double perimeter() override{
        return 3 * side();
    }

    const char *classname() override{
        return name;
    }
    unsigned int size() override{
        return sizeof (*this);
    }

    RightTriangle(CVector2D p1, CVector2D p2,  CVector2D p3, double mass_): mass_value(mass_) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;

        center.x = (points[0].x + points[1].x + points[2].x) / 3;
        center.y = (points[0].y + points[1].y + points[2].y) / 3;

    };

    RightTriangle(const std::string& input){
        points[0] = {0 , 0};
        points[1] = {0 , 0};
        points[2] = {0 , 0};
        mass_value = 10;

    }

    void initFromDialog() override{
        std::cout << "Enter points" << '\n';

        std::cin >>
        points[0].x >> points[0].y >>
        points[1].x >> points[1].y >>
        points[2].x >> points[2].y;

        center.x = (points[0].x + points[1].x + points[2].x) / 3;
        center.y = (points[0].y + points[1].y + points[2].y) / 3;
        std::cout << "Enter mass" << '\n';
        std::cin >> mass_value;
    }
};

class Hexagon: IGeoFig, IPhysObject, IPrintable, IDialogInitiable, public BaseCObject{
private:
    CVector2D points[6];
    CVector2D center;
    double mass_value;
    constexpr static const auto name = "Hexagon" ;


    void initFromDialog() override{
        std::cout << "Enter points consistently clockwise" << '\n';

        std::cin >>
                 points[0].x >> points[0].y >>
                 points[1].x >> points[1].y >>
                 points[2].x >> points[2].y >>
                 points[3].x >> points[3].y >>
                 points[4].x >> points[4].y >>
                 points[5].x >> points[5].y;

        center.x = (points[0].x + points[1].x + points[2].x + points[3].x + points[4].x + points[5].x) / 6;
        center.y = (points[0].y + points[1].y + points[2].y + points[3].y + points[4].y + points[5].y) / 6;
        std::cout << "Enter mass" << '\n';
        std::cin >> mass_value;
    }
public:
    double mass() const override {
        return mass_value;
    }

    CVector2D position() override{
        return center;
    }
    bool operator== (const IPhysObject &ob) const override{
        return mass() == ob.mass();
    }

    bool operator< (const IPhysObject &ob) const override{
        return mass() < ob.mass();
    }

    void draw() override{
        std::cout << name;
        std::cout << "Cords:\n" <<
                  points[0].x << ", " << points[0].y << '\n' <<
                  points[1].x << ", " << points[1].y << '\n' <<
                  points[2].x << ", " << points[2].y << '\n' <<
                  "Center:\n" << center.x << ", " << center.y <<
                  "\nMass:\n" << mass();
    }

    double square() override{
        return RightTriangle(points[0], points[1], points[5], 0).square() +
               RightTriangle(points[5], points[1], points[4], 0).square() +
                RightTriangle(points[4], points[1], points[3], 0).square() +
                RightTriangle(points[3], points[1], points[2], 0).square();
    }

    double perimeter() override{
        double p = 0;

        for (int i = 0; i < 6; ++i){
            p += std::sqrt((points[i + 1].x - points[i].x) * (points[i + 1].x - points[i].x) +
                           (points[i + 1].y - points[i].y) * (points[i + 1].y - points[i].y));
        }

        return p;
    }

    const char *classname() override{
        return name;
    }
    unsigned int size() override{
        return sizeof (*this);
    }

    Hexagon(CVector2D p1, CVector2D p2,  CVector2D p3, CVector2D p4, CVector2D p5,  CVector2D p6, double mass_);

    Hexagon(const std::string& input){
        initFromDialog();
    }
};

struct CmpMass{
    bool operator()(const std::unique_ptr<BaseCObject>& a, const std::unique_ptr<BaseCObject>& b) const{

        return dynamic_cast<IPhysObject*>(&*a)->mass() < dynamic_cast<IPhysObject*>(&*b)->mass();
    }
};

class Manager{
    std::set<std::unique_ptr<BaseCObject>, CmpMass> shapes;

public:
    void run(){
        int input;

        do{
            std::cout << "Enter command ID:\n"
                         "Add Right Triangle - 1\n"
                         "Add Hexagon - 2\n"
                         "Total area - 3\n"
                         "Total perimeter - 4\n"
                         "System mass center - 5\n"
                         "Total used memory - 6\n"
                         "exit - 0\n";

            std::cin >> input;

            switch (input) {
                case 1:{
                    std::cout << "Enter cords and mass of Right Triangle";
                    //auto b = RightTriangle("CONSOLE");
                    //b.initFromDialog();
                    shapes.insert(std::make_unique<RightTriangle>("CONSOLE"));
                    break;
                }




                case 3:{
                    double t_area = 0;

                    for (auto& i : shapes){
                        t_area += dynamic_cast<IPhysObject*>(&*i)->mass();
                    }

                    std::cout << "Total area is:\n" << t_area;
                }

            }
        } while (input != 0);
    }
};
