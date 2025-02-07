#include "Dessert.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}
/**
 * Displays the dessert's details.
 * @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level,
and whether it contains nuts.
*/
void Dessert::display() const
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
    std::cout << "Flavor Profile: ";
    // enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };
    switch (flavor_profile_)
    {
    case SWEET:
        std::cout << "SWEET" << std::endl;
        break;
    case BITTER:
        std::cout << "BITTER" << std::endl;
        break;
    case SOUR:
        std::cout << "SOUR" << std::endl;
        break;
    case SALTY:
        std::cout << "SALTY" << std::endl;
        break;
    case UMAMI:
        std::cout << "UMAMI" << std::endl;
        break;
    default:
        std::cout << "UNKNOWN" << std::endl;
        break;
    }
    std::cout << "Sweetness Level: " << sweetness_level_ << std::endl;
    std::cout << "Contains Nuts: ";
    if (contains_nuts_)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}

/**
 * Modifies the dessert based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Adjusts the dessert's attributes to meet the specified dietary
needs. 
- If `request.nut_free` is true:
    - Sets `contains_nuts_` to false.
    - Removes nuts from `ingredients_`.
               Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
- If `request.low_sugar` is true:
    - Reduces `sweetness_level_` by 3 (minimum of 0).
- If `request.vegan` is true:
    - Removes dairy and egg ingredients from `ingredients_`.
               Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*/
void Dessert::dietaryAccommodations(const DietaryRequest &request)
{
    if (request.nut_free)
    {
        contains_nuts_ = false;
        
        // Create a local mutable copy of ingredients
        std::vector<Ingredient> ingredients = getIngredients();

        if (!ingredients.empty())
        {
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                if (ingredients[i].name == "Almonds" || ingredients[i].name == "Walnuts" || ingredients[i].name == "Pecans" || 
                    ingredients[i].name == "Hazelnuts" || ingredients[i].name == "Peanuts" || ingredients[i].name == "Cashews" || 
                    ingredients[i].name == "Pistachios")
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;  // Adjust index after erase
                }
            }
        }

        // Set the modified ingredients back
        setIngredients(ingredients);
    }

    if (request.low_sugar)
    {
        sweetness_level_ -= 3;
        if (sweetness_level_ < 0)
        {
            sweetness_level_ = 0;
        }
    }

    if (request.vegan)
    {
        // Create a local mutable copy of ingredients
        std::vector<Ingredient> ingredients = getIngredients();

        if (!ingredients.empty())
        {
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                if (ingredients[i].name == "Milk" || ingredients[i].name == "Eggs" || ingredients[i].name == "Cheese" || 
                    ingredients[i].name == "Butter" || ingredients[i].name == "Cream" || ingredients[i].name == "Yogurt")
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;  // Adjust index after erase
                }
            }
        }

        // Set the modified ingredients back
        setIngredients(ingredients);
    }

    
}