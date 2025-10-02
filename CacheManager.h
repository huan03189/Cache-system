#pragma once
#include"LRUCache.h"
#include<stdexcept>
#include <type_traits>
//====��װ=====
enum class CacheType {
	LRU,//��������LFU��ARCʵ��
};
template<typename Key,typename Value>
class CacheManager
{
private:
	std::unique_ptr<ICacheReplaceMent<Key, Value>>cache_;//����ָ��
public:
	CacheManager(CacheType type, size_t size) {
		switch (type) {
		case CacheType::LRU:
			cache_ = std::make_unique<LRUCache<Key, Value>>(size);
			break;
		default:
			throw std::invalid_argument("Unsupported cache type");//��֧������
		}
	}

	//�򵥵Ľӿڷ���
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

