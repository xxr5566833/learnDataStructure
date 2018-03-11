#include "stdafx.h"
//����������ز���
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
//ע��headΪ�յ����
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
	//�������ж����Բ�
	if(!node)
		return ;
	if(node == head)
	{
		head = node->next;
		delete node;
	}
	else{
		//����ֻ��Ҫһ���������ɣ�����֮ǰ������bug�����node������������У���ô����q��null�����
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
			std::cout << "û���ҵ�" << std::endl;
		}

	}
}

//�ҵ���һ�������keyֵ�Ľ�㣬��ɾȥ������������ڵ�
Node* remove(int key)
{
	Node *p, *q;
	p = head;
	while(p)
	{
		if(p->key == key)
		{
			//ɾ��p��������Ҫ��¼p��ǰ�����
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
//һ��ʼ�򵥵���ʵ������ĵ�����k���ڵ㣬�����ȱ���Ȼ�󱣴�
//��Ȼ����O(n)�����������ַ����ռ�ռ�ø���

//��������������м�ڵ㣬Ҳ����������ָ����ʵ�֣�����ͷ��ʼ��һ��ÿ����������һ��ÿ����һ��������̫������
//��Ȼ������Ҫȷ���������û�л�
Node *findLastK(int k)
{
	//ע��k�ķ�Χ�ļ��
	if(k <= 0 || !head)
		return 0;
	Node *p = head, *q;
	//1.pָ����������k��
	for(int i = 0 ; i < k ; i++)
	{
		if(!p)
			return NULL;
		p = p->next;
	}
	//����һ��ʼû�п��ǵ����õ�����k���Ǹ��ڵ�����

	//2.p��qͬʱ�ߣ�ֱ��pָ�뵽�������βnull
	q = head;
	while(p)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}


//���������ͷ��㣬��β��ͷ��ӡ����,ע�������ӡ�������޸�����Ľṹ
void iterativeReversePrint()
{
	//����һ�飬�浽ջ��
}

void recursionReversePrint(Node *node)
{
	//���������ж�node�Ƿ�Ϊnull����
	if(!node)
		return ;
	if(node->next)
		recursionReversePrint(node->next);
	std::cout << node->key << std::endl;
}


//������ǲ������ͨ���ı�ָ�����ı���Ӧ�Ľ�㣬���ǻ�����ͨ���ı�ڵ�����ݼ̶��ı���Ӧ�Ľ��
//O(1)ʱ����ɾ�������ڵĽ��
//���ȿ϶�Ҫ��֤����ڵ����������ڵ�,����϶�Ҫ���������߱�֤��������������飬��ôʱ�临�Ӷ�һ����O(n)��
void delO1(Node *node)
{
	if(!node)
		return ;
	if(node->next)
	{
		//˵���������һ���ڵ㣬��ô��ֵ��ɾ��
		Node *oldnext = node->next;
		node->key = node->next->key;
		node->next = node->next->next;
		delete oldnext;
	}
	else{
		//���һ���ڵ�ֻ������ͨ�ķ���ɾ����
		del(node);
	}
}

//��ת�������֮ǰ���������α���ÿ�����
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
//�ݹ�ʵ������ķ�ת������ʵ��
Node *recursionReverse(Node *node)
{
	if(!node)
		return node;
	if(node->next)
	{
		Node *n = recursionReverse(node->next);
		n->next = node;
		//ע������ҲҪ��ԭ����head��next����Ϊ0����Ȼ�ͳ��˻���
		if(node == head)
			node->next = 0;
	}
	else{
		head = node;
	}
	return node;

}


//�ҵ�˼·���Ե�һ������Ϊ������Ȼ��ڶ����������������������
//���ϵ���ÿһ������С�ķŵ���������ð��һ��Ǿ������ϵĺ�
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
			//���p�ĵ�һ������q����ô��q����pǰ��
			if(lastp)
			{
				lastp->next = q;
				lastp = q;
			}
			else{
				//˵��p��ʱ��head1����ô���뵽head1ǰ��
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
		//qû�м��꣬��ʱlastpָ������1�����һ������
		//�������������⣬lastp����Ϊ�գ�����Ҫ�����
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

//����һ��˼·����ÿһ�ζ�ȡ���������н�С��ͷ�����뵽�������У����ҿ��Եݹ�ʵ��
//��Ϊÿһ��ȡ��Сͷ����Ժ�ʣ��������������ź����
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

//����������Ĺ�����㣬�뵽��������������ĳ��ȣ�Ȼ����������������k���ڵ�İ취���ó��Ľ������
//����һ�־�����ջ�� 
//�ɴ˿��Կ������������ʱ�临�ӶȽ���ʱ����Ҫ�����ܵĻ�ÿ����ڵ�ʱ�临�Ӷȿ��Ի�õ������������ҿ�����O��m����O��n��ʱ���ڻ�ó��ȣ�
//Ȼ��������Щ�������ҵ����õ��㷨

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
//ɾ���ظ��ڵ�
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
//��������ĸ���
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
        //�����нڵ㸴��һ��
        p = pHead;
        while(p)
        {
            if(p->random)
                p->next->random = p->random->next;

            p = p->next->next;
        }
        //����random
        
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