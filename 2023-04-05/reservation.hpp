#ifndef FMI_OOP_RESERVATION_HPP
#define FMI_OOP_RESERVATION_HPP

#include <iostream>

#include "date.hpp"


class Reservation {
private:
	Date start, end;

    friend std::ostream& operator <<(std::ostream &out, const Reservation& date);
    friend std::istream& operator >>(std::istream &in,  Reservation& date);

    void validate() {
		if (!(start <= end)) {
			throw std::invalid_argument("Start after end!");
		}
    }

public:
	// Метод дали две резервации се засичат във времето.
	bool overlaps(const Reservation& that) const {
		return (start <= that.end) && (that.start <= end);
	}
};

std::ostream& operator <<(std::ostream &out, const Reservation& r) {
	out << r.start << ' ' << r.end;

	return out;
}

std::istream& operator >>(std::istream &in,  Reservation& r) {
	in >> r.start >> r.end;
	r.validate();

	return in;
}

#endif /* FMI_OOP_RESERVATION_HPP */
