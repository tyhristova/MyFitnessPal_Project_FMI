# MyFitnessPal_Project_FMI

## Overview

MyFitnessPal is a console-based fitness tracking application that allows users to register, log in, and manage their daily nutrition and workouts. It provides functionalities to track meals, workouts, and personal information while offering an intuitive menu-driven interface.

## Features

### Main Menu

Upon launching the application, users are presented with the following options:

1. **Login** - Allows an existing user to log into the system.

2. **Register** - Enables a new user to create an account.

3. **Exit the program** - Terminates the application.

## User Authentication

* **Login**: Prompts the user to enter credentials. If successful, they gain access to the logged-in menu.

* **Registration**: Collects user information, calculates recommended calorie intake and macros, and stores user data securely.

## Logged-in Menu

After logging in, users can perform the following actions:

1. **View daily nutritional info** - Displays current day’s calorie and macro intake.

2. **Add Meal** - Logs a new meal and updates nutritional values.

3. **Add Workout** - Records a workout session for the user.

4. **Delete all info for a selected date** - Removes all meal and workout data for a specific day.

5. **Edit today's workout** - Modifies workout details for the current day.

6. **Edit today's meal** - Updates meal details for the current day.

7. **Edit personal info** - Allows users to modify personal details like weight, height, and goals.

8. **View personal info** - Displays stored user information.

9. **Show nutritional info for a selected date** - Fetches and displays nutrition data for a chosen date.

10. **Logout** - Exits the logged-in session and returns to the main menu.

## File Management

* User data is stored in a file to maintain persistence.

* Each user has personalized files for tracking their progress.

## Error Handling

* Invalid input detection in menus.

* Error messages for incorrect login attempts.

* Warnings for duplicate registrations.

## How to Run

1. Compile the project using g++:

```bash
g++ -o MyFitnessPal main.cpp utils.cpp
```

2. Run the executable:

```bash
./MyFitnessPal
```