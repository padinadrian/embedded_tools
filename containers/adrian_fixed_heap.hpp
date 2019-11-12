

#include <array>
#include <algorithm>

namespace adrian
{
    template <class T, std::size_t N, class Compare>
    class FixedHeap
    {
    public:
        typedef typename std::array<T, N>::iterator FixedHeapIterator;


        FixedHeap(Compare comp_in) :
                back_iter(elements.begin()),
                comp(comp_in)
        {
            // nothing
        }

        void Push(const T& item)
        {
            if (back_iter == elements.end())
            {
                throw std::runtime_error("Cannot push; FixedHeap is full.");
            }
            *back_iter = item;
            std::push_heap(elements.begin(), back_iter++, comp);
        }

        void Pop()
        {
            std::pop_heap(elements.begin(), back_iter--, comp);
        }

        const T& Top()
        {
            return elements.front();
        }

    private:
        std::array<T, N> elements;
        FixedHeapIterator back_iter;
        Compare comp;
    };
}
