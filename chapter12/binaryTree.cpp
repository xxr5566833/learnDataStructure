#include "stdafx.h"

//������
//���ݽṹ����
typedef struct BTREE{
	struct BTREE *p;
	struct BTREE *left;
	struct BTREE *right;
	int key;
}bTree;
//���ڵ���һ��ȫ�ֽڵ�
bTree *root;
//Ϊ�˺��淽�㣬���һ���ڵ���Ҷ���Ϊnull����ô�Ұ���Ϊ 1����0����ʾ���ӽڵ�Ϊnull�����ֿ�
bool isNull(bTree *root)
{
	return root ==0 || (int)root == 1;
}
//����rootΪ���ڵ��������СԪ�ص�ѭ��ʵ��
bTree *iterativeMinimum(bTree *root)
{
	//ע���root�ļ�飬��Ϊ������ֱ���õ���root->left
	if(isNull(root))
		return 0;
	while(!isNull(root->left))
	{
		root = root->left;
	}
	return root;
}
//����rootΪ���ڵ��������СԪ�صĵݹ�ʵ��
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
//���Ԫ��
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

//����Ĺ���˼ά������һ���ڵ㣬�����Ǹ��׽������ӽڵ�Ҳ���������ӽڵ�
//�������ڵ����丸�׵����ӽڵ㣬��ô����ڵ��Ǳ��丸�״󣬵��ǣ����ܱ�֤����ڵ�ĸ��׵ĸ����ڵ�����Ĵ�С��ϵ
//���
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
//ǰ��
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

//�ݹ�
void recursionPreorderWalk(bTree *root)
{
	if(root)
	{
		std::cout << root->key << std::endl;
		recursionPreorderWalk(root->left);
		recursionPreorderWalk(root->right);
	}
}


//�ǵݹ�+ջ
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
//��ʹ��ջֻ��һ��last������ɵ��������
void inorderWalkNotUseStack()
{
	bTree *last = 0;
	bTree *now = root;
	while(!isNull(now))
	{
		//last��Զ��¼now�ĸ��ף����now��null����ô����Ҳ����ͨ��now->p���õ������ǵ�now��nullʱ����Ҫͨ��last�õ�
		if(!isNull(now))
		{
			//���now����null
			last = now;
			now = now->left;
		}
		else{
			//��ʱ˵��now��null����ônow�����Ǹ��׵����ӽڵ㣬Ҳ���������ӽڵ�
			//���now��ĳ���ڵ�����ӽڵ㣬��ô˵����ʱӦ���now�ĸ��ף�Ȼ������nowΪ���׵�right
			//���now��ĳ���ڵ�����ӽڵ㣬����now����null����ô����last���ݣ�����һ��ʼ����д��һ��ѭ����ר�Ż��ݵ���һ����Ҫ�����Ľ�㴦
			//������ʵ����Ҫ��ֱ�ӽ�������ѭ���Ϳ��ԣ���ȫ���Ը���last��last���׵Ĺ�ϵ����now����Ϊ0����1������ֱ������Ϊlast��������ظ���������ʵ
			//������൱�ڰ�last���ڵ���������Ϊnull����Ϊ�������Ѿ��������ˣ�
			if(now == (bTree *)1)
			{
				//˵��now�����ӽڵ㣬��ô��ʱ��last�����ĸ����Ƿ�Ϊroot���������ô˵��������ɣ�������ǣ���ô��֮ǰ�����ü���
				if(last == root)
				{
					break;
				}
				else{
					//last����root����ô���ݼ���
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
//ʹ��minimum������successor��ɵ��������
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
		//�����������ֱ�Ӵ�ջ��ȡ�ڵ㣬��Ϊ�������������ң�����Ҫ�����ҽ��
		//���Ժ��������ȡ���νڵ㣬��ôʲôʱ���������ڵ��أ���Ҫ����ǰ�ڵ��ջ���ڵ�Ĺ�ϵ��
		//�����ǰ�ڵ���ջ���ڵ�����ӽڵ㣬��ôֱ�������ӽڵ㣬
		//������뷨��
		//�����ǰ�ڵ���ջ���������ӽڵ㣬��ô���������nowΪ0,��Ϊ��ȡ������ջ�����һ�����Ѿ����������ӽڵ��
		//�����ᵼ����ѭ������ȷ������Ӧ���ǲ��ϵ�ȡ��ջ��Ԫ�أ����˵��ǰ�����ջ��Ԫ�ص����ӽڵ㣬��ô��������
		bTree *p = stack[top - 1];
		if(now == 0)
		{
			//˵��now��ջ���������ӽڵ�
			now = p->right;
		}
		else{
			//˵��now��ջ���������ӽڵ�
			bTree *q = now;
			
			while(top && q == p->right)
			{
				//����Ҫ���ϵ�ȡ���Ѿ�������������ĸ��ڵ�
				top--;
				std::cout << p->key << std::endl;
				q = p;
				p = stack[top - 1];
			}
			if(top == 0)
			{
				//���top��0˵���Ѿ����������
				break;
			}
			else{
				//��ʱp��ջ��Ԫ�أ�q��p�����ӽڵ㣬��ʱ����nowΪp�����ӽڵ�
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
                //˵��now��p�����ӽڵ㣬��ô��ʱӦ���ȿ����׵����ӽڵ�
                flag[top - 1] = true;
                now = p->right;
            }
            else{
                //˵��now��p�����ӽڵ㣬˵����pΪ���ڵ����������Ѿ����������
                bTree *q = now;
                int pathlength = 0;
                for(int i = 0 ; i < top ; i++)
                {
                    pathlength += stack[i]->key;
                }
                //��ʱ�������·���Ƿ����Ҫ��
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

//�������Ĳ���ܼ򵥣�ֱ����null��λ�ò��뼴��,����ע��rootΪnull�������
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
	//������������Ϊ�յ��ж�
	if(isNull(parent))
		root = node;
	//���ﲻ��Ҫ��left��־λ����Ϊ��������parent��key��node��key�Ĵ�С��ϵ���ж����ң�
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
	//����ҲҪ���϶�r���ж�
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

//���������Ҫ����v���uԭ����λ�ã��ǽ���u�ĸ�����v֮��Ĺ�ϵ��u�Ķ�����v֮��Ĺ�ϵ�ɵ��������
void transplant(bTree *u, bTree *v)
{
	if(isNull(u))
	{
		//ͬ�������u��һ��null���ǾͲ��ÿ���transplant�ˣ���Ϊ�����ò���u�ĸ��׵���Ϣ
		return ;
	}
	//��д��һ��transplant���ӻ���ͦ��ģ�����ֻҪ��ÿ�����������ͺ�
	//����ע��u��root�ڵ�ʱ������
	if(isNull(u->p))
	{
		root = v; 
	}
	else{
		u->p->left == u ? u->p->left = v : u->p->right = v;
	}
	//�����ǿ���v��null������ˣ�
	if(!isNull(v))
		v->p = u->p;


}

//ע��ɾ������һ���ǰѺ����Ϊ���Ĵ��棡ֻ�����ҽڵ㶼����ʱ���Ǻ�̴���
//ɾ������ͦ��д�ģ��������벻�壬��Ҫע���̽ڵ��һЩ�ص�
void del(bTree *node)
{
	if(isNull(node))
		return ;

	if(isNull(node->left))
	{
		//��Ϊleft��null�ˣ�����Ҳ����Ҫ����left��node->right�ڵ�Ĺ�ϵ��
		transplant(node, node->right);
	}
	else if(isNull(node->right))
	{
		transplant(node, node->left);
	}
	else{
		//�ڿ��˵���ʦ�����ݽṹ��������ʵ����Ҫtransplant��ֱ��������������������Ȼʵ���ǽ��������ڵ㣬��ôֱ�ӽ����������ڵ��������ɣ�
		//ֻ�����ĺ�̿��Լ̳�����λ�ã����һ�����������У����һ����û�����ӽڵ��,�Һ���������node�����ӽڵ㣬��ô���һ����ĳ�����׵����ӽڵ�!
		bTree *success = successor(node);
		bTree *successright = success->right;
		//1.���success��node�����ӽڵ㣬��ô�ٽ���success��node�����ӽڵ�֮��Ĺ�ϵ�ڽ���success��node�ĸ���֮��Ĺ�ϵ
		//2.���success����node���ӽڵ㣬��ô�ٽ���success�����ӽڵ��success�ĸ���֮��Ĺ�ϵ����Ϊ���ӽڵ�Ҫ����success���ڽ���success��node��������ӽڵ�֮��Ĺ�ϵ�۽���success��node�ĸ���֮��Ĺ�ϵ
		//���Թ����Ĳ��־��Ǣ�success��node����֮��Ĺ�ϵ��success��node���ӽڵ�֮��Ĺ�ϵ
		//�����ڵ�֮�佨����ϵ�Ĺ��̷�Ϊ�������ӽڵ��p����Ϊ���ڵ�ڸ��ڵ��left������right����Ϊ�ӽڵ�
		if(!(success == node->right))
		{	
			transplant(success, success->right);
			//����nodeԭ���������ӽڵ㣬�Ҳ���success������������Ҫ������success��node�������ӽڵ�֮��Ĺ�ϵ��
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
	//����pre���׸�Ԫ�أ���in���Ϸֳ��������������������֣��ֱ�ݹ�ִ�к�õ���Ӧ��������Ȼ���뵱ǰroot�ϲ�
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
//�ж�b�ǲ���a���ӽṹ ��д����
bool bisParta(bTree *a, bTree *b)
{
	return false;
}
//�ݹ�ʵ�ֶ������ľ���
bTree *recursionImageBinaryTree(bTree *root)
{
	//�Ƚ��������ӽڵ㣬Ȼ��������������������ٷֱ���н���
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
//ѭ��ʵ�ֶ������ľ���Ӧ����Ҫ���б���	
void iterativeImageBinaryTree()
{

}

//�ж�һ��������������Ƿ�Ϸ������Ƿ�����ҵ���Ӧ�Ķ������ĺ������������ͬ
//˼·���ǣ�  ������кϷ� �ȼ��� ����������������Ľ�㶼������������� && ������е��������Ϸ� && ������е��������Ϸ�
//�ݹ������
bool checkPostorder(int a[], int left, int right)
{
	if(!a)
		return false;
	if(left >= right)
		return true;
	int r = a[right];
	int split = right - 1;
	//����Ҫ�ҵ����������ķֽ��ߣ�split��ʾ�������Ľ����ڵ�
	while(split >= left && a[split] >= r)
		split--;
	//�ҵ��ֽ���֮��������Ҫ�����������ÿ������Ƿ�С��r����Ϊ�������Ѿ������������Բ��ü��
	bool result = true;
	for(int i = split ; i >= left ; i--)
	{
		result = result && (a[i] < r);
	}
	//���result�Ѿ���false����ôֱ��return�������ٷֱ�������������
	if(!result)
		return result;
	//Ȼ��ֱ�����������
	result = result && checkPostorder(a, left, split);
	if(!result)
		return result;
	result = result && checkPostorder(a, split + 1, right - 1);
	return result;
}

//�������к�Ϊĳһֵ��·��,��д ׼���õݹ飬������ջ����ʵ����ǰ�����
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
//��Ҫʹ����Ⱥ��������ظ������������ָ����Ϊ��������
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
//�ݹ����
int TreeDepth(bTree* pRoot)
    {
        if(!pRoot)
            return 0;
        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        return left > right ? left + 1 : right + 1;
    }
//����������һ����������Ľڵ㣬�����ĺܶ����ˣ���������������˺���̵���ʶ
bTree* GetNext(bTree* pNode)
    {
        if(!pNode)
            return NULL;

            //������ӽڵ�Ϊ�գ���ô���������������ʱӦ�ñ������������������ӽڵ㣬̫ɵ����
            if(pNode->right)
            {
                //����Ҫ���ȵõ�����������
				pNode = pNode->right;
				while(pNode->left)
					pNode = pNode->left;
				return pNode;
            }
            //������ӽڵ�ҲΪ�գ���ô��ʱӦ�ð����Լ��Ǹ��׵����ӽڵ㻹�����ӽڵ�������
            if(pNode->p)
            {
                if(pNode->p->left == pNode)
                {
                    //���Լ����׵����ӽڵ㣬��ô��ʱӦ�ñ����Լ��ĸ���
                    return pNode->p;
                }
                else{
                    //���Լ����׵����ӽڵ㣬˵����ʱӦ��һֱ���ݣ�
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
                //������׽ڵ�Ϊ�գ���ôֻ��˵������һ�����ڵ㣬�Ҹ���ֻ��һ�����ڵ�
                return NULL;
            }
    }

//�������Ƿ�Գƣ��Գƶ���Ϊ��������������ľ�����ȣ���ô��˵����������Գ�
bool isSym(bTree *pRoot1, bTree *pRoot2)
    {
        if(pRoot1)
        {
            if(pRoot2)
            {
                //���������ĸ��ڵ㶼����
                //��ô�ԳƵȼ��ڸ��ڵ���ͬ�������������Ҷ�����������������ӶԳƣ�������������������������Ҷ��ӶԳ�
                return pRoot1->key == pRoot2->key && isSym(pRoot1->right, pRoot2->left) && isSym(pRoot1->left, pRoot2->right);
            }
            else{
                //���������ڣ�������������
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

//������������ĥ�˰�
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

