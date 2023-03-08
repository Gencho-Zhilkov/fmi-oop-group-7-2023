#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cassert>


const int SECS_PER_MIN = 60;
const int MINS_PER_HOUR = 60;
const int HOURS_PER_DAY = 24;
const int SECS_PER_HOUR = SECS_PER_MIN * MINS_PER_HOUR;
const int SECS_PER_DAY = SECS_PER_HOUR * HOURS_PER_DAY;


class Interval {

private:
	int secs;

public:
	Interval(const int secs=0) {
		this->secs = secs;
	}

	// Default copy, assignment, and dtor
	Interval(const Interval&) = default;
	Interval& operator =(const Interval&) = default;
	~Interval() = default;

	// Getters
	int sign() const {
		return secs < 0 ? -1 : +1;
	}

	unsigned hours() const {
		return std::abs(secs) / SECS_PER_HOUR;
	}

	unsigned minutes() const {
		return (std::abs(secs) / SECS_PER_MIN) % MINS_PER_HOUR;
	}

	unsigned seconds() const {
		return std::abs(secs) % SECS_PER_MIN;
	}
};

class Clock {

private:
	// number of seconds from start of day
	int secs;

	unsigned toSeconds(const unsigned hours, const unsigned minutes, const unsigned seconds) {
		return hours * SECS_PER_HOUR + minutes * SECS_PER_MIN + seconds;
	}

	void move(int seconds) {
		secs += seconds;
		secs %= SECS_PER_DAY;
		if (secs < 0) {
			secs += SECS_PER_DAY;
		}

		assert (0 <= secs && secs < SECS_PER_DAY);
	}

public:
	// Constructor: defaults to midnight.
	Clock(const unsigned hour=0, const unsigned minutes=0, const unsigned seconds=0) {
		if (hour >= HOURS_PER_DAY) {
			throw std::invalid_argument("Invalid hour!");
		}
		if (minutes >= MINS_PER_HOUR) {
			throw std::invalid_argument("Invalid minutes!");
		}
		if (hour >= SECS_PER_MIN) {
			throw std::invalid_argument("Invalid seconds!");
		}

		secs = toSeconds(hour, minutes, seconds);
	}

	// Default copy, assignment, and dtor
	Clock(const Clock&) = default;
	Clock& operator =(const Clock&) = default;
	~Clock() = default;

	// Getters
	unsigned hour() const {
		return secs / SECS_PER_HOUR;
	}

	unsigned minutes() const {
		return (secs / SECS_PER_MIN) % MINS_PER_HOUR;
	}

	unsigned seconds() const {
		return secs % SECS_PER_MIN;
	}

	// Move clock forwards and back
	void forward(const unsigned hours=0, const unsigned minutes=0, const unsigned seconds=0) {
		const unsigned deltaSeconds = toSeconds(hours, minutes, seconds);
		move(deltaSeconds);
	}

	void back(const unsigned hours=0, const unsigned minutes=0, const unsigned seconds=0) {
		const unsigned deltaSeconds = toSeconds(hours, minutes, seconds);
		move(-deltaSeconds);
	}

	// Compare two clocks
	bool equals(const Clock& then) const {
		return secs == then.secs;
	}

	int compare(const Clock& then) const {
		if (secs < then.secs) {
			return -1;
		} else if (secs > then.secs) {
			return +1;
		} else {
			return 0;
		}
	}

	// Calculate time interval between two clocks
	Interval until(const Clock& then) const {
		const int deltaSeconds = then.secs - secs;
		return Interval{deltaSeconds};
	}
};


// Pretty-printers
void print24h(const Clock& clock) {
	const char c = std::cout.fill('0');
	std::cout << std::setw(2) << clock.hour() << ':'
			  << std::setw(2) << clock.minutes() << ':'
			  << std::setw(2) << clock.seconds();
	std::cout.fill(c);
}

void print12h(const Clock& clock) {
	unsigned h = clock.hour();
	const char *suffix = h < 12 ? "a.m." : "p.m.";

	// 0h -> 12 a.m., 12h -> 12 p.m.
	// For more details, check: https://en.wikipedia.org/wiki/12-hour_clock
	if (h == 0) {
		h = 12;
	} else if (h > 12) {
		h -= 12;
	}

	const char c = std::cout.fill('0');
	std::cout << h << ':'
			  << std::setw(2) << clock.minutes() << ':'
			  << std::setw(2) << clock.seconds() << ' ' << suffix;
	std::cout.fill(c);
}


void print(const Interval& i) {
	const char sign = i.sign() > 0 ? '+' : '-';
	std::cout << sign << ' '
			  << i.hours() << "h "
			  << i.minutes() << "m "
			  << i.seconds() << "s";
}

int main() {
	Clock c{17, 25, 13};

	print24h(c);
	std::cout << std::endl;
	print12h(c);
	std::cout << std::endl;

	c.forward(8, 15, 10);
	print24h(c);
	std::cout << std::endl;

	c.back(3);
	print24h(c);
	std::cout << std::endl;

	print(c.until({23, 0, 0}));
	std::cout << std::endl;

	print(c.until({21, 50, 0}));
	std::cout << std::endl;

	return 0;
}
