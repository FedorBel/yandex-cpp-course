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
		TasksInfo unchanged_tasks;
		TasksInfo updated_tasks;

		try
		{
			GetPersonTasksInfo(person);
		}
		catch (const std::exception&)
		{
			return tie(updated_tasks, unchanged_tasks);
		}

		TasksInfo &tasks = person_tasks[person];		

		vector<int> old_tasks;
		old_tasks.push_back(tasks[TaskStatus::NEW]);
		old_tasks.push_back(tasks[TaskStatus::IN_PROGRESS]);
		old_tasks.push_back(tasks[TaskStatus::TESTING]);
		old_tasks.push_back(tasks[TaskStatus::DONE]);

		int sum = 0;

		for (const auto& t : old_tasks)
		{
			sum += t;
		}
				
		if (task_count > sum)
		{
			task_count = sum;
		}

		vector<int> new_tasks(4);

		int step = task_count;

		for (int i = 0; i < old_tasks.size() - 1; i++)
		{
			if (step > old_tasks[i])
			{
				step = old_tasks[i];
				new_tasks[i + 1] = step;
				task_count -= step;
				step = task_count;
			}
			else
			{
				new_tasks[i + 1] = step;
				step = task_count - step;
			}

			if (step == 0)
			{
				break;
			}
		}
				
		for (int i = 1; i < new_tasks.size(); i++)
		{
			bool final_board = 0;
			update_task(updated_tasks, new_tasks[i], i, final_board);
		}

		for (int i = 0; i < old_tasks.size() - 1; i++)
		{			
			if (i < old_tasks.size() - 1)
			{
				old_tasks[i] = old_tasks[i] - new_tasks[i + 1];
			}
			
			bool final_board = 0;
			update_task(unchanged_tasks, old_tasks[i], i, final_board);
		}

		for (int i = 0; i < old_tasks.size(); i++)
		{
			int tmp = 0;
			tmp = old_tasks[i] + new_tasks[i];
			bool final_board = 1;
			update_task(tasks, tmp, i, final_board);
		}

		return tie(updated_tasks, unchanged_tasks);
	}
private:
	void update_task(TasksInfo& updated_tasks, int num, int task, bool final_board)
	{
		if (num != 0)
		{
			switch (task)
			{
			case 0:
				updated_tasks[TaskStatus::NEW] = num;
				break;

			case 1:
				updated_tasks[TaskStatus::IN_PROGRESS] = num;
				break;

			case 2:
				updated_tasks[TaskStatus::TESTING] = num;
				break;

			case 3:
				updated_tasks[TaskStatus::DONE] = num;
				break;
			}
		}
		else
		{
			switch (task)
			{
			case 0:
				updated_tasks.erase(TaskStatus::NEW);
				break;

			case 1:
				updated_tasks.erase(TaskStatus::IN_PROGRESS);
				break;

			case 2:
				updated_tasks.erase(TaskStatus::TESTING);
				break;

			case 3:
				if (final_board != 1)
				{
					updated_tasks.erase(TaskStatus::DONE);
				}
				break;
			}
		}
	}

	map<string, TasksInfo> person_tasks;
};