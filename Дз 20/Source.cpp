#include<iostream>
#include <windows.h>
#include<time.h>
#include<iomanip>

using namespace std;

struct Teacher
{
	string l_name;
	string f_name;
};

struct Group
{
	string title;
	Teacher teacher;
};

struct Student
{
	int id = -1;
	string f_name;
	string l_name;
	Group* group = nullptr;
	int* grades = nullptr;
	int gradesCount = 0;
};

struct MarksOfGroup
{
	float* arrMarks = nullptr;
	int countS = 0;
};

//-----------------------------------------------------------------------------------------

int maxId = 1000;

void doFullScreen()
{
	COORD dummy;
	bool ret = SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), 1, &dummy);
}


void printStudent(const Student* s)
{
	cout << "id: " << s->id << '\n';
	cout << "Имя: " << s->l_name << ' ' << s->f_name << '\n';
	cout << "Группа: " << s->group->title << '\n';
	cout << "Оценки: ";
	for (int i{}; i < s->gradesCount; ++i)
		if(s->grades[i] > 0)
			cout << s->grades[i] << ", ";

	cout << "\n===================================\n";
}

int menuSt()
{
	int choice;

	cout << "\n    [1] Добавить студента";
	cout << "    [2] Удалить студента";
	cout << "    [3] Поиск студента";
	cout << "\t\t\t\t\t\t\t[0] Назад\n";

	do {
		cin >> choice;
	} while (choice < 0 || choice > 3);
	
	return choice;
}

Student* addStudent(Student* s, int& countS, Group* groups, int countG)
{
	system("cls");
	int choice;
	Student* arr = new Student[countS + 1];

	for (int i{}; i < countS; ++i)
		arr[i] = s[i];

	arr[countS].id = arr[countS - 1].id + 1;

	cout << "Введите фамилию и имя студента: ";
	cin >> arr[countS].l_name >> arr[countS].f_name;


	system("cls");
	cout << "Выберите группу\n[1] g131\n[2] g132\n[3] g133\n[4] g134\n[5] g135\n[6] g136\n[7] g137\n";
	cin >> choice;
	arr[countS].group = &groups[choice-1];


	arr[countS].gradesCount = 10;
	arr[countS].grades = new int[arr[countS].gradesCount];
	for (int i{}; i < arr[countS].gradesCount; ++i)
		arr[countS].grades[i] = 0;

	
	system("cls");
	delete[] s;
	++countS;
	return arr;
}

Student* remStudent(Student* s, int& countS, Group* groups, int countG)
{
	int choice;
	int remStudentId;
	bool inputValid = false;
	Student* arr = new Student[countS - 1];

	do{
		system("cls");
		cout << "Введите id студента, которого хотите удалить: ";
		cin >> remStudentId;

		for (int i{}; i < countS; ++i)
			if (s[i].id == remStudentId)
				inputValid = true;
	} while (inputValid == false);
	
	int currentId = 0;
	for (int i{}; i < countS; ++i)
	{
		if (remStudentId != s[i].id)
		{
			arr[currentId] = s[i];
			++currentId;
		}
	}

	system("cls");
	delete[] s;
	--countS;
	return arr;
}


void transferStudent(Student* s, int index, Group* groups, int countG)
{
	int choice;

	do {
		system("cls");

		cout << "Выберите группу\n[1] g131\n[2] g132\n[3] g133\n[4] g134\n[5] g135\n[6] g136\n[7] g137\n";
		cin >> choice;

		if (s[index].group == &groups[choice - 1])
			choice = 0;
		
	} while (choice < 1 || choice > countG);

	s[index].group = &groups[choice - 1];
	
	system("cls");
}

int* rateStudent(Student* s, int index)
{
	int mark = 0;
	int* arr = new int[s[index].gradesCount + 1];

	for (int i{}; i < s[index].gradesCount; ++i)
		arr[i] = s[index].grades[i];

	arr[s[index].gradesCount] = 0;

	while (mark < 1 || mark > 12)
	{
		system("cls");
		cout << "введите оценку: ";
		cin >> mark;
	}

	++s[index].gradesCount;

	for (int i{}; i < s[index].gradesCount; ++i)
	{
		if (arr[i] == 0)
		{
			arr[i] = mark;
			break;
		}	
	}

	delete[] s[index].grades;
	system("cls");
	return arr;
}


void searchStudentById(Student* s, int& countS, int& index, bool& successfully)
{
	int choice;
	int desiredId;
	successfully = false;

	while (successfully == false)
	{
		system("cls");
		cout << "Введите id студента: ";
		cin >> desiredId;

		for (int i{}; i < countS; ++i)
		{
			if (s[i].id == desiredId)
			{
				index = i;
				successfully = true;
			}
		}

		if (successfully == false)
		{
			cout << "Ничего не найдено. Проверьте правильность ввода.";
			cout << "\n[1] Продолжить поиск\n[2] Выйти\n";
			cin >> choice;

			if (choice == 2)
				return;
		}
	}
}

void searchStudentByName(Student* s, int& countS, int& index, bool& successfully)
{
	int choice;
	successfully = false;
	string desiredName;

	do {
		system("cls");
		cout << "Введите имя студента: ";
		cin >> desiredName;

		for (int i{}; i < countS; ++i)
		{
			if (s[i].f_name == desiredName)
			{
				index = i;
				successfully = true;
			}	
		}

		if (successfully == false)
		{
			cout << "Ничего не найдено. Проверьте правильность ввода.";
			cout << "\n[1] Продолжить поиск\n[2] Выйти\n";
			cin >> choice;

			if (choice == 2)
				return;
		}		
	} while (successfully == false);
}

void searchStudentBySurname(Student* s, int& countS, int& index, bool& successfully)
{
	int choice;
	successfully = false;
	string desiredSurname;

	do {
		system("cls");
		cout << "Введите фамилию студента: ";
		cin >> desiredSurname;

		for (int i{}; i < countS; ++i)
		{
			if (s[i].l_name == desiredSurname)
			{
				index = i;
				successfully = true;
			}
		}

		if (successfully == false)
		{
			cout << "Ничего не найдено. Проверьте правильность ввода.";
			cout << "\n[1] Продолжить поиск\n[2] Выйти\n";
			cin >> choice;

			if (choice == 2)
				return;
		}
	} while (successfully == false);
}

void searchStudent(Student* s, int& countS, Group* groups, int countG)
{	
	int choice;
	int index = 0;
	int desiredPar = -1;
	bool successfully = false;

	do {
		system("cls");

		cout << "Поиск по\n[1] Id\n[2] Имени\n[3] Фамилии\n";

		cin >> choice;
	} while (choice < 1 || choice > 3);
	
	switch (choice)
	{
	case 1:
		searchStudentById(s, countS, index, successfully);
		break;
	case 2:
		searchStudentByName(s, countS, index, successfully);
		break;
	case 3:
		searchStudentBySurname(s, countS, index, successfully);
		break;
	}

	while (successfully)
	{
		system("cls");
		printStudent(&s[index]);

		cout << "\n    [1] Перевод студента в другую группу";
		cout << "    [2] Добавить оценку";
		cout << "\t\t\t\t\t\t[0] Назад\n";
		cin >> choice;

		switch (choice)
		{
		case 0:
			return;
		case 1:
			transferStudent(s, index, groups, countG);
			break;
		case 2:
			s[index].grades = rateStudent(s, index);
			break;
		}
	}
}


int* calcCountStudent(Teacher* t, int countT, Student* s, int countS)
{
	int* arr = new int[countT] {};

	for (int i{}; i < countS; ++i)
		for (int j{}; j < countT; ++j)
			if (s[i].group->teacher.f_name == t[j].f_name && s[i].group->teacher.l_name == t[j].l_name)
				++arr[j];

	return arr;
}

int* calcCountGroup(Teacher* t, int countT, Group* g, int countG)
{
	int* arr = new int[countT] {};

	for (int i{}; i < countG; ++i)
		for (int j{}; j < countT; ++j)
			if (g[i].teacher.f_name == t[j].f_name && g[i].teacher.l_name == t[j].l_name)
				++arr[j];

	return arr;
}

void printTeachers(Teacher* t, int countT, Group* g, int countG, Student* s, int countS)
{
	int* countTeacherG = calcCountGroup(t, countT, g, countG);
	int* CountTeacherS = calcCountStudent(t, countT, s, countS);

	for (int i{}; i < countT; ++i)
	{
		cout << "Имя: " << t[i].f_name << ' ' << t[i].l_name;
		cout << "\nКол-во групп: " << countTeacherG[i];
		cout << "\nКол-во студентов: " << CountTeacherS[i];
		cout << "\n===================================\n";
	}
} 


int* studentCountInGroup(Student* s, int countS, Group* groups, int countG)
{
	int* arr = new int[countG] {};	

	for (int i{}; i < countG; ++i)
		for (int j{}; j < countS; ++j)
			if (&groups[i] == s[j].group)
				++arr[i];

	return arr;
}

float* calcAvarageMark(Student* s, int countS, Group* groups, int countG)
{
	MarksOfGroup* arr2d = new MarksOfGroup[countG];
	float* arr = new float[countG] {};
	int* countStInGroup = studentCountInGroup(s, countS, groups, countG);

	for (int i{}; i < countG; ++i)
	{
		arr2d[i].countS = countStInGroup[i];
		arr2d[i].arrMarks = new float[arr2d[i].countS]{};
	}

	int n{};
	for (int i{}; i < countG; ++i)
	{
		for (int j{}; j < countS; ++j)
		{
			if (&groups[i] == s[j].group)
			{
				for (int k{}; k < s[j].gradesCount; ++k)
					arr2d[i].arrMarks[n] += s[j].grades[k];
				arr2d[i].arrMarks[n] = arr2d[i].arrMarks[n] / s[j].gradesCount;
				++n;
			}		
		}
		n = 0;
	}

	for (int i{}; i < countG; ++i) 
	{
		for (int j{}; j < arr2d[i].countS; ++j)
			arr[i] += arr2d[i].arrMarks[j];
		arr[i] = arr[i] / arr2d[i].countS;
	}

	delete[] arr2d;
	delete[] countStInGroup;
	return arr;
}

void printGroups(Group* g, int countG, int* countSt, float* avarageMark)
{
	cout << setprecision(3);

	for (int i{}; i < countG; ++i)
	{
		cout << "Название: " << g[i].title;
		cout << "\nПреподаватель: " << g[i].teacher.l_name << ' ' << g[i].teacher.f_name;
		cout << "\nКол-во студентов: " << countSt[i];
		cout << "\nСредний бал: " << avarageMark[i]; 
		cout << "\n===================================\n";
	}
}



int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

string randomName()
{
	string arr[]{
		"Иван",
		"Дмитрий",
		"Василий",
		"Геннадий",
		"Александр",
		"Кирилл",
		"Игорь",
		"Семён",
		"Данил",
		"Евгений",
		"Артём",
		"Ростислав",
		"Роман",
		"Сергей",
		"Владимир",
		"Андрей",
		"Антон",
		"Константин",
		"Никита",
		"Ян",
		"Валерий",
		"Юрий",
		"Павел",
		"Наташа",
		"Катерина",
		"Вероника",
		"Анастасия",
		"Маша",
		"Дарина",
		"Дарья",
		"Полина",
		"Ангелина",
		"Елена",
		"Ольга",
		"Александра",
		"Анна",
		"Валерия",
	};

	return arr[rand() % 37];
}

string randomSurname()
{
	string arr[]{
		"Кравченко",
		"Коваленко",
		"Логвиненко",
		"Панченко",
		"Романенко",
		"Голубенко",
		"Слесаренко",
		"Савченко",
		"Захарченко",
		"Ткаченко",
		"Шевченко",
		"Кищенко",
		"Сковорода",
		"Вишня",
		"Глинка",
		"Мельник",
		"Половинчук",
		"Махно",
		"Михненко",
		"Мазайло",
		"Нечитайло",
		"Доренко",
		"Лачко",
		"Сидорук",
		"Хлебник",
		"Литовченко",
		"Литвиненко",
		"Кононенко",
		"Кононко",
		"Терещенко",
		"Татаренко",
		"Костенко",
		"Кривошапко",
		"Харченко",
		"Тригубенко",
		"Майстро",
		"Черненко",
		"Ефремчук",
		"Воловоденко",
		"Галько",
		"Мурко",
		"Котенко",
		"Мартыненко",
		"Полищук",
		"Павленко",
	};

	return arr[rand() % 45];
}

int* generateIntArray(int count, int min, int max)
{
	int* arr = new int[count];

	for (int i{}; i < count; ++i)
		arr[i] = random(min, max);

	return arr;
}

Student* generateDB(int count, Group* groups, int groupCount)
{
	Student* arr = new Student[count];

	for (int i{}; i < count; ++i)
	{
		arr[i].id = ++maxId;

		arr[i].f_name = randomName();
		arr[i].l_name = randomSurname();

		int gId = random(0, groupCount - 1);
		arr[i].group = &groups[gId];

		arr[i].gradesCount = random(7, 15);
		arr[i].grades = generateIntArray(arr[i].gradesCount, 1, 12);

	}

	return arr;
}

void menu(int& choice)
{
	system("cls");
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t[1] Список студентов";
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t[2] Список преподавателей";
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t[3] Список групп";
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t[4] Выход";
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tВыберите действие: ";

	cin >> choice;
	system("cls");
}

//===================================================================================

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	srand(time(0));
	rand();

	const int groupCount = 7;
	int studentCount = 50;
	const int teacherCount = 3;
	int choice;
	int* countSt;
	float* avarageMark;
	string goBack;

	Teacher* teachers = new Teacher[teacherCount]
	{
		{ "Петренко", "Владимир" },
		{ "Бойченко", "Сергей" },
		{ "Васильева", "Татьяна" },
	};
	
	Group* groups = new Group[groupCount]
	{
		{"g131", teachers[0]},
		{"g132", teachers[1]},
		{"g133", teachers[2]},
		{"g134", teachers[0]},
		{"g135", teachers[1]},
		{"g136", teachers[2]},
		{"g137", teachers[0]},
	};

	Student* students = generateDB(studentCount, groups, groupCount);
	
	doFullScreen();


	while (true)
	{
		system("cls");
		avarageMark = calcAvarageMark(students, studentCount, groups, groupCount);
		countSt = studentCountInGroup(students, studentCount, groups, groupCount);
		menu(choice);
		
		switch (choice)
		{
		case 1:
			do
			{
				system("cls");
				for (int i{}; i < studentCount; ++i)
				{
					printStudent(&students[i]);
				}

				choice = menuSt();

				switch (choice)
				{
				case 0:
					break;
				case 1:
					students = addStudent(students, studentCount, groups, groupCount);
					break;
				case 2:
					students = remStudent(students, studentCount, groups, groupCount);
					break;
				case 3:
					searchStudent(students, studentCount, groups, groupCount);
					break;
				}
			} while (choice > 0);

			break;
		case 2:
			printTeachers(teachers, teacherCount, groups, groupCount, students, studentCount);

			cout << "\t\t\t\t\t\t\t\t\t\t\t\t[0] Назад\n";
			cin >> goBack;

			break;
		case 3:
			printGroups(groups, groupCount, countSt, avarageMark);

			cout << "\t\t\t\t\t\t\t\t\t\t\t\t[0] Назад\n";
			cin >> goBack;

			break;
		case 4:
			return 0;
		}
	}
}