#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **argv)
{
	int	val;

	std::set<int> set;
	while (*argv)
	{
		val = std::atoi(*argv);
		if (set.find(val) == set.end() && val >= 0)
		{
			set.insert(val);
			_dequeValues.push_back(val);
			_listValues.push_back(val);
		}
		else
			throw std::runtime_error("Error");
		argv++;
	}
	_sortedDequeValues = _dequeValues;
	_sortedListValues = _listValues;
}

PmergeMe::PmergeMe(const PmergeMe &t)
	: _dequeValues(t._dequeValues),
		_listValues(t._listValues),
		_sortedDequeValues(t._sortedDequeValues),
		_sortedListValues(t._sortedListValues),
		_dequeTimeTaken(t._dequeTimeTaken),
		_listTimeTaken(t._listTimeTaken)
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &t)
{
	if (this != &t)
	{
		delete (this);
		return (*(new PmergeMe(t)));
	}
	return (*this);
}

const std::deque<int> &PmergeMe::getDequeValues() const
{
	return (_dequeValues);
}

const std::list<int> &PmergeMe::getListValues() const
{
	return (_listValues);
}

const std::deque<int> &PmergeMe::getSortedDequeValues() const
{
	return (_sortedDequeValues);
}

const std::list<int> &PmergeMe::getSortedListValues() const
{
	return (_sortedListValues);
}

double PmergeMe::getDequeTimeTaken() const
{
	return (_dequeTimeTaken);
}

double PmergeMe::getListTimeTaken() const
{
	return (_listTimeTaken);
}


// void PmergeMe::fordJohnsonDeque()
// {
// 	bool			hasStray = false;
// 	int				stray;
// 	int				bsLimit;
// 	clock_t	start;
// 	clock_t	end;

// 	hasStray = false;
// 	std::deque<int> cpyDequeValues;
// 	std::deque<std::deque<int> > pairs;
// 	std::deque<int> sorted;
// 	std::deque<int> waitList;
// 	cpyDequeValues = _dequeValues;
// 	start = clock();
// 	//Edge case
// 	if (_dequeValues.size() <= 1)
// 	{
// 		_sortedDequeValues = _dequeValues;
// 		end = clock();
// 		_dequeTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
// 		return ;
// 	}
// 	Making list even by storing stray one
// 	if (cpyDequeValues.size() % 2 == 1)
// 	{
// 		hasStray = true;
// 		stray = cpyDequeValues.back();
// 		cpyDequeValues.pop_back();
// 	}
// 	//Making pairs
// 	for (size_t i = 0; i < cpyDequeValues.size(); i = i + 2)
// 	{
// 		std::deque<int> temp;
// 		if (cpyDequeValues[i] > cpyDequeValues[i + 1])
// 		{
// 			temp.push_back(cpyDequeValues[i]);
// 			temp.push_back(cpyDequeValues[i + 1]);
// 		}
// 		else
// 		{
// 			temp.push_back(cpyDequeValues[i + 1]);
// 			temp.push_back(cpyDequeValues[i]);
// 		}
// 		pairs.push_back(temp);
// 	}
// 	//Sorting pairs with mergesort
// 	mergeSortDeque(pairs.begin(), pairs.end());
// 	for (size_t i = 0; i < pairs.size(); i++)
// 	{
// 		sorted.push_back(pairs[i].front());
// 		waitList.push_back(pairs[i].back());
// 	}
// 	//First element in waitList is lower than first element of sorted
// 	//so it safe to add push it to front of sorted.
// 	sorted.push_front(waitList.front());
// 	waitList.pop_front();
// 	bsLimit = 2;
// 	while (!waitList.empty())
// 	{
// 		std::deque<int>::iterator it = sorted.begin();
// 		std::advance(it, bsLimit);
// 		it = std::lower_bound(sorted.begin(), it, waitList.front());
// 		sorted.insert(it, waitList.front());
// 		waitList.pop_front();
// 		bsLimit += 2;
// 	}
// 	if (hasStray)
// 	{
// 		std::deque<int>::iterator it = std::lower_bound(sorted.begin(),
// 				sorted.end(), stray);
// 		sorted.insert(it, stray);
// 	}
// 	_sortedDequeValues = sorted;
// 	end = clock();
// 	_dequeTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
// }


void	PmergeMe::fordJohnsonDeque(int begin, int end, int pairSize)
{
	int	strayIndex = -1;
	int	strayEndIndex = -1;
	int	size;
	int	lBegin;
	int	lEnd;
	int	bsLimit;
	std::deque<std::deque<int> >	sorted;
	std::deque<std::deque<int> >	waitList;
	clock_t							tStart;
	clock_t							tEnd;

	tStart = clock();
	// Edge case
	if (_dequeValues.size() <= 1)
	{
		_sortedDequeValues = _dequeValues;
		tEnd = clock();
		_dequeTimeTaken = double((tEnd - tStart) / double(CLOCKS_PER_SEC));
		return ;
	}

	size = end - begin + 1;
	if (size < pairSize)
		return ;
	//Stray handling
	if (size % pairSize != 0)
	{
		strayEndIndex = end;
		strayIndex = end - pairSize / 2 + 1;
		end = strayIndex - 1;
	}
	lBegin = begin;
	lEnd = end;
	for (int i = begin; i < end; i += pairSize)
	{
		int bottomIndex = i + pairSize / 2;
		if (_sortedDequeValues[i] < _sortedDequeValues[bottomIndex])
		{
			for (int dT = i, dB = bottomIndex; dT < bottomIndex; dT++, dB++)
			{
				int temp = _sortedDequeValues[dT];
				_sortedDequeValues[dT] = _sortedDequeValues[dB];
				_sortedDequeValues[dB] = temp;
			}
		}
	}
	PmergeMe::fordJohnsonDeque(begin, end, pairSize * 2);
	for (int i = begin; i < end; i += pairSize)
	{
		std::deque<int>	top;
		std::deque<int>	bot;
		int bottomIndex = i + pairSize / 2;
		for (int dT = i, dB = bottomIndex; dT < bottomIndex; dT++, dB++)
		{
			top.push_back(_sortedDequeValues[dT]);
			bot.push_back(_sortedDequeValues[dB]);
		}
		sorted.push_back(top);
		waitList.push_back(bot);
	}

	sorted.push_front(waitList.front());
	waitList.pop_front();

	bsLimit = 2;
	while (!waitList.empty())
	{
		std::deque<std::deque<int> >::iterator it = sorted.begin();
		std::advance(it, bsLimit);
		it = std::lower_bound(sorted.begin(), it, waitList.front(), PmergeMe::customPairComparisonDeque);
		sorted.insert(it, waitList.front());
		waitList.pop_front();
		bsLimit += 2;
	}

	if (strayIndex != -1)
	{
		std::deque<int> temp;
		for (int i = strayIndex; i <= strayEndIndex; i++)
			temp.push_back(_sortedDequeValues[i]);
		std::deque<std::deque<int> >::iterator it;
		it = std::lower_bound(sorted.begin(), sorted.end(), temp, PmergeMe::customPairComparisonDeque);
		sorted.insert(it, temp);
	}
	for (int c = 0; !sorted.empty();)
	{
		for (size_t i = 0; i < sorted.front().size(); i++)
		{
			_sortedDequeValues[c] = sorted.front()[i];
			c++;
		}
		sorted.pop_front();
	}
	tEnd = clock();
	_dequeTimeTaken = double((tEnd - tStart) / double(CLOCKS_PER_SEC));
}

void PmergeMe::fordJohnsonList(int begin, int end, int pairSize) {
	int strayIndex = -1;
	int strayEndIndex = -1;
	int size;
	int lBegin;
	int lEnd;
	int bsLimit;
	std::list<std::list<int> > sorted;
	std::list<std::list<int> > waitList;
	clock_t tStart;
	clock_t tEnd;

	tStart = clock();

	// Edge case
	if (_listValues.size() <= 1) {
		_sortedListValues = _listValues;
		tEnd = clock();
		_listTimeTaken = double(tEnd - tStart) / CLOCKS_PER_SEC;
		return;
	}

	size = end - begin + 1;
	if (size < pairSize)
		return;

	// Stray handling
	if (size % pairSize != 0) {
		strayEndIndex = end;
		strayIndex = end - pairSize / 2 + 1;
		end = strayIndex - 1;
	}
	lBegin = begin;
	lEnd = end;

	for (int i = begin; i < end; i += pairSize) {
		int bottomIndex = i + pairSize / 2;

		// Swap elements within each pair
		std::list<int>::iterator itTop = _sortedListValues.begin();
		std::list<int>::iterator itBottom = _sortedListValues.begin();

		std::advance(itTop, i);
		std::advance(itBottom, bottomIndex);

		if (*itTop < *itBottom)
			for (int j = 0; j < pairSize / 2; j++) {
				std::iter_swap(itTop, itBottom);
				std::advance(itTop, 1);
				std::advance(itBottom, 1);
			}
	}

	fordJohnsonList(begin, end, pairSize * 2);

	for (int i = begin; i < end; i += pairSize) {
		std::list<int> top;
		std::list<int> bot;
		int bottomIndex = i + pairSize / 2;

		std::list<int>::iterator itTop = _sortedListValues.begin();
		std::list<int>::iterator itBottom = _sortedListValues.begin();

		std::advance(itTop, i);
		std::advance(itBottom, bottomIndex);

		for (int j = 0; j < pairSize / 2; j++) {
			top.push_back(*itTop);
			bot.push_back(*itBottom);
			std::advance(itTop, 1);
			std::advance(itBottom, 1);
		}
		sorted.push_back(top);
		waitList.push_back(bot);
	}

	sorted.push_front(waitList.front());
	waitList.pop_front();
	bsLimit = 2;

	while (!waitList.empty()) {
		std::list<std::list<int> >::iterator it = sorted.begin();
		std::advance(it, bsLimit);
		it = std::lower_bound(sorted.begin(), it, waitList.front(), customPairComparisonList);

		sorted.insert(it, waitList.front());
		waitList.pop_front();
		bsLimit += 2;
	}

	if (strayIndex != -1) {
		std::list<int> temp;
		for (int i = strayIndex; i <= strayEndIndex; i++) {
			std::list<int>::iterator iter = _sortedListValues.begin();
			std::advance(iter, i);
			temp.push_back(*iter);
		}
		std::list<std::list<int> >::iterator it = std::lower_bound(sorted.begin(), sorted.end(), temp, customPairComparisonList);
		sorted.insert(it, temp);
	}

	std::list<int> tempSorted;
	for (std::list<std::list<int> >::iterator it = sorted.begin(); it != sorted.end(); ++it) {
		for (std::list<int>::iterator innerIt = it->begin(); innerIt != it->end(); ++innerIt) {
			tempSorted.push_back(*innerIt);
		}
	}

	for (size_t i = 0; i < tempSorted.size(); i++)
		_sortedListValues.pop_front();
	while (!tempSorted.empty())
	{
		_sortedListValues.push_front(tempSorted.back());
		tempSorted.pop_back();
	}
	tEnd = clock();
	_listTimeTaken = double(tEnd - tStart) / CLOCKS_PER_SEC;
}

// void	PmergeMe::fordJohnsonRecursion(std::deque<int>::iterator begin, std::deque<int>::iterator end, int pairSize)
// {
// 	int							size;
// 	std::deque<int>::iterator	stray;
// 	std::deque<int>::iterator	topIt;
// 	std::deque<int>::iterator	botIt;

// 	stray = begin;
// 	size = std::distance(begin, end);
// 	if (size < pairSize)
// 		return ;
// 	if (size % pairSize != 0)
// 	{
// 		for (int i = 0; i < pairSize / 2; i++)
// 			--end;
// 		stray = end;
// 	}
// 	topIt = begin;
// 	while (topIt != end)
// 	{
// 		botIt = topIt;
// 		std::advance(botIt, pairSize / 2);
// 		if (*topIt < *botIt)
// 		{
// 			//Doing swap
// 			std::deque<int>::iterator	tempTopIt = topIt;
// 			std::deque<int>::iterator	tempBotIt = botIt;
// 			while (tempTopIt != botIt)
// 			{
// 				int	t = *tempTopIt;
// 				*tempTopIt = *tempBotIt;
// 				*tempBotIt = t;
// 				std::advance(tempTopIt, 1);
// 				std::advance(tempBotIt, 1);
// 			}
// 		}
// 		std::advance(topIt, pairSize);
// 	}
// 	PmergeMe::fordJohnsonRecursion(begin, end, pairSize * 2);
// }

// void PmergeMe::fordJohnsonList()
// {
// 	bool									hasStray = false;
// 	int										stray;
// 	int										bsLimit;
// 	clock_t									start;
// 	clock_t									end;
// 	std::list<int>::iterator				it;
// 	std::list<int>							cpyListValues;
// 	std::list<std::list<int> >				pairs;
// 	std::list<int>							sorted;
// 	std::list<int>							waitList;
// 	std::list<std::list<int> >::iterator	itPair;

// 	cpyListValues = _listValues;
// 	start = clock();

// 	// Edge case
// 	if (_listValues.size() <= 1)
// 	{
// 		_sortedListValues = _listValues;
// 		end = clock();
// 		_listTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
// 		return ;
// 	}

// 	// Making list even by storing stray one
// 	if (cpyListValues.size() % 2 == 1)
// 	{
// 		hasStray = true;
// 		stray = cpyListValues.back();
// 		cpyListValues.pop_back();
// 	}

// 	// Making pairs
// 	it = cpyListValues.begin();
// 	while (it != cpyListValues.end())
// 	{
// 		std::list<int>				temp;
// 		std::list<int>::iterator	next = ++it;
// 		--it;
// 		if (*it > *(next))
// 		{
// 			temp.push_back(*it);
// 			temp.push_back(*(next));
// 		}
// 		else
// 		{
// 			temp.push_back(*(next));
// 			temp.push_back(*it);
// 		}
// 		pairs.push_back(temp);
// 		std::advance(it, 2);
// 	}

// 	// Sorting pairs with mergesort
// 	mergeSortList(pairs.begin(), pairs.end());
// 	itPair = pairs.begin();
// 	while (itPair != pairs.end())
// 	{
// 		sorted.push_back(itPair->front());
// 		waitList.push_back(itPair->back());
// 		++itPair;
// 	}

// 	// First element in waitList is lower than the first element of sorted
// 	// so it's safe to push it to the front of sorted.
// 	sorted.push_front(waitList.front());
// 	waitList.pop_front();

// 	bsLimit = 2;
// 	while (!waitList.empty())
// 	{
// 		it = sorted.begin();
// 		std::advance(it, bsLimit);
// 		it = lower_bound_list(sorted.begin(), it, waitList.front());
// 		sorted.insert(it, waitList.front());
// 		waitList.pop_front();
// 		bsLimit += 2;
// 	}

// 	if (hasStray)
// 	{
// 		it = lower_bound_list(sorted.begin(), sorted.end(), stray);
// 		sorted.insert(it, stray);
// 	}

// 	_sortedListValues = sorted;
// 	end = clock();
// 	_listTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
// }

bool PmergeMe::customPairComparisonList(const std::list<int> &a,
		const std::list<int> &b)
{
	return (a.front() < b.front());
}

bool PmergeMe::customPairComparisonDeque(const std::deque<int> &a,
		const std::deque<int> &b)
{
	return (a.front() < b.front());
}
