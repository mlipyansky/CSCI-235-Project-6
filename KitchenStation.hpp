#ifndef KITCHENSTATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include "Dish.hpp"

class KitchenStation {

    private:
        std::string station_name_;
        std::vector<Dish*> dishes_;
        std::vector<Ingredient> ingredients_stock_;

        bool isPresent(const std::string& dish_name) const;
        bool removeIngredient(const std::string& ingredient_name);

    public:
        KitchenStation();
        KitchenStation(const std::string& station_name);
        ~KitchenStation();

        // get name of station
        std::string getName() const;
        // set name of station
        void setName(const std::string& station_name);
        // get dishes
        std::vector<Dish*> getDishes() const;
        // get ingredients stock
        std::vector<Ingredient> getIngredientsStock() const;

        bool assignDishToStation(Dish* dish);
        void replenishStationIngredients(const Ingredient& ingredient);
        bool canCompleteOrder(const std::string& dish_name) const;
        bool prepareDish(const std::string& dish_name);

};

#endif // KITCHENSTATION_HPP