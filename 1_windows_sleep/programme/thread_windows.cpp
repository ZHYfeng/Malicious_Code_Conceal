// thread_windows.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>

#define MAX_THREADS 10

using namespace std;

typedef vector<int> IntVector;

static string OUTPUT_FILENAME = "statistic.log";
static long LOOPS = 190000;
static long SLEEP = 0;
static unsigned int THREAD_NUMS = 4;
static unsigned int MCODE_NUMS = 4;

static IntVector intVector;
HANDLE hMutex;
unsigned int order = 0;

void placeholder();
void message(int msg);
void maliciousePrototype(int o);
void recordMessage();

int ThreadRoutine()
{
	for (unsigned int m = 0; m < MCODE_NUMS; m++) {
		maliciousePrototype(m+1);
	}
	return 0;
}

int ThreadCreation()
{
	static HANDLE aThreads[MAX_THREADS] = { 0 };

	const unsigned int num_threads = THREAD_NUMS;
	unsigned long thread_id = 0;

	// cout << "creating threads " << num_threads << endl;

	unsigned int running_threads = 0;
	unsigned long slot = 0;
	unsigned long thread_ret = 0;

	for (; running_threads < num_threads; running_threads++)
	{
		aThreads[running_threads] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, 0, 0, (LPDWORD)&thread_id);
	}

	while (running_threads > 0)
	{
		slot = WaitForMultipleObjects(running_threads, aThreads, FALSE, INFINITE);
		GetExitCodeThread(aThreads[slot], &thread_ret);
		CloseHandle(aThreads[slot]);
		aThreads[slot] = aThreads[running_threads - 1];
		running_threads--;
	}

	// cout << "All threads teminated" << endl;

	return 1;
}

int initMutex(const char* mutextName)
{
	hMutex = CreateMutex(NULL, FALSE, mutextName);
	if (hMutex == NULL) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Expected Output filename and loop times" << endl;
		//system("pause");
		return 0;
	}
	string f(argv[1]);
	OUTPUT_FILENAME = f;
//	THREAD_NUMS = atoi(argv[2]);
//	MCODE_NUMS = atoi(argv[3]);
//	LOOPS = atol(argv[4]);
	SLEEP = atol(argv[2]);	

	if (initMutex("MyMutext") == 0) {
		ThreadCreation();
		recordMessage();
	}else {
		cout << "Init Mutex Fail" << endl;
	}
	//system("pause");
	return 0;
}

// ͨ��ѭ������ռ�õ� CPU time slice ��ʱ�䣬���������ԣ��������߳��л��Ὰ����
inline void placeholder()
{
//	for (int i = 0; i < LOOPS; i++)
//	{
//
//	}
}

void message(int msg)
{
	intVector.push_back(msg);
}

void recordMessage()
{
	ostringstream oss;
	if (!intVector.empty()) {
		copy(intVector.begin(), intVector.end() - 1, ostream_iterator<int>(oss, ", "));
		oss << intVector.back();
	}
	// cout << oss.str() << endl;
	ofstream myfile;
	myfile.open(OUTPUT_FILENAME.c_str(), ios::out | ios::app);
	myfile << oss.str() << "\n";
	myfile.close();

}

// ��������ģ��
void maliciousePrototype(int o)
{
	placeholder();
	Sleep(SLEEP);
	WaitForSingleObject(hMutex, INFINITE);
	message(o);
	if ((o - order) == 1) {
		order = o;
	}
	ReleaseMutex(hMutex);
}
