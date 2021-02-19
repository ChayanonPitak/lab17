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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string list;
    while(getline(source, list))
    {
        const char *listchar = list.c_str();
        char listName[100];
        int listScore[3];
        sscanf(listchar, "%[^:]: %d %d %d", listName, &listScore[0], &listScore[1], &listScore[2]);
        names.push_back(listName);
        int sumScore = listScore[0]+listScore[1]+listScore[2];
        scores.push_back(sumScore);
        grades.push_back(score2grade(sumScore));
    }
    return;
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    getline(cin, key);
    key.erase(0,1);
    return;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool isFound = false;
    int index;
    cout << "---------------------------------\n";
    for (unsigned int i = 0 ; i < names.size() ; i++)
    {
        if (toUpperStr(names[i]) == key) {isFound = true; index = i; break;}
    }
    if (isFound)
    {
        cout << names[index] << "'s score = " << scores[index] << endl;
        cout << names[index] << "'s grade = " << grades[index] << endl;
    }
    else cout << "Cannot found.\n";
    cout << "---------------------------------\n";
    return;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool isFound = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0 ; i < names.size() ; i++)
    {
        string studentGrade(1,grades[i]);
        if (studentGrade == key)
        {
            isFound = true;
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    if (!isFound) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
    return;
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
