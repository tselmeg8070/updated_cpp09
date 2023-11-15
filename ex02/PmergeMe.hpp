#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP
# define K 10
# include <ctime>
# include <cmath>
# include <iostream>
# include <deque>
# include <queue>
# include <set>
# include <iterator>
# include <algorithm>
# include <sstream>
# include <string>
# include <list>
# include <iomanip>


class	PmergeMe {
	private:
		std::deque<int>		_dequeValues;
		std::list<int>		_listValues;
		std::deque<int>		_sortedDequeValues;
		std::list<int>		_sortedListValues;
		double				_dequeTimeTaken;
		double				_listTimeTaken;
	public:
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &t);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &t);

		const std::deque<int>		&getDequeValues() const;
		const std::list<int>		&getListValues() const;
		const std::deque<int>		&getSortedDequeValues() const;
		const std::list<int>		&getSortedListValues() const;
		double				getDequeTimeTaken() const;
		double				getListTimeTaken() const;

		void	fordJohnsonRecursion(std::deque<int>::iterator begin, std::deque<int>::iterator end, int pairSize);
		void	fordJohnsonDeque(int begin, int end, int pairSize);
		void	fordJohnsonList(int begin, int end, int pairSize);

		static bool customPairComparisonDeque(const std::deque<int>& a, const std::deque<int>& b);

		static bool customPairComparisonList(const std::list<int>& a, const std::list<int>& b);

		template <class Iterator>
		void mergeSortDeque(Iterator begin, Iterator end) {
			if (end <= begin + 1) return;
			Iterator middle = begin + (end - begin) / 2;
			mergeSortDeque(begin, middle);
			mergeSortDeque(middle, end);
			std::inplace_merge(begin, middle, end, customPairComparisonDeque);
		}

		template <typename T>
		typename std::list<T>::iterator lower_bound_list(typename std::list<T>::iterator first, typename std::list<T>::iterator last, const T& value) {
			while (first != last) {
				typename std::list<T>::iterator mid = first;
				std::advance(mid, std::distance(first, last) / 2);

				if (*mid < value) {
					++mid;
					first = mid;
				} else {
					last = mid;
				}
			}
			return first;
		}

		template <class Iterator>
		void mergeSortList(Iterator begin, Iterator end) {
			if (std::distance(begin, end) <= 1) return;

			Iterator middle = begin;
			std::advance(middle, std::distance(begin, end) / 2);

			mergeSortList(begin, middle);
			mergeSortList(middle, end);

			std::list<typename Iterator::value_type> temp;
			std::merge(begin, middle, middle, end, std::back_inserter(temp), customPairComparisonList);

			std::copy(temp.begin(), temp.end(), begin);
		}
};

#endif
