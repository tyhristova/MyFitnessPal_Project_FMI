#include <iostream>
#include <string.h>
#include <ctime>
#include <fstream>
#include <vector>
#include "../include/constants.h"
#include "../include/structs.h"
#include "../include/utils.h"

using namespace std;

void registrationMenu(User& user)
{
    string passwordConfirmation;
    bool isUserNameValid = true;

    // Username
    do {
        cout << "Username: ";
        cin.ignore();
        getline(cin, user.username);

        isUserNameValid = true;

        if (!isUsernameValid(user.username)) {
            cerr << "Invalid username! It must be at least " << USERNAME_LENGTH << " characters long and contain no spaces.\n";
            isUserNameValid = false;
            continue;
        } 
        
        if (doesUserExist(user.username, USERS_FILE_NAME))
        {
            cerr << "User with this username already exists!\n";
            isUserNameValid = false;
            continue;
        }

    } while (!isUserNameValid);

    // Password
    do {
        cout << "Password: ";
        getline(cin, user.password);

        cout << "Confirm password: ";
        getline(cin, passwordConfirmation);

        if (!isPasswordValid(user.password) || passwordConfirmation != user.password) {
            cerr << "Invalid password! It must meet the criteria and match the confirmation.\n";
        }

    } while (!isPasswordValid(user.password) || passwordConfirmation != user.password);

    // Age
    do {
        cout << "Age: ";
        cin.ignore();
        cin >> user.age;

        if (!isAgeValid(user.age)) {
            cerr << "Invalid age! It must be between " << AGE_MIN << " and " << AGE_MAX << ".\n";
        }

    } while (!isAgeValid(user.age));

    // Gender
    do {
        cout << "Gender (Male or Female): ";
        getline(cin, user.gender);
        toLowerCase(user.gender);

        if (!isGenderValid(user.gender)) {
            cerr << "Invalid gender! Enter 'Male' or 'Female'.\n";
        }

    } while (!isGenderValid(user.gender));

    // Height
    do {
        cout << "Height (cm): ";
        cin.ignore();
        cin >> user.height;

        if (!isHeightValid(user.height)) {
            cerr << "Invalid height! It must be between " << HEIGHT_MIN << " cm and " << HEIGHT_MAX << " cm.\n";
        }

    } while (!isHeightValid(user.height));

    // Weight
    do {
        cout << "Weight (kg): ";
        cin.ignore();
        cin >> user.weight;

        if (!isWeightValid(user.weight)) {
            cerr << "Invalid weight! It must be between " << WEIGHT_MIN << " kg and " << WEIGHT_MAX << " kg.\n";
        }

    } while (!isWeightValid(user.weight));

    // Level of Activity
    do {
        cout << "Level of activity (Sedentary, Low, Moderate, Active, Very active): ";
        getline(cin, user.levelOfActivity);
        toLowerCase(user.levelOfActivity);

        if (!isLevelOfActivityValid(user.levelOfActivity)) {
            cerr << "Invalid activity level! Choose from Sedentary, Low, Moderate, Active, or Very active.\n";
        }

    } while (!isLevelOfActivityValid(user.levelOfActivity));

    // Goal
    do {
        cout << "Goal (Weight Loss, Weight Maintenance, Weight Gain): ";
        getline(cin, user.goal);
        toLowerCase(user.goal);

        if (!isGoalValid(user.goal)) {
            cerr << "Invalid goal! Choose from Weight Loss, Weight Maintenance, or Weight Gain.\n";
        }

    } while (!isGoalValid(user.goal));

    if (user.goal == "weight maintenance")
    {
        user.weeklyWeightDiff = 0.0;
    }
    else
    {
        do
        {
            cout << "Write how much weight difference you want per week: ";
            cin.ignore();
            cin >> user.weeklyWeightDiff;

            if (!isWeeklyWeightDiffValid(user.weeklyWeightDiff)) {
                cerr << "Invalid weight difference! Choose from 0.25kg, 0.5kg, 0.75kg and 1kg.\n";
            }
        } while (!isWeeklyWeightDiffValid(user.weeklyWeightDiff));
    }

    // Type of Account
    do {
        cout << "Type of account (Standard or Premium): ";
        getline(cin, user.typeOfAccount);
        toLowerCase(user.typeOfAccount);

        if (!isTypeOfAccountValid(user.typeOfAccount)) {
            cerr << "Invalid account type! Choose either 'Standard' or 'Premium'.\n";
        }

    } while (!isTypeOfAccountValid(user.typeOfAccount));
}

void writeUserToFile(const User& user, const string& filename) {
    ofstream outFile(filename, ios::app);

    if (!outFile) {
        cerr << "Error: Could not open the file for writing!\n";
        return;
    }

    outFile << user.username << ","
            << user.password << ","
            << user.age << ","
            << user.gender << ","
            << user.height << ","
            << user.weight << ","
            << user.levelOfActivity << ","
            << user.goal << ","
            << user.typeOfAccount << ","
            << user.weeklyWeightDiff << ","
            << user.recommendedMacros.calories << ","
            << user.recommendedMacros.protein << ","
            << user.recommendedMacros.carbohydrates << ","
            << user.recommendedMacros.fats << "\n";

    outFile.close();
}

void calculateCaloriesAndMacros(User& user)
{
    MacrosInfo result;
    double calories = calculateMaintenanceCalories(user.gender, user.weight, user.height, user.age, user.levelOfActivity);

    if (user.weeklyWeightDiff == QUARTER_DIFF_KGS)
    {
        double dailyDiff = QUARTER_DIFF_CALS / DAYS_PER_WEEK;
        
        if (user.goal == "weight gain")
        {
            calories += dailyDiff;
        }
        else
        {
            calories -= dailyDiff;
        }
    }
    else if (user.weeklyWeightDiff == HALF_DIFF_KGS)
    {
        double dailyDiff = HALF_DIFF_CALS / DAYS_PER_WEEK;

        if (user.goal == "weight gain")
        {
            calories += dailyDiff;
        }
        else
        {
            calories -= dailyDiff;
        }
    }
    else if (user.weeklyWeightDiff == THREE_QUARTERS_DIFF_KGS)
    {
        double dailyDiff = THREE_QUARTERS_DIFF_CALS / DAYS_PER_WEEK;

        if (user.goal == "weight gain")
        {
            calories += dailyDiff;
        }
        else
        {
            calories -= dailyDiff;
        }
    }
    else if (user.weeklyWeightDiff == KILO_DIFF_KGS)
    {
        double dailyDiff = KILO_DIFF_CALS / DAYS_PER_WEEK;

        if (user.goal == "weight gain")
        {
            calories += dailyDiff;
        }
        else
        {
            calories -= dailyDiff;
        }
    }

    result.calories = calories;

    if (user.typeOfAccount == "premium")
    {
        result.protein = calculateProtein(calories, user.goal);
        result.carbohydrates = calculateCarbs(calories, user.goal);
        result.fats = calculateFats(calories, user.goal);
    }
    else
    {
        result.protein = 0.0;
        result.carbohydrates = 0.0;
        result.fats = 0.0;
    }

    user.recommendedMacros = result;
}

void createUserFiles(const string& username) {
    string mealsFileName = BASE_USERS_FOLDER + username + MEALS_FILE_EXTENSION;
    string workoutsFileName = BASE_USERS_FOLDER + username + WORKOUTS_FILE_EXTENSION;

    ofstream mealsFile(mealsFileName);
    if (!mealsFile) {
        cerr << "Error: Could not create meals file for user " << username << "!\n";
    } else {
        mealsFile.close();
    }

    ofstream workoutsFile(workoutsFileName);
    if (!workoutsFile) {
        cerr << "Error: Could not create workouts file for user " << username << "!\n";
    } else {
        workoutsFile.close();
    }
}

void registration()
{
    User userToRegister;

    registrationMenu(userToRegister);

    if (doesUserExist(userToRegister.username, USERS_FILE_NAME)) {
        cerr << "This user already exists!\n";
    } else {
        calculateCaloriesAndMacros(userToRegister);
        writeUserToFile(userToRegister, USERS_FILE_NAME);

        createUserFiles(userToRegister.username);

        cout << "User registered successfully and added to the file.\n";
    } 
}

User getUserFromFile(const string& username, const string& filename)
{
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return User();
    }

    string line;

    while (getline(inFile, line)) {
        size_t pos = 0;

        pos = line.find(',');
        string storedUsername = line.substr(0, pos);
        line.erase(0, pos + 1);

        if (storedUsername == username) {
            User user;
            user.username = storedUsername;

            // Extract password
            pos = line.find(',');
            user.password = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Extract age
            pos = line.find(',');
            user.age = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Extract gender
            pos = line.find(',');
            user.gender = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Extract height
            pos = line.find(',');
            user.height = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Extract weight
            pos = line.find(',');
            user.weight = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Extract level of activity
            pos = line.find(',');
            user.levelOfActivity = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Extract goal
            pos = line.find(',');
            user.goal = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Extract type of account
            pos = line.find(',');
            user.typeOfAccount = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Extract weekly weight difference
            pos = line.find(',');
            user.weeklyWeightDiff = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Extract recommended macros
            pos = line.find(',');
            user.recommendedMacros.calories = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            user.recommendedMacros.protein = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            user.recommendedMacros.carbohydrates = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            user.recommendedMacros.fats = stod(line);

            inFile.close();
            return user;
        }
    }

    inFile.close();
    cerr << "Error: User not found in the file!\n";
    return User();
}

void loginMenu(User& user)
{
    string username;
    string password;

    cout << "\nIf you want to go back to the main menu press 'M'.\n";

    while (true) {
        cout << "Username: ";
        cin.ignore();
        getline(cin, username);

        if (username == "M") {
            return;
        }

        if (doesUserExist(username, USERS_FILE_NAME)) {
            break;
        }

        cout << "User with this username doesn't exist. Try again.\n";
    }

    while (true) {
        cout << "Password: ";
        getline(cin, password);

        if (password == "M") {
            return;
        }

        if (doesUserPasswordMatch(username, password, USERS_FILE_NAME)) {
            break;
        }

        cout << "User password is incorrect. Try again.\n";
    }

    user = getUserFromFile(username, USERS_FILE_NAME);
}

void showUserInfo(User& user)
{
    cout << "Personal info:\n";
    cout << "Username:\t" << user.username << endl;
    cout << "Age:\t" << user.age << endl;
    cout << "Gender:\t" << user.gender << endl;
    cout << "Height:\t" << user.height << endl;
    cout << "Weight:\t" << user.weight << endl;

    cout << "Physical info:\n";
    cout << "Level of activity:\t" << user.levelOfActivity << endl;
    cout << "Goal:\t" << user.goal << endl;
    cout << "Weekly weight difference: " << user.weeklyWeightDiff << endl;

    cout << "Meal info:\n";
    cout << "Recommended daily calories:\t" << user.recommendedMacros.calories << endl;
    if (user.typeOfAccount == "premium")
    {
        cout << "Recommended protein:\t" << user.recommendedMacros.protein << endl;
        cout << "Recommended carbs:\t" << user.recommendedMacros.carbohydrates << endl;
        cout << "Recommended fats:\t" << user.recommendedMacros.fats << endl;
    }

    cout << "Account info:\n";
    cout << "Type of account:\t" << user.typeOfAccount << endl;
}

void showCurrentNutrition(User& user)
{
    string mealsFile = BASE_USERS_FOLDER + user.username + MEALS_FILE_EXTENSION;
    string workoutsFile = BASE_USERS_FOLDER + user.username + WORKOUTS_FILE_EXTENSION;

    double currentCalories = calculateTotalCaloriesForToday(mealsFile, workoutsFile);
    double currentProtein = calculateTotalProteinFromMeals(mealsFile);
    double currentCarbs = calculateTotalCarbsFromMeals(mealsFile);
    double currentFats = calculateTotalFatsFromMeals(mealsFile);

    cout << "\nCurrent Consumption:" << endl;
    cout << "Calories: " << currentCalories << " / " << user.recommendedMacros.calories << endl;

    if (user.typeOfAccount == "premium")
    {
        cout << "Protein: " << currentProtein << " g / " << user.recommendedMacros.protein << " g" << endl;
        cout << "Carbohydrates: " << currentCarbs << " g / " << user.recommendedMacros.carbohydrates << " g" << endl;
        cout << "Fats: " << currentFats << " g / " << user.recommendedMacros.fats << " g" << endl;
    }

    cout << endl;
}

double safeStod(const std::string& str) {
    try {
        return std::stod(str);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << str << " is not a valid number.\n";
        return 0.0;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << str << " is too large or too small for a double.\n";
        return 0.0;
    }
}

void viewDailyNutritionInfo(User& user) {
    cout << "viewDailyNutritionInfo function started for user: " << user.username << endl;

    cout << "Daily Nutrition Information for " << user.username << ":\n";
    cout << "Recommended Calories: " << user.recommendedMacros.calories << " kcal" << endl;

    if (user.typeOfAccount == "premium") {
        cout << "Recommended Macros (Premium Account):" << endl;
        cout << "Protein: " << user.recommendedMacros.protein << " g" << endl;
        cout << "Carbohydrates: " << user.recommendedMacros.carbohydrates << " g" << endl;
        cout << "Fats: " << user.recommendedMacros.fats << " g" << endl;
    }

    time_t now = time(0);
    string mealsFile = BASE_USERS_FOLDER + user.username + MEALS_FILE_EXTENSION;
    string workoutsFile = BASE_USERS_FOLDER + user.username + WORKOUTS_FILE_EXTENSION;

    double currentCalories = 0.0, currentProtein = 0.0, currentCarbs = 0.0, currentFats = 0.0;
    double workoutCalories = 0.0;

    ifstream mealsInFile(mealsFile);
    if (mealsInFile.is_open()) {
        string line;
        while (getline(mealsInFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);
            size_t lastComma = line.find_last_of(',');

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || 
                pos4 == string::npos || pos5 == string::npos || lastComma == string::npos) {
                continue;
            }

            string timestampStr = line.substr(lastComma + 1);
            time_t mealTime = stol(timestampStr);

            if (areDatesEqual(now, mealTime)) {
                currentCalories += safeStod(line.substr(pos1 + 1, pos2 - pos1 - 1));
                currentProtein += safeStod(line.substr(pos3 + 1, pos4 - pos3 - 1));
                currentCarbs += safeStod(line.substr(pos4 + 1, pos5 - pos4 - 1));
                currentFats += safeStod(line.substr(pos5 + 1, lastComma - pos5 - 1));
            }
        }
        mealsInFile.close();
    } else {
        cerr << "Error: Could not open the meals file for reading.\n";
    }

    ifstream workoutsInFile(workoutsFile);
    if (workoutsInFile.is_open()) {
        string line;
        while (getline(workoutsInFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t lastComma = line.find_last_of(',');

            if (pos1 == string::npos || pos2 == string::npos || lastComma == string::npos) {
                continue;
            }

            string timestampStr = line.substr(lastComma + 1);
            time_t workoutTime = stol(timestampStr);

            if (areDatesEqual(now, workoutTime)) {
                workoutCalories += safeStod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            }
        }
        workoutsInFile.close();
    } else {
        cerr << "Error: Could not open the workouts file for reading.\n";
    }

    double remainingCalories = user.recommendedMacros.calories - currentCalories + workoutCalories;
    double remainingProtein = user.recommendedMacros.protein - currentProtein;
    double remainingCarbs = user.recommendedMacros.carbohydrates - currentCarbs;
    double remainingFats = user.recommendedMacros.fats - currentFats;

    cout << "\nCurrent Intake (Today):\n";
    cout << "Calories from Meals: " << currentCalories << " kcal\n";
    cout << "Calories Burned from Workouts: " << workoutCalories << " kcal\n";

    if (user.typeOfAccount == "premium") {
        cout << "Protein: " << currentProtein << " g\n";
        cout << "Carbohydrates: " << currentCarbs << " g\n";
        cout << "Fats: " << currentFats << " g\n";
    }

    cout << "\nRemaining Goals for the Day:\n";
    cout << "Calories: " << (remainingCalories > 0 ? remainingCalories : 0) << " kcal\n";

    if (user.typeOfAccount == "premium") {
        cout << "Protein: " << (remainingProtein > 0 ? remainingProtein : 0) << " g\n";
        cout << "Carbohydrates: " << (remainingCarbs > 0 ? remainingCarbs : 0) << " g\n";
        cout << "Fats: " << (remainingFats > 0 ? remainingFats : 0) << " g\n\n";
    }
}

bool addMealToFile(const string& username, Meal& meal, const string filename)
{
    ofstream outFile(filename, ios::app);

    if (!outFile) {
        cerr << "Error: Could not open the file for writing!\n";
        return false;
    }

    outFile << meal.name << ","
            << meal.calories << ","
            << meal.dayPeriodType << ","
            << meal.protein << ","
            << meal.carbs << ","
            << meal.fats << ","
            << meal.createdDateTime << "\n";

    outFile.close();

    return true;
}

bool addWorkoutToFile(const string& username, Workout& workout, const string filename)
{
    ofstream outFile(filename, ios::app);

    if (!outFile) {
        cerr << "Error: Could not open the file for writing!\n";
        return false;
    }

    outFile << workout.name << ","
            << workout.calories << ","
            << workout.createdDateTime << "\n";

    outFile.close();

    return true;
}

void addMeal(User& user)
{
    string fileName = BASE_USERS_FOLDER + user.username + MEALS_FILE_EXTENSION;
    Meal mealToAdd;

    cout << "Add Meal\n";

    cout << "What type of meal you want to add?(Breakfast, Lunch, Snack or Dinner)\n";
    cin >> mealToAdd.dayPeriodType;

    do {
        cout << "Name: ";
        cin.ignore();
        getline(cin, mealToAdd.name);

        if (doesMealExist(mealToAdd.name, time(0), fileName))
        {
            cerr << "Meal for today with this name already exists! Try again.\n";
        }
    } while (doesMealExist(mealToAdd.name, time(0), fileName));

    cout << "Calories: ";
    cin >> mealToAdd.calories;

    cout << "Protein: ";
    cin >> mealToAdd.protein;

    cout << "Carbs: ";
    cin >> mealToAdd.carbs;

    cout << "Fats: ";
    cin >> mealToAdd.fats;

    mealToAdd.createdDateTime = time(0);

    if (addMealToFile(user.username, mealToAdd, fileName))
    {
        cout << "Successfully added meal for " << user.username << "!\n";
    }
    else 
    {
        cout << "Failed to add meal for " << user.username << "!\n";
    }
}

void addWorkout(User& user)
{
    string fileName = BASE_USERS_FOLDER + user.username + WORKOUTS_FILE_EXTENSION;
    Workout workoutToAdd;

    cout << "Add Workout\n";

    do {
        cout << "Name: ";
        cin.ignore();
        getline(cin, workoutToAdd.name);

        if (doesWorkoutExist(workoutToAdd.name, time(0), fileName))
        {
            cerr << "Workout for today with this name already exists! Try again.\n";
        }
    } while (doesWorkoutExist(workoutToAdd.name, time(0), fileName));

    cout << "Calories: ";
    cin >> workoutToAdd.calories;

    workoutToAdd.createdDateTime = time(0);

    if (addWorkoutToFile(user.username, workoutToAdd, fileName))
    {
        cout << "Successfully added workout for " << user.username << "!\n";
    }
    else 
    {
        cout << "Failed to add workout for " << user.username << "!\n";
    }
}

void deleteAllInfoForDate(const string& fileName, const string& date) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << " for reading!\n";
        return;
    }

    string tempFileName = fileName + ".tmp";
    ofstream outFile(tempFileName); 
    if (!outFile) {
        cerr << "Error: Could not create temporary file " << tempFileName << "!\n";
        inFile.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        string extractedDate = extractDateFromLine(line);

        // If the date doesn't match, write the line to the temporary file
        if (extractedDate != date) {
            outFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        if (remove(fileName.c_str()) != 0) {
            cerr << "Error: Could not remove the original file " << fileName << "!\n";
        } else if (rename(tempFileName.c_str(), fileName.c_str()) != 0) {
            cerr << "Error: Could not rename the temporary file!\n";
        }
    } else {
        cout << "No records found for the date " << date << " in " << fileName << ".\n";
        remove(tempFileName.c_str()); // Remove temp file if no changes
    }
}

void deleteAllInfo(User& user)
{
    string date;
    cout << "Enter date to delete all info for the day('Year-Month-Day'): " << endl;
    cin >> date;

    string mealsFileName = BASE_USERS_FOLDER + user.username + MEALS_FILE_EXTENSION;
    string workoutsFileName = BASE_USERS_FOLDER + user.username + WORKOUTS_FILE_EXTENSION;

    deleteAllInfoForDate(mealsFileName, date);
    deleteAllInfoForDate(workoutsFileName, date);
}

void editWorkout(User& user)
{
    string fileName = BASE_USERS_FOLDER + user.username + WORKOUTS_FILE_EXTENSION;
    Workout workoutToEdit;

    cout << "Edit Workout\n";
    cout << "Enter the name of the workout you want to edit: ";
    cin.ignore();
    getline(cin, workoutToEdit.name);

    if (!doesWorkoutExist(workoutToEdit.name, time(0), fileName)) {
        cerr << "No workout with this name exists for today. Please add it first.\n";
        return;
    }

    cout << "Enter new workout name: ";
    getline(cin, workoutToEdit.name);

    cout << "Enter new calories burned: ";
    cin >> workoutToEdit.calories;

    workoutToEdit.createdDateTime = time(0);

    if (updateWorkoutInFile(workoutToEdit, fileName)) {
        cout << "Workout successfully updated for " << user.username << "!\n";
    } else {
        cout << "Failed to update the workout for " << user.username << "!\n";
    }
}

void editMeal(User& user)
{
    string fileName = BASE_USERS_FOLDER + user.username + MEALS_FILE_EXTENSION;
    Meal mealToEdit;

    cout << "Enter the name of the meal you want to edit: ";
    cin.ignore();
    getline(cin, mealToEdit.name);

    if (!doesMealExist(mealToEdit.name, time(0), fileName)) {
        cerr << "No meal with this name exists for today. Please add it first.\n";
        return;
    }

    cout << "Enter new calories: ";
    cin >> mealToEdit.calories;

    if (user.typeOfAccount == "premium"){
        cout << "Enter new protein: ";
        cin >> mealToEdit.protein;

        cout << "Enter new carbs: ";
        cin >> mealToEdit.carbs;

        cout << "Enter new fats: ";
        cin >> mealToEdit.fats;
    }

    mealToEdit.dayPeriodType = getMealPeriod(); 
    mealToEdit.createdDateTime = time(0);

    if (updateMealInFile(user.username, mealToEdit, fileName)) {
        cout << "Meal successfully updated for " << user.username << "!\n";
    } else {
        cout << "Failed to update the meal for " << user.username << "!\n";
    }
}

void editPersonalInfo(User& user)
{
    cout << "Editing user data for " << user.username << endl;

    updateUserInfo(user);
    displayUpdatedInfo(user);

    fstream file(USERS_FILE_NAME, ios::in | ios::out);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for editing.\n";
        return;
    }

    long long posToModify = findUserPosition(file, user.username);
    if (posToModify == -1) {
        cout << "User not found in the file.\n";
        file.close();
        return;
    }

    updateUserInFile(file, user, posToModify);
    cout << "User data updated successfully!\n";
    file.close();
}

vector<Workout> getWorkoutsForDay(const string& username, const string& date) {
    string fileName = "../Users/" + username + "-workouts.txt";
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error: Could not open the file " << fileName << " for reading!\n";
        return vector<Workout>();
    }

    vector<Workout> workoutsForDay;

    // Convert the given date to a timestamp range
    struct tm tm = {};
    strptime(date.c_str(), "%Y-%m-%d", &tm);
    time_t startOfDay = mktime(&tm);
    time_t endOfDay = startOfDay + 86400;

    string line;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            continue;
        }

        string name = line.substr(0, pos1);
        double calories = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        time_t createdDateTime = stoll(line.substr(pos2 + 1));

        Workout workout;

        // Check if the workout falls within the given day
        if (createdDateTime >= startOfDay && createdDateTime < endOfDay) {
            workout.name = name;
            workout.calories = calories;
            workout.createdDateTime = createdDateTime;
            workoutsForDay.push_back(workout);
        }
    }

    inFile.close();

    return workoutsForDay;
}

Meal* getMealsForDay(const string& username, const string& date, int& count) {
    string fileName = "../Users/" + username + "-meals.txt";
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error: Could not open the file " << fileName << " for reading!\n";
        count = 0;
        return nullptr;
    }

    Meal* mealsForDay = new Meal[20]; // Dynamically allocate an array
    count = 0;

    // Convert the given date to a timestamp range
    struct tm tm = {};
    strptime(date.c_str(), "%Y-%m-%d", &tm);
    time_t startOfDay = mktime(&tm);
    time_t endOfDay = startOfDay + 86400;

    string line;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t pos5 = line.find(',', pos4 + 1);
        size_t pos6 = line.find(',', pos5 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos ||
            pos4 == string::npos || pos5 == string::npos || pos6 == string::npos) {
            continue; // Skip malformed lines
        }

        string name = line.substr(0, pos1);
        double calories = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        string dayPeriodType = line.substr(pos2 + 1, pos3 - pos2 - 1);
        double protein = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
        double carbs = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
        double fats = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
        time_t createdDateTime = stoll(line.substr(pos6 + 1));

        // Check if the meal falls within the given day
        if (createdDateTime >= startOfDay && createdDateTime < endOfDay) {
            mealsForDay[count].name = name;
            mealsForDay[count].calories = calories;
            mealsForDay[count].protein = protein;
            mealsForDay[count].carbs = carbs;
            mealsForDay[count].fats = fats;
            mealsForDay[count].dayPeriodType = dayPeriodType;
            mealsForDay[count].createdDateTime = createdDateTime;
            count++;

            if (count >= 20) {
                break; // Stop if the array is full
            }
        }
    }

    inFile.close();

    return mealsForDay;
}


MacrosInfo calculateNutritionalInfoForDay(vector<Workout> workoutsForDay, Meal* mealsForDay, int mealsLimit) {
    MacrosInfo result;

    double calories = 0.0;
    double protein = 0.0;
    double carbs = 0.0;
    double fats = 0.0;

    for (int i = 0; i < workoutsForDay.size(); i++) {
        calories -= workoutsForDay.at(i).calories;
    }

    for (int i = 0; i < mealsLimit; i++) {
        if (mealsForDay[i].name.empty()) break; // Stop if an empty element is found
        calories += mealsForDay[i].calories;
        protein += mealsForDay[i].protein;
        carbs += mealsForDay[i].carbs;
        fats += mealsForDay[i].fats;
    }

    result.calories = calories;
    result.protein = protein;
    result.carbohydrates = carbs;
    result.fats = fats;

    return result;
}

// TODO
void visualizeDateData(User& user) {
    string date;
    cout << "Enter a date to get all the nutritional info ('Year-Month-Day'): " << endl;
    cin >> date;

    const int mealsLimit = 20;

    int mealCount = 0;

    vector<Workout> workoutsForDay = getWorkoutsForDay(user.username, date);
    Meal* mealsForDay = getMealsForDay(user.username, date, mealCount);

    // cout << mealsForDay[0].name << endl; // Test

    MacrosInfo calculatedNutritionalInfo = calculateNutritionalInfoForDay(workoutsForDay, mealsForDay, mealsLimit);

    if (user.typeOfAccount == "Premium") {
        cout << "Suggested calories: " << user.recommendedMacros.calories << endl;
        cout << "Suggested protein intake: " << user.recommendedMacros.protein << " gr.\n";
        cout << "Suggested carbs intake: " << user.recommendedMacros.carbohydrates << " gr.\n";
        cout << "Suggested fats intake: " << user.recommendedMacros.fats << " gr.\n";
        cout << "\n\n";

        cout << "Calories for " << date << ": " << calculatedNutritionalInfo.calories << endl;
        cout << "Protein for " << date << ": " << calculatedNutritionalInfo.protein << endl;
        cout << "Carbs for " << date << ": " << calculatedNutritionalInfo.carbohydrates << endl;
        cout << "Fats for " << date << ": " << calculatedNutritionalInfo.fats << endl;
        cout << "\n\n";

        cout << "Meals: \n";
        for (int i = 0; i < mealsLimit; i++) {
            if (mealsForDay[i].name.empty()) break; // Stop if no more meals
            cout << "Name: " << mealsForDay[i].name 
                 << "\tCalories: " << mealsForDay[i].calories 
                 << "\tProtein: " << mealsForDay[i].protein 
                 << "\tCarbs: " << mealsForDay[i].carbs
                 << "\tFats: " << mealsForDay[i].fats
                 << endl;
        }
    } else {
        cout << "Suggested calories: " << user.recommendedMacros.calories << endl;
        cout << "\n\n";

        cout << "Calories for " << date << ": " << calculatedNutritionalInfo.calories << endl;
        cout << "\n\n";

        cout << "Meals: \n";
        for (int i = 0; i < mealsLimit; i++) {
            if (mealsForDay[i].name.empty()) break; // Stop if no more meals
            cout << mealsForDay[i].name << ", " << mealsForDay[i].calories << endl;
        }
    }

    cout << "Workouts: \n";
    for (int i = 0; i < workoutsForDay.size(); i++) {
        cout << workoutsForDay.at(i).name << ", " << workoutsForDay.at(i).calories << endl;
    }

    delete[] mealsForDay;
}

void showLoggedMenu(User& user)
{
    int userInput = 0;
    bool isLoggedout = false;
    bool isChoiceValid = true;

    cout << "\nHello, " << user.username << "!\n" << endl;

    do
    {
        showCurrentNutrition(user);

        cout << "\n\nSelect one of the options below:\n";
        cout << "1. View daily nutritional info\n";
        cout << "2. Add Meal\n";
        cout << "3. Add Workout\n";
        cout << "4. Delete all info for a selected date\n";
        cout << "5. Edit today's workout\n";
        cout << "6. Edit today's meal\n";
        cout << "7. Edit personal info\n";
        cout << "8. View personal info\n";
        cout << "9. Show nutritional info for a selected date\n";
        cout << "10. Logout\n";

        cout << "Enter your choice: ";
        do
        {
            cin >> userInput;

            if (userInput <= 0 || userInput > 10)
            {
                isChoiceValid = false;
                cout << "Invalid choice! Try again";
            }
            else
            {
                isChoiceValid = true;
            }
        } while (!isChoiceValid);

        switch (userInput)
        {
            case 1:
                viewDailyNutritionInfo(user); // TODO
                break;
            case 2:
                addMeal(user);
                break;
            case 3:
                addWorkout(user); // TODO
                break;
            case 4:
                deleteAllInfo(user);
                break;
            case 5:
                editWorkout(user);
                break;
            case 6:
                editMeal(user);
                break;
            case 7:
                editPersonalInfo(user);
                break;
            case 8:
                showUserInfo(user);
                break;
            case 9:
                visualizeDateData(user);
                break;
            case 10:
            default:
                isLoggedout = true;
                return;
        }
    } while (!isLoggedout);
}

void login()
{
    User userToLogin;
    loginMenu(userToLogin);
    
    if (userToLogin.username.empty()) {
        cerr << "Login failed!\n";
        return;
    }

    showLoggedMenu(userToLogin);
}

void showMainMenu()
{
    int userInput = 0;
    bool isExited = false;
    bool isChoiceValid = true;

    cout << "\nWelcome to MyFitnessPal!\n\n";

    do
    {
        cout << "Select one of the options below:\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit the program\n";

        cout << "Enter your choice: ";
        do
        {
            cin >> userInput;

            if (userInput <= 0 || userInput > 3)
            {
                isChoiceValid = false;
                cerr << "Invalid choice! Try again";
            }
            else
            {
                isChoiceValid = true;
            }
        } while (!isChoiceValid);

        switch (userInput)
        {
            case 1:
                login();
                break;
            case 2:
                registration();
                break;
            case 3:
            default:
                isExited = true;
                cout << "See you soon, bye!\n";
                return;
        }
    } while (!isExited);
}

int main()
{
    showMainMenu();

    return 0;
}
