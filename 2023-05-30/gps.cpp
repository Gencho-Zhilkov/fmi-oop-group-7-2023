#include <vector>
#include <string>

// Makes for more readable code
using std::string, std::vector;


// Simple coordinate class
struct GPSCoords {
	double latitude;
	double longitude;

	// TODO: Add ctor with lat+lon validation!
};


// Points of Interest
enum PointOfInterestType {
	GasStation,
	Restaurant,
	NaturalLandmark,
	HistoricalLandmark,

	// TODO: Possibly add others ...
};

class PointOfInterest {
private:
	string name;
	PointOfInterestType type;

public:
	// TODO: Add ctor + getters
};


// GPS Navigation nodes: City, Town, Crossroads, etc ...
class Road;

class Location {
private:
	string name;
	GPSCoords coordinates;
	vector<Road*> incoming;
	vector<Road*> outgoing;
	vector<PointOfInterest> pointsOfInterest;

public:
	// TODO: Add ctor + getters
};


// Road infrastructure
class Road {
private:
	string name;
	vector<GPSCoords> coordinates;
	Location *start;
	Location *end;

	double lenght;
	unsigned /* double */ tollTaxes;

	bool isOpen_;

public:
	// TODO: Add ctor + getters

	void open();
	void close();
	bool isOpen() const;

	virtual double  averageSpeed() const = 0;
	// Other possible methods we may want to add:
	// virtual double minSpeed() const = 0;
	// virtual double maxSpeed() const = 0;
	// virtual vector<CarClass> openToCars() const = 0;

	virtual ~Road() = default;
};

/* CountryRoad */
class SecondaryRoad: public Road {
public:
	// TODO: Add ctor

	double averageSpeed() const override {
		return 40;
	}
};

/* MainRoad */
class PrimaryRoad: public Road {
public:
	// TODO: Add ctor

	double averageSpeed() const override {
		return 65;
	}
};

class Highway: public Road {
public:
	// TODO: Add ctor

	double averageSpeed() const override {
		return 100;
	}
};


// Different navigation strategies:
class NavigationStrategy {
public:
	virtual vector<Road*> findRoute(
		const Location& start,
		const Location& end) const = 0;
	virtual ~NavigationStrategy() = default;
};

class ShortestRoute: public NavigationStrategy {
	vector<Road*> findRoute(
		const Location& start,
		const Location& end) const override;
};

class FastestRoute: public NavigationStrategy {
	vector<Road*> findRoute(
		const Location& start,
		const Location& end) const override;
};

class CheapestRoute: public NavigationStrategy {
	vector<Road*> findRoute(
		const Location& start,
		const Location& end) const override;
};


// GPS Map
class Map {
private:
	vector<Location*> locations;
	vector<Road*> roads;

public:
	Map(const vector<Location>& locations);

	void addLocation(const Location& location);
	void removeLocation(const Location& location);

	Location* findLocation(const string& name) const;
	Location* findNearestLocation(const GPSCoords& coordinates) const;

	void addRoad(Road* r);
	void removeRoad(Road *r);

	Road* findRoad(const string& name) const;
	Road* findNearestRoad(const GPSCoords& coordinates) const;

	vector<Location*> findNearby(
		const GPSCoords& coordinates,
		const vector<PointOfInterestType>& types,
		const unsigned maxCount = 5) const;

	vector<Road*> findRoute(
		const Location& start,
		const Location& end,
		const NavigationStrategy& how) const;
};


int main() {
	return 0;
}
