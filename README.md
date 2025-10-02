# C++ LRU 缓存系统
一个基于C++实现的LRU（最近最少使用）缓存替换策略系统。
## 功能特性
- LRU缓存算法实现
- 线程安全
- 模板化设计，支持任意类型
- 智能指针内存管理
## 项目结构
- `RUCache.h/cpp` - LRU缓存核心实现
- `iCacheReglaceMent.h` - 缓存替换策略接口
- `CacheManager.cpp` - 缓存管理器
- `Main.cpp` - 示例程序
## 编译运行
