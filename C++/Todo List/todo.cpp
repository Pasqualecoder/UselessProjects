#include <iostream>
#include <string>
#include <vector>

namespace date {
    typedef struct date_tag {
        unsigned short day;
        unsigned short month;
        unsigned int year;
    } Date;

    std::string date_to_string(Date date) {
        std::string day = std::to_string(date.day);
        std::string month = std::to_string(date.month);
        std::string year = std::to_string(date.year);
        return day + "/" + month + "/" + year;
    }

    Date input_date() {
        unsigned short day;
        unsigned short month;
        unsigned int year;

        using namespace std;
        do {
            cout << "Insert the year: ";
            cin >> year;
            if (year < 0) cout << "Error, year out of range" << endl;
        } while (year < 0);

        do {
            cout << "Insert the month: ";
            cin >> month;
            if (month < 1 || month > 12) cout << "Error, month out of range" << endl;
        } while (month < 1 || month > 12);

        int day_range = (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) ? ((month == 2 ) 
                        ? ((year % 4 == 0)? 29 : 28) : 30) : 31;
        do {
            cout << "Insert the day: ";
            cin >> day;
            if (day < 1 || day > day_range) cout << "Error, date out of range" << endl;
        } while (day < 1 || day > day_range);

        return {day, month, year};
    }
};


class Activity {
public:
    std::string title;
    std::string description;
    bool compleated;
    date::Date expiring_date;

    Activity(std::string title, std::string description, date::Date expiring_date) {
        this->title = title;
        this->description = description;
        this->expiring_date = expiring_date;
        std::cout << title << ": new activity created" << std::endl;
    }

    Activity() {
        std::string title;
        std::string desc;
        date::Date date;

        std::cout << "Insert the title" << std::endl;
        std::getline(std::cin, title);

        std::cout << "Insert a description" << std::endl;
        std::getline(std::cin, desc);

        date = date::input_date();

        this->title = title;
        this->description = desc;
        compleated = false;
        this->expiring_date = date;
    }

    ~Activity() {
        // std::cout << title << "deleted" << std::endl; 
    }

    void mark_completed() {
        compleated = true;
    }
    void mark_completed(bool b) {
        compleated = b;
    }

    std::string to_string() {
        std::string str;
        str = title + ": " + description + " \t exp: " + date::date_to_string(expiring_date) + "\t" + "done: " + (compleated ? "yes" : "no");
        return str;
    }
};


void print_menu() {
    using namespace std;
    cout << "0) Exit" << endl;
    cout << "1) New activity" << endl;
    cout << "2) View activities" << endl;
    cout << "3) Complete activity" << endl;
}

void add_activity(std::vector<Activity> &l) {
    Activity newact;
    l.push_back(newact);
    std::cout << "Activity added" << std::endl;
}

void print_activities(std::vector<Activity> &l) {
    if (l.empty())  return;
    
    int i = 1;
    for (Activity act : l) {
        std::cout << "Activity #" << i << std::endl;        
        std::cout << act.to_string() << std::endl;
        i++;
    }
}

void complete_activity(std::vector<Activity> &l) {
    if (l.empty()) return;
    
    unsigned int index;
    char to_del;
    do {
        std::cout << "Insert the index of the task to mark as compleated" << std::endl;
        std::cin >> index;
        index--; // to match the human counting to the array count
        if (index >= l.size()) {
            std::cout << "Error, index out of range" << std::endl;
        }
    } while (index >= l.size());

    l.at(index).mark_completed(true);
    std::cout << "Do you want to delete the task (y/N)" << std::endl;
    std::cin >> to_del;
    if (to_del == 'y' || to_del == 'Y') {
        l.erase(l.begin() + index);
    }
    
    std::cin.ignore();
}

int main(void) {
    unsigned short choose = 1;
    std::vector<Activity> todo_list;  
    
    std::cout << "Welcome" << std::endl;  
    while (choose != 0) {
        print_menu();
        std::cin >> choose;
        std::cin.ignore();
        
        switch (choose)
        {
        case 0:
            break;
        case 1:
            add_activity(todo_list);
            break;
        case 2:
            print_activities(todo_list);
            break;
        case 3:
            complete_activity(todo_list);
            break;
        default:
            std::cout << "Beep... Boop... :(" << std::endl;
            break;
        }
    }
}
