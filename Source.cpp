#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include <sys\stat.h> 
using namespace std;
class Point {
	string question;//вопрос
	string** answer;//варианты ответов
	string correct_answer;//правильный вариант
	int count_an;//количество ответов для вопроса
public:
	Point() { correct_answer = question = ""; answer = nullptr; count_an = 0; }
	Point(string question) { this->question = question; count_an = 0; correct_answer = ""; answer = nullptr;}
	void Set_an_arr(int size) { 
		if (answer == nullptr) {
			count_an = size;
			answer = new string * [count_an];
			for (size_t i = 0; i < count_an; i++)
			{
				answer[i] = new string;
			}
		}
	}
	~Point() { 
		for (size_t i = 0; i < count_an; i++)
		{
			delete answer[i];
		}
		delete answer;
	}
	string Get_question() { return question; }
	void Set_question(string question) { this->question = question; }
	void Set_correct_answer(string x) { correct_answer = x; }
	string Get_correct_answer() { return correct_answer; }
	void Set_count_an(int x) { count_an = x; }
	int Get_count_an() { return count_an; }
	string** Get_answer() { return answer; }

		void Add_answer(string an,bool flag=0){
		if(count_an==0){
			count_an++;
			answer = new string * [count_an];
			answer[0] = new string;
			*answer[0] = an.c_str();
			if (flag) { correct_answer = an; }
		}
		else {
			if (flag) { correct_answer = an; }
			count_an++;
			string** temp = new string * [count_an];
			for (size_t i = 0; i < count_an; i++)
			{
				temp[i] = new string;
			}
			for (size_t i = 0; i < count_an - 1; i++)
			{
				*temp[i] = *answer[i];
			}
			*temp[count_an - 1] = an;
			for (size_t i = 0; i < count_an-1; i++)
			{
				delete answer[i];
			}
			delete[]answer;
			answer = temp;
		}
	}
		void Print_point() { 
			cout << "Вопрос: " << question << "\n"; 
			for (size_t i = 0; i < count_an; i++)
			{
				cout << "Вариант: " << *answer[i] << endl; 
			}
		}
		int Test() {
			cout << "Вопрос: " << question << "\n";
			for (size_t i = 0, k = 1; i < count_an; i++,k++)
			{
				cout << "Вариант: " << *answer[i] << " - " << k << endl;
			}
			cout << "Выберите вариант: ";
			int q;
			cin >> q;
			cin.ignore();
			return q - 1;
		}
};
class Code_Save_Test {
	int size_q;
public:
	Code_Save_Test() :size_q(0){}
	Code_Save_Test(int x):size_q(x){}
	void Set_size(int x) { size_q = x; }
	int Get_size() { return size_q; }
};
class Test {
	Point* p;//поинтеры
	string theme;//тема теста
	int count;//количество поинтеров
public:
	static string name_code; 
	static string adress;
	static string cat_test;
	Test() { count = 0; p = nullptr; }
	Test(string theme) {
		this->theme = theme;
		count = 0;
		p = nullptr;
	}
	~Test() {
		if (p != nullptr) { delete[]p; }
	}
	void Set_P(Point* temp) { p = temp; }
	void Get_memory() {
		if (p == nullptr) {
			p = new Point[count];
		}
	}
	string Get_theme() { return theme; }
	int Get_count() { return count; }
	void Set_count(int x) { count = x; }
	Point* Get_p() { return p; }
	void Set_theme(string theme) { this->theme = theme; }
	void Add_p() {    
		for (size_t i = 0; i < 2; i++)
		{
			cout << "Добавить вопрос: 1\nБольше вопросов нет: 2" << endl;
			int c; cin >> c; cin.ignore();
			if (c == 2) { system("CLS"); break; }
			if (p == nullptr) {                    //Создание теста
				count++;
				p = new Point[count];
				string temp;
				bool t = 0; ///записан ли правильный ответ
				short menu = 1;
				system("CLS");
				cout << "Введите вопрос: "; getline(cin, temp);
				p->Set_question(temp);
				while (menu) {
					system("CLS");
					cout << "Задать вариант ответа - 1\nЗадать правильный вариант ответа - 2\nГотово - 3\n";
					cin >> menu;
					if (menu < 4 && menu>0) {
						cin.ignore();
						if (menu == 1) { cout << "Введите вариант ответа: "; getline(cin, temp); p->Add_answer(temp); }
						if (menu == 2 && t == 0) {
							cout << "Введите правильный вариант ответа: "; getline(cin, temp); p->Add_answer(temp, 1); t = 1;
						}
						else if (menu == 2 && t == 1) { cout << "Может быть создан только один правильный вариант ответа\n"; }
						if (menu == 3 && t == 1) {  menu = 0; break; }
						else if (menu == 3 && t == 0) { cout << "Нужен хотя бы один правильный вариант ответа!\n"; }
					}
					else { cin.ignore(); cout << "Wrong type!\n"; menu = 1; continue; }
				}
				system("CLS");
			}
			else {
				count++;
				Point* tempp = new Point[count];
				for (size_t i = 0; i < count - 1; i++)
				{
					(tempp + i)->Set_an_arr((p + i)->Get_count_an());
					for (size_t j = 0; j < (p + i)->Get_count_an(); j++)
					{
						*(tempp + i)->Get_answer()[j] = *(p + i)->Get_answer()[j];
					}
					(tempp + i)->Set_question((p + i)->Get_question());
					(tempp + i)->Set_correct_answer((p + i)->Get_correct_answer());
					(tempp + i)->Set_count_an((p + i)->Get_count_an());
				}
				string temp;
				bool t = 0; ///записан ли правильный ответ
				short menu = 1;
				system("CLS");
				cout << "Введите вопрос: "; getline(cin, temp);
				(tempp + (count - 1))->Set_question(temp);
				while (menu) {
					cout << "Задать вариант ответа - 1\nЗадать правильный вариант ответа - 2\nГотово - 3\n";
					cin >> menu;
					if (menu < 4 && menu>0) {
						cin.ignore();
						if (menu == 1) { cout << "Введите вариант ответа: "; getline(cin, temp); (tempp + (count - 1))->Add_answer(temp); system("CLS");}
						if (menu == 2 && t == 0) {
							cout << "Введите правильный вариант ответа: "; getline(cin, temp); (tempp + (count - 1))->Add_answer(temp, 1); t = 1; system("CLS");
						}
						else if (menu == 2 && t == 1) { cout << "Может быть создан только один правильный вариант ответа\n"; }
						if (menu == 3 && t == 1) {  menu = 0; break; }
						else if (menu == 3 && t == 0) { cout << "Нужен хотя бы один правильный вариант ответа!\n"; }
					}
					else { cin.ignore(); cout << "Wrong type!\n"; menu = 1; continue; }
				}
				delete[]p;
				p = tempp;
				system("CLS");
			}
			i = 0;
		}
	}
	void Save(string category) {
		struct stat buf;
		string categ = adress + cat_test;
		if (stat(categ.c_str(), &buf) == EOF) { system("mkdir Categories"); }


		fstream code;
		categ = adress+cat_test+"\\"+category;
		categ = "mkdir " + categ;
		string categ2 = adress +cat_test +"\\" + category;

		if (stat(categ2.c_str(), &buf) == EOF) { system(categ.c_str()); }
		categ = adress +cat_test +"\\"+category+"\\"+"Theme_sys.txt";
		code.open(categ.c_str(), fstream::app);
		code << theme << endl;                       //сохранение темы
		code.close();
		if (stat(name_code.c_str(), &buf)==EOF) { system("mkdir Code_Save_"); }
		code.open(adress+name_code+"\\"+name_code+theme+".txt", fstream::app);
		Code_Save_Test obj(count);
		code.write((char*)&obj, sizeof(obj));                //Запись количества вопросов
		for (size_t i = 0; i < count; i++)
		{
			fstream out;
			obj.Set_size((p + i)->Get_count_an());
			code.write((char*)&obj,sizeof(obj));                //Запись количества возможных ответов
			out.open(adress+cat_test+"\\"+category+"\\"+theme + ".txt", fstream::app);             //Запись теста в тему
			out << (p+i)->Get_question()<<endl;
			for (size_t j = 0; j < (p+i)->Get_count_an(); j++)
			{
				out<<*(p + i)->Get_answer()[j]<<endl;           
			}
			if (count - 1 == i) { out << (p + i)->Get_correct_answer(); }
			else { out << (p + i)->Get_correct_answer() << endl; }
			out.close();
		}
		obj.Set_size(0);
		code.close();
		code.open(adress + name_code + "\\" + cat_test + category+".txt", fstream::in);  //Записывает количество Тестов
		if (code.is_open()) { code.read((char*)&obj, sizeof(obj)); }
		code.close();
		obj.Set_size(obj.Get_size() + 1);
		code.open(adress + name_code + "\\" + cat_test + category+".txt", fstream::out);
		code.write((char*)&obj, sizeof(obj));
	}
	void Write(fstream* theme,string category) {
		getline(*theme, this->theme);   //Загрузка темы из файлика
		fstream code;
		fstream fin;
		Code_Save_Test obj;
		code.open(adress + name_code + "\\" + name_code + this->theme + ".txt", fstream::in);
		code.read((char*)&obj, sizeof(obj));          //Загрузка количества вопросов
		fin.open(adress +cat_test +"\\"+category + "\\"+this->theme + ".txt", fstream::in); //Открытие файла загрузки теста по теме
		this->count = obj.Get_size();                   //Инициализация количества вопросов
		Get_memory();                              //Выделение памяти в массиве поинтеров
		int temp_an;                                   
		for (size_t i = 0; i < count; i++)
		{
			string temp_q;
			getline(fin,temp_q);
			(p + i)->Set_question(temp_q);             //Инициализация вопроса
			code.read((char*)&obj, sizeof(obj));       //Количество возможных ответов
			temp_an = obj.Get_size();
			(p + i)->Set_an_arr(temp_an);
			(p + i)->Set_count_an(temp_an);
			for (size_t j = 0; j < temp_an; j++)
			{
				getline(fin,*(p + i)->Get_answer()[j]);      //Инициализация возможных ответов
			}
			getline(fin,temp_q);
			(p + i)->Set_correct_answer(temp_q);       //Инициализация правильного ответа

		}
		code.close();
		fin.close();
	}
	void Write_t(fstream* theme, string category,Test*c) {
		getline(*theme, c->theme);   //Загрузка темы из файлика
		fstream code;
		fstream fin;
		Code_Save_Test obj;
		code.open(adress + name_code + "\\" + name_code + c->theme + ".txt", fstream::in);
		code.read((char*)&obj, sizeof(obj));          //Загрузка количества вопросов
		fin.open(adress + cat_test + "\\" + category + "\\" + c->theme + ".txt", fstream::in); //Открытие файла загрузки теста по теме
		c->count = obj.Get_size();                   //Инициализация количества вопросов
		c->Get_memory();                              //Выделение памяти в массиве поинтеров
		int temp_an;
		for (size_t i = 0; i < c->count; i++)
		{
			string temp_q;
			getline(fin, temp_q);
			(c->p + i)->Set_question(temp_q);             //Инициализация вопроса
			code.read((char*)&obj, sizeof(obj));       //Количество возможных ответов
			temp_an = obj.Get_size();
			(c->p + i)->Set_an_arr(temp_an);
			(c->p + i)->Set_count_an(temp_an);
			for (size_t j = 0; j < temp_an; j++)
			{
				getline(fin, *(c->p + i)->Get_answer()[j]);      //Инициализация возможных ответов
			}
			getline(fin, temp_q);
			(c->p + i)->Set_correct_answer(temp_q);       //Инициализация правильного ответа

		}
		code.close();
		fin.close();
	}
	void Print_Test() {
		cout << "Тема: " << theme << endl;
		for (size_t i = 0; i < count; i++)
		{
			(p+i)->Print_point();
			cout << "Ответ: "; cout<<(p + i)->Get_correct_answer()<<endl;
		}
	}
	int Test_User() {
		int summ = 0;
		cout << "Тема: " << theme << endl;
		for (size_t i = 0, k = 1; i < count; i++)
		{
			if (*(p+i)->Get_answer()[(p + i)->Test()] == (p + i)->Get_correct_answer()) { summ++; }

		}
		float sys = 12 / count;
		int grade = summ * sys;
		cout << "Ваша оценка: " << grade << endl;
		return grade;
	}
	void Print_Test_only() {
		cout << "Тема: " << theme << endl;
	}
};
string Test::name_code = "Code_Save_";
string Test::adress = "C:\\Users\\Влад\\source\\repos\\Exam\\";
string Test::cat_test = "Categories";

class Category {
	Test* ptr;
	string name_cat;
	int size_ptr;
public:
	Category() { ptr = nullptr; name_cat = ""; size_ptr = 0; }
	Category(string name) { name_cat = name; ptr = nullptr; size_ptr = 0; struct stat buf;
	string categ = Test::adress + "Stat";
	if (stat(categ.c_str(), &buf) == EOF) { system("mkdir Stat"); }               //запись категории
	fstream out;
	out.open(categ + "\\" + "Categories.txt", ofstream::app);
	out << name_cat << endl;
	out.close();
	}
	~Category() { if (ptr != nullptr) { delete[]ptr; } }
	Test* Get_ptr() { return ptr; }
	void Set_name_cat(string name) { name_cat = name; struct stat buf;
	string categ = Test::adress + "Stat";
	if (stat(categ.c_str(), &buf) == EOF) { system("mkdir Stat"); }               //запись категории
	fstream out;
	out.open(categ + "\\" + "Categories.txt", ofstream::app);
	out << name_cat << endl;
	out.close();
	}
	string Get_name_cat() { return name_cat; }
	int Get_size_ptr() { return size_ptr; }
	void Set_size_ptr(int s) { if (size_ptr == 0) { size_ptr = s; } }
    void Add_test()
	{
		if (ptr == nullptr) {
			size_ptr++;
			ptr = new Test[size_ptr];
			string temp;
			cout << "Введите тему теста: " << endl;
			getline(cin, temp);
			ptr->Set_theme(temp);
			ptr->Add_p();
			ptr->Save(name_cat);

	}
		else {
			size_ptr++;
			Test* data = new Test[size_ptr];
			fstream* in = new fstream;
			in->open(Test::adress + Test::cat_test + "\\" + name_cat+"\\" + "Theme_sys.txt", fstream::in); //читает темы
			for (size_t i = 0; i < size_ptr-1; i++)
			{
				(data+i)->Write_t(in, name_cat, (data+i)); 
				
			}
			in->close();
			delete in;
			string temp;
			cout << "Введите тему теста: " << endl;
			getline(cin, temp);
			(data + (size_ptr - 1))->Set_theme(temp);
			(data + (size_ptr - 1))->Add_p();
			(data + (size_ptr - 1))->Save(name_cat);
			delete[]ptr;
			ptr = data;
		}
	}
	void Print_Category() {
		if (ptr != nullptr) {
			cout << "Категория: " << name_cat << endl;
			for (size_t i = 0; i < size_ptr; i++)
			{
				(ptr+i)->Print_Test();
			}
		}
	}
	void Print_menu() {
		if (ptr != nullptr) {
			cout << "Выберите тему теста: "<<endl;
			for (size_t i = 0, k = 1; i < size_ptr; i++,k++)
			{
				cout << k << " - "; (ptr + i)->Print_Test_only();
			}
			int menu;
			cin >> menu;
			cin.ignore();
			if (menu <= size_ptr) {
				(ptr + (menu - 1))->Print_Test();
			}
		}
	}
	void Category_User_Test(string cat,string log) {
		int grade=0;
		if (ptr != nullptr) {
			cout << "Выберите тему теста: " << endl;
			for (size_t i = 0, k = 1; i < size_ptr; i++,k++)
			{
				cout << k << " - "; (ptr + i)->Print_Test_only();
			}
			int menu;
			cin >> menu;
			cin.ignore();
			if (menu <= size_ptr) {
				grade=(ptr + (menu - 1))->Test_User();
			}
			fstream in;
			string temp = Test::adress + "All_Users" + "\\" + log + ".txt";
			in.open(temp, fstream::app); 
			in << cat << endl;
			in << (ptr + (menu - 1))->Get_theme()<<endl;
			in << grade << endl;
		}
	}
	void Print_Category_only() {
		if (ptr != nullptr) {
			cout << "Категоря: " << name_cat << endl;
		}
	}
	void Load_Cat(fstream*cat) {
		getline(*cat, name_cat);                                   //имя категории
		fstream code;
		Code_Save_Test obj;
		code.open(Test::adress + Test::name_code + "\\" + Test::cat_test + name_cat+".txt", fstream::in);  //Записывает количество Тестов читает
		code.read((char*)&obj, sizeof(obj));
		code.close();
		
		Test* Data = new Test[obj.Get_size()];
		Data->Set_count(obj.Get_size());
		fstream* in = new fstream;
		in->open(Test::adress + Test::cat_test + "\\" + name_cat + "\\" + "Theme_sys.txt", fstream::in);//читает темы
		Set_size_ptr(Data->Get_count());
		for (size_t i = 0; i < size_ptr; i++)
		{
			(Data + i)->Write(in, name_cat); 
		}
		ptr = Data;
		
		
		in->close();
		delete in;
	}
};
class Account {
	string login;
	string pasword;
public:
	static string ad;
	Account():login(""),pasword(""){}
	Account(string login,string pasword):login(login),pasword(pasword){}
	void Set_Login(string x) { login = x; }
	void Set_Paword(string x) { pasword = x; }
	string Get_Login() { return login; }
	string Get_Pasword() { return pasword; }
	void Print_Account() { cout << "Логин: " << login << "\nПароль: " << pasword << endl; }
};
string Account::ad= Test::adress + "Accounts\\";
class User :public Account{
protected:
	string name;
	Category* pp;
	int count_pp;
public:
	static string users;
	User() { pp = nullptr; count_pp = 0; Load_C(); Registration(); }
	User(bool x) { pp = nullptr; count_pp = 0; Load_C(); }
	~User() { if (pp != nullptr) { delete[]pp; } }
	bool Registration() {//по логину
		struct stat buf;
		cout << "Введите логин : ";
		string login;
		getline(cin, login);
		string temp=Test::adress+users;
		if (stat(temp.c_str(), &buf)) { string temp1 = "mkdir " + temp; system(temp1.c_str()); }
		temp = Test::adress+users+"\\"+login + ".txt";
		if (stat(temp.c_str(), &buf)) {
			string all = Test::adress + users + "\\" + users + ".txt";
			fstream p;
			p.open(all, fstream::app);
			p << login << endl;
			p.close();
			cout << "Идет регистрация пользователя!\n";
			cout << "Введите имя пользователя: ";
			string name;
			getline(cin, name);
			fstream in;
			in.open(temp, fstream::app);
			in << name << endl;
			cout << "Введите пароль: ";
			getline(cin, name);
			Code_Save_Test obj;
			obj.Set_size(name.size());
			in.write((char*)&obj, sizeof(obj));//количество символов пароля
			for (size_t i = 0; i < name.size(); i++)
			{
				obj.Set_size(name[i] * 100);
				in.write((char*)&obj, sizeof(obj));
			}
			in << endl;
			in.close();
			Set_Login(login);
			Set_Paword(name);
			cout << "Регистрация окончена!\n";
			return 1;
		}
		else {
			cout << "Выполняется вход в аккаунт!\n";
			fstream in;
			in.open(temp, fstream::in);
			getline(in, name);
			Code_Save_Test obj;
			in.read((char*)&obj, sizeof(obj));
			char* arr = new char[obj.Get_size() + 1];
			int size = obj.Get_size();
			for (size_t i = 0; i < size; i++)
			{
				in.read((char*)&obj, sizeof(obj));
				arr[i] = obj.Get_size() / 100;
			}
			arr[size] = '\0';
			temp = arr;
			cout << "Введите пароль: ";
			string pas;
			getline(cin, pas);
			if (temp == pas) {
				cout << "Вы вошли как " << name << endl;
				Set_Login(login);
				Set_Paword(pas);
				return 1;
			}
			else {
				cout << "Пароль не верный!\n"; return 0;
			}
		}
	}
	void Load_C(bool l = 0) {
		if (pp != nullptr) { delete[]pp; }
		fstream* c = new fstream;
		string temp;
		c->open(Test::adress + "Stat\\Categories.txt", fstream::in);
		count_pp = 0;
		while (*c) {
			getline(*c, temp); count_pp++;
		}
		count_pp++;
		c->close();
		if (count_pp != 1) {
			if (l == 0) { count_pp = count_pp - 2; }
			else { count_pp--; }
			pp = new Category[count_pp];
			c->open(Test::adress + "Stat\\Categories.txt", fstream::in);
			for (size_t i = 0; i < count_pp; i++)
			{
				(pp + i)->Load_Cat(c);
			}
			c->close();
			delete c;
		}
		else { pp = nullptr; count_pp = 0; }
	}
	void Print_Result(string log) {
		if (pp != nullptr) {
			fstream in;
			string temp = Test::adress + "All_Users" + "\\" + log + ".txt";
			in.open(temp, fstream::in);
			getline(in, temp);
			Code_Save_Test obj;
			in.read((char*)&obj, sizeof(obj));
			int size = obj.Get_size();
			for (size_t i = 0; i < size; i++)
			{
				in.read((char*)&obj, sizeof(obj)); //Чтение не нужных данных
			}
			string tem;
			string cat;
			string grade;
			int y = 0;
			while (!in.eof())
			{
				if (y == 0) { getline(in, cat); }//игнор endl}
				getline(in, cat);
				getline(in, tem);
				getline(in, grade);
				for (size_t i = 0; i < count_pp; i++)
				{
					if (cat == ((pp + i)->Get_name_cat())) {
						for (size_t j = 0; j < (pp + i)->Get_size_ptr(); j++)
						{
							if (((pp + i)->Get_ptr() + j)->Get_theme() == tem) {
								cout << "Категория: " << cat << endl;
								((pp + i)->Get_ptr() + j)->Print_Test();
								cout << "\nОценка: " << grade << endl << endl;
							}
						}

					}
				}
				y = 1;
			}
			in.close();
		}
	}
	void Show_Cat() {
		if (pp != nullptr) {
			for (size_t i = 0; i < count_pp; i++)
			{
				(pp + i)->Print_Category();
			}
		}
	}
	void Show() {
		if (pp != nullptr) {
			cout << "Выберите категорию: " << endl;
			for (size_t i = 0, k = 1; i < count_pp; i++, k++)
			{
				cout << k << " - "; (pp + i)->Print_Category_only();
			}
			int menu;
			cin >> menu;
			cin.ignore();
			if (menu <= count_pp) {
				(pp + (menu - 1))->Print_menu();
			}
			else { cout << "Wrong number!\n"; }
		}
	}
	void Take_Test() {
		if (pp != nullptr) {
			cout << "Выберите категорию: " << endl;
			for (size_t i = 0, k = 1; i < count_pp; i++, k++)
			{
				cout << k << " - "; (pp + i)->Print_Category_only();
			}
			int menu;
			cin >> menu;
			cin.ignore();
			if (menu <= count_pp) {
				(pp + (menu - 1))->Category_User_Test((pp + (menu - 1))->Get_name_cat(), Get_Login());

			}
			else { cout << "Wrong number!\n"; }
		}
	}
	void Show_Grade() {
		Print_Result(Get_Login());
	}

};
string User::users = "All_Users";
class Admin :public Account {
	string name;
	Category* pp;
	int count_pp;
public:
	Admin() { pp = nullptr; count_pp = 0; Load_C(); Registration(); }
	~Admin() { if (pp != nullptr) { delete[]pp; } }
	bool Registration() {
		struct stat buf;
		if (stat("Admin.txt", &buf)) {
			cout << "Идет регистрация администратора!\n";
			cout << "Введите логин : ";
			string login;
			getline(cin, login);
			Code_Save_Test obj;
			obj.Set_size(login.size());
			fstream in;
			in.open("Admin.txt", fstream::app);
			in.write((char*)&obj, sizeof(obj));
			
			for (size_t i = 0; i < login.size(); i++)
			{
				obj.Set_size(login[i]*100);
				in.write((char*)&obj, sizeof(obj));
			}
			
			string pas;
			cout << "Введите пароль: ";
			getline(cin, pas);
			obj.Set_size(pas.size());
			in.write((char*)&obj, sizeof(obj));
			for (size_t i = 0; i < pas.size(); i++)
			{
				obj.Set_size(pas[i] * 100);
				in.write((char*)&obj, sizeof(obj));
			}
			in.close();
			cout << "Учётная запись создана!\n";
			return 1;
		}
		else{
			cout << "Введите логин : ";
			string log;
			getline(cin, log);
			Code_Save_Test obj;
			fstream in;
			in.open("Admin.txt", fstream::in);
			in.read((char*)&obj, sizeof(obj));
			int size=obj.Get_size();
			char* code = new char[size+1];
			for (size_t i = 0; i < size; i++)
			{
				in.read((char*)&obj, sizeof(obj));
				code[i] = obj.Get_size() / 100;

			}
			code[size] = '\0';
			string temp = code;
			delete[]code;
			if (temp == log) {
				cout << "Введите пароль: ";
				getline(cin, log);
				in.read((char*)&obj, sizeof(obj));
				size = obj.Get_size();
				code = new char[size+1];
				for (size_t i = 0; i < size; i++)
				{
					in.read((char*)&obj, sizeof(obj));
					code[i] = obj.Get_size() / 100;
				}
				code[size] = '\0';
				temp = code;
				if (temp == log) { cout << "Вход выполнен!\n"; return 1; }
				else { cout << "Неверный пароль!\n"; return 0; }
			}
			else { cout << "Неверный логин!\n"; return 0; }
		}
	}
	void Load_C(bool l=0) {
		if (pp != nullptr) { delete[]pp; }
		fstream* c = new fstream;
		string temp;
		struct stat buf;
		temp = Test::adress + "Stat";
		if (stat(temp.c_str(), &buf)) { return; delete c; }
		c->open(Test::adress + "Stat\\Categories.txt", fstream::in);
		count_pp = 0;
		while (*c) {
			getline(*c, temp); count_pp++;
		}
		count_pp++;
		c->close();
		if (count_pp != 1) {
			if (l == 0) { count_pp = count_pp - 2; }
			else { count_pp--; }
			pp = new Category[count_pp];
			c->open(Test::adress + "Stat\\Categories.txt", fstream::in);
			for (size_t i = 0; i < count_pp; i++)
			{
				(pp + i)->Load_Cat(c);
			}
			c->close();
			delete c;
		}
		else { pp = nullptr; count_pp = 0; }
	}
	void Crate_Category() {
		if (pp != nullptr) { delete[]pp; }
		pp = nullptr; 
		count_pp = 0; 
		struct stat buf;
		string temp = Test::adress + "Stat";
		if (stat(temp.c_str(), &buf)) { count_pp++; pp = new Category[count_pp]; }
		else { Load_C(1); }
			cout << "Введите название новой категории: ";
			string cat;
			getline(cin, cat);
			(pp+(count_pp-1))->Set_name_cat(cat);
			for (size_t i = 0, menu = 0; i < 10; i++)
			{
				cout << "Добавить тест в категорию - 1\nКатегория готова - 2" << endl;
				cin >> menu;
				cin.ignore();
				if (menu == 1) {
					(pp + (count_pp - 1))->Add_test(); i = 0;
				}
				else if (menu == 2) { cout << "Категория создана!\n"; i = 10; }
				else { cout << "Wrong number!\n"; i = 0; }
			}
		}
	void Show_Cat() {
		if (pp != nullptr) {
			for (size_t i = 0; i < count_pp; i++)
			{
				(pp+i)->Print_Category();
			}
		}
	}
	void Show() {
		if (pp != nullptr) {
			cout << "Выберите категорию: " << endl;
			for (size_t i = 0, k = 1; i < count_pp; i++,k++)
			{
				cout << k << " - "; (pp + i)->Print_Category_only();
			}
			int menu;
			cin >> menu;
			cin.ignore();
			if (menu <= count_pp) {
				(pp + (menu - 1))->Print_menu();
			}
			else { cout << "Wrong number!\n"; }
		}
	}
	void Statistic() {
		struct stat buf;
		if (stat(User::users.c_str(), &buf)) { cout << "Пользователей ещё нет!\n"; return; }
		User p(1);
		fstream in;
		string temp = Test::adress + User::users + "\\" + User::users + ".txt";
		in.open(temp, fstream::in);
		while (in)
		{
			getline(in, temp);
			if (temp.size() == 0) { break; }
			cout << "\n\nПользователь : " << temp << endl << endl;
			p.Print_Result(temp);
		}
		in.close();
	}
};
void Prog() {
	struct stat buf;
	int menu = 0;
	if (!stat("Admin.txt", &buf)) {
		cout << "Войти как Админ - 1\nВойти как пользователь - 2\n";
		cin >> menu;
		cin.ignore();
	}
	else { menu = 1; }
	if (menu == 1) { 
		Admin obj;
		for (size_t i = 0, k = 1; i < k; i++, k++)
		{
			cout << "Создать категорию и тесты к ней - 1\nПоказать тесты по категориям - 2\nПосмотреть статистику пользователей - 3\nВыйти - 4\n";
			cin >> menu; cin.ignore();
			if (menu == 1) { obj.Crate_Category(); }
			else if (menu == 2) { obj.Show(); }
			else if (menu == 3) { obj.Statistic(); }
			else if (menu == 4) { break; }
			else { cout << "Wrong number!\n"; }
		}
	}
	else if (menu == 2) {
		User obj;
		for (size_t i = 0, k = 1; i < k; i++,k++)
		{
			cout << "Пройти тест - 1\nПоказать оценки по тестам - 2\nВыйти - 3\n";
			cin >> menu; cin.ignore();
			if (menu == 1) { obj.Take_Test(); }
			else if (menu == 2) { obj.Show_Grade(); }
			else if (menu == 3) { break; }
			else { cout << "Wrong number!\n"; }
		}
	}
	else { cout << "Wrong number!\n"; }
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Prog();
	
}