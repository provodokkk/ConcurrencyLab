#include <iostream>
#include <list>
#include <future>
#include <ctime>
#include <mutex>
#include <conio.h>
#include <time.h>
#include <thread>
#include <stdbool.h>

using namespace std;

void array_input(list<int>& arr, int n)
{
    for (int i = 0; i < n; i++) {
        arr.push_back(i);
    }
}
void array_output(list<int>& arr)
{
    cout << endl;
    for (int elem : arr) {
        cout << elem << "  ";
    }
    cout << endl;
}
double task(list<int>& arr, int n, int value, int M, int thread_number)
{
    int length = n / M;
    int end = (thread_number + 1) * length;
    if (thread_number == M - 1) {
        end = (thread_number + 1) * length + (n % M);
    }

    list<int>::iterator it = arr.begin();
    double start_time = clock();
    for (int i = thread_number * length; i < end; ++i) {
        it = arr.begin();
        advance(it, i);
        *it += value;
    }
    double end_time = clock();

    return (end_time - start_time) / CLOCKS_PER_SEC;
}


bool mode = false;
bool program_start_stop()
{
    return mode;
}
mutex m;
condition_variable cv;

void generator(char& input, list<int>& data_arr, list<int>& thread_number_arr, int thread_number)
{
    srand(time(NULL));
    while (true) {
        if (input == 'y') {
            this_thread::yield();
            mode = true;
            unique_lock<mutex> ul(m);
            data_arr.push_back(rand() % 100);
            thread_number_arr.push_back(thread_number);
            cv.notify_one();
        }
        else {
            mode = false;
            break;
        }
    }
}
void processor(list<int>& data_arr, list<int>& thread_number_arr)
{
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(50));
        if (program_start_stop() == false) {
            break;
        }

        unique_lock<mutex> ul(m);
        cv.wait(ul, program_start_stop);

        cout << "\nThread " << thread_number_arr.front() << " = " << data_arr.front();
        data_arr.pop_front();
        thread_number_arr.pop_front();
    }
}

int main()
{
    cout << "======================== Task 1 ========================" << endl;
    int n = 3001; // array length
    int M = 3; // number of array parts
    char output = 'n';
    int value = 5; // the number by which it increases
    list<int> arr; // data
    double start_time, end_time;
    list<future<double>> f_async, f_deferred;
    int thread_number = 0;


    cout << "Input the length of the array: "; cin >> n;
    cout << "Input the number of parts of the array: "; cin >> M;
    cout << "Input the number by which you want to increase the values of the array: "; cin >> value;
    cout << "\nInput 'y' to output the array and 'n' to not output: "; output = _getche();

    array_input(arr, n);
    if (output == 'y') {
        array_output(arr);
    }

    cout << "\n---------------------------------------------------------" << endl;
    cout << "---------------------- async mode ----------------------" << endl;
    start_time = clock();
    for (int i = 0; i < M; ++i) {
        f_async.push_back(async(launch::async, task, ref(arr), n, value, M, i));
    }
    for (auto& f_var : f_async) {
        cout << "async Thread = " << f_var.get() << endl;
    }
    end_time = clock();
    cout << "\nasync task time = " << (end_time - start_time) / CLOCKS_PER_SEC << endl;
    if (output == 'y') {
        array_output(arr);
    }

    cout << "---------------------------------------------------------" << endl;
    cout << "--------------------- deferred mode ---------------------" << endl;
    start_time = clock();
    for (int i = 0; i < M; ++i) {
        f_deferred.push_back(async(launch::deferred, task, ref(arr), n, value, M, i));
    }
    for (auto& f_var : f_deferred) {
        cout << "deferred Thread " << ++thread_number << " = " << f_var.get() << endl;
    }
    end_time = clock();
    cout << "\ndeferred task time = " << (end_time - start_time) / CLOCKS_PER_SEC << endl;
    if (output == 'y') { 
        array_output(arr);
    }


    cout << "\n\n================================= Task 2 =================================" << endl;
    const int N = 3;
    thread producer[N];
    thread consumer;
    list<int> data_arr;
    list<int> thread_number_arr;

    char input;
    cout << "\nInput 'y' to start the program and 'n' when to stop: ";
    input = _getche();
    for (int i = 0; i < N; i++) {
        producer[i] = thread(generator, ref(input), ref(data_arr), ref(thread_number_arr), i + 1);
    }
    consumer = thread(processor, ref(data_arr), ref(thread_number_arr));
    if (input == 'y') {
        input = _getch();
    }
    else {
        input = 'n';
        cout << "\nWrong character!";
    }

    for (auto& th : producer) {
        th.join();
    }
    consumer.join();

    cout << endl << endl;
    return 0;
}