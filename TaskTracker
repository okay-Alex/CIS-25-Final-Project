#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

// The program will center around Tasks, they store simple pieces of information and are saved in text files

class Task {
private:
    string date;
    string tag;
    string name;
    bool archived;

public:
    Task(string n) {
        name = n;
        date = "";
        tag = "Misc";
        archived = false;
    }

    Task(string n, string d) {
        name = n;
        date = d;
        tag = "Misc";
        archived = false;
    }

    Task(string n, string d, string t) {
        name = n;
        date = d;
        tag = t;
        archived = false;
    }

    string getDate() {
        return date;
    }

    string getTag() {
        return tag;
    }

    string getName() {
        return name;
    }

    bool isArchived() {
        return archived;
    }

    void updateDate(string d) {
        date = d;
    }

    void updateTag(string t) {
        tag = t;
    }

    void updateArchived(bool a) {
        archived = a;
    }
};

// Define a vector to hold our tasks

std::vector<Task> currentTasks;

int fileCount = 0;

// Gets the user's name, and also fetches the file count

string getName() {
    ifstream data("Data.txt");
    string line;
    string line2;

    getline(data, line);
    getline(data, line2);

    fileCount = atoi(line2.c_str());

    if (line.length() == 0) {
        std::cout << "Please enter your name: " << endl;
        cin >> line;
        std::cout << endl;
    }

    return line;
}

// Show's a task's information on the console

void showTask(Task currentTask) {
    string isCompletedText;

    if (currentTask.isArchived()) {
        isCompletedText = "Yes";
    }
    else {
        isCompletedText = "No";
    }

    cout << currentTask.getName() << endl;
    cout << "Due: " + currentTask.getDate() << endl;
    cout << "Category: " + currentTask.getTag() << endl;
    cout << "Completed?: " + isCompletedText << endl;
}

// Shows all tasks that fit the sort criteria

void showTasks(string tag, bool archived) {
    for (int i = 0; i < currentTasks.size(); i++) {
        Task currentTask = currentTasks[i];
        if (tag == "" || tag == currentTask.getTag()) {
            if (currentTask.isArchived() == archived) {
                cout << endl;
                showTask(currentTask);
            }
        }
    }
}

// Saves tasks into files

void saveTasks() {
    for (int i = 0; i < currentTasks.size(); i++) {
        Task toSave = currentTasks[i];

        fstream taskFile("Task" + to_string(i) + ".txt", ios::out | ios::trunc);

        taskFile << toSave.getName() << endl;
        taskFile << toSave.getDate() << endl;
        taskFile << toSave.getTag() << endl;
        taskFile << (toSave.isArchived() ? "true" : "false") << endl;

        taskFile.close();
    }
}

// Driver function, has application loop and loads initial data along with saving it at the end.

int main() {
    string name = getName();
    bool archivedMode = false;
    string tag = "";
    string dateFilter = "soonest";

    std::cout << "Welcome to your Task Tracker, " << name << "!" << std::endl;

    // Get Tasks From Files
    cout << "Tasks loaded: " << fileCount << endl;

    for (int i = 0; i < fileCount; i++) {
        fstream taskFile("Task" + to_string(i) + ".txt");
        string name, date, tag;
        string archivedStr;

        getline(taskFile, name);
        getline(taskFile, date);
        getline(taskFile, tag);
        getline(taskFile, archivedStr);

        bool archived = (archivedStr == "true" && true || false);

        Task newTask = Task(name, date, tag);
        newTask.updateArchived(archived);

        currentTasks.push_back(newTask);

        taskFile.close();
    }

    // Begin Application Loop
    while (true) {
        string taskName;
        string taskTag;
        string taskDate;
        string archiveText;
        bool archiveSuccess = false;

        cout << endl;
        cout << "(1) Look at current tasks with applied filters" << endl;
        cout << "(2) Filter by tag" << endl;
        cout << "(3) Filter by date" << endl;
        cout << "(4) Create task" << endl;
        cout << "(5) Archive task" << endl;
        cout << "(6) Show archived" << endl;
        cout << "(7) Exit" << endl;
        cout << endl;

        int input;
        cin >> input;

        switch (input) {
        case 1:
            showTasks(tag, archivedMode);
            break;
        case 2:
            if (tag == "") {
                cout << "There is not preset tag, what would you like to set it to?: " << endl;
            }
            else {
                cout << "The current tag is: " + tag + ", what would you like to change it to? (n/a): " << endl;
            }
            cin >> tag;
            if (tag == "n/a") {
                tag = "";
            }
            break;
        case 3:
            cout << "The tasks are currently sorted by: " + dateFilter + ", what would you like to change it to?" << endl;
            cout << "(1) For soonest" << endl;
            cout << "(2) For latest" << endl;

            int input;
            cin >> input;

            switch (input) {
            case 1:
                dateFilter = "soonest";
                break;
            case 2:
                dateFilter = "latest";
                break;
            default:
                // nothing
                cout << "Please enter a valid input next time!" << endl;
                break;
            }
            break;
        case 4:
            cin.ignore();

            cout << "Enter the task name: " << endl;
            getline(cin, taskName);

            cout << "Enter the task due date (MM-DD-YYYY): " << endl;
            cin >> taskDate;

            cout << "Enter the task tag (default is Misc): " << endl;
            cin >> taskTag;

            currentTasks.push_back(Task(taskName, taskDate, taskTag));

            cout << "Your task has been succesfully created!" << endl;
            break;
        case 5:
            cin.ignore();

            cout << "Enter the task name: " << endl;
            getline(cin, taskName);

            for (int i = 0; i < currentTasks.size(); i++) {
                if (currentTasks[i].getName() == taskName) {
                    archiveSuccess = true;
                    currentTasks[i].updateArchived(true);
                }
            }

            if (archiveSuccess) {
                cout << taskName + " has been succesfully archived!" << endl;
            }
            else {
                cout << taskName + " does not exist!" << endl;
            }
            break;
        case 6:
            if (archivedMode) {
                archiveText = "Archived";
            }
            else {
                archiveText = "Not Archived";
            }

            cout << "The tasks currently shown are: " + archiveText << endl;
            cout << "(1) Switch to show archived" << endl;
            cout << "(2) Switch to show non-archived \n" << endl;

            int choice;
            cin >> choice;
            
            if (choice == 1) {
                archivedMode = true;
            }
            else if (choice == 2) {
                archivedMode = false;
            }
            else {
                cout << "Please try again!" << endl;
            }

            break;
        case 7:
            break;
        default:
            cout << "Try again, that wasn't a valid input." << endl;
            break;
        }

        if (input == 7) {
            break;
        }
    }

    saveTasks();

    // Save tasks size
    fstream savingData("Data.txt", ios::out | ios::trunc);

    savingData << name << endl;
    savingData << currentTasks.size() << endl;

    savingData.close();
}
