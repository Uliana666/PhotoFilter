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

bool CompareApplicant(const Applicant* a, const Applicant* b) {
    if (a->points != b->points) {
        return a->points > b->points;
    }
    if (a->student.birth_date != b->student.birth_date) {
        return a->student.birth_date < b->student.birth_date;
    }
    return a->student.name < b->student.name;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> copy_applicants;
    for (const auto& applicant : applicants) {
        copy_applicants.push_back(&applicant);
    }
    sort(copy_applicants.begin(), copy_applicants.end(), CompareApplicant);
    AdmissionTable result;
    std::unordered_map<std::string, size_t> number_of_places;
    for (const auto& university : universities) {
        number_of_places[university.name] = university.max_students;
    }
    for (const auto& applicant : copy_applicants) {
        for (const auto& name_of_university : applicant->wish_list) {
            if (number_of_places[name_of_university] > 0) {
                --number_of_places[name_of_university];
                result[name_of_university].push_back(&applicant->student);
                break;
            }
        }
    }
    return result;
}
