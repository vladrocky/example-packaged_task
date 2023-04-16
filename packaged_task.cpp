#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

using namespace std;

// packaged_task
namespace taskExample
{

    int someTask(int delay)
    {

        cout << "START TASK" << endl;
        cout << "thread:" << this_thread::get_id() << endl;

        for (int index = 0; index < 100; index++)
        {
            cout << "*";
            this_thread::sleep_for(chrono::milliseconds(delay));
        }

        cout << endl;
        cout << "END TASK" << endl;
        return 10;
    }

    void showExample()
    {

        cout << "thread:" << this_thread::get_id() << endl;

        packaged_task<int(int)> task(someTask);
        future<int> simple_future = task.get_future();

        // синхронное выполнение задачи
        // task(10);

        // авбстрагируемся от конкретной функциональной
        // сущности и передаем задачу которая что-то
        // принимает и что-то возвращает
        thread someThr(ref(task), 10);

        // на самом деле не можем получить
        // значение функтором pacaged_task
        // int result = task(10);

        for (int index = 0; index < 100; index++)
        {

            cout << "!";
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        cout << endl;
        int value = simple_future.get();
        cout << "Value = " << value << endl;
        someThr.join();
    }
}

int main()
{

    taskExample::showExample();

    return 0;
}
