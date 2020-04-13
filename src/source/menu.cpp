#include <iostream>

using namespace std;

static const string mainMenyText = "Please choose from the following options: \n"  
    "\t1 - Create a new scan\n"                      
    "\t2 - Print out current data\n"                 
    "\t3 - Remove available data from a Network\n"   
    "At any time press 0 or CTR + C to exit\n\n";

static const string menu2Text = "Exporting data to:\n"       
    "\t1 - PDF\n"                  
    "\t2 - Text file\n"            
    "\t3 - Show in terminal only\n\n";

static const string menu3Text = "";

int choiceEvaluation(bool& validChoice)
{
    int choice = -1;
    cin  >> choice;
    validChoice = choice < 0 || choice > 3;
    
    if(!validChoice)
        cout << "Choice number '" << choice << "' is not a valid option" << endl;
}

int mainMenu()
{
    int choice = -1;
    bool validChoice = false;;
    while(!validChoice)
    {
        cout << "Please choose from the following options:"     << endl;
        cout << "1 - Create a new scan"                         << endl;
        cout << "2 - Print out current data"                    << endl;
        cout << "3 - Remove available data from a Network"      << endl;
        cout << "At any time press 0 or CTR + C to exit"        << endl;
        choice = choiceEvaluation(validChoice);
    }
    return choice;
}

int menuChoice2()
{
    int choice = -1;
    bool validChoice = false;
    while(!validChoice)
    {
        cout << "Exporting data to:"        << endl;
        cout << "1 - PDF"                   << endl;
        cout << "2 - Text file"             << endl;
        cout << "3 - Show in terminal only" << endl;
        choice = choiceEvaluation(validChoice);
    }
    return choice;
}   

int menuChoice3()
{

}
