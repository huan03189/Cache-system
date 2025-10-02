#include<iostream>
#include"CacheManager.h"


using std::cout;
using std::endl;
void testBasicLRU() {
	cout << "===����LRU����===" << endl;
	//��������Ϊ3��LRU����
	CacheManager <int, std::string > cache(CacheType::LRU, 3);

	//����1 ��������
	cout << "\n��������Ԫ��" << endl;
	cache.put(1, "one");
	cache.put(2, "two");
	cache.put(3, "three");

	cout << "��ǰ�����С" << cache.size() << endl;

	//����2 ��ȡ���ڵ�Ԫ��
	cout << "\n��ȡ���ڵ�Ԫ��" << endl;
	auto result = cache.get(2);

	if (result) {
		cout << "find key=2" << *result << endl;
	}

	//������̭
	cout << "\n ������ĸ�Ԫ�أ�Ӧ����̭��ɵ�" << endl;
	cache.put(4, "four");
	//���key=1�Ƿ���̭
	cout << "\n���key=1�Ƿ���̭" << endl;
	if (!cache.contains(1)) {
		cout << "key=1 �ѱ���ȷ��̭" << endl;
	}

	//����5 ����ģʽ����
	cout << "\n ����ģʽ����" << endl;
	cache.get(3);
	cache.put(5, "five");

	if (!cache.contains(2)) {
		cout << "����ģʽ�ɹ�" << endl;
	}

	cout << "���ջ����С" << cache.size() << endl;
}
void testEdgeCases() {
	cout << "\n�߽��������" << endl;
	CacheManager<int, std::string>cache(CacheType::LRU, 1);

	cache.put(1, "one");
	cout << "����key=1��" << cache.size() << endl;

	cache.put(2, "two");
	cout << "����key=2��" << cache.size() << endl;

	if (!cache.contains(1)) {
		cout << "�߽���Գɹ�" << endl;
	}
}
int main() {
	cout << "��ʼ���Ի���ϵͳ" << endl;

	testBasicLRU();
	testEdgeCases();

	cout << "\n���в������" << endl;
	return 0;
}