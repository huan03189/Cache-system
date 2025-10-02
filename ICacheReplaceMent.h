#pragma once
#include<memory>
#include<optional>

template<typename Key,typename Value>//ģ������
class ICacheReplaceMent//��Ҫ������������
{public:
	virtual ~ICacheReplaceMent() = default;
	//���ķ���
	virtual void put(const Key& K, const Value& V) = 0;
	virtual std::optional<Value>get(const Key& K) = 0;//std::optional�������ʧ�ܵ�һ�ַ�ʽ
	virtual bool contains(const Key& K)const = 0;//����Ƿ����
	virtual size_t size()const = 0;
};

