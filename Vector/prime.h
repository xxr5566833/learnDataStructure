#pragma once
#include "Bitmap.h"

//���ز�С��n������
int Eratosthenes(int n);

int Eratosthenes(int n)
{
	/*
	��С��7.263x10^13���������������ļ������ͳ�ƣ�ȷ������С�ļ����1�������777
	������������������󳤶�Ϊn + 777
	*/
	Bitmap  m = Bitmap(n + 778);
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
	for(int i = n ; i < n + 777 ; i++)
	{
		if(!m.test(i))
			return i;
	}
	//ʧ���ǲ�����ʧ�ܵģ�����ʧ��ͳһ����n - 1
	return n - 1;
}