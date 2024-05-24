#include <iostream>
#include <string>
#include <stdexcept>


#include "../headers/field.hpp"


#ifdef _WIN32 //windows
    #include <windows.h>
#elif __linux__  // Linux
    #include <unistd.h>
#elif __APPLE__  // macOS
    #include <mach/mach.h>
#endif

using namespace std;


void clear_terminal() {
#ifdef _WIN32 //windows
    system("cls");
#elif __linux__  // Linux
    system("clear");
#elif __APPLE__  // macOS
    system("clear");
#endif
}

int get_int(const string& in){
	try{
		int n = stoi(in);
		return n;// return number if conversion happened correctly
	}catch(const invalid_argument& e){
		return -1;//invalid position returned
	}
}


int main() {

    int side_s = 10;
    int mines = 10;
    mine_field mf(side_s, mines);

    bool playing = true;
    int r = -100, c = -100;
    string input;
    while (playing) {
        if(mf.end_game()){
            break;
        }
        clear_terminal();
        cout << "MINED FIELD";
        if (!(r == -100 && c == -100)) {
            cout << " -> Played " << r << " - " << c;
        }
        cout << endl;
        cout << "State of the field (# covered; 0 - 8 already clicked)" << endl;
        mf.print();

        cout << "Insert the row coordinate 0 - " << side_s << ": ";
        getline(cin, input);
	r = get_int(input) ;
        cout << "Insert the column coordinate 0 - " << side_s << ": ";
        getline(cin, input);
	c = get_int(input);
        if (mf.place_exists(r, c)) {
            playing = mf.played(r, c);
        }
    }
    cout << endl;
    cout << ((mf.getMines() == mines) ? "Hai vinto" : "Hai perso") << endl;
    mf.end_print();

    return 0;
}
