#include <pthread.h>
#include <iostream>

class ThreadExitException
{
public:
    /* Create an exception-signaling thread exit with RETURN_VALUE. */
    ThreadExitException(void* return_value)
        : thread_return_value_(return_value)
    {
    }

    /* Actually exit the thread, using the return value provided in the constructor. */
    void* DoThreadExit()
    {
        pthread_exit(thread_return_value_);
    }

private:
    /* The return value that will be used when exiting the thread. */
    void* thread_return_value_;
};

bool should_exit_thread_immediately(int iteration)
{
    // Simulate an exit condition after a certain number of iterations.
    return iteration >= 1000; // Change this condition as needed.
}

void do_some_work()
{
    int iteration = 0;

    while (true)
    {
        /* Do some useful things here... */
        std::cout << "Iteration " << iteration << ": Doing some work..." << std::endl;

        if (should_exit_thread_immediately(iteration))
            throw ThreadExitException(nullptr);

        iteration++;
    }
}

void* thread_function(void*)
{
    try
    {
        do_some_work();
    }
    catch (ThreadExitException& ex)
    {
        /* Some function indicated that we should exit the thread. */
        ex.DoThreadExit();
    }
    return nullptr;
}

int main()
{
    pthread_t thread;

    /* Create a thread. */
    if (pthread_create(&thread, nullptr, thread_function, nullptr) != 0)
    {
        std::cerr << "Error creating thread" << std::endl;
        return 1;
    }

    /* Wait for the thread to finish. */
    if (pthread_join(thread, nullptr) != 0)
    {
        std::cerr << "Error joining thread" << std::endl;
        return 1;
    }

    return 0;
}
