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
	size_t capacity;//����

	//LRU�������ݽṹ
	std::list<std::pair<Key, Value>> cachelist;//�����ֵ��
	std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator>cachemap;//���ٲ��ң�ָ������ڵ�ĵ�����

	//�̰߳�ȫ
	mutable std::mutex mutex_;

	//���Է���
	void printDebug(const std::string& op,const Key& K) {
		cout << op << "Key:" << K << "| current:";
		for (const auto& it : cachelist) {
			cout << it.first << "";
		}
		cout << endl;
	}
public:
	//����ʵ��
	explicit LRUCache(size_t c) {
		capacity = c;
		cout << "LRU Cache created with capacity:" << capacity << endl;
	}
	void put(const Key& K, const Value& V)override {
		std::lock_guard<std::mutex>lock(mutex_);//����
		printDebug("PUT", K);//������ִ��PUT����
		auto it = cachemap.find(K);//�Ҽ�ֵ
		if (it != cachemap.end()) {//�����ֵ����
			it->second->second = V;//��ϣ��ָ������ڵ�
			cachelist.splice(cachelist.begin(), cachelist, it->second);//���ѷ��ʵĽڵ������ǰ��
		}
		else {//��ֵ������
			if (cachelist.size() >= capacity) {//�ռ䲻��
				auto last = cachelist.back();
				cout << "Evicting Key" << last.first << endl;
				cachemap.erase(last.first);
				cachelist.pop_back();//��̭���һλԪ��
			 }
			cachelist.emplace_front(K, V);//�޿���������Ч
			cachemap[K] = cachelist.begin();
		}   
	}
	std::optional<Value>get(const Key& K)override {
		std::lock_guard<std::mutex>lock(mutex_);//����
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
		std::lock_guard<std::mutex>lock(mutex_);//����
		auto it = cachemap.find(K);
		if (it != cachemap.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	size_t size()const override {
		std::lock_guard<std::mutex>lock(mutex_);//����
		return cachelist.size();
	}
};

