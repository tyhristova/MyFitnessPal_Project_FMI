#include <iostream>
#include <string>
#include <fstream>
#include "../include/constants.h"
#include "../include/structs.h"
#include "../include/utils.h"

using namespace std;

void toLowerCase(string &str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
}

bool isUsernameValid(string username)
{
    if (username.length() < USERNAME_LENGTH)
        return false;

    for (size_t i = 0; i < username.length(); i++)
    {
        if (username[i] == ' ')
            return false;
    }

    return true;
}

bool isPasswordValid(string password)
{
    if (password.length() < PASSWORD_LENGTH)
        return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;

    for (size_t i = 0; i < password.length(); i++)
    {
        char ch = password[i];
        if (ch >= 'A' && ch <= 'Z')
            hasUpper = true;
        else if (ch >= 'a' && ch <= 'z')
            hasLower = true;
        else if (ch >= '0' && ch <= '9')
            hasDigit = true;
        else if (ch == '!' || ch == '.' || ch == '?' || ch == '_')
            hasSymbol = true;
    }

    return hasUpper && hasLower && hasDigit && hasSymbol;
}

bool isAgeValid(int age)
{
    return age >= AGE_MIN && age <= AGE_MAX;
}

bool isHeightValid(double height)
{
    return height >= HEIGHT_MIN && height <= HEIGHT_MAX;
}

bool isWeightValid(double weight)
{
    return weight >= WEIGHT_MIN && weight <= WEIGHT_MAX;
}

bool isGenderValid(string gender)
{
    return gender == "male" || gender == "female";
}

bool isLevelOfActivityValid(string levelOfActivity)
{
    return levelOfActivity == "sedentary" || levelOfActivity == "low" || levelOfActivity == "moderate" || levelOfActivity == "active" || levelOfActivity == "very active";
}

bool isGoalValid(string goal)
{
    return goal == "weight loss" || goal == "weight maintenance" || goal == "weight gain";
}

bool isTypeOfAccountValid(string typeOfAccount)
{ 
    return typeOfAccount == "standard" || typeOfAccount == "premium";
}

bool isWeeklyWeightDiffValid(double weightDiff)
{
    return weightDiff == QUARTER_DIFF_KGS || weightDiff == THREE_QUARTERS_DIFF_KGS || weightDiff == HALF_DIFF_KGS || weightDiff == KILO_DIFF_KGS;
}

bool doesUserExist(const string& username, const string& filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return false;
    }

    string line;
    string storedUsername;

    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            storedUsername = line.substr(0, pos);
            if (storedUsername == username) {
                inFile.close();
                return true;
            }
        }
    }

    inFile.close();

    return false;
}

bool doesUserPasswordMatch(const string& username, const string& password, const string& filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;;

        string storedUsername = line.substr(0, pos1);
        string storedPassword = line.substr(pos1 + 1, pos2 - pos1 - 1);

        storedUsername.erase(0, storedUsername.find_first_not_of(" \t\r\n"));
        storedUsername.erase(storedUsername.find_last_not_of(" \t\r\n") + 1);

        storedPassword.erase(0, storedPassword.find_first_not_of(" \t\r\n"));
        storedPassword.erase(storedPassword.find_last_not_of(" \t\r\n") + 1);

        if (storedUsername == username && storedPassword == password) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

double calculateBMR(string gender, double weight, double height, int age)
{
    double bmr = 0.0;

    if (gender == "male")
    {
        bmr = BMR_MALE_COEFFICIENT + (weight * BMR_MALE_WEIGHT_COEFFICIENT) + (height * BMR_MALE_HEIGHT_COEFFICIENT) - (age * BMR_MALE_AGE_COEFFICIENT);
    }
    else if (gender == "female")
    {
        bmr = BMR_FEMALE_COEFFICIENT + (weight * BMR_FEMALE_WEIGHT_COEFFICIENT) + (height * BMR_FEMALE_HEIGHT_COEFFICIENT) - (age * BMR_FEMALE_AGE_COEFFICIENT);
    }

    return bmr;
}

double calculateMaintenanceCalories(string gender, double weight, double height, int age, string levelOfActivity)
{
    double bmr = calculateBMR(gender, weight, height, age);

    if (levelOfActivity == "sedentary")
    {
        return bmr * SEDENTARY_ACTIVITY_COEFFICIENT;
    }
    else if (levelOfActivity == "low")
    {
        return bmr * LOW_ACTIVITY_COEFFICIENT;
    }
    else if (levelOfActivity == "moderate")
    {
        return bmr * MODERATE_ACTIVITY_COEFFICIENT;
    }
    else if (levelOfActivity == "active")
    {
        return bmr * ACTIVE_ACTIVITY_COEFFICIENT;
    }
    else if (levelOfActivity == "very active")
    {
        return bmr * VERY_ACTIVE_ACTIVITY_COEFFICIENT;
    }

    return 0.0;
}

double calculateProtein(double calories, string goal)
{
    if (goal == "weight loss")
    {
        return (calories * 0.35) / 4;
    }
    else if (goal == "weight maintenance")
    {
        return (calories * 0.25) / 4;
    }
    else
    {
        return (calories * 0.4) / 4;
    }
}

double calculateCarbs(double calories, string goal)
{
    if (goal == "weight maintenance")
    {
        return (calories * 0.45) / 4;
    }
    else
    {
        return (calories * 0.35) / 4;
    }
}

double calculateFats(double calories, string goal)
{
    if (goal == "weight gain")
    {
        return (calories * 0.25) / 9;
    }
    else
    {
        return (calories * 0.30) / 9;
    }
}

bool areDatesEqual(time_t time1, time_t time2) {
    struct tm t1, t2;

    localtime_r(&time1, &t1);
    localtime_r(&time2, &t2);

    return (t1.tm_year == t2.tm_year &&
            t1.tm_mon == t2.tm_mon &&
            t1.tm_mday == t2.tm_mday);
}

bool doesMealExist(const string mealName, time_t createdDateTime, const string filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return false;
    }

    string line;

    while (getline(inFile, line)) {
        // Find positions of commas
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;

        size_t pos3 = line.find(',', pos2 + 1);
        if (pos3 == string::npos) continue;

        size_t pos4 = line.find(',', pos3 + 1);
        if (pos4 == string::npos) continue;

        size_t pos5 = line.find(',', pos4 + 1);
        if (pos5 == string::npos) continue;

        size_t pos6 = line.find(',', pos5 + 1);
        if (pos6 == string::npos) continue;

        // Extract meal name and createdDateTime
        string storedMealName = line.substr(0, pos1);
        time_t storedTime = stoll(line.substr(pos6 + 1)); // Created time

        // Compare meal name and dates (ignoring time)
        if (storedMealName == mealName && areDatesEqual(storedTime, createdDateTime)) {
            inFile.close();
            return true; // Match found
        }
    }

    inFile.close();
    return false; // No match found
}

bool doesWorkoutExist(const string workoutName, time_t createdDateTime, const string filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return false;
    }

    string line;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;

        // Extract workout name and createdDateTime from the line
        string storedWorkoutName = line.substr(0, pos1); // Name before the first comma
        time_t storedTime = stoll(line.substr(pos2 + 1)); // Time after the second comma

        // Compare name and time
        if (storedWorkoutName == workoutName && areDatesEqual(storedTime, createdDateTime)) {
            inFile.close();
            return true; // Match found
        }
    }

    inFile.close();
    return false; // No match found
}

string timeToDateString(time_t timestamp) {
    struct tm* timeInfo = localtime(&timestamp);
    char buffer[11]; // YYYY-MM-DD is 10 characters + null terminator
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);
    return string(buffer);
}

// Helper function to extract the date from the last field in the line
string extractDateFromLine(const string& line) {
    size_t lastComma = line.find_last_of(',');
    if (lastComma == string::npos) {
        return ""; // Invalid line, no commas found
    }

    string timestampStr = line.substr(lastComma + 1);
    time_t timestamp = stol(timestampStr);
    return timeToDateString(timestamp);
}

double calculateTotalCaloriesForToday(const string& mealsFile, const string& workoutsFile) {
    ifstream inFile(mealsFile);
    if (!inFile) {
        cerr << "Error: Could not open meals file!\n";
        return 0.0;
    }

    string line;
    double totalCalories = 0.0;

    while (getline(inFile, line)) {
        size_t lastComma = line.find_last_of(',');
            if (lastComma == string::npos) continue;

        string timestampStr = line.substr(lastComma + 1);
        time_t mealTime = stol(timestampStr);

        if (areDatesEqual(time(0), mealTime)){
            size_t pos1 = line.find(',');
            if (pos1 == string::npos) continue;

            size_t pos2 = line.find(',', pos1 + 1);
            if (pos2 == string::npos) continue;

            double calories = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            totalCalories += calories;
        }
    }

    inFile.close();

    ifstream inFile2(workoutsFile);
    if (!inFile2) {
        cerr << "Error: Could not open workouts file!\n";
        return 0.0;
    }

    while (getline(inFile2, line)) {
        size_t lastComma = line.find_last_of(',');
            if (lastComma == string::npos) continue;

        string timestampStr = line.substr(lastComma + 1);
        time_t mealTime = stol(timestampStr);

        if (areDatesEqual(time(0), mealTime)){
            size_t pos1 = line.find(',');
            if (pos1 == string::npos) continue;

            size_t pos2 = line.find(',', pos1 + 1);
            if (pos2 == string::npos) continue;

            double calories = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            totalCalories -= calories;
        }
    }

    inFile2.close();

    return totalCalories;
}

double calculateTotalProteinFromMeals(const string& mealsFile) {
    ifstream inFile(mealsFile);
    if (!inFile) {
        cerr << "Error: Could not open meals file!\n";
        return 0.0;
    }

    string line;
    double totalProtein = 0.0;
    time_t now = time(0);

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t lastComma = line.find_last_of(',');
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) continue;

        double protein = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
        time_t mealTimestamp = stol(line.substr(lastComma + 1));

        if (areDatesEqual(mealTimestamp, now)) {
            totalProtein += protein;
        } 
    }

    inFile.close();
    return totalProtein;
}

double calculateTotalCarbsFromMeals(const string& mealsFile) {
    ifstream inFile(mealsFile);
    if (!inFile) {
        cerr << "Error: Could not open meals file!\n";
        return 0.0;
    }

    string line;
    double totalCarbs = 0.0;
    time_t now = time(0);

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t pos5 = line.find(',', pos4 + 1);
        size_t lastComma = line.find_last_of(',');
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos || pos5 == string::npos) continue;

        double carbs = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
        time_t mealTimestamp = stol(line.substr(lastComma + 1));

        if (areDatesEqual(mealTimestamp, now)) {
            totalCarbs += carbs;
        } 
    }

    inFile.close();
    return totalCarbs;
}

double calculateTotalFatsFromMeals(const string& mealsFile) {
    ifstream inFile(mealsFile);
    if (!inFile) {
        cerr << "Error: Could not open meals file!\n";
        return 0.0;
    }

    string line;
    double totalFats = 0.0;
    time_t now = time(0);

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t pos5 = line.find(',', pos4 + 1);
        size_t pos6 = line.find(',', pos5 + 1);
        size_t lastComma = line.find_last_of(',');
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos || pos5 == string::npos || pos6 == string::npos) continue;

        double fats = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
        time_t mealTimestamp = stol(line.substr(lastComma + 1));

        if (areDatesEqual(mealTimestamp, now)) {
            totalFats += fats;
        } 
    }

    inFile.close();
    return totalFats;
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void recalculateUserMacros(User& user)
{
    user.recommendedMacros.calories = calculateMaintenanceCalories(
        user.gender, user.weight, user.height, user.age, user.levelOfActivity);

    user.recommendedMacros.protein = calculateProtein(user.recommendedMacros.calories, user.goal);
    user.recommendedMacros.carbohydrates = calculateCarbs(user.recommendedMacros.calories, user.goal);
    user.recommendedMacros.fats = calculateFats(user.recommendedMacros.calories, user.goal);

    cout << "Recalculated recommended macros for " << user.username << ":\n";
    cout << "Calories: " << user.recommendedMacros.calories << " kcal\n";
    cout << "Protein: " << user.recommendedMacros.protein << " g\n";
    cout << "Carbohydrates: " << user.recommendedMacros.carbohydrates << " g\n";
    cout << "Fats: " << user.recommendedMacros.fats << " g\n";
}

void updateUserInfo(User& user)
{
    user.weight = getValidatedWeight();
    user.goal = getValidatedGoal();
    recalculateUserMacros(user);
}

double getValidatedWeight()
{
    double newWeight;
    while (true) {
        cout << "Enter new weight: ";
        if (cin >> newWeight && isWeightValid(newWeight)) {
            return newWeight;
        }
        cerr << "Invalid weight. Please enter a value between " << WEIGHT_MIN << " and " << WEIGHT_MAX << ": ";
        cin.clear();
        clearInputBuffer();
    }
}

string getValidatedGoal()
{
    string newGoal;
    while (true) {
        cout << "Enter new goal (weight loss/weight maintenance/weight gain): ";
        cin >> newGoal;
        toLowerCase(newGoal);
        if (isGoalValid(newGoal)) {
            return newGoal;
        }
        cerr << "Invalid goal. Please enter one of: weight loss, weight maintenance, or weight gain.\n";
        clearInputBuffer();
    }
}

void displayUpdatedInfo(const User& user) {
    cout << "Updated information:\n";
    cout << "New weight: " << user.weight << " kg\n";
    cout << "Goal: " << user.goal << "\n";
    cout << "Recommended Calories: " << user.recommendedMacros.calories << " kcal\n";
}

long long findUserPosition(fstream& file, const string& username)
{
    file.clear();
    file.seekg(0, ios::beg);

    string line;
    long long position = file.tellg();

    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos && line.substr(0, pos) == username) {
            return position;
        }
        position = file.tellg();
    }
    return -1;
}

void updateUserInFile(fstream& file, const User& user, long long posToModify)
{
    file.seekp(posToModify);

    string updatedLine = user.username + "," + user.password + "," + to_string(user.age) + ","
                         + user.gender + "," + to_string(user.height) + "," + to_string(user.weight) + ","
                         + user.levelOfActivity + "," + user.goal + "," + user.typeOfAccount + ","
                         + to_string(user.weeklyWeightDiff) + "," + to_string(user.recommendedMacros.calories) + ","
                         + to_string(user.recommendedMacros.protein) + "," + to_string(user.recommendedMacros.carbohydrates) + ","
                         + to_string(user.recommendedMacros.fats) + "\n";

    file << updatedLine;

    file << string(updatedLine.size(), ' ') << "\n";
}

bool updateMealInFile(const string& username, Meal& updatedMeal, const string filename)
{
    ifstream inFile(filename);
    ofstream outFile("tempFile.txt");

    if (!inFile || !outFile) {
        cerr << "Error: Could not open the files for reading/writing!\n";
        return false;
    }

    string line;
    bool mealFound = false;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;

        size_t pos3 = line.find(',', pos2 + 1);
        if (pos3 == string::npos) continue;

        size_t pos4 = line.find(',', pos3 + 1);
        if (pos4 == string::npos) continue;

        size_t pos5 = line.find(',', pos4 + 1);
        if (pos5 == string::npos) continue;

        size_t pos6 = line.find(',', pos5 + 1);
        if (pos6 == string::npos) continue;

        string storedMealName = line.substr(0, pos1);
        time_t storedTime = stoll(line.substr(pos6 + 1));

        if (storedMealName == updatedMeal.name && areDatesEqual(storedTime, updatedMeal.createdDateTime)) {
            outFile << updatedMeal.name << ","
                    << updatedMeal.calories << ","
                    << updatedMeal.dayPeriodType << ","
                    << updatedMeal.protein << ","
                    << updatedMeal.carbs << ","
                    << updatedMeal.fats << ","
                    << updatedMeal.createdDateTime << "\n";
            mealFound = true;
        } else {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    if (mealFound) {
        remove(filename.c_str());
        rename("tempFile.txt", filename.c_str());
        return true;
    } else {
        remove("tempFile.txt");
        return false;
    }
}

string getMealPeriod() {
    string period;
    cout << "Enter the meal period (Breakfast, Lunch, Snack, or Dinner): ";
    cin >> period;
    return period;
}

bool updateWorkoutInFile(Workout& updatedWorkout, const string& filename)
{
    ifstream inFile(filename);
    ofstream outFile("tempFile.txt");

    if (!inFile || !outFile) {
        cerr << "Error: Could not open the files for reading/writing!\n";
        return false;
    }

    string line;
    bool workoutFound = false;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            outFile << line << "\n";
            continue;
        }

        string storedWorkoutName = line.substr(0, pos1);
        time_t storedTime = stoll(line.substr(pos2 + 1));

        if (storedWorkoutName == updatedWorkout.name && areDatesEqual(storedTime, time(0))) {
            outFile << updatedWorkout.name << ","
                    << updatedWorkout.calories << ","
                    << updatedWorkout.createdDateTime << "\n";
            workoutFound = true;
        } else {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    if (workoutFound) {
        remove(filename.c_str());
        rename("tempFile.txt", filename.c_str());
        return true;
    } else {
        remove("tempFile.txt");
        return false;
    }
}
