#include "windows.h"
#include "TaskQueue.h"
#include <fstream>
#define THREAD_COUNT 2

TaskQueue* tq;
TaskQueue* rq;
DWORD WINAPI ProcessTask() {
	Task task = tq->RemoveTask();
	if (!task.text.empty()) {
		sort(task.text.begin(), task.text.end());
		rq->AddTask(task);
	}
	ExitThread(0);
}
void CreateThreadPool(int threadCount) {
	HANDLE* threads = (HANDLE*)malloc(sizeof(HANDLE) * threadCount);
	for (int i = 0; i < threadCount; i++)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessTask, NULL, 0, NULL);
	}
	WaitForMultipleObjects(threadCount, threads, TRUE, INFINITE);
	for (int i = 0; i < threadCount; i++)
	{
		if (threads[i] != NULL)
		{
			threads[i] = NULL;
		}
	}
	free(threads);
}
vector<string> ReadFile() {
	ifstream file("data.txt");
	string word;
	vector<string> data;
	while (file >> word) {
		data.push_back(word);
	}
	return data;
}
void WriteResult(const vector<string>& data) {
	ofstream file("../result.txt");
	for (const auto& line : data) {
		file << line << " ";
	}
}
void CreateTasks(vector<string>& data) {
	int taskSize = ceil((double)data.size() / THREAD_COUNT);
	for (int i = 0; i < THREAD_COUNT; i++) {
		Task task(vector<string>{data.begin() + i * taskSize, 
			data.size() < (i + 1) * taskSize ? 
			data.end() : data.begin() + (i + 1) * taskSize});
		tq->AddTask(task);
	}
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	tq = new TaskQueue();
	rq = new TaskQueue();
	auto data = ReadFile();
	CreateTasks(data);
	CreateThreadPool(THREAD_COUNT);
	rq->RemoveTask();
	free(tq);
	free(rq);
	return 0;
}