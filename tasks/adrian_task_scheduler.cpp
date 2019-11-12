// TODO: Header

/* ===== Includes ===== */
#include <stdint.h>

namespace adrian
{
    /**
     * Type definition for a generic Task function.
     * Accepts a single void pointer as an argument
     * and returns nothing.
     */
    typedef void (*TaskFunction)(void*);

    /** Forward declaration. */
    class TaskScheduler;

    /** Task class for wrapping TaskFunctions and arguments. */
    class Task
    {
    public:

        /** Constructor - set the function and pointer. */
        Task(TaskFunction func, void* context_ptr) :
                m_func(func),
                m_context_ptr(context_ptr)
        {
            // Nothing
        }

        /** Execute the task by calling the task function. */
        void Execute() const
        {
            m_func(m_context_ptr);
        }

    private:
        TaskFunction m_func;    //< Function pointer
        void* m_context_ptr;    //< Context pointer
    };

    /** Class for scheduling future tasks. */
    class TaskScheduler
    {
    public:
        /** Schedule a task to execute once in the future. */
        void ScheduleSingleTask(
                const Task task,
                const uint32_t delay_ms)
        {
            this->ScheduleTask()
        }

        /** Schedule a task to execute periodically. */
        void ScheduleRepeatingTask(
                const Task task,
                const uint32_t period_ms,
                const uint32_t repetitions)
        {

        }

        /**
         * Run continuously until all tasks are complete.
         * If periodic tasks are scheduled this function
         * will not return.
         */
        void Run()
        {
            while
        }

    private:

        /** */
        struct ScheduledTask
        {
            Task task;
            uint32_t remaining;


        };

        void ScheduleTask(
                const Task task,
                const uint32_t period_ms,
                const bool repeating)
        {

        }



    };
}

int main()
{

}