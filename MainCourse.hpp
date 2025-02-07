#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP

#include "Dish.hpp"
#include <string>
#include <vector>

/**
 * @class MainCourse
 * @brief Represents a main course dish, inheriting from Dish.
 */
class MainCourse : public Dish {
public:
    /**
     * @enum CookingMethod
     * @brief Describes the method used to cook the main course.
     */
    enum CookingMethod { GRILLED, BAKED, BOILED, FRIED, STEAMED, RAW };

    /**
     * @enum Category
     * @brief Describes the category of the side dish.
     */
    enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };

    /**
     * @struct SideDish
     * @brief Represents a side dish associated with the main course.
     */
    struct SideDish {
        std::string name; ///< The name of the side dish.
        Category category; ///< The category of the side dish.
    };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    MainCourse();

    /**
     * Parameterized constructor.
     * @param name The name of the main course.
     * @param ingredients The ingredients used in the main course.
     * @param prep_time The preparation time in minutes.
     * @param price The price of the main course.
     * @param cuisine_type The cuisine type of the main course.
     * @param cooking_method The cooking method used for the main course.
     * @param protein_type The type of protein used in the main course.
     * @param side_dishes The side dishes served with the main course.
     * @param gluten_free Flag indicating if the main course is gluten-free.
     */
    MainCourse(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free);

    /**
     * Sets the cooking method of the main course.
     * @param cooking_method The new cooking method.
     * @post Sets the private member `cooking_method_` to the value of the parameter.
     */
    void setCookingMethod(const CookingMethod &cooking_method);

    /**
     * @return The cooking method of the main course.
     */
    CookingMethod getCookingMethod() const;

    /**
     * Sets the type of protein in the main course.
     * @param protein_type A string representing the type of protein.
     * @post Sets the private member `protein_type_` to the value of the parameter.
     */
    void setProteinType(const std::string& protein_type);

    /**
     * @return The type of protein in the main course.
     */
    std::string getProteinType() const;

    /**
     * Adds a side dish to the main course.
     * @param side_dish A SideDish struct containing the name and category of the side dish.
     * @post Adds the side dish to the `side_dishes_` vector.
     */
    void addSideDish(const SideDish& side_dish);

    /**
     * @return A vector of SideDish structs representing the side dishes served with the main course.
     */
    std::vector<SideDish> getSideDishes() const;

    /**
     * Sets the gluten-free flag of the main course.
     * @param gluten_free A boolean indicating if the main course is gluten-free.
     * @post Sets the private member `gluten_free_` to the value of the parameter.
     */
    void setGlutenFree(const bool &gluten_free);

    /**
     * @return True if the main course is gluten-free, false otherwise.
     */
    bool isGlutenFree() const;

    /**
     * Displays the appetizer's details.
     * @post Outputs the appetizer's details, including name, ingredients,
    preparation time, price, cuisine type, serving style, spiciness level,
    and vegetarian status.
    */
    void display() const override;

    /**
     * Modifies the main course based on dietary accommodations.
     * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the main course's attributes to meet the specified
    dietary needs.
    * * *
    - If `request.vegetarian` is true:
        - Changes `protein_type_` to "Tofu".
        - Searches `ingredients_` for any non-vegetarian ingredients and replaces the first occurrence with "Beans". If there are other non-vegetarian ingredients, they are replaced with "Mushrooms".
    * Non-vegetarian ingredients are: "Meat", "Chicken",
    "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    * * * *
    * * *
    - If `request.vegan` is true:
        - Changes `protein_type_` to "Tofu".
        - Removes dairy and egg ingredients from `ingredients_`.
                Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
    "Butter", "Cream", "Yogurt".
    - If `request.gluten_free` is true:
        - Sets `gluten_free_` to true.
        - Removes side dishes from `side_dishes_` whose category
    involves gluten.
    *             Gluten-containing side dish categories are: `GRAIN`,
    `PASTA`, `BREAD`, `STARCHES`.
    */
    void dietaryAccommodations(const DietaryRequest &request) override;

private:
    // Helper function to convert cooking method to string
    std::string cookingMethodToString(const CookingMethod &cooking_method) const;
    // Helper function to convert category to string
    std::string categoryToString(const Category &category) const;
    CookingMethod cooking_method_; ///< The cooking method used for the main course.
    std::string protein_type_; ///< The type of protein used in the main course.
    std::vector<SideDish> side_dishes_; ///< The side dishes served with the main course.
    bool gluten_free_; ///< Flag indicating if the main course is gluten-free.
};

#endif // MAINCOURSE_HPP