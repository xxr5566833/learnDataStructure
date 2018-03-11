#include "stdafx.h"
//单向链表相关操作
typedef struct node
{
	int key;
	struct node *next;
}Node;
Node *head = 0;

void insert(int key)
{
	Node *n = new Node();
	n->key = key;
	if(head)
	{
		n->next = head->next;
		head->next = n;
	}
	else{
		head = n;
		n->next = 0;
	}
}
//注意head为空的情况
void insert2Tail(int key)
{
	Node *n = new Node();
	n->key = key;
	n->next = 0;
	if(head)
	{
		Node *p = head;
		while(p->next)
			p = p->next;
		p->next = n;
	}
	else{
		head = n;
	}
}

void del(Node *node)
{
	//又忘了判断了卧槽
	if(!node)
		return ;
	if(node == head)
	{
		head = node->next;
		delete node;
	}
	else{
		//这里只需要一个变量即可，而且之前这里有bug，如果node不在这个链表中，那么这里q是null会崩溃
		/*Node *p = head, *q = head->next;
		while(q != node)
		{
			p = q;
			q = q->next;
		}
		p->next = q->next;
		delete q;*/
		Node *p = head;
		while(p->next && p->next != node)
			p = p->next;
		if(p->next)
		{
			p->next = p->next->next;
			delete node;
		}
		else{
			std::cout << "没有找到" << std::endl;
		}

	}
}

//找到第一个有这个key值的结点，并删去它，返回这个节点
Node* remove(int key)
{
	Node *p, *q;
	p = head;
	while(p)
	{
		if(p->key == key)
		{
			//删除p，所以需要记录p的前驱结点
			if(p == head)
				head = p->next;
			else{
				q->next = p->next;
			}
			break;	
		}
		q = p;
		p = p->next;
	}
	return p;
}
//一开始简单的想实现链表的倒数第k个节点，就是先遍历然后保存
//虽然都是O(n)但是下面这种方法空间占用更少

//！！！求链表的中间节点，也可以用两个指针来实现，都从头开始，一个每次走两步，一个每次走一步，天呐太神奇了
//当然首先是要确保这个链表没有环
Node *findLastK(int k)
{
	//注意k的范围的检查
	if(k <= 0 || !head)
		return 0;
	Node *p = head, *q;
	//1.p指针沿链表走k步
	for(int i = 0 ; i < k ; i++)
	{
		if(!p)
			return NULL;
		p = p->next;
	}
	//错误：一开始没有考虑到正好倒数第k个是根节点的情况

	//2.p和q同时走，直到p指针到达链表结尾null
	q = head;
	while(p)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}


//给定链表的头结点，从尾到头打印链表,注意仅仅打印而不是修改链表的结构
void iterativeReversePrint()
{
	//遍历一遍，存到栈中
}

void recursionReversePrint(Node *node)
{
	//又忘记了判断node是否为null！！
	if(!node)
		return ;
	if(node->next)
		recursionReversePrint(node->next);
	std::cout << node->key << std::endl;
}


//妙啊，我们不光可以通过改变指针来改变相应的结点，我们还可以通过改变节点的内容继而改变相应的结点
//O(1)时间内删除链表内的结点
//首先肯定要保证这个节点是在链表内的,这个肯定要交给调用者保证，如果放在这里检查，那么时间复杂度一定有O(n)了
void delO1(Node *node)
{
	if(!node)
		return ;
	if(node->next)
	{
		//说明不是最后一个节点，那么赋值后删除
		Node *oldnext = node->next;
		node->key = node->next->key;
		node->next = node->next->next;
		delete oldnext;
	}
	else{
		//最后一个节点只能用普通的方法删除了
		del(node);
	}
}

//翻转链表，这个之前做过，依次遍历每个结点
void reverse()
{
	if(!head)
		return ;
	Node *p = head->next;
	Node *q = head;
	while(p)
	{
		Node *old = p->next;
		p->next = q;
		if(q == head)
			q->next = 0;
		q = p;
		p = old;

	}
	head = q;
}
//递归实现链表的翻转更容易实现
Node *recursionReverse(Node *node)
{
	if(!node)
		return node;
	if(node->next)
	{
		Node *n = recursionReverse(node->next);
		n->next = node;
		//注意这里也要把原来的head的next设置为0，不然就成了环了
		if(node == head)
			node->next = 0;
	}
	else{
		head = node;
	}
	return node;

}


//我的思路是以第一个链表为主链表，然后第二个链表在其中做插入操作
//书上的是每一次拿最小的放到新链表里，好吧我还是觉得书上的好
Node* merge2List(Node *head1, Node *head2)
{
	Node *p = head1;
	Node *lastp = 0;
	Node *q = head2;
	while(p && q)
	{
		Node *nextq = q->next;
		if(p->key >= q->key)
		{
			//如果p的第一个结点比q大，那么把q插在p前面
			if(lastp)
			{
				lastp->next = q;
				lastp = q;
			}
			else{
				//说明p此时是head1，那么插入到head1前面
				head1 = q;
				lastp = q;
			}
			q->next = p;
			q = nextq;
		}
		else{
			lastp = p;
			p = p->next;
		}
	}
	if(q)
	{
		//q没有加完，此时lastp指向链表1的最后一个链表
		//错误：这里有问题，lastp可能为空，这里要分情况
		if(lastp)
			lastp->next = q;
		else{
			head1 = q;
		}
	}
	return head1;
}

Node *merge2List2(Node *pHead1, Node *pHead2)
{
	Node *head = NULL;
        if(pHead1 == NULL)
            return pHead2;
        if(pHead2 == NULL)
            return pHead1;
        Node *last = NULL;
        while(pHead1 && pHead2)
        {
           Node *n = 0;
            if(pHead1->key > pHead2->key)
			{
				n = pHead2;
				pHead2 = pHead2->next;
			}
			else{
				n = pHead1;
				pHead1 = pHead1->next;
			}
            if(head)
            {
                last->next = n;
                last = n;
                n->next = 0;
            }
            else{
                head = n;
                last = n;
                last->next = 0;
            }
        }
        if(pHead1)
            last->next = pHead1;
        if(pHead2)
            last->next = pHead2;
        
        return head;
}

//还有一种思路就是每一次都取两个链表中较小的头结点加入到新链表中，而且可以递归实现
//因为每一次取较小头结点以后，剩余的两个链表还是排好序的
Node *recursionMerge(Node *head1, Node *head2)
{
	if(!head1)
		return head2;
	if(!head2)
		return head1;
	Node *mergehead;
	if(head1->key < head2->key)
	{
		mergehead = head1;
		head1->next = recursionMerge(head1->next, head2);
	}
	else{
		mergehead = head2;
		head2->next = recursionMerge(head1, head2->next);
	}
	return mergehead;
}

//求两个链表的公共结点，想到了先求两个链表的长度，然后用类似于求倒数第k个节点的办法，让长的结点先走
//还有一种就是用栈了 
//由此可以看出，当你想把时间复杂度降低时，你要尽可能的获得可以在低时间复杂度可以获得的条件，比如我可以在O（m）和O（n）时间内获得长度，
//然后利用这些条件，找到更好的算法

Node *commonNode()
{
	return 0;
}


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};


    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        ListNode *p = pHead, *q = pHead;
        if(pHead == 0)
            return pHead;
        while(p != q)
        {
            p = p->next->next;
            q = q->next;
        }
        int length = 0;
        do{
            p = p->next->next;
            q = q->next;
            length++;
        }while(p != q);
        p = q = pHead;
        for(int i = 0 ; i < length ; i++)
            p = p->next;
        while(p != q)
        {
            p = p->next;
            q = q->next;
        }
		std::cout << p->val << std::endl;
        return p;
    }
//删除重复节点
ListNode* deleteDuplication(ListNode* pHead)
    {
        if(!pHead)
            return pHead;
        ListNode *begin = 0;
        ListNode *last = 0;
        while(pHead)
        {
            int val = pHead->val;
            ListNode *p = pHead;
            pHead = pHead->next;
            while(pHead && pHead->val == val)
            {
                pHead = pHead->next;
            }
            if(pHead == p->next)
            {
                if(begin)
                {
                    last->next = p;
                    last = p;
                    last->next = NULL;
                }
                else{
                    begin = p;
                    last = p;
                }
            }
        }
        
        return begin;
    }
//复杂链表的复制
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
RandomListNode* Clone(RandomListNode* pHead)
    {
        if(!pHead) return NULL;
        RandomListNode *head;
        RandomListNode *p = pHead;
        while(p)
        {
            RandomListNode *n = new RandomListNode(p->label);
            n->next = p->next;
            p->next = n;
            p = p->next->next;
        }
        //把所有节点复制一遍
        p = pHead;
        while(p)
        {
            if(p->random)
                p->next->random = p->random->next;

            p = p->next->next;
        }
        //复制random
        
        head = pHead->next;
        p = pHead;
        while(p->next)
        {
            RandomListNode *temp = p->next;
            p->next = temp->next;
            p = temp;
        }
        return head;
    }
/*int main(int argc, char *argv[])
{
	insert(1);
	insert2Tail(7);
	insert2Tail(9);
	insert2Tail(11);
	insert(5);
	insert(3);
	Node *p1 = head;
	head = 0;
	insert(2);
	insert2Tail(8);
	insert2Tail(10);
	insert2Tail(12);
	insert(6);
	insert(4);
	Node *p2 = merge2List2(p1, head);
	while(p2)
	{
		std::cout << p2->key << std::endl;
		p2 = p2->next;
	}
	return 0;
}*/