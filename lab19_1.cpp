#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile (string filename, vector<string> &names, vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename);
    string name;
    while(getline(source,name)){
        int a,b,c,sum =0;
        char d[25];
        char mygrade;
        const char * cSname =name.c_str();
        char format[] ="%[^:]: %d %d %d";
        sscanf(cSname,format,d,&a,&b,&c);
        names.push_back(d);
        sum = a+b+c;
        scores.push_back(sum);
        mygrade = score2grade(sum);
        grades.push_back(mygrade);
    }
}
void getCommand(string &command, string &key){
    string x,y;
    cout << "Please input your command: ";
    getline(cin,x);
    y = toUpperStr(x);
    if(y.find("NAME")==0){
        command = x.substr(0,4);
        key = x.erase(0,5);
    }else if(y.find("GRADE")==0){
        command = x.substr(0,5);
        key = x.erase(0,6);
    }else if(y.find("EXIT")==0){
        command = x;
    }else command = x;
}
void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int x = names.size();
    string makeup;
    for(int j=0;j<x;j++){
        makeup = toUpperStr(names[j]);
        if(makeup == key){
            cout << "---------------------------------\n";
            cout << names[j] << "'s score = " << scores[j]<< "\n";
            cout << names[j] << "'s grade = " << grades[j]<< "\n";
            cout << "---------------------------------\n";
            return;
        }
    }cout << "---------------------------------\n";
     cout<< "Cannot found.\n";
     cout << "---------------------------------\n";
}
void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int x = names.size(),count=0;
    cout << "---------------------------------\n";
    for(int i=0;i<x;i++){
        char g = key[0] ;
        if(g == grades[i]){
            cout << names[i] << " " << "(" << scores[i] << ")";
            cout << "\n";
            count++;
        }
    }
    if(count==0){
    cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}
int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
