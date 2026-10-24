#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper to Automatically Create the Input File

/**
 * Creates Input.csv on disk if running in online environments like OnlineGDB
 */
void CreateInputFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "CSCI100,Introduction to Computer Science\n";
        file << "CSCI101,Introduction to Programming in C++,CSCI100\n";
        file << "CSCI200,Data Structures,CSCI101\n";
        file << "MATH201,Discrete Mathematics\n";
        file << "CSCI300,Introduction to Algorithms,CSCI200,MATH201\n";
        file << "CSCI301,Advanced Programming in C++,CSCI101\n";
        file << "CSCI350,Operating Systems,CSCI300\n";
        file << "CSCI400,Large Software Development,CSCI301,CSCI350\n";
        file.close();
    }
}

// Data Structure Definitions

// Structure to hold course information
struct Course {
    string courseNumber;          // Unique identifier (e.g., CSCI100)
    string title;                 // Course name
    vector<string> prerequisites; // List of prerequisite course numbers
};

// Internal node structure for the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Parameterized constructor
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

// Binary Search Tree class definition
class BinarySearchTree {

private:
    Node* root;

    // Helper functions for recursion and internal memory management
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyRecursive(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    void PrintInOrder();
    Course Search(string courseNumber);
    bool IsEmpty();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor to free dynamically allocated tree memory
 */
BinarySearchTree::~BinarySearchTree() {
    destroyRecursive(root);
    root = nullptr;
}

/**
 * Recursive helper to deallocate nodes in post-order sequence
 */
void BinarySearchTree::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

/**
 * Check if the binary search tree has no nodes
 */
bool BinarySearchTree::IsEmpty() {
    return root == nullptr;
}

/**
 * Insert a course into the tree
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

/**
 * Recursive helper to place a new node in alphanumeric order by courseNumber
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber.compare(node->course.courseNumber) < 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        } else {
            addNode(node->left, course);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        } else {
            addNode(node->right, course);
        }
    }
}

/**
 * Public method to trigger in-order traversal
 */
void BinarySearchTree::PrintInOrder() {
    inOrder(root);
}

/**
 * Recursive helper for in-order traversal (Left, Root, Right)
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrder(node->right);
    }
}

/**
 * Search the tree for a course matching courseNumber
 */
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber.compare(courseNumber) == 0) {
            return current->course;
        }

        if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    Course course;
    return course;
}

// Helper Utilities & Input Parsing

/**
 * Convert string to uppercase for case-insensitive input matching
 */
string ToUpper(string str) {
    string result = str;
    for (char& c : result) {
        c = toupper(c);
    }
    return result;
}

/**
 * Trim leading and trailing whitespace from string
 */
string Trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

/**
 * Custom CSV string splitting function
 */
vector<string> Split(const string& line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(Trim(token));
    }
    return tokens;
}

/**
 * Load CSV file data into Binary Search Tree using two-pass validation
 */
bool LoadCourses(const string& csvPath, BinarySearchTree* bst) {
    ifstream file(csvPath);

    if (!file.is_open()) {
        cout << "Error: Could not open file " << csvPath << endl;
        return false;
    }

    vector<Course> parsedCourses;
    vector<string> validCourseNumbers;
    string line;

    // PASS 1: Read lines, parse parameters
    while (getline(file, line)) {
        line = Trim(line);
        if (line.empty()) {
            continue;
        }

        vector<string> tokens = Split(line, ',');

        if (tokens.size() < 2) {
            cout << "Format Error: Line has fewer than 2 parameters: " << line << endl;
            file.close();
            return false;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        parsedCourses.push_back(course);
        validCourseNumbers.push_back(course.courseNumber);
    }

    file.close();

    // PASS 2: Validate prerequisite existence
    for (const Course& course : parsedCourses) {
        for (const string& prereq : course.prerequisites) {
            bool found = false;
            for (const string& validNum : validCourseNumbers) {
                if (prereq == validNum) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Validation Error: Prerequisite " << prereq 
                     << " for course " << course.courseNumber 
                     << " does not exist in dataset." << endl;
                return false;
            }
        }
    }

    for (const Course& course : parsedCourses) {
        bst->Insert(course);
    }

    cout << "Data successfully loaded into Binary Search Tree." << endl;
    return true;
}

/**
 * Display specific course details and prerequisite titles
 */
void DisplayCourseInformation(BinarySearchTree* bst, const string& courseKey) {
    string searchKey = ToUpper(Trim(courseKey));
    Course course = bst->Search(searchKey);

    if (!course.courseNumber.empty()) {
        cout << course.courseNumber << ", " << course.title << endl;

        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "Course " << searchKey << " not found." << endl;
    }
}

// Main Application Driver

int main(int argc, char* argv[]) {
    string csvPath = "Input.csv";

    // Auto-generate Input.csv on disk for OnlineGDB
    CreateInputFile(csvPath);

    BinarySearchTree* bst = new BinarySearchTree();
    string userChoiceStr;
    string searchKey;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> userChoiceStr;

        try {
            choice = stoi(userChoiceStr);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
        case 1:
            LoadCourses(csvPath, bst);
            break;

        case 2:
            if (bst->IsEmpty()) {
                cout << "Please load course data first (Option 1)." << endl;
            } else {
                cout << "Here is a sample schedule:" << endl;
                bst->PrintInOrder();
            }
            break;

        case 3:
            if (bst->IsEmpty()) {
                cout << "Please load course data first (Option 1)." << endl;
            } else {
                cout << "What course do you want to know about? ";
                cin >> searchKey;
                DisplayCourseInformation(bst, searchKey);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << userChoiceStr << " is not a valid option." << endl;
            break;
        }
    }

    delete bst;
    return 0;
}