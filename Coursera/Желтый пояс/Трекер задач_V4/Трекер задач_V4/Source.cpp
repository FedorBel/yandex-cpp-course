#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

// ������������ ��� ��� ������� ������
enum class TaskStatus {
	NEW,          // �����
	IN_PROGRESS,  // � ����������
	TESTING,      // �� ������������
	DONE          // ���������
};

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// �������� ���������� �� �������� ����� ����������� ������������
	const TasksInfo& GetPersonTasksInfo(const string& person) const
	{
		return person_tasks.at(person);
	}

	// �������� ����� ������ (� ������� NEW) ��� ����������� �������������
	void AddNewTask(const string& person)
	{
		++person_tasks[person][TaskStatus::NEW];
	}

	// �������� ������� �� ������� ���������� ����� ����������� ������������,
	// ����������� ��. ����
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

				int num = updated_tasks[TaskStatus::NEW] - new_tasks[TaskStatus::IN_PROGRESS];
				if (num != 0)
				{
					tasks[TaskStatus::NEW] = num;
					updated_tasks[TaskStatus::NEW] = tasks.at(TaskStatus::NEW);

				}
				else
				{
					tasks.erase(TaskStatus::NEW);
					//updated_tasks[TaskStatus::NEW] = new_tasks.at(TaskStatus::NEW);
				}

				//tasks[TaskStatus::NEW] -= new_tasks[TaskStatus::IN_PROGRESS];

				task_count -= tmp;
				tmp = task_count;
			}
			else
			{
				updated_tasks.erase(TaskStatus::NEW);
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

				int num = updated_tasks[TaskStatus::IN_PROGRESS] - new_tasks[TaskStatus::TESTING];
				if (num != 0)
				{
					tasks[TaskStatus::IN_PROGRESS] = num;
					updated_tasks[TaskStatus::IN_PROGRESS] = tasks[TaskStatus::IN_PROGRESS] + new_tasks[TaskStatus::IN_PROGRESS];
				}
				else
				{
					tasks.erase(TaskStatus::IN_PROGRESS);
					updated_tasks[TaskStatus::IN_PROGRESS] = new_tasks[TaskStatus::IN_PROGRESS];
				}

				task_count -= tmp;
				tmp = task_count;
			}
			else
			{
				updated_tasks.erase(TaskStatus::IN_PROGRESS);
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

			new_tasks[TaskStatus::DONE] = tmp;

			int num = updated_tasks[TaskStatus::TESTING] - new_tasks[TaskStatus::DONE];
			if (num != 0)
			{
				tasks[TaskStatus::TESTING] = num;
				updated_tasks[TaskStatus::TESTING] = tasks[TaskStatus::TESTING] + new_tasks[TaskStatus::TESTING];
			}
			else
			{
				tasks.erase(TaskStatus::TESTING);
				updated_tasks[TaskStatus::TESTING] = new_tasks[TaskStatus::TESTING];
			}

			//tasks[TaskStatus::TESTING] = updated_tasks[TaskStatus::TESTING] - new_tasks[TaskStatus::DONE];;

			task_count -= tmp;
			tmp = task_count;

			if (task_count == 0) { break; }
			//tasks.erase(TaskStatus::DONE);
			new_tasks[TaskStatus::DONE] = updated_tasks[TaskStatus::TESTING];
			task_count -= tmp;
			if (task_count == 0) { break; }

		}		
		
		updated_tasks[TaskStatus::DONE] = tasks[TaskStatus::DONE] + new_tasks[TaskStatus::DONE];

		/*if (tasks[TaskStatus::NEW] == 0)
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
		}*/

		tasks.erase(TaskStatus::DONE);

		return tie(new_tasks, tasks);
	}
private:
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