#include <iostream>
#include <fstream>
#include <tgmath.h>
#include <stack>
#include <queue>

using namespace std;

void openFiles (ifstream &infile, ofstream &outfile);
void reverseSong(ifstream& infile, ofstream &outfile, std::string firstLine, std::string secondLine);
void slowDownSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine);
void speedUpSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine);
void pauseSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine);
void remix(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine);

int main() {

    // open input & output data files
    std::cout << "Welcome to the Music Maker" << std::endl;

    ifstream infile;
    ofstream outfile;
    openFiles(infile, outfile);

    string firstLine, secondLine;

    getline(infile,firstLine);    // read in the first line
    getline(infile,secondLine);   // read in the second line

    int choice = 0;

    std::cout << "Press 1 for reverse\nPress 2 for slowdown\nPress 3 for speedup\nPress 4 for pause\nPress 5 for remix!!!" << std::endl;
    std::cout << "Enter a choice: ";
    cin >> choice;

    while(choice <= 0 || choice > 5){
        std::cout << "Invalid value. Enter a choice: ";
        cin >> choice;
    }

    if(choice == 1){
        reverseSong(infile, outfile, firstLine, secondLine);
    } else if(choice == 2){
        slowDownSong(infile, outfile, firstLine, secondLine);
    } else if(choice == 3){
        speedUpSong(infile, outfile, firstLine, secondLine);
    } else if(choice == 4){
        pauseSong(infile, outfile, firstLine, secondLine);
    } else if(choice == 5) {
        remix(infile, outfile, firstLine, secondLine);
    }

    infile.close();
    outfile.close();

    cout << "Done." << endl;

    cout << "press enter to exit";
    cin.get();
    cin.get();

    return 0;
}

// open input and output files
// pre: user is prepared to enter file names at the keyboard
// post: files have been opened
void openFiles(ifstream &infile, ofstream &outfile) {

    // open input data file
    string inFileName;
    cout << "Enter the name of the input file: ";
    cin >> inFileName;
    infile.open(inFileName.c_str());
    if (infile.fail()) {
        cout << "Error opening input data file" << endl;
        cout << "press enter to exit";
        cin.get();
        cin.get();
        exit(1);
    }

    // open output data file
    string outFileName;
    cout << "Enter the name of the output file: ";
    cin >> outFileName;
    outfile.open(outFileName.c_str());
    if (outfile.fail()) {
        cout << "Error opening output data file" << endl;
        cout << "press enter to exit";
        cin.get();
        cin.get();
        exit(1);
    }
}


// reverses a song
// pre: valid dat file
// post: same file but sound numbers are in reverse order
void reverseSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine){

    std::stack <double> sound;
    std::stack <double> timeReverse;

    double val; // value of data being put into the stacks

    // pushes data from file onto stacks
    while(infile >> val){
        timeReverse.push(val);
        infile>>val;
        sound.push(val);
    }

    outfile << firstLine << endl;
    outfile << secondLine << endl;

    // new stack that has the time in the correct order
    std::stack <double> timeCorrect;

    // puts the reversed time stack into a new stack
    while(!timeReverse.empty()){
        timeCorrect.push(timeReverse.top());
        timeReverse.pop();
    }

    // puts the data in the stacks into a new file
    while(!sound.empty()){
        outfile << "  " << timeCorrect.top() << "\t" << sound.top() << std::endl;
        timeCorrect.pop();
        sound.pop();
    }
}

void slowDownSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine){

    std::queue <double> sound;
    std::queue <double> time;

    double val;

    // pushes data from file onto stacks
    while(infile >> val){
        time.push(val);
        time.push(2*val);
        infile>>val;
        sound.push(val);
        sound.push(val);
    }

    outfile << firstLine << endl;
    outfile << secondLine << endl;

    // puts the data in the stacks into a new file
    while(!sound.empty()){
        outfile << "  " << time.front() << "\t" << sound.front() << std::endl;
        time.pop();
        sound.pop();
    }
}

void speedUpSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine){

    std::queue <double> sound;
    std::queue <double> time;

    double val;

    // pushes data from file onto stacks
    while(infile >> val){
        time.push(val);
        infile>>val;
        sound.push(val);
    }

    outfile << firstLine << endl;
    outfile << secondLine << endl;

    // puts the data in the stacks into a new file
    while(!sound.empty()){
        outfile << "  " << time.front() << "\t" << sound.front() << std::endl;
        time.pop();
        sound.pop();
        sound.pop();
    }
}

void pauseSong(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine){

    std::queue <double> sound;
    std::queue <double> time;

    double val;
    double valHalf;

    // pushes data from file onto stacks
    while(infile >> val){

        if(floor(val) == val){
            time.push(val);
            valHalf = val + .2;
            while(val < valHalf){
                sound.push(0);
                infile >> val;

                if(infile >> val){
                    time.push(val);
                }
            }

        } else{
            time.push(val);
            infile >> val;
            sound.push(val);
        }
    }

    outfile << firstLine << endl;
    outfile << secondLine << endl;

    // puts the data in the stacks into a new file
    while(!sound.empty()){
        outfile << "  " << time.front() << "\t" << sound.front() << std::endl;
        time.pop();
        sound.pop();
    }
}

void remix(ifstream &infile,ofstream &outfile, std::string firstLine, std::string secondLine){

    std::queue <double> entireRemix;
    std::queue <double> forward;
    std::stack <double> backward;
    std::stack <double> tmp;
    std::queue <double> time;

    double val;

    double i = 0;
    double checkpoint = .5;
    int sizeOfQueue;

    while(infile >> val){

        if(val >= checkpoint){

            sizeOfQueue = forward.size();

            for(int j = 0; j < sizeOfQueue/2; j++){
                entireRemix.push(forward.front());
                forward.pop();
                i = i + (double) 1 / ((double) 44100);
                time.push(i);
            }

            while(!forward.empty()) {
                entireRemix.push(forward.front());
                backward.push(forward.front());
                forward.pop();
                i = i + (double) 1 / ((double) 44100);
                time.push(i);
            }

            while(!backward.empty()){
                entireRemix.push(backward.top());
                tmp.push(backward.top());
                backward.pop();
                i = i + (double) 1 / ((double) 44100);
                time.push(i);
            }

            while(!tmp.empty()){
                entireRemix.push(tmp.top());
                tmp.pop();
                i = i + (double) 1 / ((double) 44100);
                time.push(i);
            }

            checkpoint = checkpoint + .5;

        } else {
            i = i + (double) 1 / ((double) 44100);
            time.push(i);
            infile >> val;
            forward.push(val);
            infile >> val;
        }
    }

    while(!forward.empty()){
        entireRemix.push(forward.front());
        forward.pop();
    }

    outfile << firstLine << endl;
    outfile << secondLine << endl;

    while(!entireRemix.empty()){
        outfile << "  " << time.front() << "\t" << entireRemix.front() << std::endl;
        time.pop();
        entireRemix.pop();
    }
}