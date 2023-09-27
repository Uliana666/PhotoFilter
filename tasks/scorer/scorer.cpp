#include "scorer.h"

#include <algorithm>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::map<TaskName, Status>> status;
    ScoreTable result;
    std::vector<const Event*> events_copy;
    for (const auto& event : events) {
        events_copy.push_back(&event);
    }
    sort(events_copy.begin(), events_copy.end(), [](const Event* a, const Event* b) { return a->time < b->time; });
    for (auto event : events_copy) {
        if (event->time > score_time) {
            break;
        }
        if (event->event_type == EventType::CheckFailed || event->event_type == EventType::CheckSuccess) {
            status[event->student_name][event->task_name].status_last_solve = event->event_type;
        } else {
            status[event->student_name][event->task_name].status_merge_request = event->event_type;
        }
    }
    for (const auto& [student_name, tasks] : status) {
        for (const auto& [task_name, task_status] : tasks) {
            if (task_status.status_last_solve == EventType::CheckSuccess &&
                task_status.status_merge_request == EventType::MergeRequestClosed) {
                result[student_name].insert(task_name);
            }
        }
    }
    return result;
}
