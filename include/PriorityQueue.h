#pragma once

#include <iostream>
#include <list>
#include <exception>
#include "Dog.h"

/**
 * @brief Functor for comparing elements in the priority queue.
 *
 * The MyComparator struct provides a comparison function that is used
 * to determine the priority of elements in the priority queue.
 * It subtracts two elements to compare them.
 *
 * @tparam T The type of elements to be compared.
 */
template <class T>
struct MyComparator {
	/**
	* @brief Compares two elements.
	*
	* @param a The first element.
	* @param b The second element.
	* @return The result of the comparison: a - b.
	*/
	typename T operator()(const T& a, const T& b) const {
		return a - b;
	}
};

/**
 * @brief A generic priority queue implementation using a list.
 *
 * The PriorityQueue class provides a basic priority queue functionality
 * where elements are stored in a list container and ordered based on
 * a user-defined comparison function.
 *
 * @tparam T The type of elements stored in the priority queue.
 */
template <class T>
class PriorityQueue {

public:

   /**
   * @brief Inserts an element into the priority queue.
   *
   * The element is inserted at the appropriate position based on the
   * comparison function provided.
   *
   * @param t The element to be inserted.
   */
	void push(const T& t);

	/**
	* @brief Retrieves and removes the highest priority element from the queue.
	*
	* The element with the highest priority (determined by the comparison function)
	* is removed from the queue and returned.
	*
	* @return The highest priority element.
	* @throws std::runtime_error if the priority queue is empty.
	*/
	T poll();

private:
	std::list<T> priority_queue;
};



template <class T>
void PriorityQueue<T>::push(const T& t)
{
	MyComparator<T> my_comparator;

	for (auto it = priority_queue.begin(); it != priority_queue.end(); ++it) {
		if (my_comparator(t,*it) < 0) {
			priority_queue.insert(it, t);
			return; // Exit the function after the insertion
		}
	}
	
	// If the loop completes without finding a suitable position, insert at the end
	priority_queue.insert(priority_queue.end(), t);
}

template <class T>
T PriorityQueue<T>::poll()
{
	if (priority_queue.empty()) {
		throw std::runtime_error("PriorityQueue empty!");
	}

	T element = priority_queue.front();
	priority_queue.pop_front();
	return element;

}
