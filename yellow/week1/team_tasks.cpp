#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum class TaskStatus {
  NEW,
  IN_PROGRESS,
  TESTING,
  DONE
};

// Store nr of tasks for each status
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Get a statistic of task status for current person
  const TasksInfo& GetPersonTasksInfo(const string& person) const
  {
    return persons_tasks_state.at(person);
  }

  // Add new task (With NEW status) for current person
  void AddNewTask(const string& person)
  {
    addTask(person, TaskStatus::NEW);
  }

  // Update statuses:
  // Sort un-done tasks by statuses
  // First task-count tasks move to the next status
  //return all updated tasks
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count)
      {
        TasksInfo updated_tasks, untouched_tasks;
        sort(persons_tasks[person].begin(), persons_tasks[person].end());

        for(TaskStatus& task : persons_tasks[person])
        {
          if((task_count != 0) && (task != TaskStatus::DONE))
          {
            task = static_cast<TaskStatus>(static_cast<int>(task)+1);
            updateTasksState(updated_tasks, task, false);
            task_count--;
          }
          else if (task != TaskStatus::DONE)
          {
            updateTasksState(untouched_tasks, task, false);
          }
        }

        for(auto task : persons_tasks[person])
        {
          cout<<static_cast<int>(task)<<endl;
        }

        mergeStateAfterPerform(updated_tasks, untouched_tasks, person);

        return tie(updated_tasks, untouched_tasks);
      }

private:
  map<string, TasksInfo> persons_tasks_state;
  map<string, vector<TaskStatus>>persons_tasks;

  void updateTasksState(TasksInfo& info, TaskStatus newState, bool to_remove)
  {
    if(to_remove)
    {
      info[newState]--;
    }
    else
    {
      info[newState]++;
    }
  }

  void addTask(const string& person, TaskStatus state)
  {
    vector<TaskStatus> tasks;
    tasks = persons_tasks[person];
    tasks.push_back(state);

    persons_tasks[person] = tasks;

    updateTasksState(persons_tasks_state[person], state, false);
  }

  void mergeStateAfterPerform(TasksInfo& update, TasksInfo& untouch, const string& person)
  {
    TasksInfo& internal_state = persons_tasks_state[person];
    TaskStatus status = TaskStatus::NEW;

    while(status != TaskStatus::DONE)
    {
      internal_state[status] = update.find(status)->second + untouch.find(status)->second;
      status = static_cast<TaskStatus>(static_cast<int>(status)+1);
    }

    internal_state.find(status)->second += update.find(status)->second;
  }
};


void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

    cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
