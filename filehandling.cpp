//assignment 11
// Implementation of a direct access file -Insertion and deletion of a record from a direct 
// access file.

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Record{
    int rollno, div;
    string name, address;
    public:
    Record(string title,string path, int roll, int division){
        this->name=title;
        this->address=path;
        this->rollno=roll;
        this->div=division;
    }
    friend class file;
};
class file{
    string filename;
    fstream input;
    fstream output;
    public:
    file(string title){
        this->filename=title;
    }
    /***************************************/
    //function to write records to the file
    void writeRecord(Record * r, int num){
        output.open(filename,ios::app);
        for(int i=0;i<num;i++){
            output<<r[i].rollno <<","<<r[i].name <<" SE-"<<r[i].div<<","<<r[i].address<<endl;
        }
        output.close();
    }
    /********************************************/
    //function to print all records
    void printRecord(){
        input.open(filename,ios::in);
        while(!input.eof()){
            string record;
            input>> record;
            cout<<record<<endl;
        }
        input.close();
    }

    //function to search
    void searchRecord(int r){
        input.open(filename, ios::in);
        bool isFound= false;
        while(!input.eof()){
            string record;
            input>>record;
            if(int(record[0]-48)==r){
                cout<<"Record found"<<endl;
                cout<< record <<endl <<endl;
                isFound =true;
                break;
            }
        }
        input.close();
        if(!isFound){
            cout<<"Record not found "<<endl;
        }
    }
    /*****************************************************/
    ///////delete ///////////record////////////////
    void deleteRecord(int r){
        input.open(filename, ios::in);
        vector<string>lines;
        while(!input.eof()){
            string record;
            input>>record;
            if((int(record[0])-48)!=r){
                lines.push_back(record);
            }
        }
        input.close();
        output.open(filename,ios::out);
        for(int i=0;i<lines.size();i++){
            output<<lines[i]<<endl;
        }
        output.close();
    }
};

int main(){
    file f("samplpe.txt");
    int choice,roll;
    cout << "Menu:" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Delete Record" << endl;
    cout << "3. Search Record" << endl;
    cout << "4. Display All Records" << endl;
    cout << "5. Exit" << endl;
    while(true){
        cout<<endl<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:{
                string name, address;
                int roll, div;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter address: ";
                cin >> address;
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter division: ";
                cin >> div;
                Record newRecord(name, address, roll, div);
                f.writeRecord(&newRecord, 1);
                cout << "Record added successfully!" << endl;
                break;}
            case 2:{
                cout << "Enter roll number to delete: ";
                cin >> roll;
                f.deleteRecord(roll);
                cout << "Record deleted successfully!" << endl;
                break;}
            case 3: {
                cout << "Enter roll number to search: ";
                cin >> roll;
                f.searchRecord(roll);
                break;
            } 
            case 4: {
                cout << "Records:" << endl;
                f.printRecord();
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice!" << endl;   
        }
    }
    return 0;
}
