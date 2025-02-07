#ifndef APPETIZER_HPP
#define APPETIZER_HPP

#include "Dish.hpp"
#include <string>

/**
 * @class Appetizer
 * @brief Represents an appetizer dish, inheriting from Dish.
 */
class Appetizer : public Dish {
public:
    /**
     * @enum ServingStyle
     * @brief Describes how the appetizer is served.
     */
    enum ServingStyle { PLATED, FAMILY_STYLE, BUFFET };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    Appetizer();

    /**
     * Parameterized constructor.
     * @param name The name of the appetizer.
     * @param ingredients The ingredients used in the appetizer.
     * @param prep_time The preparation time in minutes.
     * @param price The price of the appetizer.
     * @param cuisine_type The cuisine type of the appetizer.
     * @param serving_style The serving style of the appetizer.
     * @param spiciness_level The spiciness level of the appetizer.
     * @param vegetarian Flag indicating if the appetizer is vegetarian.
     */
    Appetizer(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian);

    /**
     * Sets the serving style of the appetizer.
     * @param serving_style The new serving style.
     * @post Sets the private member `serving_style_` to the value of the parameter.
     */
    void setServingStyle(const ServingStyle &serving_style);

    /**
     * @return The serving style of the appetizer.
     */
    ServingStyle getServingStyle() const;

    /**
     * Sets the spiciness level of the appetizer.
     * @param spiciness_level An integer representing the spiciness level of the appetizer.
     * @post Sets the private member `spiciness_level_` to the value of the parameter.
     */
    void setSpicinessLevel(const int &spiciness_level);

    /**
     * @return The spiciness level of the appetizer.
     */
    int getSpicinessLevel() const;

    /**
     * Sets the vegetarian flag of the appetizer.
     * @param vegetarian A boolean indicating if the appetizer is vegetarian.
     * @post Sets the private member `vegetarian_` to the value of the parameter.
     */
    void setVegetarian(const bool &vegetarian);

    /**
     * @return True if the appetizer is vegetarian, false otherwise.
     */
    bool isVegetarian() const;

    /**
     * Displays the appetizer's details.
     * @post Outputs the appetizer's details, including name, ingredients,
    preparation time, price, cuisine type, serving style, spiciness level,
    and vegetarian status.
    */
    void display() const override;

    /**
    * Modifies the appetizer based on dietary accommodations.
    * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the appetizer's attributes to meet the specified
    dietary needs.
    * * *
    - If `request.vegetarian` is true:
        - Sets `vegetarian_` to true.
        - Searches `ingredients_` for any non-vegetarian ingredients and replaces the first occurrence with "Beans". If there are other non-vegetarian ingredients, the next non-vegetarian ingredient is replaced with "Mushrooms".
    * Non-vegetarian ingredients are: "Meat", "Chicken",
    "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    * * * *
    - If `request.low_sodium` is true:
        - Reduces `spiciness_level_` by 2 (minimum of 0).
    - If `request.gluten_free` is true:
        - Removes gluten-containing ingredients from
    `ingredients_`.
    *             Gluten-containing ingredients are: "Wheat", "Flour",
    "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
    void dietaryAccommodations(const DietaryRequest &request) override;

private:
    ServingStyle serving_style_; ///< The serving style of the appetizer.
    int spiciness_level_; ///< The spiciness level of the appetizer.
    bool vegetarian_; ///< Flag indicating if the appetizer is vegetarian.
};

#endif // APPETIZER_HPP