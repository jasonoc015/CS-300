//============================================================================
// Name        : Project 2
// Author      : Jason O'Connell
// Version     : 1.0
// Description : Project 2
//============================================================================

#include <iostream>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a class to hold the course information to hold the 
class Course {
private:
public:
    string courseCode;
    string courseName;
    vector<string> prereqs;
    Course();
    Course(string courseCode, string courseName, vector<string> prereqs);

};

/**
* Public default constuctor for Course class
*/
Course::Course() {
}

/**
* Public constuctor for Course class
* 
* @param courseCode The unique code for that course
* @param courseName The name of that course
* @param prereqs A vector of prerequisite courses
*/
Course::Course(string courseCode, string courseName, vector<string> prereqs) {
    this->courseCode = courseCode;
    this->courseName = courseName;
    this->prereqs = prereqs;
}

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void destroyNode(Node* node);
    Node* removeNode(Node* node, string courseCode);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string courseCode);
    Course Search(string courseCode);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    destroyNode(root);
}


/**
 * Recursive funtion to destroy nodes
 *
 * @param node Current node in tree
 */
void BinarySearchTree::destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseCode) {
    // remove node root courseID
    this->removeNode(root, courseCode);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseCode) {
    // set current node equal to root
    Node* current = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseCode.compare(courseCode) == 0) {
            return current->course;
        }
        // if course is smaller than current node then traverse left
        if (courseCode.compare(current->course.courseCode) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseCode.compare(course.courseCode) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        else {
            // else recurse down the left node
            this->addNode(node->left, course);
        }
    }
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes left
            node->right = new Node(course);
        }
        else {
            // else recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

/**
 * Remove a node
 *
 * @param node Current node in tree
 * @param course course to be added
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    //if this node is null then return
    if (node == nullptr) {
        return node;
    }

    // recurse down left subtree
    if (courseId.compare(node->course.courseCode) < 0) {
        node->left = removeNode(node->left, courseId);
    }
    //recurse down right subtree
    else if (courseId.compare(node->course.courseCode) > 0) {
        node->right = removeNode(node->right, courseId);
    }
    else {
        // no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // one child left
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // one child right
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseCode);
        }
    }
    return node;
}

/**
* Print the tree in order
* 
* @param node a pointer to a node
*/
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output courseID, title, amount, fund
        cout << node->course.courseCode << ", " << node->course.courseName << endl;
        //InOder right
        inOrder(node->right);
    }
}

/**
* Print the tree in post order
* 
* @param node a pointer to a node
*/
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseID, title, amount, fund
        cout << node->course.courseCode << ", " << node->course.courseName << endl;
    }
}

/**
* Print the tree in pre order
* 
* @param node a pointer to a node
*/
void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output courseID, title, amount, fund
        cout << node->course.courseCode << ", " << node->course.courseName << endl;
        //preOrder left
        preOrder(node->left);
        //preOrder right    
        preOrder(node->right);
    }
}

/**
* Print out a course and its prerequisites
* 
* @param course A course instance to print
*/
void displayCourse(Course course) {
    cout << course.courseCode << ", " << course.courseName << endl;
    cout << "Prerequisites: ";
    for (int i = 0; i < course.prereqs.size(); i++) {
        if (i == course.prereqs.size() - 1) {
            cout << course.prereqs.at(i) << endl;
        }
        else {
            cout << course.prereqs.at(i) << ", ";
        }
    }
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param filepath the path to the txt file to load
 * @return a tree holding the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            vector<string> prerequisites;
            // load the course code and name
            course.courseCode = file[i][0];
            course.courseName = file[i][1];
            // load the prerequisites
            for (unsigned int j = 2; j < file[i].size(); j++) {
                if (file[i][j] != "") {
                    prerequisites.push_back(file[i][j]);
                }
            }
            course.prereqs = prerequisites;

            // push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}


int main(int argc, char* argv[]) {
    BinarySearchTree* bst;
    bst = new BinarySearchTree();

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "input.csv";
    }

    cout << "Welcome to the course planner." << endl;

    string requestedCourseCode;
    Course course;
    int choice = 0;
    while (choice != 9) {
        cout << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {

        case 1:
            // load the courses
            loadCourses(csvPath, bst);
            cout << "Data loaded!" << endl;
            break;
        case 2:
            cout << "Here is a sample schedule:" << endl;
            cout << endl;
            // print the course list
            bst->InOrder();
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> requestedCourseCode;

            // find the requested course in the tree
            course = bst->Search(requestedCourseCode);
            
            // print the course
            if (!course.courseCode.empty()) {
                displayCourse(course);
            }
            // print that the course was not found
            else {
                cout << "Course code:" << requestedCourseCode << " not found." << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }
    return 0;
}