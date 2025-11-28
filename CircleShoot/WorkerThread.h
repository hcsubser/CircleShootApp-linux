#ifndef __SEXY_WORKER_THREAD_H__
#define __SEXY_WORKER_THREAD_H__

#include "CircleCommon.h"
#include "pevents.h"

#include <vector>
#include <list>

//#include <windows.h>

namespace Sexy
{
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	class WorkerThread
	{
	public:
		neosmart::neosmart_event_t_* mUnk1;
		neosmart::neosmart_event_t_* mUnk2;
		void (*mTaskProc)(void *);
		void *mParam;
		bool mShutdown;
		pthread_t *mThread;

		WorkerThread();

		virtual ~WorkerThread();

		void WaitForTask();
		void DoTask(void (*func)(void *), void *unk);

		static void* StaticThreadProc(void* arg);
	};
};

#endif