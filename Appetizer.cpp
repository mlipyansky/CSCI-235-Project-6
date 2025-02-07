#include "Appetizer.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

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
Appetizer::Appetizer(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}



/**
 * Displays the appetizer's details.
 * @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level,
and vegetarian status.
*/
void Appetizer::display() const
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
    std::cout << "Serving Style: ";
    switch (serving_style_)
    {
    case PLATED:
        std::cout << "Plated" << std::endl;
        break;
    case FAMILY_STYLE:
        std::cout << "Family Style" << std::endl;
        break;
    case BUFFET:
        std::cout << "Buffet" << std::endl;
        break;
    }
    std::cout << "Spiciness Level: " << spiciness_level_ << std::endl;
    std::cout << "Vegetarian: ";
    if (vegetarian_)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }

}

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
void Appetizer::dietaryAccommodations(const DietaryRequest &request)
{
    if (request.vegetarian)
    {
        vegetarian_ = true;
        bool first_replacement_done = false;
        bool second_replacement_done = false;
        
        // Create a local mutable copy of the ingredients
        std::vector<Ingredient> ingredients = getIngredients(); 

        if (!ingredients.empty())
        {
            for (size_t i = 0; i < ingredients.size(); i++)
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
                        i--;  // Adjust index after removal
                    }
                }
            }
        }

        // Set the modified ingredients back, assuming a setter method is available
        setIngredients(ingredients);
    }
    if (request.low_sodium)
    {
        spiciness_level_ -=2;
        if (spiciness_level_ < 0)
        {
            spiciness_level_ = 0;
        }
    }
    if (request.gluten_free)
    {
        std::vector<Ingredient> ingredients = getIngredients(); // Make a copy since getIngredients() is const

        if (!ingredients.empty())
        {
            for (size_t i = 0; i < ingredients.size(); i++)
            {
                if (ingredients[i].name == "Wheat" || ingredients[i].name == "Flour" || ingredients[i].name == "Bread" || 
                    ingredients[i].name == "Pasta" || ingredients[i].name == "Barley" || ingredients[i].name == "Rye" || 
                    ingredients[i].name == "Oats" || ingredients[i].name == "Crust")
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;  // Adjust the index after erasing
                }
            }
        }

        // Set the modified ingredients back, assuming you have a setter or similar method
        setIngredients(ingredients);
    }
}