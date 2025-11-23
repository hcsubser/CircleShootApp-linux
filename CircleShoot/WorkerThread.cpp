#include "Zuma_Prefix.pch"

#include "WorkerThread.h"
#include <pthread.h>
#include "pevents.h"

//#ifdef _WIN32
//#include <windows.h>
//#include <process.h>
//#else
//#error WorkerThread is unimplemented on non-win32 platforms.
//#endif

using namespace Sexy;

WorkerThread::WorkerThread()
{
	mShutdown = false;
	mTaskProc = NULL;
	mUnk1 = neosmart::CreateEvent(false, false);//
	mUnk2 = neosmart::CreateEvent(false, false);

	//_beginthread((void(*)(void*)) WorkerThread::StaticThreadProc, 0, this);//
	//std::thread thread(WorkerThread::StaticThreadProc,this);
	//thread.detach();
	//printf("\n%s %s1\n",__func__);fflush(stdout);
	pthread_t *thread =(pthread_t*) malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, WorkerThread::StaticThreadProc, this);
	//pthread_detach(*thread);
	//printf("\n%s %s2\n",__func__);fflush(stdout);
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::WaitForTask()
{
	if (mTaskProc)
	{
		//WaitForSingleObject(mUnk2, 1000);//
		neosmart::WaitForEvent(mUnk2,1000);
	}

	neosmart::ResetEvent(mUnk2);//
}

void WorkerThread::DoTask(void (*theTaskProc)(void*), void* theParam)
{
	WaitForTask();

	mTaskProc = theTaskProc;
	mParam = theParam;

	neosmart::SetEvent(mUnk1);//
}

void* WorkerThread::StaticThreadProc(void* arg) 
{
	//neosmart::neosmart_event_t ct = GetCurrentThread();//
	//SetThreadPriority(ct, THREAD_PRIORITY_LOWEST);//
	//pthread_setschedparam(thr.native_handle(), policy, {priority});//TODO
	//WaitForSingleObject(thr->mUnk1, 1000);//
	//printf("\n%s %s1\n",__func__);fflush(stdout);
	WorkerThread* thr = static_cast<WorkerThread*>(arg);
    //thr->Run();  
	//printf("\n%s %s2\n",__func__);fflush(stdout);
	neosmart::WaitForEvent(thr->mUnk1,1000);
	while (!thr->mShutdown)
	{
		if (thr->mTaskProc) {
			thr->mTaskProc(thr->mParam);
			thr->mTaskProc = NULL;

			neosmart::SetEvent(thr->mUnk2);//
		}
	//printf("\n%s %s3\n",__func__);fflush(stdout);
		//WaitForSingleObject(thr->mUnk1, 1000);//
		neosmart::WaitForEvent(thr->mUnk1,1000);
	}
	//printf("\n%s %s4\n",__func__);fflush(stdout);
	neosmart::SetEvent(thr->mUnk2);//
}