/**
 * File:    adrian_fixed_list.hpp
 * Author:  padin.adrian@gmail.com
 */

#ifndef ADRIAN_FIXED_LIST_HPP_
#define ADRIAN_FIXED_LIST_HPP_

/* ===== Includes ===== */
#include <inttypes.h>
// #include <iostream>

namespace adrian
{
    template <class T, size_t N>
    class FixedList
    {
    private:
        /* ===== Private Classes ===== */

        // Single node in the list
        struct Node
        {
            Node* prev_ptr;     //< Pointer to the previous node, or NULL.
            Node* next_ptr;     //< Pointer to the next node, or NULL.
            T data;             //< Data contained by the node.
        };

    public:
        /* ===== Public Classes ===== */

        // For iterating over the list
        class Iterator
        {
        public:
            /* ===== Public Functions ===== */

            // Dereference operator - get the data from the iterator.
            const T& operator*() const
            {
                return node_ptr->data;
            }

            // Increment operator - move one forward in the list.
            Iterator operator++(int)
            {
                Iterator retval = *this;
                node_ptr = node_ptr->next_ptr;
                return retval;
            }

            // Decrement operator - move one backward in the list.
            Iterator operator--(int)
            {
                Iterator retval = *this;
                node_ptr = node_ptr->prev_ptr;
                return retval;
            }

            // Comparison operator - check if iterators are equivalent.
            bool operator==(const Iterator& rhs) const
            {
                return (this->node_ptr == rhs.node_ptr);
            }

            // Comparison operator - check if iterators are not equivalent.
            bool operator!=(const Iterator& rhs) const
            {
                return (this->node_ptr != rhs.node_ptr);
            }

        private:
            /* ===== Private Data ===== */
            Iterator(Node* ptr) : node_ptr(ptr) {}
            Node* node_ptr;

            friend class FixedList;
        };

    public:
        /* ===== Public Functions ===== */

        // Constructor: Initialize data.
        FixedList() :
                furthest_node(0),
                num_freed_nodes(0),
                front_iter(NULL),
                back_iter(NULL),
                end_iter(NULL)
        {
            // Do nothing
        }

        // Iterators at beginning and end of list (can be NULL).
        Iterator Begin() { return front_iter; }
        Iterator End() { return end_iter; }

        // Iterators at front and back of list (can be NULL).
        Iterator Front() { return front_iter; }
        Iterator Back() { return back_iter; }

        // Clear all nodes from the list.
        void Clear()
        {
            furthest_node = 0;
            num_freed_nodes = 0;
            front_iter.node_ptr = NULL;
            back_iter.node_ptr = NULL;
        }

        // Insert at front of list.
        Iterator InsertFront(const T& data)
        {
            // Create the new node.
            Node* new_node = this->GetNewNode();
            if (new_node == NULL)
            {
                // List is full, return NULL.
                return Iterator(NULL);
            }

            // Insert node into list.
            new_node->data = data;
            new_node->prev_ptr = NULL;
            new_node->next_ptr = front_iter.node_ptr;
            if (front_iter.node_ptr)
            {
                front_iter.node_ptr->prev_ptr = new_node;
            }
            front_iter.node_ptr = new_node;

            // If the list was previously empty
            // This is now the back iter too.
            if (!back_iter.node_ptr)
            {
                back_iter = front_iter;
            }

            return Iterator(new_node);
        }

        // Insert at back of list.
        Iterator InsertBack(const T& data)
        {
            // Create the new node.
            Node* new_node = this->GetNewNode();
            if (new_node == NULL)
            {
                // List is full, return NULL.
                return Iterator(NULL);
            }

            // Insert node into list.
            new_node->data = data;
            new_node->next_ptr = NULL;
            new_node->prev_ptr = back_iter.node_ptr;
            if (back_iter.node_ptr)
            {
                back_iter.node_ptr->next_ptr = new_node;
            }
            back_iter.node_ptr = new_node;

            // If the list was previously empty
            // This is now the front iter too.
            if (!front_iter.node_ptr)
            {
                front_iter = back_iter;
            }

            return Iterator(new_node);
        }

        // Insert in the middle, after the given iterator.
        // Iterator must be valid (cannot be NULL).
        Iterator Insert(Iterator iter, const T& data)
        {
            // Create new node.
            Node* new_node = this->GetNewNode();
            if (new_node == NULL)
            {
                return iter;    // If new_node is null, iter will be null
            }

            // Insert into list.
            Node* node_before = iter.node_ptr;
            Node* node_after = node_before->next_ptr;

            new_node->prev_ptr = node_before;
            if (node_before)
            {
                node_before->next_ptr = new_node;
            }

            new_node->next_ptr = node_after;
            if (node_after)
            {
                node_after->prev_ptr = new_node;
            }

            // Assing data and return new iterator.
            new_node->data = data;
            iter.node_ptr = new_node;
            return iter;
        }

        // Delete a node in the middle.
        void Erase(Iterator iter)
        {
            Node* node_ptr = iter.node_ptr;
            Node* prev_ptr = node_ptr->prev_ptr;
            Node* next_ptr = node_ptr->next_ptr;

            if (prev_ptr)
            {
                prev_ptr->next_ptr = next_ptr;
            }
            if (next_ptr)
            {
                next_ptr->prev_ptr = prev_ptr;
            }

            FreeNode(node_ptr);
        }

        // Get the number of elements in the list.
        size_t Size() const
        {
            return furthest_node - num_freed_nodes;
        }

        // Get the maximum capacity of the list.
        size_t Capacity() const
        {
            return N;
        }

    private:
        /* ===== Private Functions ===== */

        // Returns pointer to a free node.
        // If no nodes are available, returns NULL.
        Node* GetNewNode()
        {
            if (num_freed_nodes > 0)
            {
                Node* new_node = (freed_nodes[--num_freed_nodes]);
                return new_node;
            }
            else if (furthest_node < N)
            {
                Node* new_node = (node_array + (furthest_node++));
                return new_node;
            }
            return NULL;
        }

        // Releases a node from use.
        void FreeNode(Node* node_ptr)
        {
            freed_nodes[num_freed_nodes++] = node_ptr;
        }

    // public:
    //     // Debugging function
    //     void PrintInternals()
    //     {
    //         for (size_t i = 0; i < N; i++)
    //         {
    //             std::cout << "[" << node_array[i].data << "] ";
    //         }
    //         std::cout << "\nFree: ";
    //         for (size_t i = 0; i < num_freed_nodes; i++)
    //         {
    //             std::cout << "[" << freed_nodes[i] << "] ";
    //         }
    //         for (size_t i = num_freed_nodes; i < N; i++)
    //         {
    //             std::cout << "[ ] ";
    //         }
    //         std::cout << std::endl;
    //     }

    private:
        /* ===== Private Data ===== */
        Node node_array[N];         //< Holds all the actual list nodes.
        Node* freed_nodes[N];       //< Holds a cache of "freed" nodes.
                                    //< These can be reused if more space is needed.
        size_t furthest_node;       //< Index of last unused node in node_array.
        size_t num_freed_nodes;     //< Number of free nodes in the freed_nodes array.
        Iterator front_iter;        //< Iterator to first element in list.
        Iterator back_iter;         //< Iterator to last element in list.
        const Iterator end_iter;    //< Iterator to "end" element - one past the last.
                                    //< This will always be a NULL iterator.
    };
}

#endif  // ADRIAN_FIXED_LIST_HPP_
