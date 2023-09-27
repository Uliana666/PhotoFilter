#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> order_of_notebooks;
    for (auto action : student_actions) {
        if (action.side == Side::Top) {
            order_of_notebooks.push_front(action.name);
        } else {
            order_of_notebooks.push_back(action.name);
        }
    }
    return {};
}
