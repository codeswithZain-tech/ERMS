//Zain kashif			L1F23BSCS0516
//Muhammad Ismail  		L1S24BSCS0088
//Zain ali   				L1S24BSCS0049


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// ==================== CUSTOM STRING TO FLOAT ====================
float custom_stof(const string& str) {
    float result = 0.0f;
    float decimal = 0.1f;
    bool negative = false;
    bool decimalFound = false;
    int i = 0;
    
    // Check for negative sign
    if (!str.empty() && str[0] == '-') {
        negative = true;
        i = 1;
    }
    
    // Parse the string
    for (; i < (int)str.length(); i++) {
        if (str[i] == '.') {
            decimalFound = true;
            continue;
        }
        
        if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            
            if (!decimalFound) {
                result = result * 10.0f + (float)digit;
            } else {
                result += (float)digit * decimal;
                decimal *= 0.1f;
            }
        } else {
            break;
        }
    }
    
    return negative ? -result : result;
}

// ==================== CUSTOM STRING TO INT ====================
int custom_stoi(const string& str) {
    int result = 0;
    bool negative = false;
    int i = 0;

    // Check for negative sign
    if (!str.empty() && str[0] == '-') {
        negative = true;
        i = 1;
    }

    // Parse the string
    for (; i < (int)str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            // Check for overflow
            if (result > 214748364) {
                return negative ? -2147483647 - 1 : 2147483647;
            }
            result = result * 10 + (str[i] - '0');
        }
        else {
            break;
        }
    }

    return negative ? -result : result;
}

// ==================== CUSTOM INT TO STRING ====================
string custom_to_string(int value) {
    if (value == 0) return "0";

    string result = "";
    bool isNegative = false;

    if (value < 0) {
        isNegative = true;
        if (value == -2147483647 - 1) {
            result = "2147483648";
            return "-" + result;
        }
        value = -value;
    }

    while (value > 0) {
        int digit = value % 10;
        char charDigit = '0' + digit;
        result = charDigit + result;
        value = value / 10;
    }

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}

// ==================== CUSTOM FLOAT TO STRING ====================
string custom_ftoa(float value, int precision = 2) {
    string result = "";
    
    if (value < 0) {
        result += "-";
        value = -value;
    }
    
    int intPart = (int)value;
    result += custom_to_string(intPart);
    
    if (precision > 0) {
        result += ".";
        float decimal = value - intPart;
        
        for (int i = 0; i < precision; i++) {
            decimal *= 10;
            int digit = (int)decimal;
            result += '0' + digit;
            decimal -= digit;
        }
    }
    
    return result;
}

// ==================== CUSTOM ABSOLUTE VALUE ====================
float custom_abs(float x) {
    return (x < 0) ? -x : x;
}

int custom_abs(int x) {
    return (x < 0) ? -x : x;
}

// ==================== CUSTOM MAX ====================
int myMax(int a, int b) {
    return (a > b) ? a : b;
}

// ==================== CUSTOM CLEAR SCREEN ====================
void custom_clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

// ==================== NODE TEMPLATE ====================
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T d) : data(d), next(nullptr) {}
};

// ==================== LINKED LIST ====================
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void insert(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    bool remove(const T& value) {
        if (head == nullptr) return false;

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && !(current->next->data == value)) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        return false;
    }

    T* search(const T& value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    int getSize() const { return size; }
    Node<T>* getHead() const { return head; }
    bool isEmpty() const { return head == nullptr; }
};

// ==================== STACK ====================
template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        clear();
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    T pop() {
        if (isEmpty()) {
            return T();
        }

        Node<T>* temp = top;
        T value = top->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            return T();
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// ==================== QUEUE ====================
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        clear();
    }

    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            return T();
        }

        Node<T>* temp = front;
        T value = front->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    T peekFront() const {
        if (isEmpty()) {
            return T();
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// ==================== STUDENT CLASS ====================
class Student {
private:
    string studentID;
    string name;
    string className;
    string department;

    float quizzes;
    float assignments;
    float project;
    float presentation;
    float cp;
    float midterm;
    float finalExam;

    float totalWeightedScore;
    float gpa;
    char grade;
    string status;

    void calculateResults() {
        totalWeightedScore = (quizzes * 0.10f) +
            (assignments * 0.15f) +
            (project * 0.15f) +
            (presentation * 0.10f) +
            (cp * 0.05f) +
            (midterm * 0.20f) +
            (finalExam * 0.25f);

        if (totalWeightedScore >= 93.0f) gpa = 4.0f;
        else if (totalWeightedScore >= 90.0f) gpa = 3.7f;
        else if (totalWeightedScore >= 87.0f) gpa = 3.3f;
        else if (totalWeightedScore >= 83.0f) gpa = 3.0f;
        else if (totalWeightedScore >= 80.0f) gpa = 2.7f;
        else if (totalWeightedScore >= 77.0f) gpa = 2.3f;
        else if (totalWeightedScore >= 73.0f) gpa = 2.0f;
        else if (totalWeightedScore >= 70.0f) gpa = 1.7f;
        else if (totalWeightedScore >= 67.0f) gpa = 1.3f;
        else if (totalWeightedScore >= 63.0f) gpa = 1.0f;
        else if (totalWeightedScore >= 60.0f) gpa = 0.7f;
        else gpa = 0.0f;

        if (totalWeightedScore >= 90.0f) grade = 'A';
        else if (totalWeightedScore >= 80.0f) grade = 'B';
        else if (totalWeightedScore >= 70.0f) grade = 'C';
        else if (totalWeightedScore >= 60.0f) grade = 'D';
        else grade = 'F';

        status = (totalWeightedScore >= 60.0f) ? "PASS" : "FAIL";
    }

public:
    Student() : quizzes(0), assignments(0), project(0), presentation(0),
        cp(0), midterm(0), finalExam(0), totalWeightedScore(0),
        gpa(0.0f), grade('F'), status("FAIL") {}

    Student(string id, string n, string cls, string dept,
        float q, float a, float prj, float pres,
        float cp_marks, float mid, float fin)
        : studentID(id), name(n), className(cls), department(dept),
        quizzes(q), assignments(a), project(prj), presentation(pres),
        cp(cp_marks), midterm(mid), finalExam(fin) {
        calculateResults();
    }

    string getID() const { return studentID; }
    string getName() const { return name; }
    string getClassName() const { return className; }
    string getDepartment() const { return department; }
    float getQuizzes() const { return quizzes; }
    float getAssignments() const { return assignments; }
    float getProject() const { return project; }
    float getPresentation() const { return presentation; }
    float getCP() const { return cp; }
    float getMidterm() const { return midterm; }
    float getFinalExam() const { return finalExam; }
    float getTotalWeightedScore() const { return totalWeightedScore; }
    float getGPA() const { return gpa; }
    char getGrade() const { return grade; }
    string getStatus() const { return status; }

    void setQuizzes(float q) {
        quizzes = (q < 0) ? 0 : (q > 100) ? 100 : q;
        calculateResults();
    }

    void setAssignments(float a) {
        assignments = (a < 0) ? 0 : (a > 100) ? 100 : a;
        calculateResults();
    }

    void setProject(float p) {
        project = (p < 0) ? 0 : (p > 100) ? 100 : p;
        calculateResults();
    }

    void setPresentation(float p) {
        presentation = (p < 0) ? 0 : (p > 100) ? 100 : p;
        calculateResults();
    }

    void setCP(float c) {
        cp = (c < 0) ? 0 : (c > 100) ? 100 : c;
        calculateResults();
    }

    void setMidterm(float m) {
        midterm = (m < 0) ? 0 : (m > 100) ? 100 : m;
        calculateResults();
    }

    void setFinalExam(float f) {
        finalExam = (f < 0) ? 0 : (f > 100) ? 100 : f;
        calculateResults();
    }

    void setAllMarks(float q, float a, float p, float pres, float c, float m, float f) {
        setQuizzes(q);
        setAssignments(a);
        setProject(p);
        setPresentation(pres);
        setCP(c);
        setMidterm(m);
        setFinalExam(f);
    }

    void display() const {
        cout << "\n==========================================" << endl;
        cout << "          STUDENT EXAMINATION RECORD      " << endl;
        cout << "==========================================" << endl;
        cout << "ID: " << studentID << endl;
        cout << "Name: " << name << endl;
        cout << "Class: " << className << endl;
        cout << "Department: " << department << endl;

        cout << fixed << setprecision(2);
        cout << "\nASSESSMENT COMPONENTS:" << endl;
        cout << "1. Quizzes (10%):        " << quizzes << endl;
        cout << "2. Assignments (15%):    " << assignments << endl;
        cout << "3. Project (15%):        " << project << endl;
        cout << "4. Presentation (10%):   " << presentation << endl;
        cout << "5. Class Participation (5%): " << cp << endl;
        cout << "6. Mid-term (20%):       " << midterm << endl;
        cout << "7. Final Exam (25%):     " << finalExam << endl;

        cout << "\nFINAL RESULTS:" << endl;
        cout << "Total Weighted Score: " << totalWeightedScore << "%" << endl;
        cout << "GPA (4.0 Scale):      " << gpa << endl;
        cout << "Letter Grade:         " << grade << endl;
        cout << "Status:               " << status << endl;
        cout << "==========================================" << endl;
    }

    void displaySummary() const {
        string displayName = name;
        if (name.length() > 18) {
            displayName = name.substr(0, 15) + "...";
        }

        string displayDept = department;
        if (department.length() > 14) {
            displayDept = department.substr(0, 12) + "...";
        }

        cout << left << setw(10) << studentID
            << setw(20) << displayName
            << setw(15) << displayDept
            << setw(10) << fixed << setprecision(2) << totalWeightedScore
            << setw(6) << gpa
            << setw(6) << grade
            << setw(8) << status;
    }

    void saveToFile(ofstream& file) const {
        if (file.is_open()) {
            file << studentID << ","
                << name << ","
                << className << ","
                << department << ","
                << quizzes << ","
                << assignments << ","
                << project << ","
                << presentation << ","
                << cp << ","
                << midterm << ","
                << finalExam << "\n";
        }
    }

    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;

        string tokens[11];
        int tokenCount = 0;
        size_t start = 0, end = 0;

        while ((end = line.find(',', start)) != string::npos && tokenCount < 11) {
            tokens[tokenCount++] = line.substr(start, end - start);
            start = end + 1;
        }

        if (start < line.length() && tokenCount < 11) {
            tokens[tokenCount++] = line.substr(start);
        }

        if (tokenCount == 11) {
            studentID = tokens[0];
            name = tokens[1];
            className = tokens[2];
            department = tokens[3];
            quizzes = custom_stof(tokens[4]);
            assignments = custom_stof(tokens[5]);
            project = custom_stof(tokens[6]);
            presentation = custom_stof(tokens[7]);
            cp = custom_stof(tokens[8]);
            midterm = custom_stof(tokens[9]);
            finalExam = custom_stof(tokens[10]);
            calculateResults();
            return true;
        }
        return false;
    }

    void exportToCSV(ofstream& file) const {
        if (file.is_open()) {
            file << studentID << ","
                << name << ","
                << className << ","
                << department << ","
                << quizzes << ","
                << assignments << ","
                << project << ","
                << presentation << ","
                << cp << ","
                << midterm << ","
                << finalExam << ","
                << totalWeightedScore << ","
                << gpa << ","
                << grade << ","
                << status << "\n";
        }
    }

    bool operator==(const Student& other) const {
        return studentID == other.studentID;
    }

    bool operator<(const Student& other) const {
        return totalWeightedScore < other.totalWeightedScore;
    }

    bool operator>(const Student& other) const {
        return totalWeightedScore > other.totalWeightedScore;
    }
};

// ==================== ACTION CLASS ====================
class Action {
public:
    string type;
    Student studentData;
    int actionNumber;

    Action() : type(""), actionNumber(0) {}

    Action(string t, const Student& s, int num = 0) : type(t), studentData(s), actionNumber(num) {}

    void display() const {
        cout << "[" << type << "] Action #" << actionNumber << " - ID: " << studentData.getID()
            << " - " << studentData.getName();
    }

    void saveToFile(ofstream& file) const {
        if (file.is_open()) {
            file << type << ","
                << actionNumber << ","
                << studentData.getID() << ","
                << studentData.getName() << ","
                << studentData.getClassName() << ","
                << studentData.getDepartment() << ","
                << studentData.getQuizzes() << ","
                << studentData.getAssignments() << ","
                << studentData.getProject() << ","
                << studentData.getPresentation() << ","
                << studentData.getCP() << ","
                << studentData.getMidterm() << ","
                << studentData.getFinalExam() << "\n";
        }
    }

    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;

        string tokens[13];
        int tokenCount = 0;
        size_t start = 0, end = 0;

        while ((end = line.find(',', start)) != string::npos && tokenCount < 13) {
            tokens[tokenCount++] = line.substr(start, end - start);
            start = end + 1;
        }

        if (start < line.length() && tokenCount < 13) {
            tokens[tokenCount++] = line.substr(start);
        }

        if (tokenCount == 13) {
            type = tokens[0];
            actionNumber = custom_stoi(tokens[1]);

            studentData = Student(
                tokens[2],
                tokens[3],
                tokens[4],
                tokens[5],
                custom_stof(tokens[6]),
                custom_stof(tokens[7]),
                custom_stof(tokens[8]),
                custom_stof(tokens[9]),
                custom_stof(tokens[10]),
                custom_stof(tokens[11]),
                custom_stof(tokens[12])
            );
            return true;
        }
        return false;
    }
};

// ==================== BST NODE & CLASS ====================
class BSTNode {
public:
    Student data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Student& s) : data(s), left(nullptr), right(nullptr) {}
};

class StudentBST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, const Student& student) {
        if (node == nullptr) {
            return new BSTNode(student);
        }

        if (student.getID() < node->data.getID()) {
            node->left = insert(node->left, student);
        }
        else if (student.getID() > node->data.getID()) {
            node->right = insert(node->right, student);
        }

        return node;
    }

    BSTNode* search(BSTNode* node, const string& id) const {
        if (node == nullptr || node->data.getID() == id) {
            return node;
        }

        if (id < node->data.getID()) {
            return search(node->left, id);
        }
        else {
            return search(node->right, id);
        }
    }

    void inorder(BSTNode* node) const {
        if (node != nullptr) {
            inorder(node->left);
            node->data.displaySummary();
            cout << endl;
            inorder(node->right);
        }
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* remove(BSTNode* node, const string& id) {
        if (node == nullptr) return node;

        if (id < node->data.getID()) {
            node->left = remove(node->left, id);
        }
        else if (id > node->data.getID()) {
            node->right = remove(node->right, id);
        }
        else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.getID());
        }
        return node;
    }

    void clear(BSTNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    StudentBST() : root(nullptr) {}

    ~StudentBST() {
        clear();
    }

    void insert(const Student& student) {
        root = insert(root, student);
    }

    Student* search(const string& id) {
        BSTNode* result = search(root, id);
        return (result != nullptr) ? &result->data : nullptr;
    }

    void remove(const string& id) {
        root = remove(root, id);
    }

    void displaySortedByID() const {
        if (root == nullptr) {
            cout << "No students in the system!" << endl;
            return;
        }

        cout << "\n======================================================" << endl;
        cout << "           STUDENTS SORTED BY ID (BST)               " << endl;
        cout << "======================================================" << endl;
        inorder(root);
        cout << "======================================================" << endl;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

// ==================== AVL TREE ====================
class AVLNode {
public:
    Student data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Student& s) : data(s), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(AVLNode* node) const {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + myMax(getHeight(y->left), getHeight(y->right));
        x->height = 1 + myMax(getHeight(x->left), getHeight(x->right));

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + myMax(getHeight(x->left), getHeight(x->right));
        y->height = 1 + myMax(getHeight(y->left), getHeight(y->right));

        return y;
    }

    AVLNode* insert(AVLNode* node, const Student& student) {
        if (node == nullptr) {
            return new AVLNode(student);
        }

        if (student.getTotalWeightedScore() < node->data.getTotalWeightedScore()) {
            node->left = insert(node->left, student);
        }
        else {
            node->right = insert(node->right, student);
        }

        node->height = 1 + myMax(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && student.getTotalWeightedScore() < node->left->data.getTotalWeightedScore()) {
            return rightRotate(node);
        }

        if (balance < -1 && student.getTotalWeightedScore() > node->right->data.getTotalWeightedScore()) {
            return leftRotate(node);
        }

        if (balance > 1 && student.getTotalWeightedScore() > node->left->data.getTotalWeightedScore()) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && student.getTotalWeightedScore() < node->right->data.getTotalWeightedScore()) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(AVLNode* node) const {
        if (node != nullptr) {
            inorder(node->left);
            node->data.displaySummary();
            cout << endl;
            inorder(node->right);
        }
    }

    void inorderReverse(AVLNode* node) const {
        if (node != nullptr) {
            inorderReverse(node->right);
            node->data.displaySummary();
            cout << endl;
            inorderReverse(node->left);
        }
    }

    void clear(AVLNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear();
    }

    void insert(const Student& student) {
        root = insert(root, student);
    }

    void displaySortedByMarksAscending() const {
        if (root == nullptr) {
            cout << "No students in the system!" << endl;
            return;
        }

        cout << "\n======================================================" << endl;
        cout << "     STUDENTS SORTED BY MARKS (ASCENDING - AVL)      " << endl;
        cout << "======================================================" << endl;
        inorder(root);
        cout << "======================================================" << endl;
    }

    void displaySortedByMarksDescending() const {
        if (root == nullptr) {
            cout << "No students in the system!" << endl;
            return;
        }

        cout << "\n======================================================" << endl;
        cout << "     STUDENTS SORTED BY MARKS (DESCENDING - AVL)     " << endl;
        cout << "======================================================" << endl;
        inorderReverse(root);
        cout << "======================================================" << endl;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

// ==================== HEAP ====================
class StudentHeap {
private:
    Student* heap;
    int capacity;
    int size;
    bool isMaxHeap;

    void swapStudents(int i, int j) {
        Student temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if ((isMaxHeap && heap[index].getTotalWeightedScore() > heap[parent].getTotalWeightedScore()) ||
                (!isMaxHeap && heap[index].getTotalWeightedScore() < heap[parent].getTotalWeightedScore())) {
                swapStudents(index, parent);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int target = index;

            if (left < size && ((isMaxHeap && heap[left].getTotalWeightedScore() > heap[target].getTotalWeightedScore()) ||
                (!isMaxHeap && heap[left].getTotalWeightedScore() < heap[target].getTotalWeightedScore()))) {
                target = left;
            }

            if (right < size && ((isMaxHeap && heap[right].getTotalWeightedScore() > heap[target].getTotalWeightedScore()) ||
                (!isMaxHeap && heap[right].getTotalWeightedScore() < heap[target].getTotalWeightedScore()))) {
                target = right;
            }

            if (target != index) {
                swapStudents(index, target);
                index = target;
            }
            else {
                break;
            }
        }
    }

public:
    StudentHeap(int cap = 100, bool maxHeap = true) : capacity(cap), size(0), isMaxHeap(maxHeap) {
        heap = new Student[capacity];
    }

    ~StudentHeap() {
        delete[] heap;
    }

    void insert(const Student& student) {
        if (size >= capacity) {
            capacity *= 2;
            Student* newHeap = new Student[capacity];
            for (int i = 0; i < size; i++) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
        }

        heap[size] = student;
        heapifyUp(size);
        size++;
    }

    Student extractTop() {
        if (size == 0) {
            return Student();
        }

        Student top = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return top;
    }

    Student peekTop() const {
        if (size == 0) {
            return Student();
        }
        return heap[0];
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

// ==================== FILE HANDLER ====================
class FileHandler {
private:
    const string studentFile = "students.txt";
    const string actionFile = "actions.txt";

public:
    FileHandler() {}

    bool saveAllStudents(LinkedList<Student>& studentList) {
        ofstream file(studentFile, ios::trunc);
        if (!file.is_open()) {
            cout << "Error: Cannot open " << studentFile << " for writing!" << endl;
            return false;
        }

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            current->data.saveToFile(file);
            current = current->next;
        }

        file.close();
        return true;
    }

    int loadStudents(LinkedList<Student>& studentList) {
        ifstream file(studentFile);
        if (!file.is_open()) {
            cout << "No existing student data found. Starting fresh." << endl;
            return 0;
        }

        int count = 0;
        Student s;
        while (s.loadFromFile(file)) {
            studentList.insert(s);
            count++;
        }

        file.close();
        return count;
    }

    bool saveAction(const Action& action) {
        ofstream file(actionFile, ios::app);
        if (!file.is_open()) {
            cout << "Error: Cannot open " << actionFile << " for writing!" << endl;
            return false;
        }

        action.saveToFile(file);
        file.close();
        return true;
    }

    int loadActions(Stack<Action>& actionHistory) {
        ifstream file(actionFile);
        if (!file.is_open()) {
            return 0;
        }

        int count = 0;
        Action action;
        while (action.loadFromFile(file)) {
            actionHistory.push(action);
            count++;
        }

        file.close();
        return count;
    }

    bool exportToCSV(LinkedList<Student>& studentList, const string& filename) {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cout << "Error: Cannot open " << filename << " for writing!" << endl;
            return false;
        }

        file << "StudentID,Name,Class,Department,Quizzes,Assignments,Project,"
            << "Presentation,ClassParticipation,Midterm,FinalExam,TotalScore,GPA,Grade,Status\n";

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            current->data.exportToCSV(file);
            current = current->next;
        }

        file.close();
        return true;
    }

    bool clearActionFile() {
        ofstream file(actionFile, ios::trunc);
        if (!file.is_open()) return false;
        file.close();
        return true;
    }
};

// ==================== MAIN SYSTEM CLASS ====================
class ResultManagementSystem {
private:
    LinkedList<Student> studentList;
    StudentBST studentBST;
    AVLTree studentAVL;
    Stack<Action> actionHistory;
    Stack<Action> redoHistory;
    Queue<Student> displayQueue;
    FileHandler fileHandler;
    int actionCounter;

    void printLine(int length, char ch = '-') const {
        for (int i = 0; i < length; i++) cout << ch;
        cout << endl;
    }

   void printHeader(const string& title) const {
    cout << "\n";
    cout << "============================================================" << endl;
    
    // Center the title
    int titleLen = title.length();
    int spaces = (60 - titleLen) / 2;
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << title << endl;
    
    cout << "============================================================" << endl;
}

    Student inputStudentDetails() {
        string id, name, className, department;
        float quizzes, assignments, project, presentation, cp, midterm, finalExam;

        cout << "\n=== ENTER STUDENT DETAILS ===" << endl;
        cout << "Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Full Name: ";
        getline(cin, name);

        cout << "Class: ";
        getline(cin, className);

        cout << "Department: ";
        getline(cin, department);

        cout << "\n=== ENTER ASSESSMENT MARKS (0-100) ===" << endl;

        cout << "Quizzes: ";
        cin >> quizzes;
        if (quizzes < 0) quizzes = 0;
        if (quizzes > 100) quizzes = 100;

        cout << "Assignments: ";
        cin >> assignments;
        if (assignments < 0) assignments = 0;
        if (assignments > 100) assignments = 100;

        cout << "Project: ";
        cin >> project;
        if (project < 0) project = 0;
        if (project > 100) project = 100;

        cout << "Presentation: ";
        cin >> presentation;
        if (presentation < 0) presentation = 0;
        if (presentation > 100) presentation = 100;

        cout << "Class Participation: ";
        cin >> cp;
        if (cp < 0) cp = 0;
        if (cp > 100) cp = 100;

        cout << "Mid-term: ";
        cin >> midterm;
        if (midterm < 0) midterm = 0;
        if (midterm > 100) midterm = 100;

        cout << "Final Exam: ";
        cin >> finalExam;
        if (finalExam < 0) finalExam = 0;
        if (finalExam > 100) finalExam = 100;

        return Student(id, name, className, department,
            quizzes, assignments, project, presentation,
            cp, midterm, finalExam);
    }

    void updateStudentComponent(Student* student) {
        int choice;
        float newMark;

        cout << "\n=== SELECT COMPONENT TO UPDATE ===" << endl;
        cout << "1. Quizzes (Current: " << student->getQuizzes() << ")" << endl;
        cout << "2. Assignments (Current: " << student->getAssignments() << ")" << endl;
        cout << "3. Project (Current: " << student->getProject() << ")" << endl;
        cout << "4. Presentation (Current: " << student->getPresentation() << ")" << endl;
        cout << "5. Class Participation (Current: " << student->getCP() << ")" << endl;
        cout << "6. Mid-term (Current: " << student->getMidterm() << ")" << endl;
        cout << "7. Final Exam (Current: " << student->getFinalExam() << ")" << endl;
        cout << "8. Update All Components" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 7) {
            cout << "Enter new marks (0-100): ";
            cin >> newMark;

            switch (choice) {
            case 1: student->setQuizzes(newMark); break;
            case 2: student->setAssignments(newMark); break;
            case 3: student->setProject(newMark); break;
            case 4: student->setPresentation(newMark); break;
            case 5: student->setCP(newMark); break;
            case 6: student->setMidterm(newMark); break;
            case 7: student->setFinalExam(newMark); break;
            }
            cout << "Component updated successfully!" << endl;
        }
        else if (choice == 8) {
            cout << "\n=== UPDATE ALL COMPONENTS ===" << endl;

            cout << "Enter Quizzes marks (0-100): ";
            cin >> newMark; student->setQuizzes(newMark);

            cout << "Enter Assignments marks (0-100): ";
            cin >> newMark; student->setAssignments(newMark);

            cout << "Enter Project marks (0-100): ";
            cin >> newMark; student->setProject(newMark);

            cout << "Enter Presentation marks (0-100): ";
            cin >> newMark; student->setPresentation(newMark);

            cout << "Enter Class Participation (0-100): ";
            cin >> newMark; student->setCP(newMark);

            cout << "Enter Mid-term marks (0-100): ";
            cin >> newMark; student->setMidterm(newMark);

            cout << "Enter Final Exam marks (0-100): ";
            cin >> newMark; student->setFinalExam(newMark);

            cout << "All components updated successfully!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    void rebuildDataStructures() {
        studentBST.clear();
        studentAVL.clear();

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            studentBST.insert(current->data);
            studentAVL.insert(current->data);
            current = current->next;
        }
    }

    void saveData() {
        cout << "\n=== SAVING DATA TO FILE ===" << endl;

        if (fileHandler.saveAllStudents(studentList)) {
            cout << "SUCCESS: Student data saved to students.txt" << endl;
        }
        else {
            cout << "ERROR: Failed to save student data!" << endl;
        }
    }

    void addSampleData() {
        Student s1("CS101", "Ali Khan", "CS-3A", "Computer Science", 85, 90, 88, 82, 75, 78, 85);
        Student s2("CS102", "Sara Ahmed", "CS-3A", "Computer Science", 92, 88, 95, 90, 85, 92, 88);
        Student s3("EE201", "Bilal Shah", "EE-2A", "Electrical Engineering", 88, 85, 90, 87, 80, 82, 86);
        Student s4("CS103", "Fatima Noor", "CS-3B", "Computer Science", 95, 92, 96, 94, 90, 93, 97);
        Student s5("CS104", "Hamza Mehmood", "CS-3A", "Computer Science", 77, 88, 77, 66, 55, 77, 77);

        studentList.insert(s1);
        studentList.insert(s2);
        studentList.insert(s3);
        studentList.insert(s4);
        studentList.insert(s5);

        studentBST.insert(s1);
        studentBST.insert(s2);
        studentBST.insert(s3);
        studentBST.insert(s4);
        studentBST.insert(s5);

        studentAVL.insert(s1);
        studentAVL.insert(s2);
        studentAVL.insert(s3);
        studentAVL.insert(s4);
        studentAVL.insert(s5);

        cout << "Added 5 sample students" << endl;
    }

public:
    ResultManagementSystem() : actionCounter(1) {
        cout << "Loading data from files..." << endl;

        int studentCount = fileHandler.loadStudents(studentList);
        if (studentCount > 0) {
            rebuildDataStructures();
            cout << "Successfully loaded " << studentCount << " students from students.txt" << endl;
        }
        else {
            cout << "No student data found. System is empty." << endl;
            cout << "Adding sample data..." << endl;
            addSampleData();
            saveData();
        }

        int actionCount = fileHandler.loadActions(actionHistory);
        if (actionCount > 0) {
            cout << "Loaded " << actionCount << " actions from actions.txt" << endl;
            Stack<Action> temp;
            while (!actionHistory.isEmpty()) {
                Action a = actionHistory.pop();
                if (a.actionNumber >= actionCounter) {
                    actionCounter = a.actionNumber + 1;
                }
                temp.push(a);
            }
            while (!temp.isEmpty()) {
                actionHistory.push(temp.pop());
            }
        }
    }

    ~ResultManagementSystem() {
        saveData();
        cout << "System shutdown complete." << endl;
    }

    void addStudent() {
        Student newStudent = inputStudentDetails();

        if (studentBST.search(newStudent.getID()) != nullptr) {
            cout << "Error: Student with ID " << newStudent.getID() << " already exists!" << endl;
            return;
        }

        studentList.insert(newStudent);
        studentBST.insert(newStudent);
        studentAVL.insert(newStudent);

        Action action("ADD", newStudent, actionCounter++);
        fileHandler.saveAction(action);
        actionHistory.push(action);

        while (!redoHistory.isEmpty()) {
            redoHistory.pop();
        }

        saveData();

        cout << "\nStudent added successfully!" << endl;
        cout << "Total students: " << studentList.getSize() << endl;
    }

    void removeStudent() {
        string id;
        cout << "Enter Student ID to remove: ";
        cin >> id;

        Student* student = studentBST.search(id);
        if (student == nullptr) {
            cout << "Error: Student not found!" << endl;
            return;
        }

        Action action("REMOVE", *student, actionCounter++);
        fileHandler.saveAction(action);
        actionHistory.push(action);

        while (!redoHistory.isEmpty()) {
            redoHistory.pop();
        }

        studentList.remove(*student);
        studentBST.remove(id);
        rebuildDataStructures();

        saveData();

        cout << "\nStudent removed successfully!" << endl;
    }

    void searchStudent() {
        string id;
        cout << "Enter Student ID to search: ";
        cin >> id;

        Student* student = studentBST.search(id);
        if (student != nullptr) {
            student->display();
        }
        else {
            cout << "Student not found!" << endl;
        }
    }

    void updateStudentMarks() {
        string id;
        cout << "Enter Student ID to update: ";
        cin >> id;

        Student* bstStudent = studentBST.search(id);
        if (bstStudent == nullptr) {
            cout << "Error: Student not found!" << endl;
            return;
        }

        Student* listStudent = studentList.search(*bstStudent);

        if (listStudent == nullptr) {
            cout << "Internal error: Student not found in list!" << endl;
            return;
        }

        Student oldData = *listStudent;

        listStudent->display();

        updateStudentComponent(listStudent);

        rebuildDataStructures();

        Action action("UPDATE", oldData, actionCounter++);
        fileHandler.saveAction(action);
        actionHistory.push(action);

        saveData();

        cout << "Marks updated & saved successfully!" << endl;
    }

// ==================== UPDATE displayAllStudents FUNCTION ====================
void displayAllStudents() {
    if (studentList.isEmpty()) {
        cout << "No students in the system!" << endl;
        return;
    }

    cout << "\n===================================================================================================" << endl;
    cout << "                    ALL STUDENTS                            " << endl;
    cout << "=====================================================================================================" << endl;
    cout << left << setw(10) << "ID"
         << left << setw(35) << "Name"
         << left << setw(20) << "Department"
         << right << setw(3) << "Score%"
         << right << setw(8) << "GPA"
         << right << setw(8) << "Grade"
         << right << setw(10) << "Status" << endl;
    cout << "======================================================================================================" << endl;

    int count = 1;
    Node<Student>* current = studentList.getHead();
    while (current != nullptr) {
        string displayName = current->data.getName();
        if (displayName.length() > 25) {
            displayName = displayName.substr(0, 22) + "...";
        }

        string displayDept = current->data.getDepartment();
        if (displayDept.length() > 19) {
            displayDept = displayDept.substr(0, 16) + "...";
        }

        // Print with proper alignment
    
        cout << left << setw(10) << current->data.getID();
        cout << left << setw(28) << displayName;
        cout << left << setw(22) << displayDept;
        cout << right << setw(10) << fixed << setprecision(2) << current->data.getTotalWeightedScore();
        cout << right << setw(8) << current->data.getGPA();
        cout << right << setw(8) << current->data.getGrade();
        cout << right << setw(10) << current->data.getStatus() << endl;
        
        current = current->next;
    }
    cout << "============================================================" << endl;
    cout << "\nTotal Students: " << studentList.getSize() << endl;
}
    void generateMeritList() {
        if (studentList.isEmpty()) {
            cout << "No students in the system!" << endl;
            return;
        }

        StudentHeap maxHeap(studentList.getSize(), true);

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            maxHeap.insert(current->data);
            current = current->next;
        }

        printHeader("MERIT LIST (TOP 10)");
        cout << left << setw(5) << "Rank"
            << setw(10) << "ID"
            << setw(20) << "Name"
            << setw(10) << "Score%"
            << setw(8) << "GPA"
            << setw(6) << "Grade" << endl;
        printLine(60);

        int rank = 1;
        int limit = (10 < maxHeap.getSize()) ? 10 : maxHeap.getSize();
        for (int i = 0; i < limit; i++) {
            Student s = maxHeap.extractTop();

            string displayName = s.getName();
            if (displayName.length() > 18) {
                displayName = displayName.substr(0, 15) + "...";
            }

            cout << setw(5) << rank++
                << setw(10) << s.getID()
                << setw(20) << displayName
                << setw(10) << fixed << setprecision(2) << s.getTotalWeightedScore()
                << setw(8) << s.getGPA()
                << setw(6) << s.getGrade() << endl;
        }
    }

    void displayTopBottomK() {
        if (studentList.isEmpty()) {
            cout << "No students in the system!" << endl;
            return;
        }

        int k;
        cout << "Enter K value: ";
        cin >> k;

        if (k <= 0 || k > studentList.getSize()) {
            cout << "Invalid K value!" << endl;
            return;
        }

        StudentHeap maxHeap(studentList.getSize(), true);
        StudentHeap minHeap(studentList.getSize(), false);

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            maxHeap.insert(current->data);
            minHeap.insert(current->data);
            current = current->next;
        }

        printHeader("TOP " + custom_to_string(k) + " STUDENTS");
        for (int i = 0; i < k && !maxHeap.isEmpty(); i++) {
            Student s = maxHeap.extractTop();
            cout << i + 1 << ". " << s.getName() << " (ID: " << s.getID()
                << ") - Score: " << s.getTotalWeightedScore() << "% - Grade: " << s.getGrade() << endl;
        }

        printHeader("BOTTOM " + custom_to_string(k) + " STUDENTS");
        for (int i = 0; i < k && !minHeap.isEmpty(); i++) {
            Student s = minHeap.extractTop();
            cout << i + 1 << ". " << s.getName() << " (ID: " << s.getID()
                << ") - Score: " << s.getTotalWeightedScore() << "% - Grade: " << s.getGrade() << endl;
        }
    }

    void displaySortedByID() {
        studentBST.displaySortedByID();
    }

    void displaySortedByMarks() {
        int choice;
        cout << "\n1. Ascending Order (Lowest to Highest)" << endl;
        cout << "2. Descending Order (Highest to Lowest)" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            studentAVL.displaySortedByMarksAscending();
            break;
        case 2:
            studentAVL.displaySortedByMarksDescending();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    void showActionHistory() {
        printHeader("ACTION HISTORY");

        if (actionHistory.isEmpty()) {
            cout << "No actions recorded." << endl;
            return;
        }

        cout << "Recent actions (most recent first):" << endl;
        printLine(60);

        Stack<Action> tempStack;
        Stack<Action> copyStack = actionHistory;

        int count = 1;
        while (!copyStack.isEmpty()) {
            Action action = copyStack.pop();
            cout << count++ << ". ";
            action.display();
            cout << endl;
            tempStack.push(action);
        }

        cout << "\nTotal actions: " << actionHistory.getSize() << endl;
    }

    void undoLastAction() {
        if (actionHistory.isEmpty()) {
            cout << "No actions to undo!" << endl;
            return;
        }

        Action lastAction = actionHistory.pop();
        cout << "\nUndoing: ";
        lastAction.display();
        cout << endl;

        if (lastAction.type == "ADD") {
            studentList.remove(lastAction.studentData);
            studentBST.remove(lastAction.studentData.getID());
            rebuildDataStructures();
        }
        else if (lastAction.type == "REMOVE") {
            studentList.insert(lastAction.studentData);
            studentBST.insert(lastAction.studentData);
            studentAVL.insert(lastAction.studentData);
        }
        else if (lastAction.type == "UPDATE") {
            Student* student = studentBST.search(lastAction.studentData.getID());
            if (student != nullptr) {
                *student = lastAction.studentData;
                rebuildDataStructures();
            }
        }

        redoHistory.push(lastAction);

        saveData();

        cout << "Undo completed successfully! File updated." << endl;
    }

    void redoLastAction() {
        if (redoHistory.isEmpty()) {
            cout << "No actions to redo!" << endl;
            return;
        }

        Action lastUndone = redoHistory.pop();
        cout << "\nRedoing: ";
        lastUndone.display();
        cout << endl;

        if (lastUndone.type == "ADD") {
            studentList.insert(lastUndone.studentData);
            studentBST.insert(lastUndone.studentData);
            studentAVL.insert(lastUndone.studentData);
        }
        else if (lastUndone.type == "REMOVE") {
            studentList.remove(lastUndone.studentData);
            studentBST.remove(lastUndone.studentData.getID());
            rebuildDataStructures();
        }
        else if (lastUndone.type == "UPDATE") {
            Student* student = studentBST.search(lastUndone.studentData.getID());
            if (student != nullptr) {
                *student = lastUndone.studentData;
                rebuildDataStructures();
            }
        }

        actionHistory.push(lastUndone);

        saveData();

        cout << "Redo completed successfully! File updated." << endl;
    }

    void displayStatistics() {
        if (studentList.isEmpty()) {
            cout << "No students in the system!" << endl;
            return;
        }

        int total = studentList.getSize();
        float totalScore = 0, totalGPA = 0;
        float highest = 0, lowest = 100;
        string topStudent, bottomStudent;

        int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeF = 0;
        int passCount = 0;

        Node<Student>* current = studentList.getHead();
        while (current != nullptr) {
            Student& s = current->data;
            float score = s.getTotalWeightedScore();

            totalScore += score;
            totalGPA += s.getGPA();

            if (score > highest) {
                highest = score;
                topStudent = s.getName() + " (" + s.getID() + ")";
            }
            if (score < lowest) {
                lowest = score;
                bottomStudent = s.getName() + " (" + s.getID() + ")";
            }

            switch (s.getGrade()) {
            case 'A': gradeA++; break;
            case 'B': gradeB++; break;
            case 'C': gradeC++; break;
            case 'D': gradeD++; break;
            case 'F': gradeF++; break;
            }

            if (s.getStatus() == "PASS") passCount++;

            current = current->next;
        }

        printHeader("STATISTICS");

        cout << fixed << setprecision(2);
        cout << left << setw(30) << "Total Students:" << right << setw(10) << total << endl;
        cout << left << setw(30) << "Average Score:" << right << setw(10) << (totalScore / total) << "%" << endl;
        cout << left << setw(30) << "Average GPA:" << right << setw(10) << (totalGPA / total) << endl;
        cout << left << setw(30) << "Pass Rate:" << right << setw(10) << ((float)passCount / total * 100) << "%" << endl;

        cout << "\n" << left << setw(30) << "Highest Score:" << right << setw(10) << highest << "%" << endl;
        cout << "  " << topStudent << endl;

        cout << left << setw(30) << "Lowest Score:" << right << setw(10) << lowest << "%" << endl;
        cout << "  " << bottomStudent << endl;

        cout << "\nGRADE DISTRIBUTION:" << endl;
        cout << left << setw(20) << "A:" << right << setw(10) << gradeA << " (" << (gradeA * 100.0f / total) << "%)" << endl;
        cout << left << setw(20) << "B:" << right << setw(10) << gradeB << " (" << (gradeB * 100.0f / total) << "%)" << endl;
        cout << left << setw(20) << "C:" << right << setw(10) << gradeC << " (" << (gradeC * 100.0f / total) << "%)" << endl;
        cout << left << setw(20) << "D:" << right << setw(10) << gradeD << " (" << (gradeD * 100.0f / total) << "%)" << endl;
        cout << left << setw(20) << "F:" << right << setw(10) << gradeF << " (" << (gradeF * 100.0f / total) << "%)" << endl;
    }

    void exportDataToCSV() {
        string filename;
        cout << "Enter CSV filename (e.g., students.csv): ";
        cin >> filename;

        if (fileHandler.exportToCSV(studentList, filename)) {
            cout << "Data exported to " << filename << " successfully!" << endl;
            cout << "Records exported: " << studentList.getSize() << endl;
        }
        else {
            cout << "Failed to export data!" << endl;
        }
    }

    void displayMenu() const {
    cout << "\n";
    cout << "============================================================" << endl;
    cout << "      EXAMINATION RESULT MANAGEMENT SYSTEM                 " << endl;
    cout << "           (COMPLETE WORKING VERSION)                      " << endl;
    cout << "============================================================" << endl;
    cout << "  1.  Add New Student                                      " << endl;
    cout << "  2.  Remove Student                                       " << endl;
    cout << "  3.  Search Student                                       " << endl;
    cout << "  4.  Update Student Marks                                 " << endl;
    cout << "  5.  Display All Students                                 " << endl;
    cout << "  6.  Generate Merit List                                  " << endl;
    cout << "  7.  Display Top/Bottom K                                 " << endl;
    cout << "  8.  Display Sorted by ID                                 " << endl;
    cout << "  9.  Display Sorted by Marks                              " << endl;
    cout << "  10. Show Action History                                  " << endl;
    cout << "  11. Undo Last Action                                     " << endl;
    cout << "  12. Redo Last Action                                     " << endl;
    cout << "  13. Display Statistics                                   " << endl;
    cout << "  14. Export to CSV                                        " << endl;
    cout << "  15. Exit & Save                                          " << endl;
    cout << "============================================================" << endl;
    cout << "Current Students: " << studentList.getSize()
         << " | Actions: " << actionHistory.getSize() << endl;
    cout << "Data File: students.txt" << endl;
    cout << "============================================================" << endl;
    cout << "Enter choice (1-15): ";
}
    void run() {
        int choice;

        do {
            custom_clear_screen();

            printHeader("EXAMINATION RESULT MANAGEMENT SYSTEM");
            displayMenu();

            cin >> choice;

            switch (choice) {
            case 1: addStudent(); break;
            case 2: removeStudent(); break;
            case 3: searchStudent(); break;
            case 4: updateStudentMarks(); break;
            case 5: displayAllStudents(); break;
            case 6: generateMeritList(); break;
            case 7: displayTopBottomK(); break;
            case 8: displaySortedByID(); break;
            case 9: displaySortedByMarks(); break;
            case 10: showActionHistory(); break;
            case 11: undoLastAction(); break;
            case 12: redoLastAction(); break;
            case 13: displayStatistics(); break;
            case 14: exportDataToCSV(); break;
            case 15:
                cout << "\nThank you for using the system!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
            }

            if (choice != 15) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }

        } while (choice != 15);
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    ResultManagementSystem system;
    system.run();
    return 0;
}