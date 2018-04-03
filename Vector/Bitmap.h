#include "stdafx.h"
void Eratosthenes(int n);
//使用char实现的bitmap类
class Bitmap{
private:
	char *M;
	int N;
protected:
	void init(int n)
	{
		//(n + 7) / 8 是表示不小于n个bit的最小的字节数，因为M是char类型的，一定是8个bit的倍数
		M = new char[N = (n + 7) / 8];
		memset(M, 0, N);
	}
public:
	Bitmap(int n = 8)
	{
		init(n);
	}
	Bitmap(char *file, int n = 8)
	{
		init(n);
		FILE *fp = fopen(file, "r");
		fread(M, sizeof(char), N, fp);
		fclose(fp);
	}
	~Bitmap()
	{
		delete[] M;
		//delete 后指针原来的值不变！
		M = NULL;
	}
	//若被访问的Bitmap[k]已经出界，则需要扩容
	void expand(int k)
	{
		if(k < 8 * N)	return;
		int oldN = N;
		char *oldM = M;
		init(2 * k);
		memcpy_s(M, N, oldM, oldN);
		delete []oldM;
	}

	//将第i位设置为true
	void set(int i)
	{
		expand(i);
		/*1. 除以2的倍数用移位！
		2.注意这里按照位图的从左到右的顺序，第i位应该是对应字节的第 i % 8 个高位而不是地位
		3.% 8 用 & 0x07!!!!!!!
		*/
		//右移啊大哥
		M[i >> 3] |= (0x80 >> (i & 0x07));
	
		//M[i / 8] = M[i / 8] & (1 << (i % 8));
	}
	//将第i为设置为false
	void clear(int i)
	{
		expand(i);
		M[i >> 3] &= ~(0x80 >> (i & 0x07));
	}
	//测试第i位是否为true
	bool test(int i)
	{
		expand(i);
		//assert i合法
		return M[i >> 3] & (0x80 >> (i & 0x07 ));
	}

	//将位图整体导出至指定的文件，以便对伺候的新位图批量初始化
	void dump(char *file)
	{
		FILE *fp = fopen(file, "w");
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}

	//将前n位转换为字符串
	char *bits2string(int n)
	{
		//此时可以被访问的最高位是n - 1
		expand(n - 1);
		char *s = new char[n + 1];
		s[n] = '\0';
		//我明白了，它是把每一位的bit转化为了0或者1的char，所以说不能直接从M复制
		for(int i = 0 ; i < n ; i++)
		{
			s[i] = test(i) ? '1' : '0';
		}
		return s;
	}
};

void Eratosthenes(int n)
{
	Bitmap  m = Bitmap(n);
	for(int i = 2 ; i * i <= n ; i++)
	{
		//对于素数才需要设置它的倍数的标志位，如果已经被设置标志位，那么不需要遍历了！
		if(!m.test(i))
		{
			//这里j完全可以从i 开始
			for(int j = i ; i * j <= n ; j += 1)
			{
				m.set(i * j);
			}
		}
	}
	for(int i = 2 ; i <= n ; i++)
	{
		if(!m.test(i))
			std::cout << i << " ";
	}
	std::cout << std::endl;
}

//使用两个vector实现的bitmap
typedef int Rank;
/*class Bitmap{
private:
	Rank *F;
	//规模为N的向量F，记录[k]被标记的次序，即在T栈中的秩
	Rank N;
	//容量为N的栈，记录被标记各位秩的栈，以及栈顶指针
	Rank *T;
	Rank top;
protected:
	inline bool valid(Rank r)
	{
		//这里r是被标记的次序，即T的秩，所以要小于top
		return r >= 0 && r < top;
	}
	inline bool erased(Rank r)
	{
		//assert r < N 
		return valid(F[r]) && !(T[F[r]] + r + 1);
	}
public:
	Bitmap(int n = 8)
	{
		F = new int[N = n];
		T = new int[N = n];
		top = 0;
	}
	~Bitmap()
	{
		delete[] F;
		delete[] T;
	}
	void set(Rank r)
	{
		if(test(r))	return ;
		if(!erased(r))	F[r] = top++;
		T[F[r]] = r;
	}

	bool test(Rank r)
	{
		return valid(F[r]) && T[F[r]] == r; 
	}
	void clear(Rank r)
	{
		if(test(r))
		{
			T[F[r]] = -r - 1;
		}
	}
};*/