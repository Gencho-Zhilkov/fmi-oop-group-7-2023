#ifndef FMI_OOP_DATE_H
#define FMI_OOP_DATE_H

#include <iostream>

/* TODO:
Опитайте се да добавите конструктор, методи за валидация,
методи за достъп до полетата на класа (getters), както и
да имплементирате останалите оператори за сравнение
*/
class Date {
private:
    int day, month, year;

    friend std::ostream& operator <<(std::ostream &out, const Date& date);
    friend std::istream& operator >>(std::istream &in,  Date& date);

    long long toLong() const {
        return 10000 * year + 100 * month + day;
    }
public:

    bool operator <=(const Date& that) const {
        return toLong() <= that.toLong();
    }
};

std::ostream& operator <<(std::ostream &out, const Date& date) {
    out << date.day << '/' << date.month << '/' << date.year;
    return out;
}

std::istream& operator >>(std::istream &in,  Date& date) {
    in >> date.day;
    in.ignore(1, '/');
    in >> date.month;
    in.ignore(1, '/');
    in >> date.year;

    return in;
}

#endif /* FMI_OOP_DATE_H */
