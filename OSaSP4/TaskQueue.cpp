#include <Windows.h>
#include "TaskQueue.h"
TaskQueue::TaskQueue() {
	InitializeCriticalSection(&criticalSection);
}
void TaskQueue::AddTask(Task task) {
	EnterCriticalSection(&criticalSection);
	tasks.push(task);
	LeaveCriticalSection(&criticalSection);
}
Task TaskQueue::RemoveTask() {
	EnterCriticalSection(&criticalSection);
	Task task;
	if (tasks.size() > 0) {
		task = tasks.front();
		tasks.pop();
	}
	LeaveCriticalSection(&criticalSection);
	return task;
}