#include <string>
#include <ctime>

using namespace std;

struct MacrosInfo
{
    double calories;
    double protein;
    double fats;
    double carbohydrates;
};

struct User
{
    string username;
    string password;
    int age;
    string gender;
    double height;
    double weight;
    string levelOfActivity;
    string goal;
    string typeOfAccount;
    double weeklyWeightDiff;
    MacrosInfo recommendedMacros;
};

struct Meal
{
    string name;
    double calories;
    double protein;
    double carbs;
    double fats;
    string dayPeriodType;
    time_t createdDateTime;
};

struct Workout
{
    string name;
    double calories;
    time_t createdDateTime;
};