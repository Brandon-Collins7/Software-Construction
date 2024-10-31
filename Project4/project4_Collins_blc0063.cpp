/* AUTHOR: Brandon Collins
   USER ID: blc0063
   FILE NAME: project4_Collins_blc0063.cpp
   VERSION: 3/27/2024
   // compile using g++ project4_Collins_blc0063.cpp
   // run ./a.out
 */

#include <iostream>
#include <assert.h>
//#include <string>
using namespace std;


//#define UNIT_TESTING
//#define PRODUCT_VERSION



//linked list data structure for trivia questions
struct Trivia{
    
    
    int totalQuestions;
    Trivia(){
        head = NULL;
        tail = NULL;
        totalQuestions = 0;
    }

    //node for trivia questions
    struct TriviaNode{
        string question;
        string answer;
        int points; 
        TriviaNode* next;

        //creates trivia node
        TriviaNode(string q, string a, int p, TriviaNode* n = NULL){ //makes NULL the default value for next
            question = q;
            answer = a;
            points = p;
            next = n;
        }

        //set next pointer for trivia node
        void setNext(TriviaNode* n){
            next = n;
        }
    };
    
    //track beginning and end of linked list
    TriviaNode* head;
    TriviaNode* tail;


    //default trivia questions
    TriviaNode* defaultTriviaGame(){
        TriviaNode* q1 = new TriviaNode("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
        TriviaNode* q2 = new TriviaNode("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
        TriviaNode* q3 = new TriviaNode("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)", "Wii Sports", 20);
        q1->setNext(q2);
        q2->setNext(q3);
        head = q1;
        totalQuestions=3;
        tail = q3;
        return q1; //return head
    }
    
    //add a new trivia question to the linked list
    void addTrivia(string q, string a, int p){
        
        TriviaNode* t = new TriviaNode(q, a, p);

        //if linked list is empty, set head to new trivia node
        if (head == NULL){
            head = t;
        }
        tail->setNext(t);
        tail = t;
        totalQuestions++;
    }

    //int playTrivia(TriviaNode* triviaQuestion, int numQuestions);
    
    //output 0 for correct answer, 1 for failure?
    int playTrivia(TriviaNode* triviaQuestion, int numQuestions){
        int totalPoints = 0;

        //must have at least 1 question
        if (numQuestions < 1){
            cout << "Warning - The number of trivia to be asked must be equal to or larger than 1." << endl;
            return -1;
        }

        //can't ask more questions than are in the list
        if (numQuestions > totalQuestions){
            cout << "Warning - There are only " << totalQuestions << " questions in the list." << endl;
            return -2;
        }

        //intialize variables for input
        string userAnswer;
        TriviaNode* curr = triviaQuestion;
        int questionCount = 0;

        while (questionCount < numQuestions){

            //ask question and get answer
            cout << "Question: " << curr->question << endl;
            cout << "Answer: ";
            getline(cin, userAnswer);
            cin.clear();

            //check if answer is correct
            if (userAnswer == curr->answer){
                totalPoints += curr->points;
                cout << "Your answer is correct. You receive " << curr->points << " points." << endl;
            } 
            else {
                cout << "Your answer is wrong. The correct answer is: " << curr->answer << endl;
            }

            //print total points and move to next question
            cout << "Your total points: " << totalPoints << endl;
            cout << endl;
            curr = curr->next;
            questionCount++;
        }
        

        return totalPoints;

    }
    



};



//CONDITIONAL COMPILATION
#define PRODUCT_VERSION
//#define UNIT_TESTING

void testPlayTrivia(void); //test driver


//main method
int main(){

//if UNIT_TESTING is defined, run test driver
#ifdef UNIT_TESTING
    testPlayTrivia();
    return 0;
#endif


//if PRODUCT_VERSION is defined, run the trivia game
#ifdef PRODUCT_VERSION

    //create new trivia game with default questions
    Trivia t;
    t.defaultTriviaGame();
    int totalQuestions = 3;

    cout << "*** Welcome to Brandon's trivia quiz game ***" << endl;

    bool toContinue = true;
    
    //add new questions to the trivia game through input
    do {
        
        //get input for new question, answer, and points
        cout << "Enter a question: ";
        string newQuestion;
        getline(cin, newQuestion);
        cin.clear();

        cout << "Enter an answer: ";
        string newAnswer;
        getline(cin, newAnswer);
        cin.clear();

        cout << "Enter award points: ";
        int newPoints;
        cin >> newPoints;
        cin.clear();
        cin.ignore(200, '\n');

        t.addTrivia(newQuestion, newAnswer, newPoints);

        cout << "Continue? (Yes/No): ";
        string continueResponse;
        getline(cin, continueResponse);
        cin.clear();
        
        totalQuestions++;

        if (continueResponse == "No"){
            toContinue = false;
        }

    } while (toContinue);
    
    //play the trivia game by asking questions and getting answers from the user
    cout << endl;
    t.playTrivia(t.head, totalQuestions);

    //end the game
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
    return 0;
#endif

}



//***TEST DRIVER***
void testPlayTrivia(void){
    cout << "***This is a debugging version ***" << endl;

    //unit test cases

    //Test Warning because need at least one question
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
    Trivia t;
    t.defaultTriviaGame();
    assert(t.playTrivia(t.head, 0) == -1);
    cout << "Case 1 passed" << endl;
    cout << endl;

    //Test wrong answer
    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters the incorrect answer." << endl;
    t.defaultTriviaGame();
    assert(t.playTrivia(t.head, 1) == 0);
    cout << "Case 2.1 passed" << endl;
    cout << endl;

    //Test correct answer
    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters the correct answer." << endl;
    t.defaultTriviaGame();
    assert(t.playTrivia(t.head, 1) == 100);
    cout << "Case 2.2 passed" << endl;
    cout << endl;

    //Test all questions
    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
    t.defaultTriviaGame();
    assert(t.playTrivia(t.head, 3) >= 0);
    cout << "Case 3 passed" << endl;
    cout << endl;

    //Test warning for too many questions
    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    t.defaultTriviaGame();
    assert(t.playTrivia(t.head, 5) == -2);
    cout << "Case 4 passed" << endl;
    cout << endl;
    
    //End of test driver
    cout << "*** End of the Debugging Version ***" << endl;
}
