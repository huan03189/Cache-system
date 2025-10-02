#include<iostream>
#include"CacheManager.h"


using std::cout;
using std::endl;
void testBasicLRU() {
	cout << "===基础LRU测试===" << endl;
	//创建容量为3的LRU缓存
	CacheManager <int, std::string > cache(CacheType::LRU, 3);

	//测试1 基本插入
	cout << "\n插入三个元素" << endl;
	cache.put(1, "one");
	cache.put(2, "two");
	cache.put(3, "three");

	cout << "当前缓存大小" << cache.size() << endl;

	//测试2 获取存在的元素
	cout << "\n获取存在的元素" << endl;
	auto result = cache.get(2);

	if (result) {
		cout << "find key=2" << *result << endl;
	}

	//触发淘汰
	cout << "\n 插入第四个元素，应该淘汰最旧的" << endl;
	cache.put(4, "four");
	//检查key=1是否淘汰
	cout << "\n检查key=1是否被淘汰" << endl;
	if (!cache.contains(1)) {
		cout << "key=1 已被正确淘汰" << endl;
	}

	//测试5 访问模式测试
	cout << "\n 访问模式测试" << endl;
	cache.get(3);
	cache.put(5, "five");

	if (!cache.contains(2)) {
		cout << "访问模式成功" << endl;
	}

	cout << "最终缓存大小" << cache.size() << endl;
}
void testEdgeCases() {
	cout << "\n边界情况测试" << endl;
	CacheManager<int, std::string>cache(CacheType::LRU, 1);

	cache.put(1, "one");
	cout << "插入key=1后" << cache.size() << endl;

	cache.put(2, "two");
	cout << "插入key=2后" << cache.size() << endl;

	if (!cache.contains(1)) {
		cout << "边界测试成功" << endl;
	}
}
int main() {
	cout << "开始测试缓存系统" << endl;

	testBasicLRU();
	testEdgeCases();

	cout << "\n所有测试完成" << endl;
	return 0;
}