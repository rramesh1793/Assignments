
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course> * >> &DB, int id);
void remove_student(map<int, map<int, list<course> * >> &DB, int id);
void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																						  //All courses in the list should be sorted according to name (increasing order)
void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id);
void print_DB(map<int, map<int, list<course> * >> &DB);

int main() {
	map<int, map<int, list<course> *>> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;

}

void add_student(map<int, map<int, list<course> * >> &DB, int id)
{
	map<int, list<course>*> temp;

	// condition to check if the student id already exists
	// if it exists do not do anything else add 
	if (DB.find(id) != DB.end())
	{
		return;
	}
	else
	{
		DB[id] = temp;
	}
}

void remove_student(map<int, map<int, list<course> * >> &DB, int id)
{
	if (DB.size() > 0 && DB.find(id) != DB.end())
	{
		map<int, list<course>*> semMap = DB[id];

		// loop till the list and delete the list because
		// it was created using new keyword
		for each(auto itSem in semMap)
		{
			list<course>* listCourse = itSem.second;
			delete(listCourse);
		}
		DB.erase(id);
	}
	else
	{
		cout << "DB is empty and does not contain the student id" << endl;
	}
}

void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c)
{
	if (DB.size() > 0 && DB.find(id) != DB.end())
	{
		map<int, list<course>*> ma = DB[id];
		if (ma.size() > 0 && ma.find(semester) != ma.end())
		{
			list<course>* l = DB[id][semester];

			// If list already exists
			// Check if the course already exists for a given semester
			// if the course already exists
			// do not add the course 
			// if list does not exists then add a new list
			if (find((*l).begin(), (*l).end(), c) != (*l).end())
			{
				cout << "Course cannot be added as it already exists for the given semester" << endl;
			}
			else
			{
				(*l).push_back(c);
				l->sort();
			}
		}
		else
		{
			list<course> *l = new list<course>;
			l->push_back(c);
			l->sort();
			ma[semester] = l;
		}
		DB[id] = ma;
	}
}

void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c)
{
	if (DB.size() > 0 && DB.find(id) != DB.end())
	{
		map<int, list<course>*> ma = DB[id];
		if (ma.find(semester) != ma.end())
		{
			list<course> * l = DB[id][semester];
			for each(auto removecourse in (*l))
			{
				if (removecourse.name == c.name)
				{
					(*l).remove(removecourse);
					break;
				}
			}
		}
	}
}

void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id)
{
	if (DB.size() > 0 && DB.find(id) != DB.end())
	{
		cout << "student id = " << id << endl;
		map<int, list<course>*> ma = DB[id];
		if (ma.find(semester) != ma.end())
		{
			cout << "semester = " << semester << endl;
			list<course> * l = DB[id][semester];
			for each(auto c in (*l))
			{
				cout << c.name << " " << c.section << " " << c.credits << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id)
{
	if (DB.size() > 0 && DB.find(id) != DB.end())
	{
		cout << "student id = " << id << endl;
		map<int, list<course>*> ma = DB[id];
		for each(auto a in ma)
		{
			cout << "semester = " << a.first << endl;
			list<course> * l = a.second;
			for each(auto courses in *l)
			{
				cout << courses.name << " " << courses.section << " " << courses.credits << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "DB is empty" << endl;
	}
}

void print_DB(map<int, map<int, list<course> * >> &DB)
{
	if (DB.size() > 0)
	{
		for each(auto printDB in DB)
		{
			cout << "student id = " << printDB.first << endl;
			map<int, list<course>*> semesterMap = printDB.second;
			if (semesterMap.size() > 0)
			{
				for each(auto printSem in semesterMap)
				{
					cout << "semester = " << printSem.first << endl;
					list<course>* courseList = printSem.second;
					if ((*courseList).size() > 0)
					{
						for each (auto printCourse in (*courseList))
						{
							cout << printCourse.name << " " << printCourse.section << " " << printCourse.credits << " ";
						}
						cout << endl;
					}
					else
					{
						cout << "There are no courses in the list" << endl;
					}
				}
			}
			else
			{
				cout << "There are no semesters" << endl;
			}
		}
		cout << endl;
	}
	else
	{
		cout << "DB is empty" << endl;
	}
}
