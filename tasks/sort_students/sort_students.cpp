#include "sort_students.h"

#include <algorithm>

bool Date::operator<(const Date& other) const {
    if (this->year != other.year) {
        return this->year < other.year;
    }
    if (this->month != other.month) {
        return this->month < other.month;
    }
    return this->day < other.day;
}

bool Date::operator!=(const Date& other) const {
    return this->operator<(other) || other < *this;
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.birth_date != b.birth_date) {
                return a.birth_date < b.birth_date;
            }
            if (a.last_name != b.last_name) {
                return a.last_name < b.last_name;
            }
            return a.name < b.name;
        });
    }
    if (sortKind == SortKind::Name) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.last_name != b.last_name) {
                return a.last_name < b.last_name;
            }
            if (a.name != b.name) {
                return a.name < b.name;
            }
            return a.birth_date < b.birth_date;
        });
    }
}
