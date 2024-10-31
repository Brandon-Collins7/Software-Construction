# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
using namespace std;


//constants
const int AaronAccuracy = 33; //hits 1/3 of the time
const int BobAccuracy = 50; //hits 1/2 of the time
const int CharlieAccuracy = 100; //never misses
const double runs = 10000;
int AaronStrat2FirstShot = true;



//prototypes
void pressEnter(void);
//User must press enter to allow next test to proceed

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/* Input: A_alive indicates whether Aaron is alive */
       /* B_alive indicates whether Bob is alive */
       /* C_alive indicates whether Charlie is alive */

/* Return: true if at least two are alive */
        /* otherwise return false */

void Aaron_shoots1(bool& B_alive, bool& C_alive);
/* Strategy 1: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/

void Bob_shoots(bool& A_alive, bool& C_alive);
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change C_alive into false if Charlie is killed.
*/

void Charlie_shoots(bool& A_alive, bool& B_alive);
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* B_alive indicates whether Bob is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change B_alive into false if Bob is killed.
*/

void Aaron_shoots2(bool& B_alive, bool& C_alive);
/* Strategy 2: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/



//test drivers
void test_at_least_two_alive(void);
/* This is a test driver for at_least_two_alive() */

void test_Aaron_shoots1(void);
/* This is a test driver for test_Aaron_shoots1() */

void test_Bob_shoots(void);
/* This is a test driver for test_Bob_shoots() */

void test_Charlie_shoots(void);
/* This is a test driver for test_Charlie_shoots() */

void test_Aaron_shoots2(void);
/* This is a test driver for test_Aaron_shoots2() */



int main()
{
//initialize RNG
srand(time(0)); 

cout << "*** Welcome to Brandon's Duel Simulator ***\n";

//test through all test drivers
test_at_least_two_alive();
pressEnter();
cout << "\n";

test_Aaron_shoots1();
pressEnter();
cout << "\n";

test_Bob_shoots();
pressEnter();
cout << "\n";

test_Charlie_shoots();
pressEnter();
cout << "\n";

test_Aaron_shoots2();
pressEnter();
cout << "\n";

cout << "Ready to test strategy 1 (run 10000 times):\n";
pressEnter();
cout << "\n";

//strategy 1 here
int i=0;
int AWins1 = 0;
int BWins = 0;
int CWins = 0;

//all people alive for next run
bool A_alive = true;
bool B_alive = true;
bool C_alive = true;

while(i < runs){
    A_alive = true;
    B_alive = true;
    C_alive = true;

    while (at_least_two_alive(A_alive, B_alive, C_alive)){
        if(A_alive){
        Aaron_shoots1(B_alive, C_alive);
        }

        if(B_alive){
        Bob_shoots(A_alive, C_alive);
        }
        
        if(C_alive){
        Charlie_shoots(A_alive, B_alive);
        }
    }

    //whoever is alive wins
    if (A_alive){
        AWins1+=1;
    }
    if (B_alive){
        BWins+=1;
    }
    if (C_alive){
        CWins+=1;
    }

    i++;
}

//decimal formatting for win rate
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout.precision(2);

//wins for each person
cout << "Aaron won " << AWins1 << "/" << int(runs) << " duels or " << (AWins1*100/runs) << "%\n";
cout << "Bob won " << BWins << "/" << int(runs) << " duels or " << (BWins*100/runs) << "%\n";
cout << "Charlie won " << CWins << "/" << int(runs) << " duels or " << (CWins*100/runs)<< "%\n";
cout << "\n";


cout << "Ready to test strategy 2 (run 10000 times):\n";
pressEnter();
cout << "\n";


//strategy 2 here
i=0;
int AWins2 = 0;
BWins = 0;
CWins = 0;


while(i < runs){
    A_alive = true;
    B_alive = true;
    C_alive = true;
    AaronStrat2FirstShot = true;

    while (at_least_two_alive(A_alive, B_alive, C_alive)){
        if(A_alive){
        Aaron_shoots2(B_alive, C_alive);
        }

        if(B_alive){
        Bob_shoots(A_alive, C_alive);
        }
        
        if(C_alive){
        Charlie_shoots(A_alive, B_alive);
        }
    }

    if (A_alive){
        AWins2+=1;
    }
    else if (B_alive){
        BWins+=1;
    }
    else if (C_alive){
        CWins+=1;
    }

    i++;
}

//wins for each person
cout << "Aaron won " << AWins2 << "/" << int(runs) << " duels or " << (AWins2*100/runs) << "%\n";
cout << "Bob won " << BWins << "/" << int(runs) << " duels or " << (BWins*100/runs) << "%\n";
cout << "Charlie won " << CWins << "/" << int(runs) << " duels or " << (CWins*100/runs)<< "%\n";
cout << "\n";


//evaluate which strategy was better for Aaron
if (AWins1 > AWins2){
    cout << "Strategy 1 is better than strategy 2\n";
}
else if (AWins1 < AWins2){
    cout << "Strategy 2 is better than strategy 1\n";
}


return 0;
}







void pressEnter(void){
    cout << "Press Enter to continue...";
    cin.ignore(); //Pause Command for Linux Terminal
}

/* Implementation of at_least_two_alive() */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)
{
/* add the implementation below */
    if ((!A_alive && !B_alive) || (!B_alive && !C_alive) || (!A_alive && !C_alive))  {
        return false;
    }
    return true;
}


bool shootC;
bool shootB;
bool shootA;
/* Implementation of Aaron_shoots1() */
void Aaron_shoots1(bool& B_alive, bool& C_alive){
    
    if(C_alive){
        
        shootC = true;
    }
    else if(B_alive){
        
        shootB = true;
    }


    //using 99 so that 1/3 can be calculated as a number from 0 to 32, inclusive on both ends. using 100 would lead to unequal distribution
    int AShot = rand()%99;

    if (AShot < AaronAccuracy){

        //then shoot at C because he never misses
        if (C_alive){
            C_alive = false;
        }
        else if(B_alive){
            B_alive = false;
        }
    }

}

/* Implementation of Bob_shoots() */
void Bob_shoots(bool& A_alive, bool& C_alive){
    if(C_alive){
        
        shootC = true;
    }
    else if(A_alive){
        
        shootA = true;
    }

    //using 100 so that 1/2 can be calculated as a number from 0 to 49, inclusive on both ends
    int BShot = rand()%99;

    if (BShot < BobAccuracy){

        //then shoot at C because he never misses
        if (C_alive){
            C_alive = false;
         
        }
        else if(A_alive){
            A_alive = false;
            
        }
    }

}

/* Implementation of Charlie_shoots() */
void Charlie_shoots(bool& A_alive, bool& B_alive){
    if(B_alive){
        
        shootB = true;
    }
    else if(A_alive){
        
        shootA = true;
    }


    //using 100 so that number will always be between 0 and 99, both ends inclusive,
    //but can also change constant for testing so that he doesn't always hit his shot
    int CShot = rand()%100;

    if (CShot < CharlieAccuracy){

        //then shoot at B because he is more accurate than A
        if (B_alive){
            B_alive = false;
           
        }
        else if(A_alive){
            A_alive = false;
            
        }
    }

}

/* Implementation of Aaron_shoots2() */
void Aaron_shoots2(bool& B_alive, bool& C_alive){

    if (AaronStrat2FirstShot){

        AaronStrat2FirstShot = false;
    }


    else{

        if (C_alive){
            
            shootC = true;
        }

        else if(B_alive){
            
            shootB = true;
        }


        //using 99 so that 1/3 can be calculated as a number from 0 to 32, inclusive on both ends. using 100 would lead to unequal distribution
        int AShot = rand()%99;

        if (AShot < AaronAccuracy){

            //then shoot at C because he never misses
            if (C_alive){
                C_alive = false;

            }   
            else if(B_alive){
                B_alive = false;
                
            }
        }
    }

}


/* Implementation of the test driver for at_least_two_alive() */
void test_at_least_two_alive(void) {
cout << "Unit Testing 1: Function – at_least_two_alive()\n";

cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
assert(true == at_least_two_alive(true, true, true));
cout << "\tCase passed ...\n";

cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
assert(true == at_least_two_alive(false, true, true));
cout << "\tCase passed ...\n";

cout << "\tCase 3: Aaron dead, Bob dead, Charlie alive\n";
assert(false == at_least_two_alive(false, false, true));
cout << "\tCase passed ...\n";

cout << "\tCase 4: Aaron dead, Bob dead, Charlie dead\n";
assert(false == at_least_two_alive(false, false, false));
cout << "\tCase passed ...\n";

cout << "\tCase 5: Aaron alive, Bob dead, Charlie alive\n";
assert(true == at_least_two_alive(true, false, true));
cout << "\tCase passed ...\n";

cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
assert(false == at_least_two_alive(false, true, false));
cout << "\tCase passed ...\n";
}


/* Implementation of the test driver for test_Aaron_shoots1() */
void test_Aaron_shoots1(void) {
cout << "Unit Testing 2: Function – at_Aaron_shoots1()\n";

bool b = true;
bool c = true;

bool A_alive = true;
bool B_alive = true;
bool C_alive = true;
cout << "\tCase 1: Bob alive, Charlie alive\n";
Aaron_shoots1(b, c);
assert(true == shootC);
cout<<"\t\tAaron is shooting at Charlie\n";

b = false;
A_alive = true;
B_alive = true;
C_alive = true;
cout << "\tCase 2: Bob dead, Charlie alive\n";
Aaron_shoots1(b, c);
assert(true == shootC);
cout<<"\t\tAaron is shooting at Charlie\n";

b = true;
c = false;
cout << "\tCase 3: Bob alive, Charlie dead\n";
Aaron_shoots1(b, c);
assert(true == shootB);
cout << "\t\tAaron is shooting at Bob\n";

}


/* Implementation of the test driver for test_Bob_shoots() */
void test_Bob_shoots(void) {
cout << "Unit Testing 3: Function – at_Bob_shoots()\n";

bool a = true;
bool c = true;

cout << "\tCase 1: Aaron alive, Charlie alive\n";
Bob_shoots(a, c);
assert(true == shootC);
cout<<"\t\tBob is shooting at Charlie\n";

a = false;
cout << "\tCase 2: Aaron dead, Charlie alive\n";
Bob_shoots(a, c);
assert(true == shootC);
cout<<"\t\tBob is shooting at Charlie\n";

a = true;
c = false;
cout << "\tCase 3: Aaron alive, Charlie dead\n";
Bob_shoots(a, c);
assert(true == shootA);
cout<<"\t\tBob is shooting at Aaron\n";

}

/* Implementation of the test driver for test_Charlie_shoots() */
void test_Charlie_shoots(void) {\

bool a = true;
bool b = true;

cout << "Unit Testing 4: Function – at_Charlie_shoots()\n";

cout << "\tCase 1: Aaron alive, Bob alive\n";
Charlie_shoots(a, b);
assert(true == shootB);
cout<<"\t\tCharlie is shooting at Bob\n";

a = false;
cout << "\tCase 2: Aaron dead, Bob alive\n";
Charlie_shoots(a, b);
assert(true == shootB);
cout<<"\t\tCharlie is shooting at Bob\n";

a = true;
b = false;
cout << "\tCase 3: Aaron alive, Bob dead\n";
Charlie_shoots(a, b);
assert(true == shootA);
cout<<"\t\tCharlie is shooting at Aaron\n";

}




/* Implementation of the test driver for test_Aaron_shoots2() */
void test_Aaron_shoots2(void) {
cout << "Unit Testing 5: Function – at_Aaron_shoots2()\n";

bool b = true;
bool c = true;

cout << "\tCase 1: Bob alive, Charlie alive\n";
AaronStrat2FirstShot = true;
Aaron_shoots2(b, c);
cout<<"\t\tAaron intentionally misses his first shot\n";
cout<<"\t\tBoth Bob and Charlie are alive.\n";

b = false;
AaronStrat2FirstShot = false;
cout << "\tCase 2: Bob dead, Charlie alive\n";
Aaron_shoots2(b, c);
assert(true == shootC);
cout<<"\t\tAaron is shooting at Charlie\n";

b = true;
c = false;
cout << "\tCase 3: Bob alive, Charlie dead\n";
Aaron_shoots2(b, c);
assert(true == shootB);
cout<<"\t\tAaron is shooting at Bob\n";

}
