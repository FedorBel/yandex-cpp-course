#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const
	{
		return person_tasks.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person)
	{
		++person_tasks[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
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

		for (int i = 0; i < old_tasks.size()-1; i++)
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

void PrintTasksInfo(const TasksInfo& tasks_info) {
	if (tasks_info.count(TaskStatus::NEW)) {
		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
	}
	if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
	}
	if (tasks_info.count(TaskStatus::TESTING)) {
		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
	}
	if (tasks_info.count(TaskStatus::DONE)) {
		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
	}
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
	std::cout << "Updated: [";
	PrintTasksInfo(updated_tasks);
	std::cout << "] ";

	std::cout << "Untouched: [";
	PrintTasksInfo(untouched_tasks);
	std::cout << "] ";

	std::cout << std::endl;
}

int main() {
	TeamTasks tasks;
	TasksInfo updated_tasks;
	TasksInfo untouched_tasks;

	/* TEST 1 */
	std::cout << "Alice" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
		2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
	PrintTasksInfo(updated_tasks, untouched_tasks);

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	/* TEST 2 */
	std::cout << "\nJack" << std::endl;

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

	tasks.AddNewTask("Jack");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
	std::cout << std::endl;

	/* TEST 3 */
	std::cout << "\nLisa" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tasks.AddNewTask("Lisa");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	return 0;
}