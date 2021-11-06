/*
 * RevolverList.h
 *
 *  Created on: 31.01.2017
 *      Author: SFG
 */

#ifndef REVOLVERLIST_H_
#define REVOLVERLIST_H_

#include <cstddef>
#include <stdint.h>
#include <vector>
#include "RevolverListItem.h"

template<typename _TYPE>
class RevolverList {
private:
	uint32_t length;
	RevolverListItem<_TYPE>* first;
	RevolverListItem<_TYPE>* last;
	RevolverListItem<_TYPE>* current;
public:
	RevolverList() :
			length(0), first(NULL), last(NULL), current(NULL) {
	}
	virtual ~RevolverList() {
		RevolverListItem<_TYPE>* tmp = first;
		first->setPrev(NULL);
		last->setNext(NULL);
		while (tmp->getNext()) {
			if (tmp->getPrev()) {
				delete tmp->getPrev();
			}
			tmp = tmp->getNext();
		}
		delete tmp;
		length = 0;
		first = NULL;
		last = NULL;
		current = NULL;
	}

	void rollNext() {
		current = current->getNext();
	}
	void rollPrev() {
		current = current->getPrev();
	}
	void rollTo(int index) {
		current = first;
		for (int i = 0; i < index; i++) {
			current = current->getNext();
		}
	}

	uint32_t getLength() {
		return length;
	}

	RevolverListItem<_TYPE>* getFirst() {
		return first;
	}
	RevolverListItem<_TYPE>* getLast() {
		return last;
	}

	RevolverListItem<_TYPE>* getCurrent(int offset = 0) {
		if (offset == 0) {
			return current;
		} else {
			RevolverListItem<_TYPE>* ret = NULL;
			if (offset < 0) {
				ret = current->getPrev();
				for (int i = -1; i > offset; i--) {
					ret = ret->getPrev();
				}
			} else {
				ret = current->getNext();
				for (int i = 1; i < offset; i++) {
					ret = ret->getNext();
				}
			}
			return ret;
		}
	}
	_TYPE getCurrentData(int offset = 0) {
		return getCurrent(offset)->getData();
	}

	void add(_TYPE newData) {
		RevolverListItem<_TYPE>* newItem = new RevolverListItem<_TYPE>(newData);
		if (length <= 0) {
			newItem->setNext(newItem);
			newItem->setPrev(newItem);
			first = newItem;
			last = newItem;
			current = newItem;
		} else {
			newItem->setNext(first);
			newItem->setPrev(last);
			first->setPrev(newItem);
			last->setNext(newItem);
			last = newItem;
		}
		length++;
	}
};

#endif /* REVOLVERLIST_H_ */
