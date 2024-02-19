
/*
 * ArraySet.h
 *
 *  Created on: Jul 22, 2020
 *      Author: hardware
 */


#ifndef INC_ARRAYSET_H_
#define INC_ARRAYSET_H_


#include <utility>
#include <functional>

#include "d_debug.h"


template<typename K, typename V, size_t MAX_COUNT, K DEFAULT_K = nullptr,
		 V DEFAULT_V = nullptr, bool STRICT = true>
class ArraySet {


	std::pair<K, V> handles[MAX_COUNT];


public:


	typedef std::function<bool(V)> Predicate;


	inline
	ArraySet()
	{
		for (size_t i = 0; i < reserved(); i++) {
			handles[i] = std::make_pair(DEFAULT_K, DEFAULT_V);
		}
	}


	inline size_t
	reserved() const
	{
		return MAX_COUNT;
	}


	inline void
	put(K key, V value)
	{
		size_t i;

		if (STRICT) {
			for (i = 0; i < reserved(); i++) {
				d_debug_assert(handles[i].first != key);
			}
		}

		for (i = 0; i < reserved() && handles[i].first != DEFAULT_K; i++);

		d_debug_assert(i < reserved());

		handles[i] = std::make_pair(key, value);
	}


	inline V
	tryGet(K key, Predicate predicate = nullptr, V defaultValue = DEFAULT_V)
	{
		for (size_t i = 0; i < reserved(); i++) {
			auto &pair = handles[i];

			if (pair.first == key &&
				(!predicate || predicate(pair.second))) {

				return pair.second;
			}
		}

		return defaultValue;
	}


	inline V
	get(K key, Predicate predicate = nullptr)
	{
		auto value = tryGet(key, predicate);

		if (value == DEFAULT_V) {
			d_debug_assert(0);
		}

		return value;
	}


};


#endif /* INC_ARRAYSET_H_ */
