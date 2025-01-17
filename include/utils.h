#include <string>

void toLowerCase(string &str);

bool isUsernameValid(string username);
bool isPasswordValid(string password);
bool isAgeValid(int age);
bool isHeightValid(double height);
bool isWeightValid(double weight);
bool isGenderValid(string gender);
bool isLevelOfActivityValid(string levelOfActivity);
bool isGoalValid(string goal);
bool isTypeOfAccountValid(string typeOfAccount);
bool isWeeklyWeightDiffValid(double weightDiff);

bool doesUserExist(const string& username, const string& filename);
bool doesUserPasswordMatch(const string& username, const string& password, const string& filename);

double calculateBMR(string gender, double weight, double height, int age);
double calculateMaintenanceCalories(string gender, double weight, double height, int age, string levelOfActivity);
double calculateProtein(double calories, string goal);
double calculateCarbs(double calories, string goal);
double calculateFats(double calories, string goal);

bool areDatesEqual(time_t time1, time_t time2);
bool doesMealExist(const string mealName, time_t createdDateTime, const string filename);
bool doesWorkoutExist(const string workoutName, time_t createdDateTime, const string filename);
string timeToDateString(time_t timestamp);
string extractDateFromLine(const string& line);

double calculateTotalCaloriesForToday(const string& mealsFile, const string& workoutsFile);
double calculateTotalProteinFromMeals(const string& mealsFile);
double calculateTotalCarbsFromMeals(const string& mealsFile);
double calculateTotalFatsFromMeals(const string& mealsFile);
void recalculateUserMacros(User& user);

void clearInputBuffer();
void updateUserInfo(User& user);
double getValidatedWeight();
string getValidatedGoal();
void displayUpdatedInfo(const User& user);
long long findUserPosition(fstream& file, const string& username);
void updateUserInFile(fstream& file, const User& user, long long posToModify);
bool updateMealInFile(const string& username, Meal& updatedMeal, const string filename);
string getMealPeriod();
bool updateWorkoutInFile(Workout& updatedWorkout, const string& filename);
