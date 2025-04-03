#include <iostream>
#include <cmath>

/* Структура стека через массивы*/
struct Stack{
private:
    int* stack_body;
    int stack_size;
    int used_memory;

public:
/* Конструктор*/
    Stack(){
        this -> stack_body = new int[0];
        this -> stack_size = 0;
        this -> used_memory = 0;
    }
/* Деструктор*/
    ~Stack(){
        if(used_memory != 0)
            delete[] stack_body;
    }
/* Проверяем, пуст ли стек */
    bool is_empty(){
        return (this -> used_memory == 0);
    }
/* Добавляем элемент в стек путем перекопирования
старого стека и нового элемента в новый массив*/
    void push(int element){
        if(used_memory+1 >= stack_size){
            int* copy_array = new int[stack_size*2];
            for(int i = 0; i < used_memory; i++){
                copy_array[i] = stack_body[i];
            }
            this -> stack_size *= 2;
            this -> stack_body = copy_array;
        }
        stack_body[used_memory] = element;
        this -> used_memory++;

    }
/* Если стек пуст, возвращаем INFINITY; иначе возвращаем последний элемент*/
    int pop(){
        if(is_empty()){
            return INFINITY;
        }
        used_memory--;
        return this -> stack_body[used_memory];
    }
};

/* Структура очереди через два стека */
struct Queue{
private:
    Stack stack1, stack2;
    int size = 0;
public:
/* Конструктор: инициализируем два стека и считаем, что размер очереди 0 */
    Queue(){
        this -> stack1 = Stack();
        this -> stack2 = Stack();
        this -> size = 0;
    }

/* Пуста ли очередь */
    bool is_empty(){
        if(size == 0)
            return 1;
        return 0;
    }
/* Добавление элемента в очередь: 
просто кидаем во внутренний стек элементы и увеличиваем размер*/
    void enqueue(int element){
        stack1.push(element);
        size++;
    }
/* Удаление элемента: если во внешнем стеке ничего нет,
то перекидываем все, что есть из внутреннего. Иначе просто push*/
    int dequeue(){
        if(stack2.is_empty()){
            while (!stack1.is_empty())
            {
                stack2.push(stack1.pop());
                size--;
            }
            
        }
        return stack2.pop();
    }

};

int main() {
    Queue empty_queue;
    std::cout << empty_queue.dequeue() << std::endl; // INFINITY

    std::cout << "====" << std::endl;

    Queue large_queue;
    int element;
    for(int i = 0; i < 5; i++){
        element = rand()%10;
        large_queue.enqueue(element);
        std::cout << "Add: " << element << std::endl;
    }

    std::cout << "====" << std::endl;

    for(int j = 0; j < 5; j++){
        std::cout << "Pop: " << large_queue.dequeue() << std::endl;
    }
    return 0;
}
