#include <vector>
#include <string>

// За по-лесно четим код
using std::string, std::vector;


// Идеи за допълнителни функционалности:
//
// Работно време и заетост на ресторанти
// Поръчки
// Промоции/Остъпки за редовни клиенти ...
// Различни видове (типове/роли) потребители:
// потребител (клиент), мениджър на ресторант,
// мениджър на верига, администратор на платформата
// ...


// Видове кухня: българска, азиатска, френска ...
class Cuisine {
public:
	virtual string name() const = 0;
	// Потенциално и други методи ...

	virtual ~Cuisine() = default;
};

class Asian: public Cuisine {
public:
	string name() const override {
		return "Asian";
	}
};

class Bulgarian: public Cuisine {
public:
	string name() const override {
		return "Bulgarian";
	}
};

class Japanese: public Cuisine {
public:
	string name() const override {
		return "Japanese";
	}
};

// "Фюжън" кухня, напр. френско-азиатска
class Fusion: public Cuisine {
private:
	vector<Cuisine*> bases;

public:
	Fusion(const vector<Cuisine*>& bases);

	string name() const override;
};


// Различни категории: антре, основно, десерт, салата, суши ...
class DishCategory {
public:
	virtual string name() const = 0;
	// Потенциално и други методи ...

	virtual ~DishCategory() = default;
};

class Starter: public DishCategory {
public:
	string name() const override {
		return "Starter";
	}
};

class Main: public DishCategory {
public:
	string name() const override {
		return "Main";
	}
};

class Desert: public DishCategory {
public:
	string name() const override {
		return "Desert";
	}
};

class Salad: public DishCategory {
public:
	string name() const override {
		return "Salad";
	}
};

class Pizza: public DishCategory {
public:
	string name() const override {
		return "Pizza";
	}
};

class Sushi: public DishCategory {
public:
	string name() const override {
		return "Sushi";
	}
};

class Drink: public DishCategory {
public:
	string name() const override {
		return "Drink";
	}
};


// Ястия и меню
class Dish {
private:
	string name;
	vector<string> ingredients;
	vector<DishCategory*> categories;
	Cuisine *cuisine;
	unsigned price;

public:
	// TODO: Add ctor + getters
};

class Menu {
private:
	vector<Dish> dishes;

public:
	Menu() = default;
	void addDish(const Dish& dish);
	void removeDish(const string& name);
	const vector<Dish>& getDishes() const;
};


// Ресторанти и Вериги
class Client;

class Restaurant {
private:
	string name;
	string city;
	string address;
	string phone;
	string email;
	// etc...

	Menu menu;

	// За средна оценка (брой звезди) и
	// нотификации на абонирани клиенти
	double averageRating;
	unsigned numberOfRatings;

	vector<Client*> subscibers;
	void notifySubscribers();

public:
	// Add ctor + getters.

	void addSubscriber(Client* c);
	void removeSubscriber(Client *c);
};

class RestaurantChain {
private:
	vector<Restaurant*> restaurants;

public:
	// Add ctor + getters.

	void addRestaurant();
	void removeRestaurant();
};


// Клиенти
class Client {
private:
	string name;
	string city;
	string address;
	string phone;
	string email;
	// etc...

	vector<Restaurant*> subscriptions;

public:
	// Add ctor + getters.

	void subscribe(Restaurant* r);
	void unsubscribe(Restaurant* r);
	void getNotified() const;
};


int main() {
	return 0;
}