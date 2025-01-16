// Input fields
const int INPUT_FIELDS_COUNT = 9;
const int USERNAME_INPUT_FIELD = 0;
const int PASSWORD_INPUT_FIELD = 1;
const int AGE_INPUT_FIELD = 2;
const int GENDER_INPUT_FIELD = 3;
const int HEIGHT_INPUT_FIELD = 4;
const int WEIGHT_INPUT_FIELD = 5;
const int LEVEL_OF_ACTIVITY_INPUT_FIELD = 6;
const int GOAL_INPUT_FIELD = 7;
const int TYPE_OF_ACCOUNT_INPUT_FIELD = 8;

// Constraints
const int USERNAME_LENGTH = 6;
const int PASSWORD_LENGTH = 8;
const int AGE_MIN = 13;
const int AGE_MAX = 120;
const int HEIGHT_MIN = 50;
const int HEIGHT_MAX = 300;
const int WEIGHT_MIN = 20;
const int WEIGHT_MAX = 500;

// BMR coefficients
const double BMR_MALE_COEFFICIENT = 88.362;
const double BMR_MALE_WEIGHT_COEFFICIENT = 13.397;
const double BMR_MALE_HEIGHT_COEFFICIENT = 4.799;
const double BMR_MALE_AGE_COEFFICIENT = 5.677;

const double BMR_FEMALE_COEFFICIENT = 447.593;
const double BMR_FEMALE_WEIGHT_COEFFICIENT = 9.247;
const double BMR_FEMALE_HEIGHT_COEFFICIENT = 3.098;
const double BMR_FEMALE_AGE_COEFFICIENT = 4.330;

// Activity coefficients
const double SEDENTARY_ACTIVITY_COEFFICIENT = 1.2;
const double LOW_ACTIVITY_COEFFICIENT = 1.375;
const double MODERATE_ACTIVITY_COEFFICIENT = 1.55;
const double ACTIVE_ACTIVITY_COEFFICIENT = 1.725;
const double VERY_ACTIVE_ACTIVITY_COEFFICIENT = 1.9;

// Calories differences
const double QUARTER_DIFF_CALS = 275.0;
const double HALF_DIFF_CALS = 550.0;
const double THREE_QUARTERS_DIFF_CALS = 825.0;
const double KILO_DIFF_CALS = 1100.0;

// Kilogram differences
const double QUARTER_DIFF_KGS = 0.25;
const double HALF_DIFF_KGS = 0.5;
const double THREE_QUARTERS_DIFF_KGS = 0.75;
const double KILO_DIFF_KGS = 1.0;

const int DAYS_PER_WEEK = 7;

// File names
const std::string USERS_FILE_NAME = "../Users/UsersList.txt";
const std::string BASE_USERS_FOLDER = "../Users/";
const std::string MEALS_FILE_EXTENSION = "-meals.txt";
const std::string WORKOUTS_FILE_EXTENSION = "-workouts.txt";