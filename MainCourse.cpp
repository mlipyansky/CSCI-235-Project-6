#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

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
MainCourse::MainCourse(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}
/**
 * Displays the main course's details.
 * @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status.
*/

void MainCourse::display() const
{
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    for (size_t i = 0; i < getIngredients().size(); ++i) {
        std::cout << getIngredients()[i].name;
        if (i != getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;

    std::cout << "Cooking Method: " << cookingMethodToString(cooking_method_) << std::endl;
    std::cout << "Protein Type: " << protein_type_ << std::endl;
    std::cout << "Side Dishes: ";
    for (size_t i = 0; i < side_dishes_.size(); ++i) {
        std::cout << side_dishes_[i].name << " (Category: " << categoryToString(side_dishes_[i].category) << ")";
        if (i != side_dishes_.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << (gluten_free_ ? "Yes" : "No") << std::endl;
}

/**
     * Modifies the main course based on dietary accommodations.
     * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the main course's attributes to meet the specified
    dietary needs.
    * * *
    - If `request.vegetarian` is true:
        - Changes `protein_type_` to "Tofu".
        - Searches `ingredients_` for any non-vegetarian ingredients and replaces the first occurrence with "Beans". If there are other non-vegetarian ingredients, the next non-vegetarian ingredient is replaced with "Mushrooms".
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
void MainCourse::dietaryAccommodations(const DietaryRequest &request)
{
    if (request.vegetarian)
    {
        protein_type_ = "Tofu";
        bool first_replacement_done = false;
        bool second_replacement_done = false;

        // Create a local mutable copy of ingredients
        std::vector<Ingredient> ingredients = getIngredients();

        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            if (ingredients[i].name == "Meat" || ingredients[i].name == "Chicken" || ingredients[i].name == "Fish" || 
                ingredients[i].name == "Beef" || ingredients[i].name == "Pork" || ingredients[i].name == "Lamb" || 
                ingredients[i].name == "Shrimp" || ingredients[i].name == "Bacon")
            {
                if (!first_replacement_done)
                {
                    ingredients[i].name = "Beans";  // First replacement
                    first_replacement_done = true;
                }
                else if (!second_replacement_done)
                {
                    ingredients[i].name = "Mushrooms";  // Second replacement
                    second_replacement_done = true;
                }
                else
                {
                    ingredients.erase(ingredients.begin() + i);  // Remove non-vegetarian item
                    i--;  // Adjust index after erase
                }
            }
        }
        // Update ingredients
        setIngredients(ingredients);
        
    }
    if (request.vegan)
    {
        protein_type_ = "Tofu";

        // Create a local mutable copy of ingredients
        std::vector<Ingredient> ingredients = getIngredients();

        if (!ingredients.empty())
        {
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                if (ingredients[i].name == "Milk" || ingredients[i].name == "Eggs" || ingredients[i].name == "Cheese" || 
                    ingredients[i].name == "Butter" || ingredients[i].name == "Cream" || ingredients[i].name == "Yogurt")
                {
                    ingredients.erase(ingredients.begin() + i);  // Remove non-vegan item
                    i--;  // Adjust index after erase
                }
            }
        }
        // Update ingredients
        setIngredients(ingredients);
    }
    if (request.gluten_free)
    {
        gluten_free_ = true;
        if (side_dishes_.size() > 0)
        {
            for (size_t i = 0; i < side_dishes_.size(); ++i)
            {
                if (categoryToString(side_dishes_[i].category) == "GRAIN" || categoryToString(side_dishes_[i].category) == "PASTA" || categoryToString(side_dishes_[i].category) == "BREAD" || categoryToString(side_dishes_[i].category) == "STARCHES")
                {
                    side_dishes_.erase(side_dishes_.begin() + i);
                    i--;
                }
            }
        }
    }
    
    
}
//enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };
std::string MainCourse::categoryToString(const Category &category) const {
    switch (category) {
        case GRAIN:
            return "GRAIN";
        case PASTA:
            return "PASTA";
        case LEGUME:
            return "LEGUME";
        case BREAD:
            return "BREAD";
        case SALAD:
            return "SALAD";
        case SOUP:
            return "SOUP";
        case STARCHES:
            return "STARCHES";
        case VEGETABLE:
            return "VEGETABLE";
    }
}

//enum CookingMethod { GRILLED, BAKED, BOILED, FRIED, STEAMED, RAW };
std::string MainCourse::cookingMethodToString(const CookingMethod &cooking_method) const {
    switch (cooking_method) {
        case GRILLED:
            return "GRILLED";
        case BAKED:
            return "BAKED";
        case BOILED:
            return "BOILED";
        case FRIED:
            return "FRIED";
        case STEAMED:
            return "STEAMED";
        case RAW:
            return "RAW";
    }
}