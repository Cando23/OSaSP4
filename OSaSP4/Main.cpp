#include "windows.h"
#include "TaskQueue.h"
#include <fstream>
#define THREAD_COUNT 2

TaskQueue* tq;
TaskQueue* rq;
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
	ofstream file("result.txt");
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
vector<string> MergeSort(vector<string> v1, vector<string> v2)
{
	int i = 0, j = 0;
	vector<string> res{};
	while (i < v1.size() && j < v2.size()) {
		if (v1[i] < v2[j])
			res.push_back(v1[i++]);
		else
			res.push_back(v2[j++]);
	}
	while (i < v1.size())
		res.push_back(v1[i++]);
	while (j < v2.size())
		res.push_back(v2[j++]);
	return res;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	tq = new TaskQueue();
	rq = new TaskQueue();
	auto data = ReadFile();
	CreateTasks(data);
	vector<string> result;
	if (rq->Size() > 0) {
		result = tq->RemoveTask().text;
		while (rq->Size() > 0) {
			data = rq->RemoveTask().text;
			result = MergeSort(result, data);
		}
		WriteResult(result);
	}
	free(tq);
	free(rq);
	return 0;
}