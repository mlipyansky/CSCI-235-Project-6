#include "KitchenStation.hpp"

KitchenStation::KitchenStation() 
    : station_name_("UNKNOWN"), dishes_({}), ingredients_stock_({}) {
}

KitchenStation::KitchenStation(const std::string& station_name) 
    : station_name_(station_name), dishes_({}), ingredients_stock_({}) {
}

KitchenStation::~KitchenStation() {
    for (Dish* dish : dishes_) {
        delete dish;
    }
}
std::string KitchenStation::getName() const {
    return station_name_;
}
void KitchenStation::setName(const std::string& station_name) {
    station_name_ = station_name;
}

// get dishes
std::vector<Dish*> KitchenStation::getDishes() const
{
    return dishes_;
}
// get ingredients stock
std::vector<Ingredient> KitchenStation::getIngredientsStock() const
{
    return ingredients_stock_;
}

bool KitchenStation::assignDishToStation(Dish* dish) {
    if (dish == nullptr) {
        return false;
    }
    if (isPresent(dish->getName())) {
        return false;
    }
    else {  
        dishes_.push_back(dish);
        return true;
    }
}

bool KitchenStation::isPresent(const std::string& dish_name) const {
    for (Dish* dish : dishes_) {
        if (dish->getName() == dish_name) {
            return true;
        }
    }
    return false;
}

void KitchenStation::replenishStationIngredients(const Ingredient& ingredient) {
    //check if ingredient is already in stock
    for (Ingredient& stock_ingredient : ingredients_stock_) {
        if (stock_ingredient.name == ingredient.name) {
            // std::cout<< "Found ingredient "<< stock_ingredient.name << std::endl;
            // std::cout<< "We have "<< stock_ingredient.quantity << " of "<< stock_ingredient.name << std::endl;
            // std::cout<< "We are adding "<< ingredient.quantity << " of "<< ingredient.name << std::endl;
            stock_ingredient.quantity += ingredient.quantity;
            // std::cout<< "We now have "<< stock_ingredient.quantity << " of "<< stock_ingredient.name << std::endl;
            return;
        }
    }
    ingredients_stock_.push_back(ingredient);
}

bool KitchenStation::canCompleteOrder(const std::string& dish_name) const {
    for (Dish* dish : dishes_) {
        // std::cout<< "Dish name: "<< dish->getName()<<std::endl;
        if (dish->getName() == dish_name) {
            // std::cout << "Checking if we can complete order for " << dish_name << std::endl;
            for (Ingredient ingredient : dish->getIngredients()) {
                // std::cout << "Checking for ingredient " << ingredient.name << std::endl;
                bool found = false;
                for (Ingredient stock_ingredient : ingredients_stock_) {
                    if (stock_ingredient.name == ingredient.name) {
                        // std::cout<< "Found ingredient "<< stock_ingredient.name << " and we have "<< stock_ingredient.quantity << std::endl;
                        if (stock_ingredient.quantity >= ingredient.required_quantity) {
                            // std::cout<<"YAY We need "<< ingredient.required_quantity << " of "<< ingredient.name << " and we have "<< stock_ingredient.quantity << std::endl;
                            // std::cout << "Found enough quantity of " << stock_ingredient.name << std::endl;
                            found = true;
                        }
                        else {
                            // std::cout << "Did not find enough quantity of " << stock_ingredient.name << std::endl;
                            // std::cout<<"NO We need "<< ingredient.required_quantity << " of "<< ingredient.name << " and we have "<< stock_ingredient.quantity << std::endl;
                            return false;
                        }
                    }
                }
                if (!found) {
                    // std::cout<< "Did not find " << ingredient.name << std::endl;
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool KitchenStation::prepareDish(const std::string& dish_name) {
    if (!canCompleteOrder(dish_name)) {
        return false;
    }
    else{
        //std::cout<< "Preparing dish: "<< dish_name << std::endl;
    }
    for (Dish* dish : dishes_) {
        if (dish->getName() == dish_name) {
            // Check if we have all the ingredients and the right quantity before doing anything else
            for (Ingredient ingredient : dish->getIngredients()) {
                bool found = false;
                for (Ingredient& stock_ingredient : ingredients_stock_) {
                    if (stock_ingredient.name == ingredient.name) {
                        // Check if we have enough stock
                        if (stock_ingredient.quantity >= ingredient.quantity) {
                            found = true;
                            break; // breaks out of the inner loop, so we check the next ingredient
                        }
                    }
                }
                if (!found) { // one of the ingredients is missing or not enough
                    return false;
                }
                // If we reach this point, we have all the ingredients in stock. Hooray!
            }
            // Deduct the ingredients from stock
            for (Ingredient ingredient : dish->getIngredients()) {
                for (Ingredient& stock_ingredient : ingredients_stock_) {
                    if (stock_ingredient.name == ingredient.name) {
                        stock_ingredient.quantity -= ingredient.required_quantity;
                        // if we have 0 quantity of an ingredient, we should remove it from stock
                        if (stock_ingredient.quantity == 0) {
                            removeIngredient(stock_ingredient.name);
                        }
                    }
                }
            }
            return true;
        }
    }
    return false; 
}

bool KitchenStation::removeIngredient(const std::string& ingredient_name) {
    for (size_t i = 0; i < ingredients_stock_.size(); i++) {
        if (ingredients_stock_[i].name == ingredient_name) {
            ingredients_stock_.erase(ingredients_stock_.begin() + i);
            return true;
        }
    }
    return false;
}