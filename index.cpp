#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Question {
private:
    string questionText;
    string options[4];
    char correctAnswer;

public:
    Question(string q, string opt[], char ans) {
        questionText = q;
        for(int i = 0; i < 4; i++) {
            options[i] = opt[i];
        }
        correctAnswer = ans;
    }

    void displayQuestion() {
        cout << "\n" << questionText << endl;
        for(int i = 0; i < 4; i++) {
            cout << char('A' + i) << ") " << options[i] << endl;
        }
    }

    bool checkAnswer(char ans) {
        return (toupper(ans) == correctAnswer);
    }
};

class Student {
private:
    string name;
    string rollNo;
    int score;

public:
    Student() {
        name = "";
        rollNo = "";
        score = 0;
    }

    void setName(string n) { name = n; }
    void setRollNo(string r) { rollNo = r; }
    void incrementScore() { score++; }

    string getName() { return name; }
    string getRollNo() { return rollNo; }
    int getScore() { return score; }
    float getPercentage() { return (score * 10.0); }
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getValidInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    while(input.empty()) {
        cout << "Input cannot be empty. " << prompt;
        getline(cin, input);
    }
    return input;
}

char getValidOption() {
    char answer;
    while(true) {
        cin >> answer;
        answer = toupper(answer);
        if(answer >= 'A' && answer <= 'D') {
            clearInputBuffer();
            return answer;
        }
        cout << "Invalid option. Please enter A, B, C, or D: ";
        clearInputBuffer();
    }
}

int main() {
    vector<Question> quiz = {
        Question("What is the capital of France?", 
                new string[4]{"London", "Paris", "Berlin", "Madrid"}, 'B'),
        Question("Which planet is known as the Red Planet?", 
                new string[4]{"Venus", "Jupiter", "Mars", "Saturn"}, 'C'),
        Question("What is 2 + 2?", 
                new string[4]{"3", "4", "5", "6"}, 'B'),
        Question("Who wrote 'Romeo and Juliet'?", 
                new string[4]{"Charles Dickens", "William Shakespeare", "Jane Austen", "Mark Twain"}, 'B'),
        Question("What is the largest mammal?", 
                new string[4]{"African Elephant", "Blue Whale", "Giraffe", "Hippopotamus"}, 'B'),
        Question("Which element has the symbol 'O'?", 
                new string[4]{"Gold", "Silver", "Oxygen", "Iron"}, 'C'),
        Question("What is the square root of 16?", 
                new string[4]{"2", "3", "4", "5"}, 'C'),
        Question("Which country is known as the Land of Rising Sun?", 
                new string[4]{"China", "Korea", "Thailand", "Japan"}, 'D'),
        Question("What is the chemical formula for water?", 
                new string[4]{"H2O", "CO2", "O2", "N2"}, 'A'),
        Question("How many continents are there?", 
                new string[4]{"5", "6", "7", "8"}, 'C')
    };

    ofstream outFile("quiz_results.txt");
    if(!outFile) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return 1;
    }

    outFile << left << setw(20) << "Name" 
            << setw(15) << "Roll No" 
            << setw(15) << "Score" 
            << "Percentage" << endl;
    outFile << string(60, '-') << endl;

    char continueQuiz;
    do {
        Student student;
        cout << "\n=== QUIZ MANAGEMENT SYSTEM ===\n";
        
        string name = getValidInput("Enter your name: ");
        string rollNo = getValidInput("Enter your roll number: ");
        
        student.setName(name);
        student.setRollNo(rollNo);

        cout << "\nWelcome " << name << "! The quiz contains 10 MCQ questions.\n";
        cout << "Please select options (A/B/C/D) for each question.\n";

        for(int i = 0; i < 10; i++) {
            cout << "\nQuestion " << (i + 1) << "/10";
            quiz[i].displayQuestion();
            cout << "Your answer: ";
            char answer = getValidOption();
            if(quiz[i].checkAnswer(answer)) {
                student.incrementScore();
            }
        }

        outFile << left << setw(20) << student.getName()
                << setw(15) << student.getRollNo()
                << setw(15) << student.getScore()
                << fixed << setprecision(2) << student.getPercentage() << "%" << endl;

        cout << "\nQuiz completed!\n";
        cout << "Your score: " << student.getScore() << "/10\n";
        cout << "Percentage: " << student.getPercentage() << "%\n";

        cout << "\nDo you want another student to take the quiz? (y/n): ";
        cin >> continueQuiz;
        clearInputBuffer();
    } while(tolower(continueQuiz) == 'y');

    outFile.close();
    cout << "\nAll results have been saved to 'quiz_results.txt'\n";

    return 0;
}
