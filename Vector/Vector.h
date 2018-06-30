#pragma once
#include "fib.h"
typedef int Rank;	//��
#define DEFAULT_CAPACITY 3

template<typename T>
static Rank fibSearch(T *a, T const &e, Rank hi, Rank lo);
template<typename T>
static Rank exponentialSearch(T *a, T const &e, Rank lo, Rank hi);
template <typename T>
static int interpolationSearch(T *a, T const &e, int lo, int hi, int *sum);
template<typename T>
static Rank binSearchB(T *A, T const &e, Rank lo, Rank hi, int *sum );
template<typename T>

class Vector
{
	//Ϊ�˷�����ԣ�������public
public:
	Rank _size;
	int _capacity;
	T *_elem;
	//���캯�������õ�
	void copyFrom(T const* A, Rank lo, Rank hi);		//������������[lo,hi)
	void expand();										//�ռ䲻��ʱ����
	void shrink();		//װ�����ӹ�Сʱѹ��
	//��������һЩ�����㷨�Լ����ǵĸ�������
	Rank bubble(Rank lo, Rank hi);		//ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);	//ð������
	Rank max(Rank lo, Rank hi);			//ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi);	//ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi);	//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);		//�鲢�����㷨
	Rank partition(Rank lo, Rank hi);		//��㹹���㷨
	void quickSort(Rank lo, Rank hi);		//���������㷨
	void heapSort(Rank lo, Rank hi);		//������
public:

	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		//Լ��s <= c���ڲ���������
		_capacity = c;
		_elem = new T[_capacity];
		/*
		for(_size = 0 ; _size < s ; _size++)
		{
			_elem[_size] = v;
		}
		*/
		for(_size = 0 ; _size < s ; _elem[_size++] = v);
	}
	Vector(T const *A, Rank lo, Rank hi)
	{
		//���⣺��û����þ����������ķ�������
		copyFrom(A, lo, hi);
	}
	Vector(T const *A, Rank n)
	{
		copyFrom(A, 0, n);
	}
	Vector(Vector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}
	Vector(Vector<T> const &V)
	{
		copyFrom(V._elem, 0, V._size);
	}
	
	//��������
	~Vector()
	{
		//˭����˭�ͷ�ԭ�����Ԫ�ز��Ǽ����ͣ���ô�Ƿ�delete�ɵ����߾�������������ͷ�_elem
		delete[] _elem;
	}

	//ֻ�����ʽӿ�
	Rank size() const { return _size;}
	bool empty() const {return !_size;}
	int disordered() const;//�ж������Ƿ��Ѿ�����
	Rank find(T const& e)const {return find(e, 0, _size);}	//���������������
	Rank find(T const& e, Rank lo, Rank hi)const;			//���������������
	Rank search(T const& e)const			//���������������
	{return (_size <= 0 ? -1 : search(e, 0, _size));}
	Rank search(T const &e, Rank lo, Rank hi)const;		//���������������
	
	//��д���ʽӿ�
	T& operator[](Rank r)const;		//�����±������
	Vector<T> & operator=(Vector<T> const &);	//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r);		//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);		//ɾ����������[lo, hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const &e);	//����Ԫ��
	Rank insert(T const &e){return insert(_size, e);}	//Ĭ����ΪĩβԪ�ز���
	void sort(Rank lo, Rank hi);		//��[lo, hi)����
	void sort() {sort(0, _size);}		//��������
	void unsort(Rank lo, Rank hi);		//��[lo, hi)����
	void unsort()	{unsort(0, _size);}	//��������
	int deduplicate();					//����ȥ��
	int uniquify();						//����ȥ��

	//����
	void traverse(void(*) (T&));		//������ʹ�ú���ָ�룬ֻ����ֲ����޸�
	template <typename VST> void traverse(VST &);	//������ʹ�ú������󣬿�ȫ�����޸ģ�

	void print();

};

template<typename T>

void Vector<T>::print()
{
	for(int i = 0 ; i < this->size(); std::cout << _elem[i++] << " ");
	std::cout << std::endl;
}

//����������[lo, hi)Ϊ����
template<typename T>


void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
	//��ʼһ��capacity�� hi - lo������
	//copyFrom�ᴴ���µ�_elem
	//�κ�2-2
	//����Ҫ��֤_elem��A�Ķ����ԣ�������ܱ�֤����ô������Ҫע��copy��˳��
	//����һ��ʼ����ˣ�A��ÿһ��Ԫ������Ч�ģ�_elem�Ǵ���ֵ����
	//���_elem��ĳһ��׺��Aǰ׺�ص�����ô��ʱӦ�ô�A��0λ��Ԫ�ؿ�ʼcopy����������ʼ���ƣ���ôA��ǰ׺�ᱻ����
	//���_elem��ĳһǰ׺��A��׺�ص�����ô��ʱӦ�ô�A�������ǰ���ƣ�����ӿ�ʼ������ƣ���ôA�ĺ�׺�ᱻ����
	//���ϣ��ӿ��ܱ����ǵĵط���ʼ����
	_elem = new T[_capacity = 2 * (hi - lo)];
	//��ķ����˵�˼ά�ǹ̶��ģ����˺ܳ�ʱ����д�������������forѭ����������
	for(_size = 0 ; _size < hi - lo ; _elem[_size++] = A[lo + _size]);
}

template<typename T>

Vector<T> & Vector<T>::operator=(Vector<T> const &V)
{
	if(_elem)	delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	//���ص�ǰ��������ã��Ա���ʽ��ֵ
	return *this;
}

template<typename T>
//insertһ��ʼ��Ҫ��������㷨
//2-1 ��̯�����вο���ֵ����̯��ƽ��û���̺���ϵ
//O(1)��̯ʱ��

void Vector<T>::expand()
{
	//û�����������˲���
	if(_size < _capacity) return ;
	//���⣺��������С������_capacity������С���������ܷ�������shrink��Ҳ���ᷢ����
	if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;	//��������С����
	T *oldElem = _elem;
	//����ע���2����λ��������������
	_elem = new T[_capacity <<= 1];	//�����ӱ�
	for(int i = 0 ; i < _size ; i++)
		//TΪ�������ͣ������Ѿ�����=
		_elem[i] = oldElem[i];
	delete[] oldElem;
	
	//_size û��
}

//װ�����ӹ�Сʱѹ��������ռ�ռ�
template<typename T>
void Vector<T>::shrink()
{
	//������������default����������
	if(_capacity < DEFAULT_CAPACITY << 1)	return ;
	//ע�����ƶ�λ�ǳ���
	if(_size << 2 > _capacity)	return;
	//�����ǰ��ģ���������ķ�֮һ���ϣ�����ǰ��װ���Ӵ���1/4����ôҲ������
	T *oldElem = _elem;
	_elem = new T[_capacity >>= 1];//��������
	for(int i = 0 ; i < _size ; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>

//get set����ȡ���ˣ����ص������ã�����get��set���ᱻȡ��
T& Vector<T>::operator[](Rank k)const
{
	//assert: 0<=r<_size
	return _elem[k];
}


template<typename T>
//��Ԫ�صȸ��ʳ�����ÿһ��λ��
void permute(Vector<T> &V)
{
	for(int i = V.size() ; i > 0 ; i--)
	{
		//�Ժ���ǰ
		swap(V[i- 1], V[rand() % i]);
	}
}
//��������
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T *V = _elem + lo;
	for(Rank i = hi - lo ; i > 0 ; i--)
		swap(V[i - 1], V[rand() % i]);
}

//�ȽϺͱȶ�
template<typename T> static bool lt(T *a, T *b)	{return lt(*a, *b);}
template<typename T> static bool lt(T &a, T &b)	{return a < b;}
template<typename T> static bool equal(T *a, T *b)	{return equal(*a, *b);}
template<typename T> static bool equal(T &a, T &b)	{return a == b;}

template<typename T>


//ͳһԼ�����������������
//������e��ȵ�Ԫ�أ�Լ��[lo, hi)
//��ģ��ͬ���ڲ���ɲ�ͬ�����룬��������ʱ��ȴ�б������������㷨Ҳ���������е��㷨
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	while((lo < hi--) && (e != _elem[hi]));
	return hi;
	//��hiС��lo����ô����ʧ�ܣ�����hi��ΪҪ�ҵ�Ԫ�ص���
	//�Ӻ���ǰ���ң����Ի᷵�����Ԫ�ص�����������ڵ�������
}
//��e���뵽��Ϊr��λ�ã�����ʱ�����������ں�׺�ĳ��ȣ�������λ�õȸ��ʷֲ���ƽ������ʱ��ΪO(n)
template<typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
	expand();
	for(int i = _size ; i > r ; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size ++;
	return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if(lo == hi)	return 0;
	while(hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
//ɾ�������������ظ�Ԫ�أ���Ч�棩
int Vector<T>::deduplicate()
{
	int oldSize = _size;
	Rank i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0) ?
		i++ : remove(i);
	return oldSize - _size;
}

template<typename T>
//���ú���ָ��
void Vector<T>::traverse(void (*visit)(T&))
{
	for(int i = 0 ; i < _size ; i++)
		visit(_elem[i]);
}
template<typename T>
template<typename VST>
//����������Ƶı���
void Vector<T>::traverse(VST &visit)
{
	for(int i = 0 ; i < _size ; i++)
		visit(_elem[i]);
}

template<typename T>
struct Increase
{
	virtual void operator()(T &e)
	{
		e++;
	}
};
template<typename T>
void increase(Vector<T> &V)
{
	V.traverse(Increase<T>());
}

template<typename T>
struct Double
{
	virtual void operator()(T &e)
	{
		e *= 2;
	}
};

template<typename T>
void doub(Vector<T> &T)
{
	V.traverse(Double<T>());
}

/*
�������ܽ�һ���������������������ص�
Rank find(e, lo, hi)	�Ӻ���ǰɨ��	������ͬԪ���������ģ��Ҳ�������lo - 1	ƽ��O(n)���������У�ʱ��ȡ����Ԫ���������к�̵ĸ���
Rank insert(e, r)		�Ӻ���ǰ�ƶ�	����r��һ��ʼ�����Ƿ���Ҫexpand()			ƽ��O(n)���������У�ʱ��ȡ���� size - r����Ҳ�Ǻ�̵ĸ���
int remove(lo, hi)		��ǰ�����ƶ�	����ɾ����Ԫ�ظ���hi - lo������shrink		ƽ��O(n)���������У�ʱ��ȡ���ڱ�ɾ������ĺ�̸���
T remove(r)				��ǰ�����ƶ�	���ر�ɾ��Ԫ�ص�ֵ							ƽ��O(n)���������У�ʱ��ȡ���ڱ�ɾ��Ԫ�صĺ�̸�����size - r
void unsort(lo, hi)		�Ӻ���ǰ����	rand()������룬��ô���Եȸ����������		O(n)������Ͳ�����
����[]									�������ã�ȡ��get put						O(1)

���Կ����ܶ��㷨���ǴӺ���ǰ�ģ�������find����unsort���������ڴ����һ��Ԫ�ؿ�ʼ
*/


//ͨ��������������Եĸ������ж��Ƿ�����
template<typename T>
int Vector<T>:: disordered()const	
{
	int n = 0;
	for(int i = 1 ; i < _size ; i++)
	{
		if(_elem[i - 1] > _elem[i])	n++;
	}
	return n;
}

//���������ظ�Ԫ���޳��㷨
	//���ϵ�˼·��������ԭ������ɾ�����ɣ�������ֳ������֣�
	//ǰ�벿�����Ѿ�ȷ��û����ͬԪ�ص�
	//�м䲿����һЩ��ͬ�Ŀ��Զ�����Ԫ��
	//��벿���Ǵ��鿴��Ԫ��
	//��partition�м�������
//���߿��԰���ͬ��Ԫ�ؿ���һ���飬��ôÿһ�ζ�ֻ��ȡÿ��ĵ�һ��Ԫ��
template<typename T>
int Vector<T>::uniquify()
{
	int i = 0 , j = 0;
	while(j++ < _size)
	{
		if(_elem[j] != _elem[i])
			_elem[i++] = _elem[j];
	}
	_size = ++i;
	shrink();
	return j - i;
}
//���ң��򵥵Ķ��ֲ��Ҿ�����ô��ԭ��������
template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi)const
{
	return binSearch(_elem, e, lo, hi) ;
}
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi)
{
	while(lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi + 1;
	}
	return lo - 1;
}

//���������Ķ��ֲ��ң���1��2����2
//��ԭʼ�汾��ϵ��1.50����û������Լ��
	//[lo, hi)
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	int count = 0;
	while(lo < hi)
	{
		Rank mid = (lo + hi) >> 1;
		if(e < A[mid])	{
			count++;
			hi = mid;
		}
		else if(A[mid] < e){
			count += 2;
			lo = mid + 1;
		}
		else{
			count += 2;
			*sum = *sum + count;
			std::cout << "���ֲ���A�ĳɹ����ҳ���Ϊ   " << count << std::endl;
			return mid;
		}
	}
	*sum = *sum + count;
	std::cout << "���ֲ���A��ʧ�ܲ��ҳ���Ϊ" << count << std::endl;
	return -1;
}

//����������Ƶ����һ��쳲����������㷨
//�������鳤��n = fib(k) - 1
//����ֲ������Ƶ��ǣ�Ҳ�Ǽ�����֮��ֻ�����зֵ��� fib(k - 1) - 1
//����Ϊ��������Ҳ��ҵĲ�������ͬ�����з�ʱ������٣���֤������ߵĸ��ʸ���

template<typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	Fib fib(hi - lo);
	int count = 0;
	while(lo < hi)
	{
		while(hi - lo < fib.get())	fib.prev();
		Rank mi = lo + fib.get() - 1;
		if(e < A[mi]) {
			count++;
			hi = mi;
		}
		else if (A[mi] < e){
			count += 2;
			lo = mi + 1;
		}
		else{
			count += 2;
			*sum = *sum + count;
			std::cout << "fibonacci���ҵĳɹ����ҳ���Ϊ   " << count << std::endl;
			return mi;
		}
	}
	*sum = *sum + count;
	std::cout << "fibonacci��ʧ�ܲ��ҳ���Ϊ" << count << std::endl;
	return -1;
}

//���ֲ��ң��汾B�����Ҷ�ֻ��һ��Ԫ�رȽϼ���
template<typename T>

static Rank binSearchB(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	int count = 0;
	while(lo < hi - 1)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi;
		count+=1;
	}
	count++;
	*sum = *sum + count;
	if(e == A[lo])
	{
		std::cout << "���ֲ���B�ĳɹ����ҳ���Ϊ   " << count << std::endl;
		return lo;
	}
	else{
		std::cout << "���ֲ���B��ʧ�ܲ��ҳ���Ϊ" << count << std::endl;
		return -1;
	}
}

/*
//���ֲ������հ汾����������
template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi, int *sum)
{
	while(lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])	hi = mi;
		else	lo = mi + 1;
		count ++;
	}
	return lo - 1;
}*/
/*ָ�����ң�
��һ���ǽ�������������A[0,n)�У��������������Ԫ��x <= A[n - 1]���Ӹ��������ҳ�һ��Ԫ��A[k]��ʹ�� A[k] <= x <= A[min(n - 1, kƽ��)]
�ж�����践������һ��������ʱ�䲻����O(loglogk)
����ʧ�ܷ��� lo - 1 �� hi
*/
template<typename T>
static Rank exponentialSearch(T *a, T const &e, Rank lo, Rank hi)
{
	//assert:e <= a[hi - 1]
	a = a + lo;
	if(e < a[0])	return lo - 1;
	for(int i = 0 ; i * i < hi - lo ; i++)
	{
		if(e <= a[i * i] && e >= a[i])
		{
			return lo + i;
		}
	}
	return hi;
}

/*�����ң�����һ�����˶��֣�fibo��expo�������ҵ��㷨*/

/*�����һ��  ��ֵ���ң� ���Աƽ�����ʵҲ�����зֵ�*/
template <typename T>
static int interpolationSearch(T *a, T const &e, int lo, int hi, int *sum)
{
	int count = 0;
	while(lo < hi - 1)
	{
		//����ֲ��Ҳ�֮ͬ�����ڣ������ڼ����зֵ�ʱ������зֵ㲻һ������[lo, hi)��Χ����һ������зֵ�û�����У���ôֻ��˵��e����[lo,hi)��Χ��
		int y = (e - a[lo]) * (hi - lo - 1) /  (a[hi - 1] - a[lo]) + lo;
		if(y < lo || y >= hi)
			return -1;
		if(a[y] < e)
		{
			count ++;
			lo = y + 1;
		}
		else if(e < a[y]){
			count += 2;
			hi = y;
		}
		else
			{
				count += 2;
				std::cout << "��ֵ���ҵĳɹ����ҳ���Ϊ   " << count << std::endl;
				*sum = *sum + count;
				return y;
		}
	}
	count += 1;
	if(a[lo] == e)
	{
		std::cout << "��ֵ���ҵĳɹ����ҳ���Ϊ2   " << count << std::endl;
		*sum = *sum + count;
		return lo;
	}
	else{
		std::cout << "��ֵ���ҵ�ʧ�ܲ��ҳ���Ϊ" << count << std::endl;
		*sum = *sum + count;
		return -1;
	}
}

//ר�����������㷨��ʵ��

//ð������
//���ʼ����ð�����򣬾���һ����һ���ɨ�裬ֱ��û������Ծͽ���
//��������ʦ�Ľ��������ˣ���k = n��ʼ��ÿһ�˴�k��ǰɨ��
//ɨ������󣬶����Ա�֤��k + 1��Ԫ������Ϊk��λ���ϣ�������������̾ͱ����n - 1�˵�ɨ��

//����ʵ������ʱ��һ��������n - 1�ˣ����ܻ���ǰ����������˵���ԡ��չ���ĳһ���Ѿ��ź����ɨ�裬��ô��һ����ȫ���԰��ϴ�ɨ�轻���˵�����±���Ϊ��һ��ɨ���hi��
//���ݿκ��⣬���ǿ��Է������ִ��ɨ�轻������̬��¼��������ҵ�����Ԫ��

//ʱ���ϵ������д�����հ��
template<typename T>




void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while(lo < (hi = bubble(lo, hi)))
	{
		this->print();
	}
}

template<typename T>
Rank Vector<T>::bubble(Rank lo, Rank hi)
{
	Rank last = lo;
	while(lo < hi - 1)
	{
		if(_elem[lo + 1] < _elem[lo])
		{
			T temp = _elem[lo];
			_elem[lo] = _elem[lo + 1];
			_elem[lo + 1] = temp;
			last = lo + 1;
		}
		lo++;
	}
	return last;
}

//��·�鲢�����ʵ��
template<typename T>

void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if(lo < hi - 1)
	{
		int mi = (lo + hi) >> 1;
		mergeSort(lo, mi);
		mergeSort(mi, hi);
		merge(lo, mi, hi);
	}
}


template<typename T>


void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *B = new T[mi - lo];
	T *C = _elem + mi;
	Rank left = 0, right = 0;
	Rank leftb = mi - lo, rightb = hi - mi;
	for(Rank i = 0 ; i < leftb ; i ++)
		B[i] = _elem[i + lo];
	Rank p = lo;
	while(left < leftb)
	{
		if(right < rightb)
		{
			//ע���ȶ���
			if(B[left] <= C[right])
				_elem[p++] = B[left++];
			else
				_elem[p++] = C[right++];
		}
		else 
		{
			_elem[p++] = B[left++];
		}
	}
}
/*
//ѧ����ָ��ӷ�
//ֻ��ҪB�ø����ռ䣬Ȼ����԰�ĳ������Ϊ�գ���һ����Ϊ������������Ҳд��forѭ����
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *A = _elem + lo;
	T *B = new T[mi - lo];
	for(int i = 0 ; i < mi - lo ; B[i++] = A[i]);
	T *C = _elem + mi;
	int lb = mi - lo;
	int lc = hi - mi;
	for(int i = 0, j = 0, k = 0 ; (j < lb) || (k < lc);)
	{
		if(j < lb && (lc <= k || B[j] <= C[k]))	A[i++] = B[j++];
		if(k < lc && (lb <= j || C[k] < B[j]))	A[i++] = C[k++];
	}
	delete[] B;
}
*/

//ѡ������
template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	for(int i = hi - 1 ; i > lo ; i--)
	{
		int mx;
		//����maxһ��Ҫ����ֵ������ĩβ��Ԫ��
		if((mx = max(lo, hi)) != i)
		{
			T temp = _elem[i];
			_elem[i] = _elem[mx];
			_elem[mx] = temp;
		}
	}
}

template<typename T>
int Vector<T>::max(Rank lo, Rank hi)
{
	int mx = lo;
	for(int i = lo + 1 ; i < hi ; i++)
	{
		//������˳��ɨ������Ϊ�˱�֤�ȶ�����������>=
		if(_elem[i] >= _elem[mx])
			mx = i;
	}
	return mx;
}