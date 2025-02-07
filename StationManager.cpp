/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the StationManager class, which manages a collection of kitchen stations in a virtual bistro simulation.
 *
 * The StationManager class includes methods to add, remove, and find stations, assign dishes to stations, replenish ingredients, and prepare dishes.
 * It also provides functionality to merge stations, move a station to the front of the list, and check if an order can be completed.
 * The class maintains a queue of dishes to be prepared and a list of backup ingredients for replenishment.
 *
 * @date 11/20/2024
 * @author Mitchell Lipyansky
*/

#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

/**
* Adds a dish to the preparation queue without dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @pre: The dish pointer is not null.
* @post: The dish is added to the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish) {
    if (dish != nullptr) { // Check if dish pointer is valid
        dish_queue_.push(dish); // Add dish to the queue
    }
}

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary
accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish, const Dish::DietaryRequest& request) {
    if (dish != nullptr) { // Check if dish pointer is valid
        dish->dietaryAccommodations(request); // Adjust dish for dietary accommodations
        dish_queue_.push(dish); // Add dish to the queue
    }
}

/**
* Prepares the next dish in the queue if possible.
* @pre: The dish queue is not empty.
* @post: The dish is processed and removed from the queue.
* If the dish cannot be prepared, it stays in the queue
* @return: True if the dish was prepared successfully; false otherwise.
*/
bool StationManager::prepareNextDish () {
    if (!dish_queue_.empty()) { // Check if the dish queue is not empty
        Dish* dish = dish_queue_.front(); // Get dish at front of the queue

        Node<KitchenStation*>* station_node = getHeadNode(); // Attempt to find a station to prepare the dish
        while (station_node != nullptr) { // Loop through all stations
            KitchenStation* station = station_node->getItem(); // Get station
            if (station->canCompleteOrder(dish->getName())) { // Check if station can prepare dish
                if (station->prepareDish(dish->getName())) { // Prepare dish
                    dish_queue_.pop();  // Remove dish from the queue
                    return true;
                }
            }
            station_node = station_node->getNext();  // Move to next station
        }
    }
    return false;
}

/**
* Retrieves the current dish preparation queue.
* @return A copy of the queue containing pointers to Dish objects.
* @post: The dish preparation queue is returned unchanged.
*/
std::queue<Dish*> StationManager::getDishQueue() const {
    return dish_queue_;
}

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup
supplies.
* @post: The list of backup ingredients is returned unchanged.
*/
std::vector<Ingredient> StationManager::getBackupIngredients() const {
    return backup_ingredients_;
}

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
* @post: The dish preparation queue is replaced with the provided
queue.
*/
void StationManager::setDishQueue(const std::queue<Dish*>& dish_queue) {
    dish_queue_ = dish_queue;
}

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/
void StationManager::displayDishQueue() const {
    std::queue<Dish*> temp_queue = dish_queue_; // Create temporary queue to preserve original queue
    while (!temp_queue.empty()) { // Loop through all dishes in the queue
        std::cout << temp_queue.front()->getName() << std::endl; //Display dish name
        temp_queue.pop(); // Remove dish from the queue
    }
}

/**
* Clears all dishes from the preparation queue.
* @pre: None.
* @post: The dish queue is emptied and all allocated memory is freed.
*/
void StationManager::clearDishQueue() {
    while (!dish_queue_.empty()) { // Loop through all dishes in the queue
        delete dish_queue_.front(); // Delete dynamically allocated dish
        dish_queue_.pop(); // Remove dish from queue
    }
}

/**
* Replenishes a specific ingredient at a given station from the backup
ingredients stock by a specified quantity.
* @param station_name A string representing the name of the station.
* @param ingredient_name A string representing the name of the ingredient
to replenish.
* @param quantity An integer representing the amount to replenish.
* @pre None.
* @post If the ingredient is found in the backup ingredients stock and has
sufficient quantity, it is added to the station's ingredient stock by the
specified amount, and the function returns true.
* The quantity of the ingredient in the backup stock is decreased by
the specified amount.
* If the ingredient in backup stock is depleted (quantity becomes
zero), it is removed from the backup stock.
* If the ingredient does not have sufficient quantity in backup
stock, or the ingredient or station is not found, returns false.
* @return True if the ingredient was replenished from backup; false
otherwise.
*/
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity) {
    if (quantity <= 0) { // Check for valid quantity
        return false;
    }

    KitchenStation* station = findStation(station_name); // Find station
    if (!station) { // Check if station exists
        return false;
    }

    for (auto it = backup_ingredients_.begin(); it != backup_ingredients_.end(); ++it) { // Loop through all backup ingredients
        if (it->name == ingredient_name) { // Check if ingredient exists in backup
            if (it->quantity >= quantity) { // Check if there is sufficient quantity in backup
                Ingredient replenished_ingredient(ingredient_name, quantity, 0, it->price); // Create a new Ingredient object with the replenished quantity

                station->replenishStationIngredients(replenished_ingredient); // Add the replenished ingredient to the station

                it->quantity -= quantity; // Update the backup stock quantity

                if (it->quantity == 0) {
                    backup_ingredients_.erase(it); // Remove ingredient from backup if quantity is zero
                }

                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}

/**
* Sets the backup ingredients stock with the provided list of ingredients.
* @param ingredients A vector of Ingredient objects to set as the backup
stock.
* @pre None.
* @post The backup_ingredients_ vector is replaced with the provided
ingredients.
* @return True if the ingredients were added; false otherwise.
*/
bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients) {
    backup_ingredients_ = ingredients;
    return true;
}

/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/
bool StationManager::addBackupIngredient(const Ingredient& ingredient) {
    for (auto& backup_ingredient : backup_ingredients_) { // Check if ingredient already exists in backup
        if (backup_ingredient.name == ingredient.name) { // Check if ingredient exists
            backup_ingredient.quantity += ingredient.quantity; // Increase quantity if ingredient exists
            return true;
        }
    }

    backup_ingredients_.push_back(ingredient); // Add ingredient to backup if it does not exist
    return true;
}

/**
* Empties the backup ingredients vector
* @post The backup_ingredients_ private member variable is empty.
*/
void StationManager::clearBackupIngredients() {
    backup_ingredients_.clear();
}

/**
* Processes all dishes in the queue and displays detailed results.
* @pre: None.
* @post: All dishes are processed, and detailed information is displayed
(as per the format in the specifications), including station replenishments
and preparation results.
* If a dish cannot be prepared even after replenishing ingredients, it
stays in the queue in its original order...
* i.e. if multiple dishes cannot be prepared, they will remain in the queue
in the same order

EXAMPLE OUTPUT

PREPARING DISH: Spaghetti Bolognese
Pasta Station attempting to prepare Spaghetti Bolognese...
Pasta Station: Insufficient ingredients. Replenishing ingredients...
Pasta Station: Ingredients replenished.
Pasta Station: Successfully prepared Spaghetti Bolognese.


All dishes have been processed.


PREPARING DISH: Vegan Salad
Salad Station attempting to prepare Vegan Salad...
Salad Station: Successfully prepared Vegan Salad.


All dishes have been processed.


PREPARING DISH: Seafood Paella
Seafood Station attempting to prepare Seafood Paella...
Seafood Station: Insufficient ingredients. Replenishing ingredients...
Seafood Station: Unable to replenish ingredients. Failed to prepare Seafood
Paella.
Seafood Paella was not prepared.


All dishes have been processed.


PREPARING DISH: Grilled Chicken
Grill Station attempting to prepare Grilled Chicken...
Grill Station: Insufficient ingredients. Replenishing ingredients...
Grill Station: Unable to replenish ingredients. Failed to prepare Grilled
Chicken.
Oven Station attempting to prepare Grilled Chicken...
Oven Station: Successfully prepared Grilled Chicken.

PREPARING DISH: Beef Wellington
Grill Station attempting to prepare Beef Wellington...
Grill Station: Dish not available. Moving to next station...
Oven Station attempting to prepare Beef Wellington...
Oven Station: Dish not available. Moving to next station...
Pasta Station attempting to prepare Beef Wellington...
Pasta Station: Dish not available. Moving to next station...
Salad Station attempting to prepare Beef Wellington...
Salad Station: Dish not available. Moving to next station...
Beef Wellington was not prepared.
All dishes have been processed.
*/
void StationManager::processAllDishes() {
    std::queue<Dish*> temp_queue; // Temporary queue to hold dishes that cannot be prepared

    while (!dish_queue_.empty()) { // Loop through all dishes in the queue
        Dish* dish = dish_queue_.front(); // Get the dish at the front
        dish_queue_.pop(); // Remove the dish from the main queue

        std::cout << "PREPARING DISH: " << dish->getName() << std::endl;

        Node<KitchenStation*>* station_node = getHeadNode(); // Start at the first station
        bool dish_prepared = false; // Track if the dish was successfully prepared

        while (station_node != nullptr) { // Loop through all stations
            KitchenStation* station = station_node->getItem(); // Get the station
            std::cout << station->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;

            bool dish_assigned = false; // Track if the dish is assigned to the station
            for (Dish* assigned_dish : station->getDishes()) { // Check if the dish is assigned to the station
                if (assigned_dish->getName() == dish->getName()) { // Check if the dish is assigned
                    dish_assigned = true;
                    break;
                }
            }

            if (!dish_assigned) { // Check if the dish is assigned to the station
                std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
                station_node = station_node->getNext(); // Move to the next station
                continue;
            }

            if (station->canCompleteOrder(dish->getName())) { // Attempt to prepare the dish
                if (station->prepareDish(dish->getName())) { // Check if the dish was prepared
                    std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                    dish_prepared = true;
                    break;
                }
            } else {
                std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;

                bool replenishment_success = true; // Track if ingredient replenishment is successful
                for (const Ingredient& ingredient : dish->getIngredients()) { // Loop through all ingredients in the dish
                    int required_quantity = ingredient.required_quantity; // Get the required quantity
                    int current_quantity = 0; // Initialize current quantity

                    for (const Ingredient& stock_ingredient : station->getIngredientsStock()) { // Loop through all ingredients in the station
                        if (stock_ingredient.name == ingredient.name) { // Check if the ingredient is in stock
                            current_quantity = stock_ingredient.quantity; // Get the current quantity
                            break;
                        }
                    }

                    int replenish_quantity = required_quantity - current_quantity; // Calculate the replenish quantity
                    if (replenish_quantity > 0) { // Check if replenishment is needed
                        if (!replenishStationIngredientFromBackup(station->getName(), ingredient.name, replenish_quantity)) { // Replenish ingredient from backup
                            replenishment_success = false;
                            break;
                        }
                    }
                }

                if (replenishment_success) { // Check if replenishment was successful
                    std::cout << station->getName() << ": Ingredients replenished." << std::endl;
                    if (station->prepareDish(dish->getName())) { // Attempt to prepare the dish
                        std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                        dish_prepared = true;
                        break;
                    } else {
                        std::cout << station->getName() << ": Unable to prepare " << dish->getName() << "." << std::endl;
                    }
                } else {
                    std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;
                }
            }

            station_node = station_node->getNext(); // Move to the next station
        }

        if (!dish_prepared) { // Check if the dish was prepared
            std::cout << dish->getName() << " was not prepared." << std::endl;
            temp_queue.push(dish); // Add the dish to the temporary queue
        }
    }

    dish_queue_ = temp_queue; // Restore unprepared dishes back to the original queue

    std::cout << "\n\nAll dishes have been processed." << std::endl;
}
