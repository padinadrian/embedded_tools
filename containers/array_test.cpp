#include <iostream>
#include "adrian_fixed_heap.hpp"
using namespace adrian;

int main()
{
    FixedHeap<int, 5, std::greater<int>> heap(std::greater<int>{});
    heap.Push(6);
    heap.Push(10);
    heap.Push(4);
    heap.Push(25);
    std::cout << heap.Top() << std::endl;
    heap.Pop();
    std::cout << heap.Top() << std::endl;
    heap.Pop();
    std::cout << heap.Top() << std::endl;
}



