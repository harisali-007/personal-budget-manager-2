#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
struct expenses{
	string category;
	int amount;
};
class budgetmanager{
	private:
		vector<expenses>expense;
		int t_budget=0;
		int t_expenses=0;
		int number;
		int  cut;
		int new_budget;
	public:
		void addmonthlybudget(){
			if(t_budget>0){
				cout<<"monthly budget is already set to:"<<t_budget<<endl;
			}
			else{
				cout<<"enter your monthly budget:"<<endl;
				cin>>t_budget;
			}
		}
		
		
		void addexpense(){
			if(t_budget == 0){
				cout<<"enter monthly budget first!!"<<endl;
			}
			else{
						expenses exp;
			cout<<"enter expense category: ";
			cin>>exp.category;
			cout<<"enter amount: ";
			cin>>exp.amount;
		
			if(t_expenses +exp.amount >t_budget){
		cout<<"your expenses exceeds the monthly budget upto"<<(t_expenses + exp.amount - t_budget)<<endl;
	}
	else{
		t_expenses += exp.amount;
		cout<<"your remaing budget is:"<<(t_budget - t_expenses)<<endl;
	     cout << "Total expenses after adding: " << t_expenses << endl;
	}
			expense.push_back(exp);
		}
		
			}
	
		
		
		void displayexpenses(){
			for(int i=0;i<expense.size();i++){
				 cout << "Category: " << expense[i].category <<"\n"<< ", Amount: " << expense[i].amount<<"\n";
			}
		}
		
	void savetofile(const string& filename){
		ofstream file(filename);
		if(!file){
			cout<<"no file for opening";
		}
		else{
			file <<t_budget<<"\n";
			file <<t_expenses<<"\n";
			for(int i=0;i<expense.size();i++){
				file<<expense[i].category<<" "<<expense[i].amount<<"\n";;
			}
		}
		file.close();
		cout<<"expense saved to "<<filename<<endl;
			
	}
	
	void loadfromfile(const string& filename){
	ifstream file(filename);
	 if(!file){
	 	cout<<"data cannot be loaded";
	 }
	 expense.clear();
        file>>t_budget;
        file>>t_expenses;
		expenses exp;
		while(file >> exp.category >> exp.amount){
			expense.push_back(exp);
	
		}
	
	file.close();
	cout<<"data loaded successfully";
	}
	
	void editexpense(){
		displayexpenses();
		cout<<"enter the expense you want to edit"<<endl;
		cin>>number;
		if(number<0 || number>expense.size()){
			cout<<"No Expense avilable for editing!!";
		}
		else{
			number--;
			cout<<"the expense you selected is"<<expense[number].category<<":"<<expense[number].amount<<endl;
			t_expenses -= expense[number].amount;
			cout<<"enter new category"<<endl;
			cin>>expense[number].category;
			cout<<"enter amount"<<endl;
			cin>>expense[number].amount;
			t_expenses += expense[number].amount;
             savetofile("budgetmanager.txt");
		}
		
	} 
	void deleteexpense(){
		displayexpenses();
		cout<<"enter the expense you want to delete"<<endl;
		cin>>cut;
		if(cut<0 || cut>>expense.size()){
			cout<<"No Expense avilable for deleting!!";
		}
		else{
			cut--;
			cout<<"the expense you want to delete is"<<expense[cut].category<<":"<<expense[cut].amount<<endl;
		    t_expenses -= expense[cut].amount;
			expense.erase(expense.begin()+cut);
             savetofile("budgetmanager.txt");
			
		}
	} 
	void rolloverbudget() {
    int remaining_budget = t_budget - t_expenses;
    if (remaining_budget < 0) {
        cout << "You cannot roll over. You have overspent by: "<<-remaining_budget<<endl;
    } else {
        cout << "Remaining budget from the previous month: "<<remaining_budget<<endl;
        cout << "Enter the new month's budget: "<<endl;
        cin >> new_budget;
        t_budget = new_budget + remaining_budget;
        t_expenses = 0;  
        cout << "New budget:" << t_budget << endl;
    }
}

	
};
int main(){
	
	budgetmanager m;
int choice;
	
	string filename="budgetmanager.txt";
	m.loadfromfile(filename);
	do {
        cout <<"\n"<<"--- Budget Manager ---"<<endl;
        cout<<"1.Add Mnthly Budget"<<endl;
        cout << "2.Add Expense:"<<endl;
        cout << "3.Display Expenses"<<endl;
        cout << "4.Save Expenses to File"<<endl;
        cout << "5.Edit Expenses"<<endl;
        cout << "6.Delete Expense"<<endl;
        cout << "7.Roll over Budget"<<endl;
        cout << "8.Exit"<<endl;
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        switch (choice) {
        	case 1:
        		m.addmonthlybudget();
        		break;
            case 2:
                m.addexpense();
                m.savetofile(filename);
                break;
            case 3:
                m.displayexpenses();
                break;
            case 4:
                m.savetofile(filename);
                break;
            case 5:
            		m.editexpense();
            		m.savetofile(filename);
            		break;
            case 6:
            	m.deleteexpense();
            	m.savetofile(filename);
            	break;
            case 7:
            	m.rolloverbudget();
            case 8:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
	 return 0;
}










