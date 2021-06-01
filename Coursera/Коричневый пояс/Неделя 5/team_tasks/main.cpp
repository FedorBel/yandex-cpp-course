#include <iostream>
#include <sstream>

#include "team_tasks.h"

stringstream ss;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info)
{
    ss << tasks_info[TaskStatus::NEW] << " new tasks"
       << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
       << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
       << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

void TestResult()
{
    stringstream expected;
    expected << "Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done\n"
             << "Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done\n"
             << "Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done\n"
             << "Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done\n"
             << "Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done\n"
             << "Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done\n";

    if (expected.str() != ss.str())
    {
        cout << "ERROR!\n\n";
        cout << "Expected:\n"
             << expected.str()
             << "\n";

        cout << "Result:\n"
             << ss.str() << endl;
    }
    else
    {
        cout << "Result:\n"
             << ss.str() << endl;
    }
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i)
    {
        tasks.AddNewTask("Ivan");
    }
    ss << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    ss << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    ss << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    ss << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    ss << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    ss << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    TestResult();

    return 0;
}

// int main(int, char **)
// {
//     using namespace std;

//     if (0)
//     {
//         std::ss << "-1 == true" << std::endl;
//     }
//     else
//     {
//         std::ss << "-1 == false" << std::endl;
//     }
// }
