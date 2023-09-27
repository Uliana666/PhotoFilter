#include "admission.h"

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

bool CompareApplicant(const Applicant& a, const Applicant& b){
    if (a.points != b.points){
        return a.points > b.points;
    }
    if (a.student.birth_date != b.student.birth_date){
        return a.student.birth_date < b.student.birth_date;
    }
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<Applicant> copy_applicant = applicants;
    sort(copy_applicant.begin(), copy_applicant.end(), []())
}
