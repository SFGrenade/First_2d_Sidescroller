/*
 * RevolverListItem.h
 *
 *  Created on: 31.01.2017
 *      Author: SFG
 */

#ifndef REVOLVERLISTITEM_H_
#define REVOLVERLISTITEM_H_

#include <cstddef>

template <typename _TYPE>
class RevolverListItem {
	_TYPE data;
	RevolverListItem<_TYPE>* next;
	RevolverListItem<_TYPE>* prev;
public:
	RevolverListItem(_TYPE newData) : data(newData), next(NULL), prev(NULL) {
	}
	virtual ~RevolverListItem() {
		next = NULL;
		prev = NULL;
	}

	_TYPE getData() {
		return data;
	}

	RevolverListItem<_TYPE>* getNext() {
		return next;
	}
	void setNext(const RevolverListItem<_TYPE>* next) {
		this->next = (RevolverListItem<_TYPE>*) next;
	}

	RevolverListItem<_TYPE>* getPrev() {
		return prev;
	}
	void setPrev(const RevolverListItem<_TYPE>* prev) {
		this->prev = (RevolverListItem<_TYPE>*) prev;
	}
};

#endif /* REVOLVERLISTITEM_H_ */
