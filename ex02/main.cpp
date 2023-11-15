#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	try {
		PmergeMe p(argv + 1);
		p.fordJohnsonDeque(0, p.getDequeValues().size() - 1, 2);
		p.fordJohnsonList(0, p.getDequeValues().size() - 1, 2);
		std::cout << "Before: ";
		const std::deque<int> original = p.getDequeValues();
		for (size_t i = 0; i < original.size(); i++)
			std::cout << original[i] << " ";
		std::cout << std::endl;
		std::cout << "After: ";
		const std::deque<int> sorted = p.getSortedDequeValues();
		std::list<int> sortedList = p.getSortedListValues();
		// std::list<int>::iterator it;
		// for (it = sortedList.begin(); it != sortedList.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		for (size_t i = 0; i < sorted.size(); i++)
			std::cout << sorted[i] << " ";
		std::cout << std::endl;
		std::cout << "Time to process a range of " << original.size()
			<< " elements with std::deque : "
			<< std::fixed << p.getDequeTimeTaken() << std::setprecision(5)
			<< std::endl;
		std::cout << "Time to process a range of " << original.size()
			<< " elements with std::list : "
			<< std::fixed << p.getListTimeTaken() << std::setprecision(5)
			<< std::endl;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
