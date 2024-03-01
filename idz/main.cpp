#include <iostream>
#include <fstream>
using namespace std;

struct Profile
{
  char name[50];
  char sex;
  int age;
  char city[30];
  int averageFinalsScore;
  bool originalCertificateStatus;
  float averageCertificateScore;
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
	Profile applicant;          
	cin.clear();
	cout << "Введите ФИО абитуриента: ";
	cin >> applicant.name;
	cout << endl;
	cin.clear();
	cout << "Введите пол абитуриента: ";
	cin >> applicant.sex; 
	cout << endl;
	cin.clear();
	cout << "Введите возраст абитуриента: ";
	cin >> applicant.age; 
	cout << endl;
	cin.clear();
	cout << "Введите город студента: ";
	cin >> applicant.city; 
	cout << endl;
	cin.clear();
	cout << "Введите средний балл за ЕГЭ: ";
	cin >> applicant.averageFinalsScore; 
	cout << endl;
	cin.clear();
	cout << "Введите статус оригинала аттестата: ";
	cin >> applicant.originalCertificateStatus;
	cin.clear();
	cout << endl;
	cout << "Введите средний балл аттестата:";
	cin >> applicant.averageCertificateScore;
	cin.clear();
	cout << endl;
	ofstream database; 	
	database.open("applicants.txt", ios::app); 
	if (!database.is_open()) 	
		cout << '\n' << "Ошибка сохранения"; 
	else 
	{
		database << applicant.name << '\n';
		database << applicant.sex << '\n';
		database << applicant.age << '\n';
		database << applicant.city << '\n';
		database << applicant.averageFinalsScore << '\n';
		database << applicant.originalCertificateStatus << '\n';
		database << applicant.averageCertificateScore << '\n';
		database.close();
		cout << '\n' << "Профиль сохранен в базу" << endl;
	}
}

int countApplicants()
{
	ifstream database("applicants.txt");
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
		n = temp / 7;
		return n;
	}
	else return 0;
}

void writeToFile(Profile *applicant)
{
	int size = countApplicants();
  int temp = 0;
	ofstream database; 	
	database.open("applicants.txt"); 
	for (int i = 0; i < size; ++i)
	{
			if (!database.is_open()) 	
				cout << '\n' << "Ошибка сохранения"; 
			else 
			{
				database << applicant[i].name << '\n';
				database << applicant[i].sex << '\n';
				database << applicant[i].age << '\n';
				database << applicant[i].city << '\n';
				database << applicant[i].averageFinalsScore << '\n';
				database << applicant[i].originalCertificateStatus << '\n';
				database << applicant[i].averageCertificateScore << '\n';
			}
	}
	database.close();
}

void readFromFile(Profile *applicant)
{
	ifstream database("applicants.txt");
	if (!database.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countApplicants();
		if (size == 0)
			cout << "База пуста" << endl;
		else
		{
			for (int i = 0; i < size; i++) 
			{
				database >> applicant[i].name;
				database >> applicant[i].sex;
				database >> applicant[i].age;
				database >> applicant[i].city;
				database >> applicant[i].averageFinalsScore;
				database >> applicant[i].originalCertificateStatus;
				database >> applicant[i].averageCertificateScore;
			}
			database.close(); 
		}
	}
}

void printApplicantData(Profile *applicant, int i)
{
	printCharArray(applicant[i].name);
	cout << endl;
	cout << "Возраст: " << applicant[i].age;
	cout << endl;
	cout << "Город: ";
	printCharArray(applicant[i].city);
	cout << endl;
	cout << "Средний балл ЕГЭ: ";
	cout << applicant[i].averageFinalsScore;
	cout << endl;
	cout << "Оригинал аттестата: ";
	if (applicant[i].originalCertificateStatus)
		cout << "Да" << endl;
	else
		cout << "Нет" << endl;
	cout << "Средний балл аттестата: " << applicant[i].averageCertificateScore;
	cout << endl << endl;
}

void printInfoLess18()
{
	int size = countApplicants();
	Profile *applicant = new Profile[size];
	readFromFile(applicant);
	for (int i = 0; i < size; ++i)
	{
		if (applicant[i].age < 18)
			printApplicantData(applicant, i); 
	}
}

void printInfoEgeMore85()
{
	int size = countApplicants();
	Profile *applicant = new Profile[size];
	readFromFile(applicant);
	for (int i = 0; i < size; ++i)
	{
		if (applicant[i].averageFinalsScore > 85)
			printApplicantData(applicant, i); 
	}
}

bool charArrayComparasing(char *array1, char *array2)
{
	if (lenOfCharArray(array1) == lenOfCharArray(array2))
	{
		bool f = 0;
		for (int i = 0; i < lenOfCharArray(array1); ++i)
		{
			if (array1[i] != array2[i])
			{
				f = 1;
				return 0;
				break;
			}
		}
		if (f == 0)
			return 1;
	}
	return 0;
}

void printNoneresident()
{
	int size = countApplicants();
	Profile *applicant = new Profile[size];
	readFromFile(applicant);
	char SPB[] = "Saint-Petersburg";
	for (int i = 0; i < size; ++i)
	{
		if (!charArrayComparasing(SPB, applicant[i].city))
			printApplicantData(applicant, i); 
	}
}

void printInfoPerfectCertificate()
{
	int size = countApplicants();
	Profile *applicant = new Profile[size];
	readFromFile(applicant);
	for (int i = 0; i < size; ++i)
	{
		if (applicant[i].averageCertificateScore == 5.0)
			printApplicantData(applicant, i); 
	}
}

int menu()
{
	cout << "1. Создать новую запись абитуриента" << endl;
	cout << "2. Вывод всех абитуриентов возрастом меньше 18 лет" << endl;
	cout << "3. Вывод всех абитуриентов со средним баллом ЕГЭ больше 85" << endl;
	cout << "4. Вывод всех абитуриентов с аттестатом с отличием" << endl;
	cout << "5. Вывод всех иногородних (не из Санкт-Петербурга) абитуриентов" << endl;
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
				printInfoLess18();
				break;
			}
			case 3:
			{
				printInfoEgeMore85();
				break;
			}
			case 4:
			{
				printInfoPerfectCertificate();
				break;
			}
			case 5:
			{
				printNoneresident();
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
