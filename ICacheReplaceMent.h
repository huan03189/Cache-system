#pragma once
#include<memory>
#include<optional>

template<typename Key,typename Value>//模板声明
class ICacheReplaceMent//主要声明几个方法
{public:
	virtual ~ICacheReplaceMent() = default;
	//核心方法
	virtual void put(const Key& K, const Value& V) = 0;
	virtual std::optional<Value>get(const Key& K) = 0;//std::optional处理可能失败的一种方式
	virtual bool contains(const Key& K)const = 0;//查键是否存在
	virtual size_t size()const = 0;
};

