#include <iostream>
#include "StationManager.hpp"
#include "Dish.hpp"

class TestDish : public Dish {
public:
    TestDish(const std::string& name, const std::vector<Ingredient>& ingredients, int prep_time, double price, CuisineType cuisine_type)
            : Dish(name, ingredients, prep_time, price, cuisine_type) {}

    void display() const override {
        std::cout << "Test Dish: " << getName() << std::endl;
    }

    void dietaryAccommodations(const DietaryRequest& request) override {
        // Simple implementation for testing
    }
};

int main() {
    // Create a StationManager
    StationManager manager;

    // Create Kitchen Stations
    KitchenStation* grillStation = new KitchenStation("Grill Station");
    KitchenStation* pastaStation = new KitchenStation("Pasta Station");

    // Add stations to manager
    manager.addStation(grillStation);
    manager.addStation(pastaStation);

    // Create some dishes
    std::vector<Ingredient> spaghettiIngredients = {
            Ingredient("Spaghetti", 0, 1, 1.5),
            Ingredient("Tomato Sauce", 0, 1, 0.75)
    };
    std::vector<Ingredient> chickenIngredients = {
            Ingredient("Chicken", 0, 1, 2.0),
            Ingredient("Spices", 0, 1, 0.5)
    };

    Dish* spaghetti = new TestDish("Spaghetti Bolognese", spaghettiIngredients, 20, 12.99, Dish::CuisineType::ITALIAN);
    Dish* chicken = new TestDish("Grilled Chicken", chickenIngredients, 15, 10.99, Dish::CuisineType::AMERICAN);

    // Assign dishes to stations
    manager.assignDishToStation("Pasta Station", spaghetti);
    manager.assignDishToStation("Grill Station", chicken);

    // Add ingredients to backup
    manager.addBackupIngredient(Ingredient("Spaghetti", 5, 0, 1.5));
    manager.addBackupIngredient(Ingredient("Tomato Sauce", 5, 0, 0.75));
    manager.addBackupIngredient(Ingredient("Chicken", 5, 0, 2.0));
    manager.addBackupIngredient(Ingredient("Spices", 5, 0, 0.5));

    // Add dishes to preparation queue
    manager.addDishToQueue(spaghetti);
    manager.addDishToQueue(chicken);

    // Process all dishes
    manager.processAllDishes();

    // Clean up
    delete grillStation;
    delete pastaStation;

    return 0;
}
