#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

// The program will center around Tasks, they store simple pieces of information and are saved in text files

// Task Class
// Attributes:

// date (string) - stores date in format: MM-DD-YYYY
// tag (string) - task's tag (default/standard tag is Misc)
// name (string) - tasks's name
// posInVector (int) - a task's position in the currentTasks vector
// archived (bool) - determines if a task is completed (true = yes, false = no) and will be shown by default (true = no, false = yes)

class Task {
private:
    string date;
    string tag;
    string name;
    int posInVector;
    bool archived;

public:
    Task(string n) {
        name = n;
        date = "";
        tag = "Misc";
        posInVector = -1;
        archived = false;
    }

    Task(string n, string d) {
        name = n;
        date = d;
        tag = "Misc";
        posInVector = -1;
        archived = false;
    }

    Task(string n, string d, string t) {
        name = n;
        date = d;
        tag = t;
        posInVector = -1;
        archived = false;
    }

    // Show's a task's information on the console

    void show() {
        string isCompletedText;

        if (archived) {
            isCompletedText = "Yes";
        }
        else {
            isCompletedText = "No";
        }

        cout << name << endl;
        cout << "Due: " + date << endl;
        cout << "Category: " + tag << endl;
        cout << "Completed?: " + isCompletedText << endl;
    }

    // Method to save this task in its designated file

    void save() {
        fstream taskFile("Task" + to_string(posInVector) + ".txt", ios::out | ios::trunc);

        taskFile << name << endl;
        taskFile << date << endl;
        taskFile << tag << endl;
        taskFile << (archived ? "true" : "false") << endl;

        taskFile.close();
    }

    string getDate() const {
        return date;
    }

    string getTag() const {
        return tag;
    }

    string getName() const {
        return name;
    }

    int getPosInVector() const {
        return posInVector;
    }

    bool isArchived() const {
        return archived;
    }

    void setPosInVector(int p) {
        posInVector = p;
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

// Define variables to store date filter sort and file count
string dateFilter = "soonest";
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

// Function to parse date string into comparable number
int parseDate(string date) {
    int year = stoi(date.substr(6, 9));
    int month = stoi(date.substr(0, 2));
    int day = stoi(date.substr(3, 5));

    int secondsFromYear = (year - 2025) * 31536000;
    int secondsFromMonth = month * 2592000;
    int secondsFromDay = day * 86400;

    return (secondsFromYear + secondsFromMonth + secondsFromDay);
}


bool compare(const Task &a, const Task &b) {
    int dateA = parseDate(a.getDate());
    int dateB = parseDate(b.getDate());
    
    return dateFilter == "soonest" ? dateA < dateB : dateA > dateB;
}

// Shows all tasks that fit the sort criteria
void showTasks(string tag, bool archived) {
    std::vector<Task> tasksToShow;
    // Filter tasks by tag
    for (int i = 0; i < currentTasks.size(); i++) {
        Task currentTask = currentTasks[i];
        if (tag == "" || tag == currentTask.getTag()) {
            if (currentTask.isArchived() == archived) {
                tasksToShow.push_back(currentTask);
            }
        }
    }
    // Sort tasks by soonest or latest
    std::sort(tasksToShow.begin(), tasksToShow.end(), compare);
    // Display tasks
    for (int i = 0; i < tasksToShow.size(); i++) {
        cout << endl;
        tasksToShow[i].show();
    }
}

// Saves tasks into files
void saveTasks() {
    for (int i = 0; i < currentTasks.size(); i++) {
        Task toSave = currentTasks[i];
        toSave.save();
    }
}

// Driver function, has application loop and loads initial data along with saving it at the end.
int main() {
    string name = getName();
    bool archivedMode = false;
    string tag = "";

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
        newTask.setPosInVector(i);

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

        // Print out options for the user

        cout << endl;
        cout << "(1) Look at current tasks with applied filters" << endl;
        cout << "(2) Filter by tag" << endl;
        cout << "(3) Sort by date" << endl;
        cout << "(4) Create task" << endl;
        cout << "(5) Archive task" << endl;
        cout << "(6) Show archived" << endl;
        cout << "(7) Exit" << endl;
        cout << endl;

        int input;
        cin >> input;

        // Switch case for each of the options designated above

        
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
            currentTasks[currentTasks.size() - 1].setPosInVector(currentTasks.size() - 1);

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

        // An input of 7 will end the application loop

        if (input == 7) {
            break;
        }
    }

    // Save Tasks into long term storage

    saveTasks();

    // Save username and amount of tasks in data file

    fstream savingData("Data.txt", ios::out | ios::trunc);

    savingData << name << endl;
    savingData << currentTasks.size() << endl;

    savingData.close();
}
