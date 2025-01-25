#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class Student;

template<class K, class Student>

struct node
{
public:
	K key;
	Student value;
	node* leftChild;
	node* rightChild;
};

template<class K>

class specialBST
{
public:
	node<K,Student>* root;
	bool insert_flag;      //flag to check while inserting
	bool search_flag;      // flag to check while searching
	vector<Student> traverse;
	specialBST()
	{
		root = NULL;
		insert_flag = 0;
		search_flag = 0;
	}

	node<K,Student>* insert(node<K,Student>*& root, K key, Student val)
	{
		if (root == NULL)
		{
			node<K,Student>* temp = new node<K,Student>();
			temp->key = key;
			temp->value = val;
			temp->leftChild = NULL;
			temp->rightChild = NULL;
			insert_flag = true;
			return temp;
		}
		else if (root->key == key)
		{
			return nullptr;          //no need to insert in BST
		}
		else if (root->key < key)   //  right side
		{
			node<K,Student>* temp = insert(root->rightChild, key, val);

			if (root == NULL)
			{
				return root;
			}

			root->rightChild = temp->leftChild;
			temp->leftChild = root;
			return temp;

		}
		else                        //  left side 
		{
			node<K,Student>* temp = insert(root->leftChild, key, val);
			if (root == NULL)
			{
				return root;
			}
			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}
	}


	node<K,Student>* search(node<K,Student>*& root, K key)
	{
		if (root == NULL)
		{
			return nullptr;    //not found
		}
		else if (root->key == key)
		{
			search_flag = true;   //set flag true
			return root;          
		}
		else if (root->key < key)
		{
			node<K,Student>* temp = search(root->rightChild, key);
			if (temp == NULL)
			{
				return root;       // if not found then move last accessed noe to top
			}
			root->rightChild = temp->leftChild;
			temp->leftChild = root;
			return temp;
		}
		else
		{
			node<K,Student>* temp = search(root->leftChild, key);
			if (temp == NULL)
			{
				return root;      // if not found then move last accessed node to top
			}
			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}

	}

	node<K,Student>* deleting(node<K,Student>*& root, K key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->key > key)
		{
			node<K, Student>* temp = deleting(root->leftChild, key);

			if (temp == nullptr)
			{
				return root;
			}

			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}
		else if (root->key < key)
		{
			node<K, Student>* temp = deleting(root->rightChild, key);

			if (temp == nullptr)
			{
				return root;
			}

			root->rightChild = temp->leftChild;
			temp->leftChild = root;
			return temp;
		}

		else
		{
			search_flag = true;
			node<K, Student>* temp = root;

			if (root->rightChild == nullptr)
			{
				root = root->leftChild;
				delete temp;
				return root;
			}

			if (root->leftChild == nullptr)
			{
				root = root->rightChild;
				delete temp;
				return root;
			}


			else
			{
				node<K, Student>* next_largest = getNODE(root->rightChild);  // next smallest node
				root->key = next_largest->key;
				root->value = next_largest->value;
				root->rightChild = deleting(root->rightChild, next_largest->key);
				return root->rightChild;
			}
		}
	}
	node<K,Student>* getNODE(node<K,Student>*& root)
	{
		while (root != nullptr && root->leftChild != nullptr)
		{
			root = root->leftChild;
		}
		return root;
	}

	void inOrder(node<K,Student>*& root)
	{
		if (root == NULL)
		{
			return;
		}
		inOrder(root->leftChild);

		traverse.emplace_back(root->value);  
		
		inOrder(root->rightChild);
	}

	void levelWise(node<K,Student>*& root)
	{  

		if (root == nullptr) return;
		queue<node<K,Student>*> que;
		que.push(root);
		while (!que.empty())
		{
			node<K,Student>* front = que.front();
			que.pop();
			traverse.emplace_back(front->value);
			
			if (front->leftChild != nullptr)
			{
				que.push(front->leftChild);
			}
			if (front->rightChild != nullptr)
			{
				que.push(front->rightChild);
			}
		}
	}


	// wraper functions
	vector<Student>* inOrder()
	{
		traverse.clear();
		inOrder(root);
		cout << endl;
		return &traverse;
	}

	vector<Student>* levelWise()
	{
		traverse.clear();
		levelWise(root);
		cout << endl;
		return &traverse;
	}

	bool insert(K key, Student val)
	{
		insert_flag = false;
		root = insert(root, key, val);
		return insert_flag;
	}

	Student* search(K key)
	{
		search_flag = false;
		root = search(root, key);
		if (search_flag == true)
		{
			return &root->value;
		}
		else
		{
			return nullptr;
		}
		cout << endl;
	}

	bool deleting(K key)
	{
		search_flag = false;
		root = deleting(root, key);
		return search_flag;
	}



	void destroy(node<K, Student>* root)
	{
		if (root == nullptr)
		{
			return;
		}
		destroy(root->leftChild);
		destroy(root->rightChild);
		delete root;
	}

	~specialBST()
	{
		destroy(root);
	}
};


class Student : public specialBST<int>
{
public:
	int rollNumber;
	string firstName;
	string lastName;
	int batch;
	string department;
	float cgpa;
	int totalStudents;

	Student()
	{
		rollNumber = 0;
		firstName = "";
		lastName = "";
		batch = 0;
		department = "";
		cgpa = 0.0;
		totalStudents = 0;
	}

	Student(int roll,  string& first,  string& last, int b, string& dept, float cg) :
     rollNumber(roll), firstName(first), lastName(last), batch(b), department(dept), cgpa(cg) {}
};

//template<class S>
class StudentList:public specialBST<int>
{
public:

	Student studentBST;
	

	bool InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
	{
		if (studentBST.search(rollNumber) != nullptr)
		{
			cout << "Error: Student with Roll Number " << rollNumber << " already exists." << endl;
			return false;
		}
		else
		{
			Student temp(rollNumber, firstName, lastName, batch, department, cgpa);
			studentBST.insert(rollNumber, temp);
			studentBST.totalStudents++;
			return true;
		}
	}

	bool deleteStudent(int rollNumber)
	{
		if (studentBST.deleting(rollNumber))
		{
			studentBST.totalStudents--;
			return true;
		}
		else
		{
			return false;
		}
	}

	void searchStudent(int rollNUMBER)
	{
		Student *temp = studentBST.search(rollNUMBER);
		
		if (temp)
		{
			cout << "ROLL Number :" << rollNUMBER<< endl;
			cout << "First Name : " << temp->firstName<< endl;
			cout << "Last Name : " << temp->lastName<< endl;
			cout << "Batch NO : " << temp->batch<< endl;
			cout << "Department Name : " << temp->department<< endl;
			cout << "CGPA : " << temp->cgpa<< endl;
			cout << "First Name : " << temp->firstName<< endl;
		}

		else
		{
			cout << "Student doesn't exist\n";
		}
	}


	void printALLstudents()
	{
		vector<Student> *temp = studentBST.inOrder();
		
		/*cout << "Roll Number | First Name | Last Name | Batch | Department | CGPA" << endl;
        cout << "------------------------------------------------------------------" << endl;*/
		
		for ( auto& student : *temp)
		{
			cout << student.rollNumber << "	|"
				<< student.firstName << "	|"
				<< student.lastName << "	|"
				<< student.batch << "	|"
				<< student.department << "	 |"
				<< student.cgpa << "	|" << endl;
		}
	}


	bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch,  string newDepartment, float newCgpa)
	{
		// Check if the old roll number exists
		Student* existingStudent = studentBST.search(oldRollNumber);
		if (existingStudent == nullptr) 
		{
			cout << "Error: Student with Roll Number " << oldRollNumber << " not found." << endl;
			return false;
		}

		// If the roll number is not changing, update the attributes directly
		if (oldRollNumber == newRollNumber) 
		{
			existingStudent->firstName = newFirstName;
			existingStudent->lastName = newLastName;
			existingStudent->batch = newBatch;
			existingStudent->department = newDepartment;
			existingStudent->cgpa = newCgpa;
			return true;
		}
		else 
		{
			// Check if the new roll number already exists
			if (studentBST.search(newRollNumber) != nullptr)
			{
				cout << "Error: Student with Roll Number " << newRollNumber << " already exists." << endl;
				return false;
			}

			// Delete the old roll number and insert the updated student with the new roll number
			studentBST.deleting(oldRollNumber);
			Student updatedStudent(newRollNumber, newFirstName, newLastName, newBatch, newDepartment, newCgpa);
			studentBST.insert(newRollNumber, updatedStudent);
			return true;
		}
		
	}

	int getTotal()
	{
		return studentBST.totalStudents;
	}

};


bool INSERT(StudentList &students)
{
	//system("CLS");
	int rollNO;
	string fNAME;
	string lNAME;
	string department;
	int batch;
	float cgpa;

	cout << "Enter roll number:";
	cin >> rollNO;
	while (rollNO <= 0)
	{
		cout << "Please enter correct roll number:";
		cin >> rollNO;
	}
	cout << "Enter first name:";
	cin >> fNAME;
	cout << "Enter last name:";
	cin >> lNAME;
	cout << "Enter the bacth no:";
	cin >> batch;
	while (batch <= 0)
	{
		cout << "Please enter correct batch number:";
		cin >> batch;
	}
	cout << "Enter the name of department:";
	cin >> department;
	cout << "Enter the cgpa:";
	cin >> cgpa;
	while (cgpa < 0)
	{
		cout << "Please enter correct cgpa:";
		cin >> cgpa;
	}

	return students.InsertNewStudent(rollNO, fNAME, lNAME, batch, department, cgpa);

}

bool DELETE(StudentList &students)
{
	int rollNO;
	cout << "Enter a roll number to be deleted\n";
	cin >> rollNO;
	while (rollNO <= 0)
	{
		cout << "Please enter the correct roll number\n";
		cin >> rollNO;
	}
	return students.deleteStudent(rollNO);

}

void SEARCH(StudentList &students)
{
	int rollNUMBER;
	cout << "Enter the roll number of the student to be searched\n";
	cin >> rollNUMBER;
	while (rollNUMBER <= 0)
	{
		cout << "Please enter the correct roll number\n";
		cin >> rollNUMBER;
	}
	students.searchStudent(rollNUMBER);
}

bool UPDATE(StudentList &students)
{
	//system("CLS");
	int OldrollNO;
	int NewrollNO;
	string fNAME;
	string lNAME;
	string department;
	int batch;
	float cgpa;

	//cout << "Please enter the data of new student in the order:Old Roll Number, New Roll Number, First Name, Last Name, Batch, Department, CGPA\n";
	cout << "Enter old roll number:";
	cin >> OldrollNO;
	while (OldrollNO <= 0)
	{
		cout << "Please enter correct roll number:";
		cin >> OldrollNO;
	}
	cout << "Enter new roll number:";
	cin >> NewrollNO;
	while (NewrollNO <= 0)
	{
		cout << "Please enter correct roll number:";
		cin >> NewrollNO;
	}
	cout << "Enter first name:";
	cin >> fNAME;
	cout << "Enter last name:";
	cin >> lNAME;
	cout << "Enter the bacth no:";
	cin >> batch;
	while (batch <= 0)
	{
		cout << "Please enter correct batch number:";
		cin >> batch;
	}
	cout << "Enter the name of department:";
	cin >> department;
	cout << "Enter the cgpa:";
	cin >> cgpa;
	while (cgpa < 0)
	{
		cout << "Please enter correct cgpa:";
		cin >> cgpa;
	}

	//Update a student

	return students.updateStudent(OldrollNO,NewrollNO, fNAME, lNAME, batch, department, cgpa);
}

void PRINT(StudentList &students)
{
	cout << "All Students:" << students.getTotal();
    students.printALLstudents();
	cout << "------------------------\n";

}


void menu(StudentList &students)
{
	char option;
	//StudentList students;
	cout << "---------------------------------------------------------------------\n\n";
	cout << "Press I to insert a new student \n"
		<< "Press D to delete a student \n"
		<< "Press S to search a student by roll number\n"
		<< "Press U to update the data of a student\n"
		<< "Press P to print all students sorted by roll number\n"
		<< "Press E to exit\n";

	cin >> option;

	if (option == 'I' || option=='i')
	{
		if(INSERT(students))
		{
			cout << "Successfully Inserted\n";
		}
		else
		{
			cout << "Not Successfully Inserted\n";
		}
		menu(students);
	}
	if (option == 'D'||option=='d')
	{
		if (DELETE(students))
		{
			cout << "Successfully Deleted\n";
		}
		else
		{
			cout << "Not Successfully Deleted\n";
		}

		menu(students);
	}
	if (option == 'S'|| option=='s')
	{
		SEARCH(students);

		menu(students);
	}
	if (option == 'U'|| option=='u')
	{
		if (UPDATE(students))
		{
			cout << "Successfully Updated\n";
		}
		else
		{
			cout << "Not Successfully Updated\n";
		}
		menu(students);
	}
	if (option == 'P'||option=='p')
	{
		PRINT(students);
		menu(students);
	}
	if (option == 'E'||option=='e')
	{
		cout << "Take Care \n";
	}
	else 
	{
		cout << "Dear User please Enter the correct option\n";
		menu(students);
	}
}

int main()
{
	
	StudentList students;
	menu(students);

	
	return 0;
}