# Поставщик асинхронных результатов packaged_task

* Некая абстракция над функциональной сущностью
* Является поставщиком асинхронных результатов
* Позволяет получить экземпляр класса `future` с помощью метода `get_future()`

## Пример
```cpp
int someTask(int delay) {    
        cout << "START TASK" << endl;
        cout << "thread:" << this_thread::get_id() << endl;
        for (int index = 0; index < 100; index++) {
            cout << "*";
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
        cout << endl;
        cout << "END TASK" << endl;
        return 10;
    }
```

```cpp
cout << "thread:" << this_thread::get_id() << endl;  packaged_task<int(int)> task(someTask);
future<int> simple_future = task.get_future();
// синхронное выполнение задачи
//task(10);
// абстрагируемся от конкретной функциональной
// сущности и передаем задачу которая что-то 
// принимает и что-то возвращает
thread someThr(ref(task), 10);
// на самом деле не можем получить 
// значение функтором packaged_task
//int result = task(10);
for (int index = 0; index < 100; index++) {         
cout << "!";
            this_thread::sleep_for(chrono::milliseconds(10));
}
cout << endl;
int value = simple_future.get();
cout << "Value = " << value << endl;
someThr.join();
```
Вывод:
```cpp
thread:15804
!START TASK
thread:10476
*!**!*!!*!**!!**!*!!**!!*!*!*!**!!**!*!!*!**!*!!**!*!!**!!**!*!*!*!!**!!**!*!*!!*!*!**!!*!**!*!!*!*!**!!*!*!*!**!!**!*!*!*!!*!*!*!**!*!!**!!**!!*!*!**!!*!*!**!*!*!!*!**!!**!!**!*!!**!*!!**!*!!*!**!*!

END TASK
Value = 10
```