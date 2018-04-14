#pragma once
template <typename K, typename V>
struct Entry
{
	K key;
	V value;
	//默认为0了。
	Entry(K k = K(), V v = V()):
	key(k), value(v) {};
	//基于克隆的构造函数
	Entry(Entry<K, V> const &e):
	key(e.key), value(e.value)	{};

	//比较器：
	bool operator<(Entry<K, V> const &e)
	{
		return key < e.key;
	}

	bool operator>(Entry<K, V> const &e)
	{
		return key > e.key;
	}

	bool operator==(Entry<K, V> const &e)
	{
		return key == e.key;
	}

	bool operator!=(Entry<K, V> const &e)
	{
		return key != e.key;
	}
	//定义友元函数，这里需要再加一个K， V，保证与上面的K， V区分开
	template<typename K, typename V>
	friend std::ostream &operator<<(std::ostream &out, Entry<K, V> &obj)
	{
		return  out << "(" << obj.key << "," << obj.value << ")" << std::endl;
	}
};
//缺少;在template前面，注意就该在它的头文件里面找