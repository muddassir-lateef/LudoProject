#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

class log{
    private:
    string filename;
    public:
    log(const string file){
        this->filename = file;
    }
    void write(string line){
        ofstream out;
        out.open(filename, ios::app);
        out<<line<<"\t";
        time_t now = time(0);
        char* dt = ctime(&now);
        out<<dt;
    }
};