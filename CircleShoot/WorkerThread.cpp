#include "Zuma_Prefix.pch"

#include "WorkerThread.h"
#include <pthread.h>
#include "pevents.h"

using namespace Sexy;

WorkerThread::WorkerThread()
{
	mShutdown = false;
	mTaskProc = NULL;
	mUnk1 = neosmart::CreateEvent(false, false);//
	mUnk2 = neosmart::CreateEvent(false, false);

	mThread =(pthread_t*) malloc(sizeof(pthread_t));
	pthread_create(mThread, NULL, WorkerThread::StaticThreadProc, this);
}

WorkerThread::~WorkerThread()
{
	free(mThread);
}

void WorkerThread::WaitForTask()
{
	if (mTaskProc)
	{
		neosmart::WaitForEvent(mUnk2,1000);
	}

	neosmart::ResetEvent(mUnk2);
}

void WorkerThread::DoTask(void (*theTaskProc)(void*), void* theParam)
{
	WaitForTask();

	mTaskProc = theTaskProc;
	mParam = theParam;

	neosmart::SetEvent(mUnk1);
}

void* WorkerThread::StaticThreadProc(void* arg) 
{
	//neosmart::neosmart_event_t ct = GetCurrentThread();//
	//SetThreadPriority(ct, THREAD_PRIORITY_LOWEST);//
	//pthread_setschedparam(thr.native_handle(), policy, {priority});//TODO
	//WaitForSingleObject(thr->mUnk1, 1000);//
	//printf("\n%s %s1\n",__func__);fflush(stdout);
	WorkerThread* thr = static_cast<WorkerThread*>(arg);

	neosmart::WaitForEvent(thr->mUnk1,1000);
	while (!thr->mShutdown)
	{
		if (thr->mTaskProc) {
			thr->mTaskProc(thr->mParam);
			thr->mTaskProc = NULL;

			neosmart::SetEvent(thr->mUnk2);
		}
		neosmart::WaitForEvent(thr->mUnk1,1000);
	}
	neosmart::SetEvent(thr->mUnk2);
}