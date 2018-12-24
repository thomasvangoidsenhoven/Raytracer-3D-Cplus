#include "tasks/parallel-task-scheduler.h"
using namespace tasks;

namespace
{
	/// <summary>
	/// 
	/// </summary>
	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{
	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{
		
			// [&] capture all variables within scope by reference
			parallel_for(tasks.size(), [&](int start, int end) {
				for (int i = start; i < end; ++i) {
					
					tasks[i]->perform();
				}
			
			});
			
			
		}


	
	};
	
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}
