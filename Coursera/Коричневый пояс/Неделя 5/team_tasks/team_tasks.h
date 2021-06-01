#include <iostream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        return team_info_.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person)
    {
        TasksInfo &tasks_info = team_info_[person];
        tasks_info[TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string &person, int task_count)
    {
        TasksInfo &tasks_info = team_info_.at(person);

        // create updated and old tasks
        TasksInfo updated_tasks;
        TasksInfo old_tasks;
        for (const auto &tasks : tasks_info)
        {
            if (tasks.first == TaskStatus::DONE)
            {
                break;
            }
            if (!task_count)
            {
                break;
            }

            int tasks_to_move = (task_count > tasks.second) ? tasks.second : task_count;
            TaskStatus next_status = GetNextStatus(tasks.first);
            updated_tasks[next_status] = tasks_to_move;

            int old_tasks_count = tasks.second - tasks_to_move;
            old_tasks_count = (old_tasks_count < 0) ? 0 : old_tasks_count;
            if (old_tasks_count)
            {
                old_tasks[tasks.first] = old_tasks_count;
            }
        }

        // update tasks info with new data
        size_t task_status_size = static_cast<size_t>(TaskStatus::DONE) + 1;
        for (size_t i = 0; i < task_status_size; i++)
        {
            TaskStatus current_status = static_cast<TaskStatus>(i);
            try
            {
                tasks_info[current_status] = updated_tasks.at(current_status) + old_tasks.at(current_status);
            }
            catch (const std::exception &e)
            {
            }
        }

        return {updated_tasks, old_tasks};
    }

private:
    map<string, TasksInfo> team_info_;

private:
    TaskStatus GetNextStatus(TaskStatus old_status)
    {
        switch (old_status)
        {
        case TaskStatus::NEW:
            return TaskStatus::IN_PROGRESS;

        case TaskStatus::IN_PROGRESS:
            return TaskStatus::TESTING;

        case TaskStatus::TESTING:
            return TaskStatus::DONE;

        default:
            return {};
        }
    }
};