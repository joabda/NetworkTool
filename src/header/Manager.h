#pragma once

#include <algorithm>
#include <map>
#include <set>

using namespace  std;

template<typename T, typename C>
class Manager
{
public:

/*	@det	Method to get of a copy of the container
	@param	void
	@ret	C a container of template typee
*/
	C getContainer() const 
	{
		C copiedContainer;
		copiedContainer = container_;
		return copiedContainer;
	}

/*	@det	Adding an element to the container
	@param	T an element to be added 
	@ret	void
*/
	void add(T t)
	{
		container_.insert(t);
	}

/*	@det	Getter for the number of elements inside the container
	@param	void
	@ret	int number of elements
*/
	int getNumberOfElements() const
	{
		return container_.size();
	}

	C* getPointerToContainer() 
	{
		return &container_;
	}

protected:
	C container_;
};