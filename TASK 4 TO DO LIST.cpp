#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <limits>

namespace TodoList {

    using namespace std;

    // Define a structure for tasks
    struct Task {
        string description;
        bool completed;
        time_t datetime;
    };

    // Function to add a task to the list
    void addTask(vector<Task>& tasks, const string& description, time_t datetime) {
        tasks.push_back({description, false, datetime});
        cout << "Task added: " << description << endl;
    }

    // Function to display the list of tasks
    void viewTasks(vector<Task>& tasks) {
        if (tasks.empty()) {
            cout << "No tasks in the list." << endl;
            return;
        }
        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". ";
            cout << (tasks[i].completed ? "[X] " : "[ ] ");
            cout << tasks[i].description << " (Time: " << ctime(&tasks[i].datetime) << ")";
        }
    }

    // Function to edit a task description
    void editTaskDescription(vector<Task>& tasks, size_t index, const string& newDescription) {
        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].description = newDescription;
            cout << "Task description updated: " << tasks[index - 1].description << endl;
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    // Function to toggle task completion status
    void toggleTaskCompletion(vector<Task>& tasks, size_t index) {
        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].completed = !tasks[index - 1].completed;
            cout << "Task completion status toggled." << endl;
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    // Function to remove a task from the list
    void removeTask(vector<Task>& tasks, size_t index) {
        if (index >= 1 && index <= tasks.size()) {
            cout << "Task removed: " << tasks[index - 1].description << endl;
            tasks.erase(tasks.begin() + index - 1);
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    // Function to sort tasks by completion status
    void sortTasksByCompletion(vector<Task>& tasks) {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            if (a.completed && !b.completed) {
                return false;
            } else if (!a.completed && b.completed) {
                return true;
            } else {
                return a.description < b.description;
            }
        });
        cout << "Tasks sorted by completion status." << endl;
    }

    // Function to display completed tasks
    void displayCompletedTasks(vector<Task>& tasks) {
        cout << "Completed Tasks:" << endl;
        bool found = false;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].completed) {
                cout << i + 1 << ". ";
                cout << tasks[i].description << " (Time: " << ctime(&tasks[i].datetime) << ")";
                found = true;
            }
        }
        if (!found) {
            cout << "No completed tasks found." << endl;
        }
    }

    // Function to display the menu options
    void displayMenu() {
        cout << "Menu:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Edit Task Description" << endl;
        cout << "4. Toggle Task Completion Status" << endl;
        cout << "5. Remove Task" << endl;
        cout << "6. Sort Tasks by Completion Status" << endl;
        cout << "7. Choose Completed Tasks" << endl;
        cout << "8. Quit" << endl;
    }

    // Function to handle user input and perform actions based on the input
    void handleInput(vector<Task>& tasks) {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        switch (choice) {
            case 1: {
                string description;
                time_t datetime = time(0); // Get current time
                cout << "Enter task description: ";
                cin.ignore(); // Ignore the newline character left in the input buffer
                getline(cin, description);
                addTask(tasks, description, datetime);
                break;
            }
            case 2:
                viewTasks(tasks);
                break;
            case 3: {
                size_t index;
                cout << "Enter task index to edit description: ";
                cin >> index;
                string newDescription;
                cout << "Enter new task description: ";
                cin.ignore(); // Ignore the newline character left in the input buffer
                getline(cin, newDescription);
                editTaskDescription(tasks, index, newDescription);
                break;
            }
            case 4: {
                size_t index;
                cout << "Enter task index to toggle completion status: ";
                cin >> index;
                toggleTaskCompletion(tasks, index);
                break;
            }
            case 5: {
                size_t index;
                cout << "Enter task index to remove: ";
                cin >> index;
                removeTask(tasks, index);
                break;
            }
            case 6:
                sortTasksByCompletion(tasks);
                break;
            case 7:
                displayCompletedTasks(tasks);
                return; // Return to the main menu after displaying completed tasks
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

} // namespace TodoList

int main() {
    using namespace TodoList;

    vector<Task> tasks;

    cout << "Welcome to Todo List!" << endl;

    bool quit = false;
    while (!quit) {
        displayMenu();
        handleInput(tasks);
        cout << endl;
    }

    return 0;
}
