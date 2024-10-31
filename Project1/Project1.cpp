#include <iostream>
using namespace std;

int main(){
    //Intialize variables
    double loan = -1;
    double interestRate = -1;
    double interestRateDisplay; //because interest rate should be displayed as a percent, but calculated as a decimal
    double monthlyPay = -1;
    int month;
    double interestTotal;

    //Currency formating
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);


    //User input: Loan amount
    while(loan <= 0){
        
        cout << "Loan Amount: ";
        cin >> loan;

        //must input a double
        if(cin.fail()){
            cin.clear();
            cin.ignore(200, '\n');
            cout << "Invalid loan\n"; 
        }

        //must have positive loan
        else if(loan <= 0){
            cout << "Invalid loan\n"; 
        }
    }



    //User input: Interest rate
    while(interestRate < 0){
        cout << "Interest Rate: ";
        cin >> interestRate;

        //must input a double
        if(cin.fail()){
            cin.clear();
            cin.ignore(200, '\n');
            cout << "Invalid interest rate\n"; 
            interestRate = -1; //to make sure loop repeats
        }

        //must have nonnegative interest rate
        else if((interestRate) < 0){
            cout << "Invalid interest rate\n"; 
        }
    }


    //calculate decimal interest rate but save percent as it's own variable
    interestRate /= 12;
    interestRateDisplay = interestRate;
    interestRate /= 100;
    
    //User input: Monthly pay
    while(monthlyPay <= 0 || monthlyPay <= interestRate*loan){
        cout << "Monthly Payments: ";
        cin >> monthlyPay;

        //must input a double
        if(cin.fail()){
            cin.clear();
            cin.ignore(200, '\n');
            cout << "Invalid payment\n"; 
        }

        //must have positive monthly pay
        else if (monthlyPay <= 0){
            cout << "Invalid payment\n";
        }
        //must have a greater monthly pay than the interest for that month (greatest interest will be first month)
        else if (monthlyPay <= interestRate*loan){
            cout << "Insufficient payment\n";
        }

    }
 


    cout << endl;
    //Amortization Table
    cout << "**************************************************************************\n"
         << "\tAmortization Table\n"
         << "**************************************************************************\n"
         << "Month\tBalance\t\tPayment\t\tRate\tInterest\tPrincipal\n";
        
    // LOOP TO FILL TABLE
    while (loan > 0){
        //for month "0", , just need to declare total loan
        if (month == 0){
            cout << month++ << "\t$" << loan;
            if (loan < 1000) cout << "\t"; //Formatting
            cout << "\t" << "N/A\t\tN/A\tN/A\t\tN/A\n";
        }
        else{
            
            //last payment
            //once the normal monthly pay is greater than the remaining loan, the final principal should be equal to the remaining loan,
            //and the monthly pay will less than normal
            if (loan - (monthlyPay - interestRate*loan) < 0){

                cout << month++ << "\t$" << 0.00 << "\t\t$" << loan+interestRate*loan << "\t";
                if(monthlyPay < 1000) cout << "\t"; //formatting
                cout << interestRateDisplay << "\t$" << interestRate*loan << "\t\t$" << loan << "\n";
                interestTotal+=interestRate*loan;
                loan = 0;
            }

            //normal monthly calculations
            else{
                cout << month++ << "\t$" << loan-(monthlyPay-interestRate*loan);
                if (loan-(monthlyPay-interestRate*loan) < 1000) cout << "\t"; //Formatting 

                cout << "\t$" << monthlyPay << "\t";
                if (monthlyPay < 1000) cout << "\t"; //formatting
                cout << interestRateDisplay << "\t$" << interestRate*loan << "\t\t$" << monthlyPay - interestRate*loan << "\n";
                interestTotal+=interestRate*loan;
                loan -= (monthlyPay - interestRate*loan); //subtract Principal from loan
            }  

        }
        
    }

    //Formatting and results
    cout << "**************************************************************************\n";
    cout << "\nIt takes " << --month << " months to pay off "
         << "the loan.\n"
         << "Total interest paid is: $" << interestTotal;
    cout << endl;
    return 0;

}
