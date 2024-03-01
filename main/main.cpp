#include <iostream>
#include <fstream>
using namespace std;
const int gradeNumber = 8;
struct Profile
{
  char fullName[30]; 	
  char sex;
	int group;
	int id;
	int grades[8];
	char depart[9];
};

int lenOfCharArray(char *array)
{
	int len = 0;
	while (*(array+len) != 0)
	{
		len += 1;
	}
	return len;
}
void printCharArray(char *array)
{
	int len = lenOfCharArray(array);
	for (int i = 0; i < len; ++i)
	{
		cout << array[i];
	}
}

void creatingRecord()
{
	Profile student;          
	cin.clear();
	cout << "Введите фамилию студента: ";
	cin >> student.fullName;
	cout << endl;
	cin.clear();
	cout << "Введите группу студента: ";
	cin >> student.group; 
	cout << endl;
	cin.clear();
	cout << "Введите номер студента: ";
	cin >> student.id; 
	cout << endl;
	cin.clear();
	cout << "Введите пол студента: ";
	cin >> student.sex; 
	cout << endl;
	cin.clear();
	cout << "Введите форму обучения студента: ";
	cin >> student.depart; 
	cout << endl;
	cin.clear();
	cout << "Введите 3 оценки за экзамен и 5 за диф зачеты" << endl;
	for (int i = 0; i < gradeNumber; i++) 
	{
		cin >> student.grades[i];
		cin.clear();
	}
	cout << endl;
  int temp = 0;
	for (int i = 0; i < gradeNumber; i++)
	{
		if (student.grades[i] == 2) 
			temp++;
	}
	if (temp == 0)
	{
		ofstream database; 	
		database.open("students.txt", ios::app); 
		if (!database.is_open()) 	
			cout << '\n' << "Ошибка сохранения"; 
		else 
		{
			database << student.fullName << '\n';
			database << student.group << '\n';
			database << student.id << '\n';
			database << student.sex << '\n';
			database << student.depart << '\n';
			for (int i = 0; i < gradeNumber; i++)
				database << student.grades[i] << " ";
			database << '\n';
			database.close();
			cout << '\n' << "Профиль сохранен в базу";
		}
	}
	else 
		cout << '\n' << "Этот студент будет исключен. Профиль не будет сохранен в базу";
}

int countStudents()
{
	ifstream database("students.txt");
	if (database.is_open())
	{
		int temp = 0;
		string data;
		while (!database.eof())
		{
			getline(database, data);
			temp++;
		}
		database.close();
		int n;
		n = temp / 6;
		return n;
	}
	else return 0;
}

void writeToFile(Profile *student)
{
	int size = countStudents();
  int temp = 0;
	ofstream database; 	
	database.open("students.txt"); 
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < gradeNumber; j++)
		{
			if (student[i].grades[j] == 2) 
				temp++;
		}
		if (temp == 0)
		{
			if (!database.is_open()) 	
				cout << '\n' << "Ошибка сохранения"; 
			else 
			{
				database << student[i].fullName << '\n';
				database << student[i].group << '\n';
				database << student[i].id << '\n';
				database << student[i].sex << '\n';
				database << student[i].depart << '\n';
				for (int j = 0; j < gradeNumber; j++)
					database << student[i].grades[j] << " ";
				database << '\n';
			}
		}
		else
		{
			cout << "У одного из студентов есть оценка 2, редактирование не удалось" << endl;
		}
	}
	database.close();
}

void readFromFile(Profile *student)
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "База пуста" << endl;
		else
		{
			for (int i = 0; i < size; i++) 
			{
				database >> student[i].fullName;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < gradeNumber; j++)
					database >> student[i].grades[j];
			}
			database.close(); 
		}
	}
}

void printStudentData(Profile *student, int i)
{
	cout << student[i].id << " ";
	printCharArray(student[i].fullName);
	cout << '\n';
	cout << student[i].sex << '\n';
	cout << "Семестровые оценки: ";
	for (int j = 0; j < gradeNumber; j++)
		cout << student[i].grades[j] << " ";
	cout << "\n\n";
}

void showData()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Ошибка открытия файла";
	else
	{
		int temp;
		temp = countStudents(); 
		if (temp == 0)
			cout << "Файл пуст";
		else
		{
			string data;
			while (!database.eof())
			{
				getline(database, data); 
				cout << data << '\n';
			}
		}
		database.close();
	}
}

void showGroup()
{
	int n;
	cout << "Введите номер группы: " << endl;
	cin >> n;
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Ошибка!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "База пуста" << endl;
		else
		{
			Profile *student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				database >> student[i].fullName;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++) 
			{
				if (student[i].group == n)
				{
					cout << student[i].id << " " ;
					printCharArray(student[i].fullName);
					cout << '\n';
					cout << student[i].sex << '\n';
					cout << "Семестровые оценки: ";
					for (int j = 0; j < gradeNumber; j++)
						cout << student[i].grades[j] << " ";
					cout << "\n\n";
					temp++;
				}
			}
			if (temp == 0)
				cout << "Ни одной записи не найдено" << endl;
			delete[] student;
		}
	}
}

void showSex()
{
	int countMale = 0;
	int size = countStudents();
	Profile *student = new Profile[size];
	readFromFile(student);
	for (int i = 0; i < size; ++i)
	{
		if (student[i].sex == 'm')
			countMale +=  1;
	}
	cout << "В файле" << endl;
	cout <<  countMale << " студентов мужского пола" << endl;
	cout << (size - countMale) << " студентов женского пола" << endl;
}

void showRate()
{
	int k;
	cout << "Введите номер: ";
	cin >> k;
	cout << endl;
	int temp = 0;
	int size = countStudents();
	Profile *student = new Profile[size];
	readFromFile(student);
	for (int i = 0; i < size; ++i)
	{
		if (student[i].id == k)
		{
			printStudentData(student, i);
			temp += 1;
		}
	}
	if (temp == 0)
	{
		cout << "Нет студентов с id " << k << endl;
	}
}

int sumOfGrades(int *grades)
{
	int s = 0;
	for (int i = 0; i < gradeNumber; ++i)
	{
		s += grades[i];
	}
	return s;
}

void scholarshipStatus()
{	
	int size = countStudents();
	Profile *student = new Profile[size];
	readFromFile(student);
	cout << "Студенты не получающие стипендию:" << endl;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < gradeNumber; ++j)
		{
			if (student[i].grades[j] == 3)
			{
				printStudentData(student, i);
				break;
			}
		}
	}
	cout << "Студенты учащиеся на хорошо и отлично: " << endl;
	for (int i = 0; i < size; ++i)
	{
		int flag = 0;
		for (int j = 0; j < gradeNumber; ++j)
		{
			if (student[i].grades[j] == 3)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			printStudentData(student, i);
	}
	cout << "Студенты отличники: " << endl;
	for (int i = 0; i < size; ++i)
	{
		if (sumOfGrades(student[i].grades) == gradeNumber*5)
		{
			printStudentData(student, i);
		}
	}
}

float averageScore(int *grades)
{
	float sum = 0;
	for (int i = 0; i < gradeNumber; ++i)
		sum += grades[i];
	return sum/gradeNumber;
}

void bubbleSort(Profile *student)
{
	int size = countStudents();
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = 0; j < size-1; ++j)
		{
			if (averageScore(student[j].grades) < averageScore(student[j+1].grades))
			{
				swap(student[j], student[j+1]);
			}
		}
	}
}

void averageScoreRating()
{
	int size = countStudents();
	Profile *student = new Profile[size];
	readFromFile(student);
	bubbleSort(student);
	for (int i = 0 ; i < size; ++i)
	{
		cout << '(' << averageScore(student[i].grades) << ')' << ' ';
		printStudentData(student, i);
	}
}


void editRecord()
{
	int size = countStudents();
	Profile *student = new Profile[size];
	readFromFile(student);
	cout << "Введите номер студента в базе для редактирования: ";
	int studentNumber;
	cin >> studentNumber;
	cout << endl;
	cout << "Введите пункт профиля студента для редактирования: ";
	int memberNumber;
	cin >> memberNumber;
	cout << endl;
	switch (memberNumber)
	{
		case 1:
		{
			cout << "Введите новую фамилию студента: ";
			cin >> student[studentNumber-1].fullName;
			cout << endl;
			break;
		}
		case 2:
		{
			cout << "Введите новую группу студента: ";
			cin >> student[studentNumber-1].group;
			cout << endl;
			break;
		}
		case 3:
		{
			cout << "Введите новый номер студента: ";
			cin >> student[studentNumber-1].id;
			cout << endl;
			break;
		}
		case 4:
		{
			cout << "Введите новую форму обучения студента: ";
			cin >> student[studentNumber-1].depart;
			cout << endl;
			break;
		}
		case 5:
		{
			cout << "Введите номер оценки для изменения: ";
			int gradePosition;
			cin >> gradePosition;
			cout << endl;
			cout << "Введите новую оценку: ";
			int grade;
			cin >> grade;
			cout << endl;
			student[studentNumber-1].grades[gradePosition-1] = grade;
			break;
		}
	}
	writeToFile(student);
}

int menu()
{
	cout << "1.Создание новой записи о студенте." << endl;
	cout << "2.Внесение изменений в уже имеющуюся запись." << endl;
	cout << "3.Вывод всех данных о студентах." << endl;
	cout << "4.Вывод информации обо всех студентах группы N." << endl;
	cout << "5.Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию." << endl;
	cout << "6.Вывод количества студентов мужского и женского пола." << endl;
	cout << "7.Вывод данных о статусе стипендии для студентов;" << endl;
	cout << "8.Вывод данных о студентах, имеющих номер в списке – k." << endl;
	int choice;
	cin >> choice;
	return choice;
}

int main()
{
	int exit = 0;
	while (exit != 1)
	{
		switch (menu())
		{
			case 1:
			{
				creatingRecord();
				break;
			}
			case 2:
			{
				editRecord();
				break;
			}
			case 3:
			{
				showData();
				break;
			}
			case 4:
			{
				showGroup();
				break;
			}
			case 5:
			{
				averageScoreRating();
				break;
			}
			case 6:
			{
				showSex();
				break;
			}
			case 7:
			{
				scholarshipStatus();
				break;
			}
			case 8:
			{
				showRate();
				break;
			}
			default:
			{
				cout << "Неверно задан пункт меню" << endl;
			}
		}
	cout << "Продолжить выполнять программу (0 - да, 1 - нет): ";
	cin >> exit;
	cout << endl;
	}
	return 0;
}
