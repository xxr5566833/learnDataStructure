#include "stdafx.h"

//二叉树
//数据结构定义
typedef struct BTREE{
	struct BTREE *p;
	struct BTREE *left;
	struct BTREE *right;
	int key;
}bTree;
//根节点是一个全局节点
bTree *root;
//为了后面方便，如果一个节点的右儿子为null，那么我把它为 1，与0（表示左子节点为null）区分开
bool isNull(bTree *root)
{
	return root ==0 || (int)root == 1;
}
//求以root为根节点的树的最小元素的循环实现
bTree *iterativeMinimum(bTree *root)
{
	//注意对root的检查，因为后面是直接用到了root->left
	if(isNull(root))
		return 0;
	while(!isNull(root->left))
	{
		root = root->left;
	}
	return root;
}
//求以root为根节点的树的最小元素的递归实现
bTree *minimum(bTree *root)
{
	if(isNull(root))
		return root;
	if(isNull(root->left))
	{
		return root;
	}
	else{
		return minimum(root->left);
	}
}
//最大元素
bTree *maximum(bTree *root)
{
	if(isNull(root))
		return root;
	if(isNull(root->right))
	{
		return root;
	}
	else{
		return maximum(root->right);
	}

}

bTree *iterativeMaximum(bTree *root)
{
	if(isNull(root))
		return 0;
	while(!isNull(root->right))
		root = root->right;
	return root;
}

//错误的惯性思维，对于一个节点，可能是父亲结点的左子节点也可能是右子节点
//如果这个节点是其父亲的右子节点，那么这个节点是比其父亲大，但是！不能保证这个节点的父亲的父辈节点和它的大小关系
//后继
bTree *successor(bTree *root)
{
	if(!isNull(root->right))
	{
		return minimum(root->right);
	}
	bTree *temp = root->p;
	while(!isNull(temp) && root != temp->left)
	{
		root = temp;
		temp = temp->p;
		
	}
	return temp;
}
//前驱
bTree *predecessor(bTree *root)
{
	if(isNull(root))
		return root;
	if(isNull(root->left))
	{
		bTree *p = root->p;
		bTree *q = root;
		while(!isNull(p) && p->right != q)
		{
			q = p;
			p = p->p;
		}
		return p;
	}
	else{
		return iterativeMaximum(root->left);
	}
}

//递归
void recursionPreorderWalk(bTree *root)
{
	if(root)
	{
		std::cout << root->key << std::endl;
		recursionPreorderWalk(root->left);
		recursionPreorderWalk(root->right);
	}
}


//非递归+栈
void preorderWalk()
{
	bTree* stack[50] = {0};
	int top = 0;
	bTree *now = root;
	while(!isNull(now) || top)
	{
		while(!isNull(now))
		{
			stack[top++] = now;
			std::cout << now->key << std::endl;
			now = now->left;
		}
		now = stack[--top];
		now = now->right;
	}
}

void recursioniInorderWalk(bTree *root)
{
	if(!isNull(root))
	{
		recursioniInorderWalk(root->left);
		std::cout << root->key << std::endl;
		recursioniInorderWalk(root->right);
	}
}
void inorderWalk()
{
	bTree* stack[50] = {0};
	int top = 0;
	bTree *now = root;
	while(!isNull(now) || top)
	{
		while(!isNull(now))
		{
			stack[top++] = now;
			now = now->left;
		}
		now = stack[--top];
		std::cout << now->key << std::endl;
		now = now->right;
	}
}
//不使用栈只用一个last即可完成的中序遍历
void inorderWalkNotUseStack()
{
	bTree *last = 0;
	bTree *now = root;
	while(!isNull(now))
	{
		//last永远记录now的父亲，如果now非null，那么父亲也可以通过now->p来得到，但是当now是null时就需要通过last得到
		if(!isNull(now))
		{
			//如果now不是null
			last = now;
			now = now->left;
		}
		else{
			//此时说明now是null，那么now可能是父亲的左子节点，也可能是右子节点
			//如果now是某个节点的左子节点，那么说明此时应输出now的父亲，然后设置now为父亲的right
			//如果now是某个节点的右子节点，而且now还是null，那么借助last回溯，这里一开始单独写了一个循环，专门回溯到下一个需要遍历的结点处
			//但是其实不需要，直接借助外层的循环就可以，完全可以根据last和last父亲的关系，把now设置为0或者1（不能直接设置为last，否则会重复遍历，其实
			//这里就相当于把last所在的子树设置为null，因为反正都已经遍历过了）
			if(now == (bTree *)1)
			{
				//说明now是右子节点，那么此时看last即它的父亲是否为root，如果是那么说明遍历完成，如果不是，那么照之前的设置即可
				if(last == root)
				{
					break;
				}
				else{
					//last不是root，那么回溯即可
					now = last == last->p->left ? 0 : (bTree*) 1;
					last = last->p;
				}
			}
			else{
				std::cout << last->key << std::endl;
				now = last->right;
			}
			
		}
	}
}
//使用minimum函数和successor完成的中序遍历
void inorderWalk2()
{
	bTree *min = iterativeMinimum(root);
	while(!isNull(min))
	{
		std::cout << min->key << std::endl;
		min = successor(min);
	}
}

void recursionPostorderWalk(bTree *root)
{
	if(root)
	{
		recursionPostorderWalk(root->left);
		recursionPostorderWalk(root->right);
		std::cout << root->key << std::endl;
	}
}

void postorderWalk()
{
	bTree *stack[50] = {0};
	int top = 0;
	bTree *now = root;
	while(!isNull(now) || top)
	{
		while(!isNull(now))
		{
			stack[top++] = now;
			now = now->left;
		}
		//后序遍历不能直接从栈中取节点，因为后序是先左再右，所以要先找右结点
		//所以后序遍历会取两次节点，那么什么时候输出这个节点呢，就要看当前节点和栈顶节点的关系了
		//如果当前节点是栈顶节点的左子节点，那么直接找右子节点，
		//错误的想法：
		//如果当前节点是栈顶结点的右子节点，那么输出并设置now为0,因为刚取出来的栈顶结点一定是已经遍历完左子节点的
		//这样会导致死循环，正确的做法应该是不断地取出栈顶元素，如果说当前结点是栈顶元素的右子节点，那么继续回溯
		bTree *p = stack[top - 1];
		if(now == 0)
		{
			//说明now是栈顶结点的左子节点
			now = p->right;
		}
		else{
			//说明now是栈顶结点的右子节点
			bTree *q = now;
			
			while(top && q == p->right)
			{
				//这里要不断的取出已经遍历完的子树的根节点
				top--;
				std::cout << p->key << std::endl;
				q = p;
				p = stack[top - 1];
			}
			if(top == 0)
			{
				//如果top是0说明已经遍历完成了
				break;
			}
			else{
				//此时p是栈顶元素，q是p的左子节点，此时设置now为p的右子节点
				now = p->right;
			}
		}
	}
}

void FindPath(bTree* root,int expectNumber) {
        bTree *stack[50] = {0};
        int top = 0;
        bool flag[50] = {0};
        bTree *now = root;

        while(!isNull(now) || top)
        {
            while(!isNull(now))
            {
                flag[top] =false;
                stack[top++] = now;
               
                now = now->left;
            }
            bTree *p = stack[top - 1];
            if(!flag[top - 1])
            {
                //说明now是p的左子节点，那么此时应该先看父亲的右子节点
                flag[top - 1] = true;
                now = p->right;
            }
            else{
                //说明now是p的右子节点，说明以p为根节点的这课子树已经遍历完毕了
                bTree *q = now;
                int pathlength = 0;
                for(int i = 0 ; i < top ; i++)
                {
                    pathlength += stack[i]->key;
                }
                //此时检查这条路径是否符合要求
                    if(expectNumber == pathlength)
                    {
                        for(int i = 0 ; i< top ; i++)
                        {
                            std::cout << stack[i]->key << " ";
                        }
						std::cout << "\n";
                    }
                while(top && q == p->right)
                {
                    top--;
                    q = p;
                    p = stack[top - 1];
                }
                if(top == 0)
                    break;
                else{
                    now = p->right;
                }
            }
        }
    }

bool iterativeSearch(int key)
{
	bTree *now = root;
	while(now)
	{
		if(now->key == key)
		{
			return true;
		}
		else{
			now = now->key > key ? now->left : now->right;
		}
	}
	return false;
}

bool search(bTree *root, int key)
{
	if(!root)
		return false;
	if(root->key > key)
		return search(root->left, key);
	else if(root->key < key)
		return search(root->right, key);
	else
		return true;
}

//二叉树的插入很简单，直接在null的位置插入即可,但是注意root为null的情况！
void iterativeInsert(int key)
{
	bTree *node = new bTree();
	node->key = key;
	bTree *parent = 0;
	bTree *now = root;
	while(!isNull(now))
	{
		parent = now;
		if(now->key < key)
		{
			now = now->right;
		}
		else{
			now = now->left;
		}
	}
	node->key >= parent->key ? parent->right = node : parent->left = node;
	node->p = parent;
	//这里加上如果树为空的判断
	if(isNull(parent))
		root = node;
	//这里不需要加left标志位，因为可以利用parent的key和node的key的大小关系来判断左右！
	node->left = 0;
	node->right = (bTree *)1;

}


bTree *initNode(bTree *p, int key)
{
	bTree *n = new bTree();
	n->key = key;
	n->left = 0;
	n->right = (bTree *)1;
	n->p = p;
	if(isNull(p))
		root = n;
	return n;
}

void insert(bTree *r, int key)
{
	//这里也要加上对r的判断
	if(r == root && isNull(r))
	{
		r = new bTree();
		r->key = key;
		r->left = 0;
		r->right = (bTree *)1;
		r->p = 0;
		return ;
	}
	if(r->key < key)
	{
		if(isNull(r->right))
		{
			r->right = initNode(r, key);
		}
		else{
			insert(r->right, key);
		}
	}
	else{
		if(isNull(r->left))
		{
			r->left = initNode(r, key);
		}
		else{
			insert(r->left, key);
		}
	}
}

//这个过程主要是用v替代u原来的位置，是建立u的父亲与v之间的关系，u的儿子与v之间的关系由调用者完成
void transplant(bTree *u, bTree *v)
{
	if(isNull(u))
	{
		//同样，如果u是一个null，那就不用考虑transplant了，因为根本得不到u的父亲的信息
		return ;
	}
	//重写了一遍transplant，坑还是挺多的，但是只要把每种情况想清楚就好
	//这里注意u是root节点时的设置
	if(isNull(u->p))
	{
		root = v; 
	}
	else{
		u->p->left == u ? u->p->left = v : u->p->right = v;
	}
	//又忘记考虑v是null的情况了！
	if(!isNull(v))
		v->p = u->p;


}

//注意删除并不一定是把后继作为它的代替！只有左右节点都存在时才是后继代替
//删除还是挺难写的，很容易想不清，需要注意后继节点的一些特点
void del(bTree *node)
{
	if(isNull(node))
		return ;

	if(isNull(node->left))
	{
		//因为left是null了，所以也不需要设置left与node->right节点的关系了
		transplant(node, node->right);
	}
	else if(isNull(node->right))
	{
		transplant(node, node->left);
	}
	else{
		//在看了邓老师的数据结构后，这里其实不需要transplant，直接类似于链表那样，既然实质是交换两个节点，那么直接交换这两个节点的数据项即可！
		//只有它的后继可以继承它的位置，后继一定在右子树中，后继一定是没有左子节点的,且后继如果不是node的右子节点，那么后继一定是某个父亲的左子节点!
		bTree *success = successor(node);
		bTree *successright = success->right;
		//1.如果success是node的右子节点，那么①建立success和node的左子节点之间的关系②建立success与node的父亲之间的关系
		//2.如果success不是node右子节点，那么①建立success的右子节点和success的父亲之间的关系（因为右子节点要代替success）②建立success与node的左和右子节点之间的关系③建立success与node的父亲之间的关系
		//所以公共的部分就是①success与node父亲之间的关系②success与node左子节点之间的关系
		//两个节点之间建立关系的过程分为两步①子节点的p设置为父节点②父节点的left或者是right设置为子节点
		if(!(success == node->right))
		{	
			transplant(success, success->right);
			//但是node原来就有右子节点，且不是success，所以这里需要建立好success与node的左右子节点之间的关系！
			success->right = node->right;
			node->right->p = success;
		}
		success->left = node->left;
		node->left->p = success;
		transplant(node, success);
	}
}

bTree *buildByWalk(int pre[], int in[], int preleft, int preright, int inleft, int inright)
{
	//根据pre的首个元素，把in集合分成左子树和右子树两部分，分别递归执行后得到相应的子树，然后与当前root合并
	if(preleft > preright)
		return 0;
	int rootkey = pre[preleft];
	int rootindex;
	for(int i = inleft ; i <= inright ; i++)
	{
		if(in[i] == rootkey)
		{
			rootindex = i;
			break;
		}
	}
	int prerightbegin = rootindex - inleft + preleft + 1;
	bTree *left = buildByWalk(pre, in, preleft + 1, prerightbegin - 1, inleft, rootindex - 1);
	bTree *right = buildByWalk(pre, in, prerightbegin, preright, rootindex + 1, inright);
	bTree *r = new bTree();
	r->key = rootkey;
	r->left = left;
	r->right = right;
	r->p = 0;
	if(!isNull(left))
		left->p = r;
	if(!isNull(right))
		right->p = r;
	else{
		r->right = (bTree *)1;
	}
	return r;
}
//判断b是不是a的子结构 待写！！
bool bisParta(bTree *a, bTree *b)
{
	return false;
}
//递归实现二叉树的镜像
bTree *recursionImageBinaryTree(bTree *root)
{
	//先交换左右子节点，然后对于左子树和右子树再分别进行交换
	if(!isNull(root))
	{
		bTree *temp = root->left;
		root->left = root->right;
		root->right = temp;
		recursionImageBinaryTree(root->left);
		recursionImageBinaryTree(root->right);
	}
	return root;
}
//循环实现二叉树的镜像，应该需要队列遍历	
void iterativeImageBinaryTree()
{

}

//判断一个后序遍历序列是否合法，即是否可以找到对应的二叉树的后序遍历和它相同
//思路就是：  这个序列合法 等价于 这个序列左右子树的结点都满足二叉树性质 && 这个序列的左子树合法 && 这个序列的右子树合法
//递归就行了
bool checkPostorder(int a[], int left, int right)
{
	if(!a)
		return false;
	if(left >= right)
		return true;
	int r = a[right];
	int split = right - 1;
	//首先要找到左右子树的分界线，split表示左子树的结束节点
	while(split >= left && a[split] >= r)
		split--;
	//找到分界线之后，首先需要检查左子树中每个结点是否小于r，因为右子树已经遍历过了所以不用检查
	bool result = true;
	for(int i = split ; i >= left ; i--)
	{
		result = result && (a[i] < r);
	}
	//如果result已经是false，那么直接return，不用再分别检查左右子树了
	if(!result)
		return result;
	//然后分别检查左右子树
	result = result && checkPostorder(a, left, split);
	if(!result)
		return result;
	result = result && checkPostorder(a, split + 1, right - 1);
	return result;
}

//二叉树中和为某一值的路径,待写 准备用递归，或者用栈，其实就是前序遍历
void sumEqualValuePath(bTree *r, int value, int path[], int pathsize)
{

}

bTree *tranlateTree2List(bTree *pRootOfTree)
{
	if(!pRootOfTree)
            return NULL;
    bTree *left = tranlateTree2List(pRootOfTree->left);
    bTree *right = tranlateTree2List(pRootOfTree->right);
    if(left)
    {
        bTree *l = left;
        while(l->right)
            l = l->right;
        l->right = pRootOfTree;
        pRootOfTree->left = l;
    }
    else{
        left = pRootOfTree;
        pRootOfTree->left = NULL;
    }
    pRootOfTree->right = right;
    if(right)
        right->left = pRootOfTree;
    return left;
	
}

bTree *translateTree(bTree *pRootOfTree)
{
	if(!pRootOfTree)
            return NULL;
        bTree *stack[50] = {0};
        int top = 0;
        bTree *now = pRootOfTree;
        bTree *head = 0;
        bTree *last = 0;
        while(now || top)
        {
            while(now)
            {
                stack[top++] = now;
                now = now->left;
            }
            now = stack[--top];
            if(!head)
            {
                head = now;
                last = now;
                head->left = 0;
            }
            else{
                last->right = now;
                now->left = last;
                last = now;
            }
            now = now->right;
        }
        last->right = 0;
        return head;
}
//不要使用深度函数，会重复遍历，深度用指针作为参数传递
	bool isBalance(bTree *root, int *depth)
    {
        if(!root)
        {
            *depth = 0;
            return true;
        }
        int left, right;
        if(isBalance(root->left, &left) && isBalance(root->right, &right))
        {
            int dis = left - right;
            if(dis <= 1 && dis >= -1)
            {
                *depth = left > right ? left + 1 : right + 1;
                return true;
            }
        }
        return false;
    }
//递归深度
int TreeDepth(bTree* pRoot)
    {
        if(!pRoot)
            return 0;
        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        return left > right ? left + 1 : right + 1;
    }
//二叉树的下一个中序遍历的节点，这个真的很锻炼人，对中序遍历又有了很深刻的认识
bTree* GetNext(bTree* pNode)
    {
        if(!pNode)
            return NULL;

            //如果左子节点为空，那么按照中序遍历，此时应该遍历其右子树的最左子节点，太傻比了
            if(pNode->right)
            {
                //所以要首先得到其右子树啊
				pNode = pNode->right;
				while(pNode->left)
					pNode = pNode->left;
				return pNode;
            }
            //如果右子节点也为空，那么此时应该按照自己是父亲的左子节点还是右子节点来区别
            if(pNode->p)
            {
                if(pNode->p->left == pNode)
                {
                    //是自己父亲的左子节点，那么此时应该遍历自己的父亲
                    return pNode->p;
                }
                else{
                    //是自己父亲的右子节点，说明此时应该一直回溯，
                    bTree *p = pNode->p;
                    bTree *q = pNode;
                    while(p && p->right == q)
                    {
                        q = p;
                        p = p->p;
                    }
                    return p;
                }
            }
            else{
                //如果父亲节点为空，那么只能说明这是一个根节点，且该树只有一个根节点
                return NULL;
            }
    }

//二叉树是否对称，对称定义为二叉树如果和它的镜像相等，那么就说这个二叉树对称
bool isSym(bTree *pRoot1, bTree *pRoot2)
    {
        if(pRoot1)
        {
            if(pRoot2)
            {
                //两个子树的根节点都存在
                //那么对称等价于根节点相同，且左子树的右儿子与右子树的左儿子对称，左子树的左儿子与右子树的右儿子对称
                return pRoot1->key == pRoot2->key && isSym(pRoot1->right, pRoot2->left) && isSym(pRoot1->left, pRoot2->right);
            }
            else{
                //左子树存在，右子树不存在
                return false;
            }
        }
        else{
            if(pRoot2)
            {
                return false;
            }
            else{
                return true;
            }
        }
    }
bool isSymmetrical(bTree* pRoot)
    {
        if(!pRoot)
            return true;
        return isSym(pRoot->left, pRoot->right);
    }

//这个题真的是折磨人啊
std::vector<std::vector<int> > Print(bTree* pRoot) {
        std::vector<std::vector<int> > result;
		if(!pRoot)	 return result;
        std::vector<bTree *> row;
        row.push_back(pRoot);
        int line = 1;
        while(row.size())
        {
            std::vector<bTree *> newrow;
            std::vector<int> *level = new std::vector<int>();
            if(line & 1)
            {
                for(int i = 0 ; i < row.size() ; i++)
                {
                    level->push_back(row[i]->key);
                    
                }
            }
            else{
                for(int i = row.size() - 1 ; i >= 0 ; i--)
                {
                    level->push_back(row[i]->key);
                }
               
            }
            for(int i = 0 ; i < row.size() ; i++)
                {
                    if(!isNull(row[i]->left))
                        newrow.push_back(row[i]->left);
                    if(!isNull(row[i]->right))
                        newrow.push_back(row[i]->right);
                }
            row.clear();
            for(int i = 0 ; i < newrow.size() ; i++)
            {
                row.push_back(newrow[i]);
            }
            result.push_back(*level);
            line++;
        }
        return result;
    }
/*int main(int argc, char* argv[])
{
	root = new bTree();
	root->key = 12;
	root->p = 0;
	root->left = new bTree();
	root->left->key = 8;
	root->left->p = root;
	root->left->left = new bTree();
	root->left->left->p = root->left;
	root->left->left->key = 6;
	root->left->left->left = 0;
	root->left->left->right = (bTree *)1;
	root->left->right = new bTree();
	root->left->right->p = root->left;
	root->left->right->key = 10;
	root->left->right->left = new bTree();
	root->left->right->left->key = 9;
	root->left->right->left->p = root->left->right;
	root->left->right->left->right = (bTree *)1;
	root->left->right->left->left = new bTree();
	root->left->right->left->left->key = 8;
	root->left->right->left->left->p = root->left->right->left;
	root->left->right->left->left->left = 0;
	root->left->right->left->left->right = (bTree *)1;
	root->left->right->right = (bTree *)1;
	root->right = new bTree();
	root->right->p = root;
	root->right->key = 20;
	root->right->left = new bTree();
	root->right->left->p = root->right;
	root->right->left->key = 18;
	root->right->left->left = 0;
	root->right->left->right = (bTree *)1;
	root->right->right = new bTree();
	root->right->right->p = root->right;
	root->right->right->key = 30;
	root->right->right->left = 0;
	root->right->right->right = (bTree *)1;

	std::vector<std::vector<int>> result = Print(root);
	for(int i = 0 ; i < result.size(); i ++)
	{
		for(int j = 0 ; j < result[i].size() ; j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << "\n";
	}
	return 0;
}*/

