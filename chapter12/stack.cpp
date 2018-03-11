#include "stdafx.h"

int top1 = 0;
int top2 = 0;
int stack1[50] = {0};
int stack2[50] = {0};

void enqueue(int key)
{
	//忘了对边界条件的检查
	stack1[top1++] = key;
}
//一开始想的是每一次都把栈1的n-1个元素拿到栈2再拿回来
//后来发现拿到栈2后不需要拿回来，太蠢了，删除直接看栈2就行了
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

//如何设计一个数据结构，不仅有栈一样的操作（压入，弹出，后进先出），而且可以实现min函数，返回当前栈里的最小值，且之前的操作都只能是O(1
//我一开始的想法是，让当过最小值的数值用链表穿起来，这样在最小值弹出后，可以通过指针域得到上一个最小值（因为栈后进先出的性质，先进来的最小值一定后出去）
//书上的做法是，另做一个辅助栈，在压栈时，如果栈为空或者栈顶元素大于压栈元素，那么这个元素不仅压栈而且压入辅助栈，如果栈顶元素小于等于压栈元素，那么把辅助栈的栈顶元素再压一遍
//（我觉得不需要再压一遍，可以在pop时检查一下就行了）

//两个序列，第一个序列表示栈的压入顺序，第二个序列表示栈的弹出顺序，确定这个第二个序列是否正确
//经过思考后，可以模拟这个过程，如果不能行的通，那么说明第二个序列不正确
//假设是它给的输入是合法的输入
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
			//如果pushindex<size表示还没有把所有数据压入栈中，那么此时需要进行压栈过程
			int pushvalue = pushorder[pushindex];
			int popvalue = poporder[popindex];
			if(pushvalue != popvalue)
			{
				//错误：如果要压入栈的值和要被弹出的栈的值不一样，那么就把这个值压栈
				//如果要压入栈的值和要被弹出的栈的值不一样，那么先检查要被弹出的值是否和当前栈顶的值相等，
				//如果相等，那么执行pop操作，如果不相等或者栈为空，那么先压栈
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
				//如果要压入栈的值和要被弹出栈的值一样，那么就直接popindex++，pushindex++表示这个压入和弹出过程
				pushindex++;
				popindex++;
			}
		}
		else{
			//如果pushindex>=size表示所有数据已被压入栈中，那么此时按照poporder依次弹出，并检验是否正确
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

