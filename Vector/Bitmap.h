#include "stdafx.h"
void Eratosthenes(int n);
//ʹ��charʵ�ֵ�bitmap��
class Bitmap{
private:
	char *M;
	int N;
protected:
	void init(int n)
	{
		//(n + 7) / 8 �Ǳ�ʾ��С��n��bit����С���ֽ�������ΪM��char���͵ģ�һ����8��bit�ı���
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
		//delete ��ָ��ԭ����ֵ���䣡
		M = NULL;
	}
	//�������ʵ�Bitmap[k]�Ѿ����磬����Ҫ����
	void expand(int k)
	{
		if(k < 8 * N)	return;
		int oldN = N;
		char *oldM = M;
		init(2 * k);
		memcpy_s(M, N, oldM, oldN);
		delete []oldM;
	}

	//����iλ����Ϊtrue
	void set(int i)
	{
		expand(i);
		/*1. ����2�ı�������λ��
		2.ע�����ﰴ��λͼ�Ĵ����ҵ�˳�򣬵�iλӦ���Ƕ�Ӧ�ֽڵĵ� i % 8 ����λ�����ǵ�λ
		3.% 8 �� & 0x07!!!!!!!
		*/
		//���ư����
		M[i >> 3] |= (0x80 >> (i & 0x07));
	
		//M[i / 8] = M[i / 8] & (1 << (i % 8));
	}
	//����iΪ����Ϊfalse
	void clear(int i)
	{
		expand(i);
		M[i >> 3] &= ~(0x80 >> (i & 0x07));
	}
	//���Ե�iλ�Ƿ�Ϊtrue
	bool test(int i)
	{
		expand(i);
		//assert i�Ϸ�
		return M[i >> 3] & (0x80 >> (i & 0x07 ));
	}

	//��λͼ���嵼����ָ�����ļ����Ա���ź����λͼ������ʼ��
	void dump(char *file)
	{
		FILE *fp = fopen(file, "w");
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}

	//��ǰnλת��Ϊ�ַ���
	char *bits2string(int n)
	{
		//��ʱ���Ա����ʵ����λ��n - 1
		expand(n - 1);
		char *s = new char[n + 1];
		s[n] = '\0';
		//�������ˣ����ǰ�ÿһλ��bitת��Ϊ��0����1��char������˵����ֱ�Ӵ�M����
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
		//������������Ҫ�������ı����ı�־λ������Ѿ������ñ�־λ����ô����Ҫ�����ˣ�
		if(!m.test(i))
		{
			//����j��ȫ���Դ�i ��ʼ
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

//ʹ������vectorʵ�ֵ�bitmap
typedef int Rank;
/*class Bitmap{
private:
	Rank *F;
	//��ģΪN������F����¼[k]����ǵĴ��򣬼���Tջ�е���
	Rank N;
	//����ΪN��ջ����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ��
	Rank *T;
	Rank top;
protected:
	inline bool valid(Rank r)
	{
		//����r�Ǳ���ǵĴ��򣬼�T���ȣ�����ҪС��top
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