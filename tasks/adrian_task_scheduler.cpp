// TODO: Header

/* ===== Includes ===== */
#include <stdint.h>
#include <iostream>

namespace adrian
{
    /* ===== Typedefs ===== */

    /**
     * Type definition for a generic Task function.
     * Accepts a single void pointer as an argument
     * and returns nothing.
     */
    typedef void (*TaskFunction)(void*);


    /* ===== Public Classes ===== */

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
    template<size_t N>
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

        /* ===== Private Classes ===== */

        struct ScheduledTask
        {
            Task task;
            uint32_t execs_remaining;
            uint32_t exec_time_ms;
        };

        /* ===== Private Functions ===== */

        void ScheduleTask(
                const Task task,
                const uint32_t period_ms,
                const bool repeating)
        {
            const uint32_t scheduled_exec_time = period_ms +
            for (auto iter = scheduled_tasks.Begin();
                iter != scheduled_tasks.End();
                iter++)
            {
                if ()
            }
        }

    private:
        /* ===== Private Data ===== */
        FixedList<ScheduledTask, N> scheduled_tasks;
    };
}

int main()
{
    adrian::TaskScheduler scheduler;

    scheduler.ScheduleSingleTask()
}