#include <iostream>
#include <string>
using namespace std;

// Structure for a Task Node
struct Task {
    int id;
    string description;
    int priority;
    Task* next;

    Task(int taskId, string taskDesc, int taskPriority) {
        id = taskId;
        description = taskDesc;
        priority = taskPriority;
        next = nullptr;
    }
};

// Task Manager Class
class TaskManager {
private:
    Task* head;
public:
    TaskManager() { head = nullptr; }

    // Function to add a new task in order of priority
    void addTask(int id, string description, int priority) {
        Task* newTask = new Task(id, description, priority);
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next && temp->next->priority >= priority) {
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks available!\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->id << "\n";
        delete temp;
    }

    // Function to remove a task by ID
    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available!\n";
            return;
        }
        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task removed successfully!\n";
            return;
        }
        Task* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }
        if (!temp->next) {
            cout << "Task not found!\n";
            return;
        }
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task removed successfully!\n";
    }

    // Function to display all tasks
    void displayTasks() {
        if (!head) {
            cout << "No tasks available!\n";
            return;
        }
        Task* temp = head;
        cout << "\nTask List:\n";
        while (temp) {
            cout << "ID: " << temp->id << " | Description: " << temp->description << " | Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    TaskManager tm;
    int choice, id, priority;
    string description;

    while (true) {
        cout << "\nTask Management System:\n";
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore(); // To ignore newline character
                cout << "Enter Task Description: ";
                getline(cin, description);
                cout << "Enter Task Priority: ";
                cin >> priority;
                tm.addTask(id, description, priority);
                break;
            case 2:
                tm.displayTasks();
                break;
            case 3:
                tm.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                tm.removeTaskById(id);
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
