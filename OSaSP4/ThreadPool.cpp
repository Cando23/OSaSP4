//#include "ThreadPool.h"
//ThreadPool::ThreadPool(int threadCount,TaskQueue* pQueue) {
//	HANDLE* threads = (HANDLE*)malloc(sizeof(HANDLE) * threadCount);
//    queue = pQueue;
//	for (int i = 0; i < threadCount; i++)
//	{
//		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPool::ProcessTask, NULL, 0, NULL);
//	}
//	WaitForMultipleObjects(threadCount, threads, TRUE, INFINITE);
//    for (int i = 0; i < threadCount; i++)
//    {
//        CloseHandle(threads[i]);
//        if (threads[i] != NULL)
//        {
//            threads[i] = NULL; 
//        }
//    }
//    free(queue);
//    free(threads);
//}
//vector<string> ThreadPool::ProcessTask() {
//    WaitForSingleObject(mutexQueue, INFINITE);
//    Task task = queue->RemoveTask();
//    ReleaseMutex(mutexQueue);
//    vector<string> v = task.text;
//    sort(v.begin(), v.end());
//    return v;
//}