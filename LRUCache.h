#pragma once
#include"ICacheReplaceMent.h"
#include<list>
#include<mutex>
#include<unordered_map>
#include<optional>
#include <stdexcept> 
#include <iostream>
using std::cout;
using std::endl;
template<typename Key,typename Value>
class LRUCache:public ICacheReplaceMent<Key,Value>
{
private:
	size_t capacity;//容量

	//LRU核心数据结构
	std::list<std::pair<Key, Value>> cachelist;//储存键值对
	std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator>cachemap;//快速查找，指向链表节点的迭代器

	//线程安全
	mutable std::mutex mutex_;

	//调试方法
	void printDebug(const std::string& op,const Key& K) {
		cout << op << "Key:" << K << "| current:";
		for (const auto& it : cachelist) {
			cout << it.first << "";
		}
		cout << endl;
	}
public:
	//方法实现
	explicit LRUCache(size_t c) {
		capacity = c;
		cout << "LRU Cache created with capacity:" << capacity << endl;
	}
	void put(const Key& K, const Value& V)override {
		std::lock_guard<std::mutex>lock(mutex_);//上锁
		printDebug("PUT", K);//表明在执行PUT操作
		auto it = cachemap.find(K);//找键值
		if (it != cachemap.end()) {//如果键值存在
			it->second->second = V;//哈希表指向链表节点
			cachelist.splice(cachelist.begin(), cachelist, it->second);//将已访问的节点放在最前面
		}
		else {//键值不存在
			if (cachelist.size() >= capacity) {//空间不足
				auto last = cachelist.back();
				cout << "Evicting Key" << last.first << endl;
				cachemap.erase(last.first);
				cachelist.pop_back();//淘汰最后一位元素
			 }
			cachelist.emplace_front(K, V);//无拷贝，更高效
			cachemap[K] = cachelist.begin();
		}   
	}
	std::optional<Value>get(const Key& K)override {
		std::lock_guard<std::mutex>lock(mutex_);//上锁
		auto item = cachemap.find(K);
		if (item != cachemap.end()) {
			cachelist.splice(cachelist.begin(), cachelist, item->second);
			printDebug("Get hit", K);
			return item->second->second;
		}
		else {
			printDebug("Get miss", K);
			return nullptr;
		}
	}
	bool contains(const Key& K) const override{
		std::lock_guard<std::mutex>lock(mutex_);//上锁
		auto it = cachemap.find(K);
		if (it != cachemap.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	size_t size()const override {
		std::lock_guard<std::mutex>lock(mutex_);//上锁
		return cachelist.size();
	}
};

