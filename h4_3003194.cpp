/*************************************************
Aufgabe Nr./Task No.: H4
Nachname/Last,Family Name: Rahman
Vorname/First,Given Name: Md.Mashiur
Matrikelnummer/Matriculation number: 3003194
Uni-Email: md.rahman.omi@stud.uni-due.de
Studiengang/Course of Studies: ISE (Software)
*************************************************/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/*
* TypeOfDay Enumeration
*/

enum TypeOfDay {mondayToFriday, saturday, sundayAndPublicHoliday};

//enumeration types
std::ostream& operator<<(std::ostream& os, TypeOfDay typ)
{
	switch (typ)
	{
	case mondayToFriday: os << "Monday ToFriday";    break;
	case saturday: os << "Saturday"; break;
	case sundayAndPublicHoliday: os << "Sunday and Public Holiday";  break;
	default: os.setstate(std::ios_base::failbit);
	}
	return os;
}
/*
* Time Class
*/
class Time
{
public:
	//Default Constructor
	Time() {
		minutesOfDay = 0;

	}
	//hh:mm Constructor
	Time( int h, int m) {
		if (h > 0 && m > 0 && h < 24 && m < 60)
			minutesOfDay = h * 60 + m;
		else
			cout << "Error. Invalid hour or minute!";

	}

	//Overload >> to read input for class Time
	friend std::istream& operator>>(std::istream& is, Time& obj)
	{
		// read obj from stream
		int minutes, hours;
		is >> hours >> minutes;
		obj.minutesOfDay = hours * 60 + minutes;
		return is;
	}
	//Overload << to print Time object
	friend ostream &operator<<(ostream &os, const Time& obj) {
		int hours = obj.minutesOfDay / 60;
		int minutes = obj.minutesOfDay % 60;
		if (hours < 10)
			os << "0" << hours;
		else
			os << hours;

		os << ":";

		if (minutes < 10)
			os << "0" << minutes;
		else
			os << minutes;

		return os;
	}
	//Overload + to add minutes to time object
	void operator+(unsigned int added_minutes)
	{
		minutesOfDay += added_minutes;
		minutesOfDay %= 1440;// 1440 is 23::60 and equals 00:00
	}
	//Overload == to compare 2 times
	bool operator==(const Time & obj)
	{
		return (minutesOfDay == obj.minutesOfDay);
	}
	//Overload != to compare 2 times
	bool operator!=(Time & obj)
	{
		return (minutesOfDay != obj.minutesOfDay);
	}
	//Overload < to compare 2 times
	bool operator<(Time & obj)
	{
		return (minutesOfDay < obj.minutesOfDay);
	}
	//Overload > to compare 2 times
	bool operator>(Time & obj)
	{
		return (minutesOfDay > obj.minutesOfDay);
	}

private:
	//time in minutes a day
	unsigned int minutesOfDay;
};

/*
* Stop Class
*/
class Stop
{
public:
	//Contstructor
	Stop(int number_of_minutes , string description , Stop * next_stop)
	{
		text = description;
		//only positive number
		if (number_of_minutes > 0)
			minutesToNext = number_of_minutes;
		next = next_stop;
	}
	int get_minutesToNext()
	{
		return minutesToNext;
	}
	string get_text()
	{
		return text;
	}
	Stop* get_next()
	{
		return next;
	}
private:
	string text; // description of Stop
	Stop * next; // The next stop
	unsigned int minutesToNext = 0;//minutes to the next stop

};

/*
* Time DepartureTime Class
*/

class DepartureTime
{
public:
	//Constructor
	DepartureTime(Time lev, DepartureTime* depTm)
	{
		leave = lev;
		if (depTm == NULL)
			next = NULL;
		else
			next = depTm;
	}
	Time get_leave()
	{
		return leave;
	}
	DepartureTime* get_next()
	{
		return next;
	}
	void set_next(DepartureTime *next_time)
	{
		next = next_time;
	}
private:
	Time leave;
	DepartureTime* next;

};
/*
Class Line
*/

class Line
{
public:
	//Default Constructor
	Line()
	{
		no = 0;
		from = NULL;
		//Time nullTime();
		mondaysToFridays = NULL;
		saturdays = NULL;
		sundaysAndPublicHolidays = NULL;
	}
	//Constructor
	Line(unsigned int num, Stop* head)
	{
		no = num;
		from = head;
		//Time nullTime();
		mondaysToFridays = NULL;
		saturdays = NULL;
		sundaysAndPublicHolidays = NULL;
	}
	//The description of the first stop
	string get_from()
	{
		return from->get_text();
	}
	//The duration of the line
	int get_duration()
	{
		int duration = 0;
		Stop* tmp = from;
		while (tmp != NULL)
		{
			duration += tmp->get_minutesToNext();
			tmp = tmp->get_next();
		}
		return duration;
	}
	//Add a stop On MondaysToFridays
	void addOnMondaysToFridays(DepartureTime dt)
	{
		//DepartureTime dt = DepartureTime(tim, NULL);
		insert(dt,  mondaysToFridays);
	}
	//Add a stop On Saturdays
	void addOnSaturdays(Time tim)
	{
		DepartureTime dt = DepartureTime(tim, NULL);
		insert(dt, saturdays);
	}
	//Add a stop On Sundays and Public Holidays
	void addOnSundaysAndPublicHolidays(Time tim)
	{
		DepartureTime dt = DepartureTime(tim, NULL);
		insert(dt, sundaysAndPublicHolidays);
	}
	// Print Start Time
	void print_startTimes(TypeOfDay t_day)
	{
		DepartureTime* tmp = NULL;
		switch (t_day)
		{
		case mondayToFriday:
			cout << "start times of tours on mondays to fridays: ";
			tmp = mondaysToFridays;
			break;
		case saturday:
			cout << "start times of tours on saturdays: ";
			tmp = saturdays;
			break;
		case sundayAndPublicHoliday:
			cout << "start times of tours on sundays and public holidays: ";
			tmp = sundaysAndPublicHolidays;
			break;
		default:
			break;
		}
		while (tmp != NULL)
		{
			cout << tmp->get_leave();
			cout << " ";
			tmp = tmp->get_next();
		}
	}
	//Print Route
	void print_route()
	{
		Stop* tmp = from;
		//duration to current stop
		int total_duration = 0;
		while (tmp != NULL)
		{
			if (tmp->get_text() != "")
				cout <<"   "<< tmp->get_text();
			cout << "  " << endl;
			if (tmp->get_next() != NULL)
			{
				total_duration += tmp->get_minutesToNext();
				cout << total_duration << "  ";
				if (total_duration < 10)
					cout << " ";
			}
			tmp = tmp->get_next();
		}
	}
	//Print Schedule
	bool print_schedule(TypeOfDay t_day, Time tim)
	{
		bool found = false;
		switch (t_day)
		{
		case mondayToFriday:
		{
			DepartureTime *tmpDep = mondaysToFridays;
			while (tmpDep != NULL)
			{
				if (tim == tmpDep->get_leave())
				{
					found = true;
					Time tmpTime(tim);
					Time firstTime(tmpTime);
					Stop* stp = from;
					cout << stp->get_text()<< setw(20)<< tim << endl;
					while (stp->get_next() != NULL)
					{

						firstTime + stp->get_minutesToNext();
						cout << stp->get_next()->get_text()<< setw(20)<< firstTime<< endl;
						stp = stp->get_next();
					}
					break;
				}
				tmpDep = tmpDep->get_next();
			}
			break;
		}
		case saturday:
		{
			DepartureTime *tmpDep1 = saturdays;
			while (tmpDep1 != NULL)
			{
				if (tim == tmpDep1->get_leave())
				{
					found = true;
					Time tmpTime(tim);
					Time firstTime(tmpTime);
					Stop* stp = from;
					cout << stp->get_text();
					cout<<setw(15);
					cout << tim;
					cout << endl;
					while (stp->get_next() != NULL)
					{

						firstTime + stp->get_minutesToNext();
						cout << stp->get_next()->get_text();
						cout << setw(15);
						cout << firstTime;
						cout << endl;
						stp = stp->get_next();
					}
					break;
				}
				tmpDep1 = tmpDep1->get_next();
			}
			break;
		}
		case sundayAndPublicHoliday:
		{
			DepartureTime *tmpDep2 = sundaysAndPublicHolidays;
			while (tmpDep2 != NULL)
			{
				if (tim == tmpDep2->get_leave())
				{
					found = true;
					Time tmpTime(tim);
					Time firstTime(tmpTime);
					Stop* stp = from;
					cout << stp->get_text();
					cout << setw(15);
					cout << tim;
					cout << endl;
					while (stp->get_next() != NULL)
					{

						firstTime + stp->get_minutesToNext();
						cout << stp->get_next()->get_text();
						cout << setw(15);
						cout << firstTime;
						cout << endl;
						stp = stp->get_next();
					}
					break;
				}
				tmpDep2 = tmpDep2->get_next();
			}
			break;
		}
		default:
			break;
		}
		return found;
	}
	//Overload << to print Line object
	friend ostream &operator<<(ostream &os, Line& obj) {
		Stop* tmp = obj.from;
		while (tmp != NULL && tmp->get_next() != NULL)
		{
			tmp = tmp->get_next();
		}
		os << "line:     " << obj.no <<endl;
		os << "from:     " << obj.get_from() << endl;
		os << "to:       " << tmp->get_text() << endl;
		os << "duration: " << obj.get_duration() << " min";


		return os;
	}
private:
	unsigned int no;
	Stop* from;
	DepartureTime *mondaysToFridays, *saturdays, *sundaysAndPublicHolidays;
	void insert(DepartureTime depTm, DepartureTime* &head)
	{
		// if list is empty
		if (head == NULL)
		{
			//DepartureTime depTim(depTm);
			head = new DepartureTime(Time(depTm.get_leave()),NULL);
		}
		else
		{
			DepartureTime* tmp = head->get_next();
			if (tmp == NULL)
				head->set_next(new DepartureTime(Time(depTm.get_leave()), NULL));
			else
			{
				//While there is a next
				while (tmp->get_next() != NULL)
				{
					tmp = tmp->get_next();

				}
				//depTm.set_next(NULL);
				tmp->set_next(new DepartureTime(Time(depTm.get_leave()), NULL));
			}
		}
	}
};
//function that returs a pointer to an object of class Line
Line* line_933()
{
	Line *line933 = new Line(933,
		new Stop(1, "Duisberg Rheindeich",
		new Stop(2, "Lilienthalstrasse",
		new Stop(1, "Javastrasse",
		new Stop(1, "Katholische Kirche",
		new Stop(1, "Am Schluetershof",
		new Stop(2, "Tierheim",
		new Stop(2, "Sperrschleuse",
		new Stop(2, "Landesarchiv NRW",
		new Stop(3, "Schwanentor",
		new Stop(2, "Friedrich-Wilhem-Platz",
		new Stop(1, "Lehmbruck-Museum",
		new Stop(2, "Tonhallenstrasse",
		new Stop(2, "Duisburg Hbf",
		new Stop(1, "Disburg Hbf Osteingang",
		new Stop(2, "Blumenstrasse",
		new Stop(2, "Bismarckstrasse",
		new Stop(1, "Kammerstrasse",
		new Stop(1, "Lenaustrasse",
		new Stop(1, "NettleBeckstrasse",
		new Stop(1, "Buergerstrasse",
		new Stop(1, "Universitaet",
		new Stop(0, "Uni-Nord", NULL
		)))))))))))))))))))))));
	//Monday_to_fridy start depratures
	Time mon_inittimes[16];
	mon_inittimes[0] = Time(4, 18);
	for (int i = 0; i < 5; i++)
	{
		Time prev_time = mon_inittimes[i];
		prev_time + 30;
		mon_inittimes[i + 1] = prev_time;
	}
	mon_inittimes[6] = Time(18, 18);
	for (int i = 6; i < 10; i++)
	{
		Time prev_time = mon_inittimes[i];
		prev_time + 15;
		mon_inittimes[i + 1] = prev_time;
	}
	mon_inittimes[11] = Time(21, 29);
	for (int i = 10; i < 15; i++)
	{
		Time prev_time = mon_inittimes[i];
		prev_time + 30;
		mon_inittimes[i + 1] = prev_time;
	}
	//Saturday start depratures
	Time sat_inittimes[16];
	sat_inittimes[0] = Time(4, 29);
	for (int i = 0; i < 5; i++)
	{
		Time prev_time = sat_inittimes[i];
		prev_time + 30;
		sat_inittimes[i + 1] = prev_time;
	}
	sat_inittimes[6] = Time(15, 18);
	for (int i = 6; i < 10; i++)
	{
		Time prev_time = sat_inittimes[i];
		prev_time + 30;
		sat_inittimes[i + 1] = prev_time;
	}
	sat_inittimes[11] = Time(21, 29);
	for (int i = 10; i < 15; i++)
	{
		Time prev_time = sat_inittimes[i];
		prev_time + 30;
		sat_inittimes[i + 1] = prev_time;
	}

	for (int i = 0; i < 16; i++)
	{
		DepartureTime dt = DepartureTime(mon_inittimes[i], NULL);
		line933->addOnMondaysToFridays(dt);
	}
	for (int i = 0; i < 16; i++)
	{
		line933->addOnSaturdays(sat_inittimes[i]);
	}
	return line933;

}
//Main Function
int main()
{

	//Line* line993 = line_933();
	//line993->print_route();
	//(*line993).print_startTimes(mondayToFriday);

	Line all_lines[1000];
	all_lines[933] = *line_933();
	cout << all_lines[933]<<endl<<endl	;
	cout << "route of line 933\n";
	all_lines[933].print_route();
	cout << endl;

	all_lines[933].print_startTimes(mondayToFriday);
	cout << endl<<endl;

	all_lines[933].print_startTimes(saturday);
	cout << endl << endl;

	//Choice of user
	int choice = 0;
	bool found = false;
	while (!found)
	{
		cout << "which type of day?\n";
		cout << "1 mondays to fridays\n";
		cout << "2 saturdays\n";
		cout << "3 sundays and public holidays\n";
		cin >> choice;
		if (choice > 0 && choice < 4)
		{
			cout << "which time?\n";
			Time time;
			cin >> time;
			found = all_lines[933].print_schedule(
				(choice == 1) ? mondayToFriday : ((choice == 2) ? saturday : sundayAndPublicHoliday),
				time);
			if (!found)
				cout << "\nsorry no line data";
		}
	}
	int c;
	cin >> c;
}
