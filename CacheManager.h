#pragma once
#include"LRUCache.h"
#include<stdexcept>
#include <type_traits>
//====封装=====
enum class CacheType {
	LRU,//后续会有LFU、ARC实现
};
template<typename Key,typename Value>
class CacheManager
{
private:
	std::unique_ptr<ICacheReplaceMent<Key, Value>>cache_;//智能指针
public:
	CacheManager(CacheType type, size_t size) {
		switch (type) {
		case CacheType::LRU:
			cache_ = std::make_unique<LRUCache<Key, Value>>(size);
			break;
		default:
			throw std::invalid_argument("Unsupported cache type");//无支持类型
		}
	}

	//简单的接口方法
	void put(const Key& K, const Value& V) {
		cache_->put(K, V);
	}

	std::optional<Value>get(const Key& K) {
		return cache_->get(K);
	}

	bool contains(const Key& K)const {
		return cache_->contains(K);
	}

	size_t size()const {
		return cache_->size();
	}
};

