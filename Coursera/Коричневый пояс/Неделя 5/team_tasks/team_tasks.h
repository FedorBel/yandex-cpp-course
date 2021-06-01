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
        auto it = team_info_.find(person);
        if (it == team_info_.end())
        {
            return {};
        }

        TasksInfo &tasks_info = it->second;

        // create updated and old tasks
        TasksInfo updated_tasks;
        TasksInfo old_tasks;
        for (const auto &tasks : tasks_info)
        {
            if (tasks.first == TaskStatus::DONE)
            {
                break;
            }

            if (task_count)
            {
                int tasks_to_move = (task_count > tasks.second) ? tasks.second : task_count;
                task_count -= tasks_to_move;
                TaskStatus next_status = GetNextStatus(tasks.first);
                updated_tasks[next_status] = tasks_to_move;

                int old_tasks_count = tasks.second - tasks_to_move;
                if (old_tasks_count)
                {
                    old_tasks[tasks.first] = old_tasks_count;
                }
            }
            else
            {
                old_tasks[tasks.first] = tasks.second;
            }
        }

        int old_done_tasks = tasks_info[TaskStatus::DONE];
        tasks_info.clear();
        for (const auto &tasks : updated_tasks)
        {
            tasks_info[tasks.first] = tasks.second;
        }
        for (const auto &tasks : old_tasks)
        {
            tasks_info[tasks.first] += tasks.second;
        }

        if (old_done_tasks)
        {
            tasks_info[TaskStatus::DONE] += old_done_tasks;
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