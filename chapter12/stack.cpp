#include "stdafx.h"

int top1 = 0;
int top2 = 0;
int stack1[50] = {0};
int stack2[50] = {0};

void enqueue(int key)
{
	//���˶Ա߽������ļ��
	stack1[top1++] = key;
}
//һ��ʼ�����ÿһ�ζ���ջ1��n-1��Ԫ���õ�ջ2���û���
//���������õ�ջ2����Ҫ�û�����̫���ˣ�ɾ��ֱ�ӿ�ջ2������
int dequeue()
{
	if(top2 != 0)
	{
		return stack2[--top2];
	}
	while(top1 != 1)
		stack2[top2++] = stack1[--top1];
	int key = stack1[--top1];
	return key;
}

//������һ�����ݽṹ��������ջһ���Ĳ�����ѹ�룬����������ȳ��������ҿ���ʵ��min���������ص�ǰջ�����Сֵ����֮ǰ�Ĳ�����ֻ����O(1
//��һ��ʼ���뷨�ǣ��õ�����Сֵ����ֵ��������������������Сֵ�����󣬿���ͨ��ָ����õ���һ����Сֵ����Ϊջ����ȳ������ʣ��Ƚ�������Сֵһ�����ȥ��
//���ϵ������ǣ�����һ������ջ����ѹջʱ�����ջΪ�ջ���ջ��Ԫ�ش���ѹջԪ�أ���ô���Ԫ�ز���ѹջ����ѹ�븨��ջ�����ջ��Ԫ��С�ڵ���ѹջԪ�أ���ô�Ѹ���ջ��ջ��Ԫ����ѹһ��
//���Ҿ��ò���Ҫ��ѹһ�飬������popʱ���һ�¾����ˣ�

//�������У���һ�����б�ʾջ��ѹ��˳�򣬵ڶ������б�ʾջ�ĵ���˳��ȷ������ڶ��������Ƿ���ȷ
//����˼���󣬿���ģ��������̣���������е�ͨ����ô˵���ڶ������в���ȷ
//�����������������ǺϷ�������
bool checkSequence(int pushorder[], int poporder[], int size)
{
	if(!pushorder || !poporder || !size)
		return false;
	int top = 0;
	int *stack = new int[size];
	int pushindex = 0;
	int popindex = 0;
	while(popindex < size)
	{
		if(pushindex < size)
		{
			//���pushindex<size��ʾ��û�а���������ѹ��ջ�У���ô��ʱ��Ҫ����ѹջ����
			int pushvalue = pushorder[pushindex];
			int popvalue = poporder[popindex];
			if(pushvalue != popvalue)
			{
				//�������Ҫѹ��ջ��ֵ��Ҫ��������ջ��ֵ��һ������ô�Ͱ����ֵѹջ
				//���Ҫѹ��ջ��ֵ��Ҫ��������ջ��ֵ��һ������ô�ȼ��Ҫ��������ֵ�Ƿ�͵�ǰջ����ֵ��ȣ�
				//�����ȣ���ôִ��pop�������������Ȼ���ջΪ�գ���ô��ѹջ
				if(top)
				{
					if(stack[top - 1] == popvalue)
					{
						--top;
						popindex++;
					}
					else{
						stack[top++] = pushorder[pushindex++];
					}
				}
				else{
					stack[top++] = pushorder[pushindex++];
				}

			}
			else{
				//���Ҫѹ��ջ��ֵ��Ҫ������ջ��ֵһ������ô��ֱ��popindex++��pushindex++��ʾ���ѹ��͵�������
				pushindex++;
				popindex++;
			}
		}
		else{
			//���pushindex>=size��ʾ���������ѱ�ѹ��ջ�У���ô��ʱ����poporder���ε������������Ƿ���ȷ
			while(popindex < size)
			{
				int popvalue = poporder[popindex++];
				int stackvalue = stack[--top];
				if(popvalue != stackvalue)
					return false;
			}
		}
	}
	return true;
}

/*int main(int argc, char* argv[])
{
	
	int a[] = {1, 2};
	int b[] = {1, 2};
	std::cout << checkSequence(a, b, 2) << std::endl;
	return 0;
}*/

