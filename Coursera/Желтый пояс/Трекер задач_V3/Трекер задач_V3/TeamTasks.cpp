#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

class TeamTasks {
public:
	// ѕолучить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const
	{
		return person_tasks.at(person);
	}

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
	void AddNewTask(const string& person)
	{
		++person_tasks[person][TaskStatus::NEW];
	}

	// ќбновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count)
	{
		TasksInfo tasks;
		TasksInfo new_tasks;

		try
		{
			tasks = GetPersonTasksInfo(person);
		}
		catch (const std::exception&)
		{
			return tie(new_tasks, tasks);
		}

		int tmp = task_count;
		auto& updated_tasks = person_tasks[person];

		while (true)
		{
			/*if (updated_tasks[TaskStatus::NEW] < tmp) // NEW -> IN_PROGRESS
			{
				tmp = tasks[TaskStatus::NEW];
			}*/

			if (updated_tasks[TaskStatus::NEW] != 0) // NEW->IN_PROGRESS
			{
				if (updated_tasks[TaskStatus::NEW] <= tmp)
				{
					tmp = tasks[TaskStatus::NEW];
				}

				new_tasks[TaskStatus::IN_PROGRESS] = tmp;

				tasks[TaskStatus::NEW] -= new_tasks[TaskStatus::IN_PROGRESS];

				task_count -= tmp;
				tmp = task_count;
			}
			/*else if (updated_tasks[TaskStatus::IN_PROGRESS] != 0)
			{
				new_tasks[TaskStatus::IN_PROGRESS] = tmp - updated_tasks[TaskStatus::IN_PROGRESS];
			}*/

			if (task_count == 0) { break; }

			if (updated_tasks[TaskStatus::IN_PROGRESS] != 0)
			{
				if (tasks[TaskStatus::IN_PROGRESS] <= tmp)
				{
					tmp = tasks[TaskStatus::IN_PROGRESS];
				}

				new_tasks[TaskStatus::TESTING] = tmp;

				tasks[TaskStatus::IN_PROGRESS] = updated_tasks[TaskStatus::IN_PROGRESS] - new_tasks[TaskStatus::TESTING];

				task_count -= tmp;
				tmp = task_count;
			}
			/*else if (updated_tasks[TaskStatus::TESTING] != 0)
			{
				new_tasks[TaskStatus::TESTING] = 0;
			}*/

			if (task_count == 0) { break; }

			if (tasks[TaskStatus::TESTING] <= tmp) // TESTING -> DONE
			{
				tmp = tasks[TaskStatus::TESTING];
			}

			new_tasks[TaskStatus::DONE] = tmp - updated_tasks[TaskStatus::DONE];

			tasks[TaskStatus::TESTING] = updated_tasks[TaskStatus::TESTING] - new_tasks[TaskStatus::DONE];;

			task_count -= tmp;
			if (task_count == 0) { break; }
		}

		updated_tasks[TaskStatus::NEW] = tasks[TaskStatus::NEW] + new_tasks[TaskStatus::NEW];
		updated_tasks[TaskStatus::IN_PROGRESS] = tasks[TaskStatus::IN_PROGRESS] + new_tasks[TaskStatus::IN_PROGRESS];
		updated_tasks[TaskStatus::TESTING] = tasks[TaskStatus::TESTING] + new_tasks[TaskStatus::TESTING];
		updated_tasks[TaskStatus::DONE] = tasks[TaskStatus::DONE] + new_tasks[TaskStatus::DONE];

		tasks.erase(TaskStatus::DONE);

		if (tasks[TaskStatus::NEW] == 0)
		{
			tasks.erase(TaskStatus::NEW);
		}
		if (tasks[TaskStatus::IN_PROGRESS] == 0)
		{
			tasks.erase(TaskStatus::IN_PROGRESS);
		}
		if (tasks[TaskStatus::TESTING] == 0)
		{
			tasks.erase(TaskStatus::TESTING);
		}
		if (tasks[TaskStatus::DONE] == 0)
		{
			tasks.erase(TaskStatus::DONE);
		}

		if (new_tasks[TaskStatus::NEW] == 0)
		{
			new_tasks.erase(TaskStatus::NEW);
		}
		if (new_tasks[TaskStatus::IN_PROGRESS] == 0)
		{
			new_tasks.erase(TaskStatus::IN_PROGRESS);
		}
		if (new_tasks[TaskStatus::TESTING] == 0)
		{
			new_tasks.erase(TaskStatus::TESTING);
		}
		if (new_tasks[TaskStatus::DONE] == 0)
		{
			new_tasks.erase(TaskStatus::DONE);
		}

		if (updated_tasks[TaskStatus::NEW] == 0)
		{
			updated_tasks.erase(TaskStatus::NEW);
		}
		if (updated_tasks[TaskStatus::IN_PROGRESS] == 0)
		{
			updated_tasks.erase(TaskStatus::IN_PROGRESS);
		}
		if (updated_tasks[TaskStatus::TESTING] == 0)
		{
			updated_tasks.erase(TaskStatus::TESTING);
		}
		if (updated_tasks[TaskStatus::DONE] == 0)
		{
			updated_tasks.erase(TaskStatus::DONE);
		}


		return tie(new_tasks, tasks);
	}
private:
	map<string, TasksInfo> person_tasks;
};