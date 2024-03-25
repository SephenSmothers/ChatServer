#pragma once
#include <list>

template<typename Key, typename Value>
class Dictionary {

	// The objects stored in the hash-table
	struct Pair {
		Key key;			// The key for insertion/lookup
		Value value;		// The data

		Pair(const Key& _key, const Value& _value) {
			key = _key;
			value = _value;
		}

		// For testing
		bool operator==(const Pair& _comp) const {
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);						
	size_t mNumBuckets = -1;																
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);


public:

	//Dictionary()
	//{
	//	mTable = reinterpret_cast<std::list<Pair>*>(-1);
	//	mNumBuckets = -1;
	//	*mHashFunc(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);
	//}

	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) {
		mNumBuckets = _numBuckets;
		mHashFunc = _hashFunc;
		mTable = new std::list<Pair>[_numBuckets];
	}

	~Dictionary() {

		delete[] mTable;
	}

	Dictionary(const Dictionary& _copy) {
		mNumBuckets = _copy.mNumBuckets;
		mHashFunc = _copy.mHashFunc;
		mTable = new std::list<Pair>[_copy.mNumBuckets];

		for (int i = 0; i < mNumBuckets; i++)
		{
			mTable[i] = _copy.mTable[i];
		}
	}

	Dictionary& operator=(const Dictionary& _assign) {

		if (this != &_assign)
		{
			Clear();
			delete[] mTable;

			mTable = new std::list<Pair>[_assign.mNumBuckets];
			mNumBuckets = _assign.mNumBuckets;
			mHashFunc = _assign.mHashFunc;

			for (int i = 0; i < mNumBuckets; i++)
			{
				mTable[i] = _assign.mTable[i];
			}
		}

		return *this;
	}

	void Clear() {

		for (int i = 0; i < mNumBuckets; i++)
		{
			mTable[i].clear();
		}
	}

	void Insert(const Key& _key, const Value& _value) {

		int ndx = mHashFunc(_key);

		for (typename std::list<Pair>::iterator iter = mTable[ndx].begin(); iter != mTable[ndx].end();)
		{
			if (_key == iter->key)
			{
				iter->value = _value;
				break;
			}

			iter++;

			if (iter == mTable[ndx].end())
			{
				Pair newPair(_key, _value);

				mTable[ndx].push_back(newPair);
			}
		}
	}
	Value* Find(const Key& _key) {

		int ndx = mHashFunc(_key);

		for (typename std::list<Pair>::iterator iter = mTable[ndx].begin(); iter != mTable[ndx].end();)
		{
			if (_key == iter->key)
				return &iter->value;

			iter++;

			if (iter == mTable[ndx].end())
				return nullptr;
		}
	}

	bool Remove(const Key& _key) {

		int ndx = mHashFunc(_key);
		bool removed = false;

		for (typename std::list<Pair>::iterator iter = mTable[ndx].begin(); iter != mTable[ndx].end();)
		{
			if (_key == iter->key)
			{
				removed = true; 
				mTable[ndx].remove(*iter);
				break;
			}

			iter++;

			if (iter == mTable[ndx].end())
			{
				removed = false;
			}
		}

		return removed; 
	}
};