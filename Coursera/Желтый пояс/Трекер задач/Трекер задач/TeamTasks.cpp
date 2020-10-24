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
			new_tasks = GetPersonTasksInfo(person);
		}
		catch (const std::exception&)
		{
			return tie(new_tasks, tasks);
		}

		int tmp = task_count;

		while (true)
		{
			if (tasks[TaskStatus::NEW] < tmp) // NEW -> IN_PROGRESS
			{
				tmp -= tasks[TaskStatus::NEW];
			}
			new_tasks[TaskStatus::NEW] = 0;
			new_tasks[TaskStatus::IN_PROGRESS] = tmp;

			tasks[TaskStatus::NEW] -= tmp;

			//new_per_tasks[TaskStatus::NEW] -= tmp;

			tmp = task_count - tmp;
			task_count -= tmp;
			if (tmp == 0) { break; }

			if (tasks[TaskStatus::IN_PROGRESS] < tmp) // IN_PROGRESS -> TESTING
			{
				tmp -= tasks[TaskStatus::IN_PROGRESS];
			}

			new_tasks[TaskStatus::TESTING] = tmp;

			tasks[TaskStatus::IN_PROGRESS] -= tmp;

			tmp = task_count - tmp;
			task_count -= tmp;
			if (tmp == 0) { break; }

			if (tasks[TaskStatus::TESTING] < tmp) // TESTING -> DONE
			{
				tmp -= tasks[TaskStatus::TESTING];
			}

			new_tasks[TaskStatus::DONE] = tmp;

			tasks[TaskStatus::TESTING] -= tmp;
			tasks.erase(TaskStatus::DONE);

			tmp = task_count - tmp;
			if (tmp == 0) { break; }
		}

		auto& updated_tasks = person_tasks[person];

		updated_tasks[TaskStatus::NEW] = tasks[TaskStatus::NEW] + new_tasks[TaskStatus::NEW];
		updated_tasks[TaskStatus::IN_PROGRESS] = tasks[TaskStatus::IN_PROGRESS] + new_tasks[TaskStatus::IN_PROGRESS];
		updated_tasks[TaskStatus::TESTING] = tasks[TaskStatus::TESTING] + new_tasks[TaskStatus::TESTING];
		updated_tasks[TaskStatus::DONE] = tasks[TaskStatus::DONE] + new_tasks[TaskStatus::DONE];

		return tie(new_tasks, tasks);
	}
private:
	map<string, TasksInfo> person_tasks;
};