#pragma once
template <typename K, typename V>
struct Entry
{
	K key;
	V value;
	//Ĭ��Ϊ0�ˡ�
	Entry(K k = K(), V v = V()):
	key(k), value(v) {};
	//���ڿ�¡�Ĺ��캯��
	Entry(Entry<K, V> const &e):
	key(e.key), value(e.value)	{};

	//�Ƚ�����
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
	//������Ԫ������������Ҫ�ټ�һ��K�� V����֤�������K�� V���ֿ�
	template<typename K, typename V>
	friend std::ostream &operator<<(std::ostream &out, Entry<K, V> &obj)
	{
		return  out << "(" << obj.key << "," << obj.value << ")" << std::endl;
	}
};
//ȱ��;��templateǰ�棬ע��͸�������ͷ�ļ�������