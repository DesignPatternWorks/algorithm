
/*******************头文件包含****************/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "linear_list_lk.h"


LkLinearList::LkLinearList()
{
	initList();
}

void LkLinearList::initList(void)
{
	_list = (LNode*)malloc(sizeof(LNode)); // 开辟头结点
	MALLOC_FAIL_NO_RETURN(_list);

	_list->data = 0;
	_list->pNext = NULL;

	_size = 0;
}

LkLinearList::~LkLinearList()
{
	LNode *insertNode = _list->pNext; 

	while (!NULL_PTR(insertNode)) // 与头插入法类似，每次删除head结点的直接后驱
	{
		_list->pNext = insertNode->pNext; // 修改head结点的直接后驱为待删除结点的直接后驱
		free(insertNode);              // 释放删除结点
		insertNode = _list->pNext; // 重新判断下一个待删除结点
	}

	free(_list); // 释放头结点
}


void LkLinearList::insertList(ElemType &e)
{
	LNode *newNode = (LNode*)malloc(sizeof(LNode));
	MALLOC_FAIL_NO_RETURN(newNode);

// 头插入法，每次把新元素插入到第一个位置(即作为链表的头结点的直接后驱)，此时元素在链表中顺序和插入顺序是相反的
	newNode->data = e;
	newNode->pNext = _list->pNext; // 钩链，从右到左
	_list->pNext = newNode;  //新元素插入到第一个位置(即作为链表的头结点的直接后驱)
	_size++;

// 尾插入法，每次把新元素插入到尾结点的后面(即作为链表的尾结点的直接后驱)，此时元素在链表中顺序和插入顺序是一致的
	//newNode->data = e;
	//newNode->pNext = NULL;
	//LNode *loopNode = _list;
	//while (!NULL_PTR(loopNode->pNext))
	//{
	//	loopNode = loopNode->pNext;
	//}  // 不断向后遍历找到尾结点(其pNext == NULL)
	//loopNode->pNext = newNode;
	//_size++;
}

ElemType LkLinearList::deleteList(ElemType &key)
{
	LNode *loopNode = _list;
	bool isFound = false;
	ElemType e;

	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // 空默认返回头结点的默认值0
	}

	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key)
		{
			//find data域为key元素删除之
			isFound = true;
			LNode* delNode = loopNode->pNext; // 先保存删除结点的指针，待后续释放内存
			e = delNode->data; // 保存删除结点loopNode->pnext的data值
			loopNode->pNext = delNode->pNext; // 直接修改delNode（loopNode->pnext）的直接前驱loopNode结点的直接后驱
			free(delNode);
			_size--;
			return e;
		}
		loopNode = loopNode->pNext;
	}
	if (!isFound)
	{
		std::cout << "not found key: " << key << std::endl;
		return _list->data; // 未找到默认返回头结点的默认值0
	}
}

bool LkLinearList::isListEmpty(void)
{
	return (NULL == _list->pNext); // or _size == 0
}

// 获取索引为index的元素，从0开始（且不包括head结点，即从head的直接后驱结点开始算起）
ElemType& LkLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // 空情况默认返回第一个结点的data, 默认值为0
	}

	if (index > _size-1)
	{
		std::cout << "index is out of range[0," << _size-1 << "] " << std::endl;
		return _list->data; // 默认返回第一个结点的data, 默认值为0
	}

	int loopIndex = 0;  //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopIndex == index)
		{
			return loopNode->pNext->data; //loopNode->pNext为当前结点，返回该结点的值
		}
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
}

// 获取第一个元素值为key的索引index，从0开始
int LkLinearList::locateList(ElemType &key)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key) //loopNode->pNext为当前结点，返回该结点的索引
		{
			isFound = true;
			return loopIndex; 
		}
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _list->data; // 未找到情况默认返回第一个结点data, 默认值为0
	}
}

int LkLinearList::getListSize(void)
{
	return _size;
}

void LkLinearList::traverseList(void)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return;
	}

	std::cout << "_________begin traverse____________" << std::endl;
	int loopIndex = 0; //loopIndex从0开始
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		std::cout << "listNode[" << loopIndex <<"]: " << loopNode->pNext->data << "  "; //loopNode->pNext为当前结点，返回该结点的索引
		loopNode = loopNode->pNext; // 循环下一个结点
		loopIndex++; // 记录有效结点(除head结点以外)数目+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}






/*******************宏定义****************/

/*******************数据类型定义****************/

/*******************变量声明****************/

/*******************内部函数声明****************/

/*******************外部函数声明****************/


/*******************函数实现****************/
/**********************************************
Function Name: CreateList_Lk_Reverse 
Function Ref：逆序创建单链表
Input：aeInput[], wLen
OutPut：ptLkList
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL CreateList_Lk_Reverse(LNode **ptLkList,ElemType aeInput[],WORD16 wLen)//或 pLNode &node
{
	int nLoop = 0;
	*ptLkList = NULL;  //空链表
	LNode   *ptNewNode = NULL; //每次新构建的链表节点

	for (nLoop = wLen - 1; nLoop >= 0; nLoop--) //从数组索引最大的开始（倒序）
	{
		ptNewNode = (LNode *)malloc(sizeof(LNode));
		if (NULL == ptNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptNewNode->data  = aeInput[nLoop];
		ptNewNode->pNext = (*ptLkList); //每次插入到链表头之前
         *ptLkList       =  ptNewNode; //改变链表头
	}
	return TRUE;
}
/**********************************************
Function Name: CreateList_DbLk_Reverse 
Function Ref：逆序创建双链表
Input：aeInput[], wLen
OutPut：ptDbLkList
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL CreateList_DbLk_Reverse(DbLNode **ptDbLkList, ElemType aeInput[], WORD16 wLen)
{
	int nLoop = 0;
	*ptDbLkList = NULL;  //空链表
	DbLNode   *ptDbNewNode = NULL; //每次新构建的链表节点

	for (nLoop = wLen - 1; nLoop >= 0; nLoop--) //从数组索引最大的开始（倒序）
	{
		ptDbNewNode = (DbLNode *)malloc(sizeof(DbLNode));
		if (NULL == ptDbNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptDbNewNode->data     = aeInput[nLoop];
		ptDbNewNode->pPrior   = NULL;
		ptDbNewNode->pNext    = (*ptDbLkList); //每次插入到链表头之前,新Node前驱、后驱变了
		if (NULL != (*ptDbLkList))
		{
		    (*ptDbLkList)->pPrior = ptDbNewNode;  //头Node的前驱变了
		}
		(*ptDbLkList)         =  ptDbNewNode; //改变链表头
	}
	return TRUE;
}
/**********************************************
Function Name: CreateList_CircularLk_Reverse 
Function Ref：顺序创建循环单链表
Input：aeInput[], wLen
OutPut：ptLkList
Return：BOOL
Author:By Frank_tly
PS：循环链表通常在表中的第一个结点之前附加一个“头结点”，并令“头指针”指向最后一个结点
**********************************************/
BOOL CreateList_CircularLk(LNode **ptLkList,ElemType aeInput[],WORD16 wLen)//或 pLNode &node
{
	int nLoop = 0;
	*ptLkList = NULL;  //空链表
	LNode   *ptNewNode = NULL; //每次新构建的链表节点
	LNode   *ptHeadNode = NULL;

	ptHeadNode = (LNode*)malloc(sizeof(LNode));  //生成头结点
	if (NULL == ptHeadNode)
	{
		printf("Malloc Failed\n");
		return FALSE;
	}
	ptHeadNode->data  = INVALID_VALUE;
	ptHeadNode->pNext = ptHeadNode;
	(*ptLkList) = ptHeadNode; // 空的循环链表的时候 *ptLkList（头指针指向头结点，头结点也是最后一个结点此时)
	for (nLoop = 0; nLoop < wLen; nLoop++) //从数组索引最大的开始（倒序）
	{
		ptNewNode = (LNode *)malloc(sizeof(LNode));
		if (NULL == ptNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptNewNode->data    = aeInput[nLoop];
		ptNewNode->pNext   = ptHeadNode;  //ptNewNode->pNext指向表头结点，形成环
        (*ptLkList)->pNext =  ptNewNode; //把ptNewNode 插入到*ptLkList（头指针），也是最后一个结点之后
		(*ptLkList)        = ptNewNode;  //每次使*ptLkList（头指针）指向表的最后一个结点
	}
	return TRUE;
}

/**********************************************
Function Name: LocateElem_Lk 
Function Ref：在单链表中，根据给定的data域查找Node
Input：ptLkList, element
OutPut：无
Return：LNode* //若未找到，则返回NULL
Author:By Frank_tly
**********************************************/
LNode* LocateElem_Lk(LNode *ptLkList,ElemType element)
{
	LNode *pTmp = ptLkList;

	while ((NULL != pTmp) && (pTmp->data != element))
	{
		pTmp = pTmp->pNext;
	}
	return pTmp; 
}
/**********************************************
Function Name: LocateElem_DbLk 
Function Ref：在双链表中，根据给定的data域查找Node
Input：ptDbLkList, element
OutPut：无
Return：DbLNode* //若未找到，则返回NULL
Author:By Frank_tly
**********************************************/
DbLNode* LocateElem_DbLk(DbLNode *ptDbLkList,ElemType element)
{
	DbLNode *pDbTmp = ptDbLkList;

	while ((NULL != pDbTmp) && (pDbTmp->data != element))
	{
		pDbTmp = pDbTmp->pNext;
	}
	return pDbTmp; 
}

/**********************************************
Function Name: LocateElem_CircularLk 
Function Ref：在循环单链表中，根据给定的data域查找Node
Input：ptLkList, element
OutPut：无
Return：LNode* //若未找到，则返回NULL
Author:By Frank_tly
**********************************************/
LNode* LocateElem_CircularLk(LNode *ptLkList,ElemType element)
{
	LNode *pHead = ptLkList->pNext; //头结点
	LNode *pTmp  = pHead->pNext;  //第一个结点

	while ((pHead != pTmp) && (pTmp->data != element))
	{
		pTmp = pTmp->pNext;
	}
	if (pHead == pTmp)
	{
		return NULL;
	}
	else
	{
	    return pTmp; 
	}
}
/**********************************************
Function Name: IsExistNode_Lk 
Function Ref：在单链表中，查找是否存在给定的Node
Input：ptLkList, ptTargetNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsExistNode_Lk(LNode *ptLkList,LNode *ptTargetNode)
{
	LNode *pTmp = ptLkList;

	while ((NULL != pTmp) && (pTmp != ptTargetNode))
	{
		pTmp = pTmp->pNext;
	}
	if (NULL == pTmp)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/**********************************************
Function Name: IsExistNode_DbLk 
Function Ref：在双链表中，查找是否存在给定的Node
Input：ptDbLkList, ptDbTargetNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsExistNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbTargetNode)
{
	DbLNode *pDbTmp = ptDbLkList;

	while ((NULL != pDbTmp) && (pDbTmp != ptDbTargetNode))
	{
		pDbTmp = pDbTmp->pNext;
	}
	if (NULL == pDbTmp)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/**********************************************
Function Name: IsExistNode_CircularLk 
Function Ref：在循环单链表中，查找是否存在给定的Node
Input：ptLkList, ptTargetNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsExistNode_CircularLk(LNode *ptLkList,LNode *ptTargetNode)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp =  pHead->pNext;

	while ((pHead != pTmp) && (pTmp != ptTargetNode))
	{
		pTmp = pTmp->pNext;
	}
	if (pHead == pTmp)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
/**********************************************
Function Name: IsListEmpty_Lk 
Function Ref：判断单链表是否为空
Input：ptLkList
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_Lk(LNode *ptLkList)
{
	return (NULL == ptLkList)? TRUE : FALSE;
}

/**********************************************
Function Name: IsListEmpty_DbLk 
Function Ref：判断双链表是否为空
Input：ptLkList
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_DbLk(DbLNode *ptDbLkList)
{
	return (NULL == ptDbLkList)? TRUE : FALSE;
}
/**********************************************
Function Name: IsListEmpty_CircularLk 
Function Ref：判断循环单链表是否为空
Input：ptLkList
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_CircularLk(LNode *ptLkList)
{
	LNode  *pHead = ptLkList->pNext;
	return (pHead == ptLkList)? TRUE : FALSE;
}
/**********************************************
Function Name: GetLength_Lk 
Function Ref：得到单链表的长度
Input：ptLkList
OutPut：无
Return：WORD16
Author:By Frank_tly
**********************************************/
WORD16 GetLength_Lk(LNode *ptLkList)
{
	LNode *pTmp = ptLkList;
	WORD16 wLen = 0;
	while (NULL != pTmp)
	{
		pTmp = pTmp->pNext;
		wLen++;
	}
	return wLen;
}
/**********************************************
Function Name: GetLength_DbLk 
Function Ref：得到双链表的长度
Input：ptLkList
OutPut：无
Return：WORD16
Author:By Frank_tly
**********************************************/
WORD16 GetLength_DbLk(DbLNode *ptDbLkList)
{
	DbLNode *pDbTmp = ptDbLkList;
	WORD16 wLen = 0;
	while (NULL != pDbTmp)
	{
		pDbTmp = pDbTmp->pNext;
		wLen++;
	}
	return wLen;
}
/**********************************************
Function Name: GetLength_CircularLk 
Function Ref：得到循环单链表的长度
Input：ptLkList
OutPut：无
Return：WORD16
Author:By Frank_tly
**********************************************/
WORD16 GetLength_CircularLk(LNode *ptLkList)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp  = pHead->pNext;
	WORD16 wLen  = 0;
	while (pHead != pTmp)
	{
		pTmp = pTmp->pNext;
		wLen++;
	}
	return wLen;
}
/**********************************************
Function Name: BehindInsertNode_Lk 
Function Ref：单链表在ReferNode之后插入InsertNode
Input：ptLkList,ptReferNode,ptInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_Lk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pTmp = ptLkList;
	while ((pTmp != ptReferNode) && (NULL != pTmp))  //找到ptReferNode在链表中的位置
	{
		pTmp = pTmp->pNext;
	}
	if (NULL == pTmp)    //找不到ptReferNode在链表中的位置
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //在ptReferNode（==pTmp）之后插入Node
	{                          
		//ptInsertNode->pNext = pTmp->pNext; 
		//pTmp->pNext = ptInsertNode;
		//OR pTmp 用ptReferNode代替，两者一样与ptLkList也关联起来了
		ptInsertNode->pNext = ptReferNode->pNext; 
		ptReferNode->pNext = ptInsertNode;
		return TRUE;
	}
}

/**********************************************
Function Name: BehindInsertNode_DbLk 
Function Ref：双链表在DbReferNode之后插入DbInsertNode
Input：ptDbLkList,ptDbReferNode,ptDbInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbReferNode,DbLNode *ptDbInsertNode)
{
	DbLNode *pDbTmp = ptDbLkList;
	while ((pDbTmp != ptDbReferNode) && (NULL != pDbTmp))  //找到ptReferNode在链表中的位置
	{
		pDbTmp = pDbTmp->pNext;
	}
	if (NULL == pDbTmp)    //找不到ptReferNode在链表中的位置
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //在ptDbReferNode（==pDbTmp）之后插入Node
	{                          
		//OR pDbTmp 用ptDbReferNode代替，两者一样与ptDbLkList也关联起来了
		if (NULL != (ptDbReferNode->pNext)) //不是最后一个Node
		{
           (ptDbReferNode->pNext)->pPrior = ptDbInsertNode;    //先参考后面点的前驱  !!!!!注意顺序，从后面到前面的顺序写，不然ptDbReferNode->pNext值会变，1,4顺序
		}
		ptDbInsertNode->pPrior = ptDbReferNode;
		ptDbInsertNode->pNext = ptDbReferNode->pNext;  //插入Node的前驱、后驱		
		ptDbReferNode->pNext = ptDbInsertNode;    //参考点的后驱
		return TRUE;
	}
}

/**********************************************
Function Name: BehindInsertNode_CircularLk 
Function Ref：循环单链表在ReferNode之后插入InsertNode
Input：ptLkList,ptReferNode,ptInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_CircularLk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp  = pHead->pNext;
	if (ptLkList == ptReferNode) //若参考点是最后一个结点
	{
		ptInsertNode->pNext = ptReferNode->pNext;
		ptReferNode->pNext  = ptInsertNode;
		ptLkList            = ptInsertNode;
	}
	while ((pTmp != ptReferNode) && (pHead != pTmp))  //找到ptReferNode在链表中的位置
	{
		pTmp = pTmp->pNext;
	}
	if (pHead == pTmp)    //找不到ptReferNode在链表中的位置
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //在ptReferNode（==pTmp）之后插入Node
	{                          
		//ptInsertNode->pNext = pTmp->pNext; 
		//pTmp->pNext = ptInsertNode;
		//OR pTmp 用ptReferNode代替，两者一样与ptLkList也关联起来了
		ptInsertNode->pNext = ptReferNode->pNext; 
		ptReferNode->pNext = ptInsertNode;
		return TRUE;
	}
}
/**********************************************
Function Name: BeforeInsertNode_Lk 
Function Ref：单链表在ReferNode之前插入InsertNode
Input：ptLkList,ptReferNode,ptInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_Lk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pTmp = NULL;
	if (ptLkList == ptReferNode)  //若参考Node是链表的头结点
	{
		ptInsertNode->pNext = ptLkList;
		ptLkList = ptInsertNode;
		return TRUE;
	} 
	else
	{
		pTmp = ptLkList;
		while ((pTmp->pNext) != ptReferNode && (NULL != (pTmp->pNext))) //找到ptReferNode在链表中的位置(直接前驱pTmp),此处是单链表，必须用pTmp->pNext来判断
		{
			pTmp = pTmp->pNext;
		}
		if (NULL == pTmp->pNext)    //找不到ptReferNode在链表中的位置
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //在ptReferNode（==pTmp->pNext）之前(pTmp之后)插入Node
		{
			//ptInsertNode->pNext = pTmp->pNext;
			//pTmp->pNext = ptInsertNode;
		    //OR pTmp->pNext 用ptReferNode代替，两者一样与ptLkList也关联起来了
			ptInsertNode->pNext = ptReferNode;
			pTmp->pNext = ptInsertNode;			
			return TRUE;
		}       
	}
}

/**********************************************
Function Name: BeforeInsertNode_DbLk 
Function Ref：双链表在DbReferNode之前插入DbInsertNode
Input：ptDbLkList,ptDbReferNode,ptDbInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbReferNode,DbLNode *ptDbInsertNode)
{
	DbLNode *pDbTmp = NULL;
	if (ptDbLkList == ptDbReferNode)  //若参考Node是链表的头结点
	{
		ptDbInsertNode->pPrior = NULL;
		ptDbInsertNode->pNext  = ptDbLkList; //Insert Node的前驱、后驱
		ptDbLkList->pPrior = ptDbInsertNode; //Refer Node的前驱
		ptDbLkList = ptDbInsertNode;  //改变头指针
		return TRUE;
	} 
	else
	{
		pDbTmp = ptDbLkList->pNext;
		while (pDbTmp!= ptDbReferNode && (NULL != pDbTmp)) //找到ptDbReferNode在链表中的位置，不需要变量存前驱了
		{
			pDbTmp = pDbTmp->pNext;
		}
		if (NULL == pDbTmp)    //找不到ptDbReferNode在链表中的位置
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //在ptDbReferNode（==pDbTmp）之前插入Node
		{
		    //OR pDbTmp用ptReferNode代替，两者一样与ptDbLkList也关联起来了
			(ptDbReferNode->pPrior)->pNext = ptDbInsertNode;  //参考点之前Node 的后驱，1,4顺序
			 ptDbInsertNode->pPrior        = ptDbReferNode->pPrior;
		     ptDbInsertNode->pNext         = ptDbReferNode;  // 插入点Node的前驱、后驱
			 ptDbReferNode->pPrior         = ptDbInsertNode; // 参考点的前驱	
			return TRUE;
		}       
	}
}

/**********************************************
Function Name: BeforeInsertNode_CircularLk 
Function Ref：循环单链表在ReferNode之前插入InsertNode
Input：ptLkList,ptReferNode,ptInsertNode
OutPut：无
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_CircularLk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp = NULL;
	if (pHead == ptReferNode)  //若参考Node是循环链表的头结点
	{
		ptInsertNode->pNext = pHead;
		ptLkList->pNext     = ptInsertNode;
		ptLkList            = ptInsertNode;
		return TRUE;
	} 
	else
	{
		pTmp = pHead->pNext; //第一个结点
		while ((pTmp->pNext) != ptReferNode && (pHead != (pTmp->pNext))) //找到ptReferNode在链表中的位置(直接前驱pTmp),此处是单链表，必须用pTmp->pNext来判断
		{
			pTmp = pTmp->pNext;
		}
		if (pHead == pTmp->pNext)    //找不到ptReferNode在链表中的位置
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //在ptReferNode（==pTmp->pNext）之前(pTmp之后)插入Node
		{
			//ptInsertNode->pNext = pTmp->pNext;
			//pTmp->pNext = ptInsertNode;
		    //OR pTmp->pNext 用ptReferNode代替，两者一样与ptLkList也关联起来了
			ptInsertNode->pNext = ptReferNode;
			pTmp->pNext = ptInsertNode;			
			return TRUE;
		}       
	}
}
/**********************************************
Function Name: DeleteNode_Lk 
Function Ref：单链表删除DeleteNode
Input：ptLkList,ptDeleteNode
OutPut：pelement 被删Node的数据域
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_Lk(LNode *ptLkList,LNode *ptDeleteNode,ElemType *pelement)
{
	LNode *pTmp = NULL;
	if (ptLkList == ptDeleteNode) //被删的为头结点
	{	
		*pelement = ptDeleteNode->data;
		ptLkList = ptDeleteNode->pNext;//重新赋值头结点
		free(ptDeleteNode) ;
		ptDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pTmp = ptLkList; 
		while (((pTmp->pNext) != ptDeleteNode) && ( NULL != (pTmp->pNext))) //从第二个Node开始,找到ptDeleteNode在链表中的位置(直接前驱pTmp)
		{
			pTmp = pTmp->pNext;
		}
		if (NULL == (pTmp->pNext))    //找不到ptDeleteNode在链表中的位置
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //删除ptDeleteNode（== pTmp->pNext）,
		{                          
			//pTmp->pNext = pTmp->pNext->pNext; 
			//OR pTmp->pNext 用ptDeleteNode代替(DeleteNode之前Node是pTmp)，两者一样与ptLkList也关联起来了
			*pelement = ptDeleteNode->data;
			pTmp->pNext = ptDeleteNode->pNext;
			free(ptDeleteNode) ;
			ptDeleteNode = NULL;
			return TRUE;
		}	
	}	
}

/**********************************************
Function Name: DeleteNode_DbLk 
Function Ref：双链表删除DbDeleteNode
Input：ptDbLkList,ptDbDeleteNode
OutPut：pelement 被删Node的数据域
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbDeleteNode,ElemType *pelement)
{
	DbLNode *pDbTmp = NULL;
	if (ptDbLkList == ptDbDeleteNode) //被删的为头结点
	{	
		*pelement = ptDbDeleteNode->data;
		ptDbLkList = ptDbDeleteNode->pNext;//重新赋值头结点
		free(ptDbDeleteNode) ;
		ptDbDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pDbTmp = ptDbLkList->pNext; 
		while ((pDbTmp != ptDbDeleteNode) && ( NULL != pDbTmp)) //从第二个Node开始,找到ptDbDeleteNode在链表中的位置
		{
			pDbTmp = pDbTmp->pNext;
		}
		if (NULL == pDbTmp)    //找不到ptDbDeleteNode在链表中的位置
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //删除ptDbDeleteNode（pDbTmp）, 
		{                          

			//OR pDbTmp用ptDbDeleteNode代替，两者一样与ptLkList也关联起来了
			*pelement = ptDbDeleteNode->data;
			(ptDbDeleteNode->pPrior)->pNext = ptDbDeleteNode->pNext;
			(ptDbDeleteNode->pNext)->pPrior = ptDbDeleteNode->pPrior;
			free(ptDbDeleteNode) ;
			ptDbDeleteNode = NULL;
			return TRUE;
		}	
	}	
}

/**********************************************
Function Name: DeleteNode_CircularLk 
Function Ref：循环单链表删除DeleteNode
Input：ptLkList,ptDeleteNode
OutPut：pelement 被删Node的数据域
Return：BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_CircularLk(LNode *ptLkList,LNode *ptDeleteNode,ElemType *pelement)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmpDeletePre = pHead->pNext;
	LNode *pTmp = NULL;
	if (ptLkList == ptDeleteNode) //被删的为头指针指向的结点，即最后一个结点
	{	
		*pelement = ptDeleteNode->data;
		while ((pTmpDeletePre->pNext) != ptDeleteNode) //找到DeleteNode的前一个结点pTempDeletePre
		{
			pTmpDeletePre = pTmpDeletePre->pNext;
		}
		pTmpDeletePre->pNext = ptDeleteNode->pNext;//ptDeleteNode->pNext == ptLkList->pNext == pHead
		ptLkList = pTmpDeletePre;//重新赋值头指针，最后一个结点
		free(ptDeleteNode) ;
		ptDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pTmp = pHead->pNext; 
		while (((pTmp->pNext) != ptDeleteNode) && ( pHead != (pTmp->pNext))) //从第二个Node开始,找到ptDeleteNode在链表中的位置(直接前驱pTmp)
		{
			pTmp = pTmp->pNext;
		}
		if (pHead == (pTmp->pNext))    //找不到ptDeleteNode在链表中的位置
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //删除ptDeleteNode（== pTmp->pNext）,
		{                          
			//pTmp->pNext = pTmp->pNext->pNext; 
			//OR pTmp->pNext 用ptDeleteNode代替(DeleteNode之前Node是pTmp)，两者一样与ptLkList也关联起来了
			*pelement = ptDeleteNode->data;
			pTmp->pNext = ptDeleteNode->pNext;
			free(ptDeleteNode) ;
			ptDeleteNode = NULL;
			return TRUE;
		}	
	}	
}
/**********************************************
Function Name: TraverseList_Lk 
Function Ref：打印单链表的所有数据域
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void TraverseList_Lk(LNode *ptLkList)
{
	LNode *pTmp = ptLkList;
	WORD16 wLen = 0;

	if (NULL == ptLkList)
	{
		printf("Empty Link List!\n");
		return;
	}
	while (NULL != pTmp)
	{
		if (0 == (wLen%3))
		{
			printf("\n");
		}
		printf("LkList[%d] = %d\t",wLen,pTmp->data);
		pTmp = pTmp->pNext;
		wLen++;
	}
	printf("\n");
}

/**********************************************
Function Name: TraverseList_Lk 
Function Ref：打印双链表的所有数据域
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void TraverseList_DbLk(DbLNode *ptDbLkList)
{
	DbLNode *pDbTmp = ptDbLkList;
	WORD16 wLen = 0;

	if (NULL == ptDbLkList)
	{
		printf("Empty DbLink List!\n");
		return;
	}
	while (NULL != pDbTmp)
	{
		if (0 == (wLen%3))
		{
			printf("\n");
		}
		printf("DbLkList[%d] = %d\t",wLen,pDbTmp->data);
		pDbTmp = pDbTmp->pNext;
		wLen++;
	}
	printf("\n");
}

/**********************************************
Function Name: TraverseList_CircularLk 
Function Ref：打印循环单链表的所有数据域
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void TraverseList_CircularLk(LNode *ptLkList)
{
	if (!ptLkList)
	{
		printf("ptLkList is Null!\n");
		return;
	}
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp  = pHead->pNext;
	WORD16 wLen  = 0;

	if (pHead == ptLkList)
	{
		printf("Empty CircularLink List!\n");
		return;
	}
	while (pHead != pTmp)
	{
		if (0 == (wLen%3))
		{
			printf("\n");
		}
		printf("CircularLkList[%d] = %d\t",wLen,pTmp->data);
		pTmp = pTmp->pNext;
		wLen++;
	}
	printf("\n");
}
/**********************************************
Function Name: InvertList_Lk 
Function Ref：逆序单链表

p1 ----> p2 ---->p3 ....->pn

pn ----> pn-1 ---->pn-2 ....->p1
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void InvertList_Lk(LNode **ptLkList)       //改变了ptLkList指针地址的值，所以要传指针的指针
{
	LNode *pTmp = (*ptLkList);
	*ptLkList = NULL;  //设定逆置后的链表初态为NULL
	LNode *pRemoveLNode = NULL;	
    while (NULL != pTmp)
    {
		pRemoveLNode        = pTmp; //当前移动的Node 
		pTmp                = pTmp->pNext;              //注意位置，不能放在后面，不然找不到pTmp->pNext了
		pRemoveLNode->pNext = *ptLkList; //插入到表头
		*ptLkList            = pRemoveLNode;	//表头始终在最前面   ,类似于逆序创建链表
                     
    }
}

/**********************************************
Function Name: InvertList_DbLk 
Function Ref：逆序双链表
逆序前：
p1 ----> p2 ---->p3 ....->pn
逆序后：
pn ----> pn-1 ---->pn-2 ....->p1
Input：ptDbLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void InvertList_DbLk(DbLNode **ptDbLkList)
{
	DbLNode *pDbTmp = (*ptDbLkList);
	DbLNode *pDbRemoveLNode = NULL;

	(*ptDbLkList) = NULL;	
    while (NULL != pDbTmp)
    {
		pDbRemoveLNode = pDbTmp; //当前移动的Node
		pDbTmp = pDbTmp->pNext; // 在第4句修改了指向的下个Node，故指针移动放在此处
		pDbRemoveLNode->pPrior = NULL;       
		pDbRemoveLNode->pNext  = (*ptDbLkList); //插入到表头，当前移动点的前驱和后驱,
		if (NULL != (*ptDbLkList))
		{
			(*ptDbLkList)->pPrior     = pDbRemoveLNode; // 非第一个Node时，参考点（表头）的前驱
		}    
		(*ptDbLkList) = pDbRemoveLNode;	//表头始终在最前面   ,类似于逆序创建链表                             
    }
}
/**********************************************
Function Name: InvertList_CircularLk 
Function Ref：逆序循环单链表
 逆序前：
   -----------------------------------
  ↓                                 ↑
pHead ---> p1 ----> p2 ---->p3 ....->pn <----ptLkList  

逆序后：
   -----------------------------------
  ↑                                 ↓
pHead <--- p1 <--- p2 <--- p3....<---pn
           ↑
		   ptLkList

Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void InvertList_CircularLk(LNode **ptLkList)       //改变了ptLkList指针地址的值，所以要传指针的指针
{
	LNode *pHead        = (*ptLkList)->pNext; //头结点不变
	LNode *pTmpPre      = pHead;              // 新循环链表第一个结点位置指针
	LNode *pTmp         = pHead->pNext;       //旧的循环链表的遍历的当前位置指针
	LNode *pRemoveLNode = NULL;	
	(*ptLkList)         = pHead->pNext;      //第一个结点是新链表的最后一个结点了      
	
    while(pHead != pTmp)
    {
		pRemoveLNode        = pTmp; //当前移动的Node 
		pTmp                = pTmp->pNext;              //注意位置，不能放在后面，不然找不到pTmp->pNext了
		pRemoveLNode->pNext = pTmpPre; 
		pTmpPre             = pRemoveLNode;	//每次pHead更新到新的位置                 
    };
	pTmp->pNext             = pTmpPre;     // 此时pTmp == pHead，连成闭环
}
/**********************************************
Function Name: DestroyList_Lk 
Function Ref：销毁单链表
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void DestroyList_Lk(LNode **ptLkList)
{
	LNode *pTmp = NULL;
	while (NULL != (*ptLkList))
	{
		pTmp = (*ptLkList);
		(*ptLkList) = (*ptLkList)->pNext;
		free(pTmp);
		pTmp = NULL;
	}
}

/**********************************************
Function Name: DestroyList_DbLk 
Function Ref：销毁双链表
Input：ptDbLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void DestroyList_DbLk(DbLNode **ptDbLkList)
{
	DbLNode *pDbTmp = NULL;
	while (NULL != (*ptDbLkList))
	{
		pDbTmp = (*ptDbLkList);
		(*ptDbLkList) = (*ptDbLkList)->pNext;
		free(pDbTmp);
		pDbTmp = NULL;
	}
}

/**********************************************
Function Name: DestroyList_CircularLk 
Function Ref：销毁循环单链表
Input：ptLkList
OutPut：无
Return：无
Author:By Frank_tly
**********************************************/
void DestroyList_CircularLk(LNode **ptLkList)
{
	LNode *pHead      = (*ptLkList)->pNext;
	LNode *pTmp       = pHead->pNext;
	LNode *pTmpDelete = NULL;
	while (pHead != pTmp)
	{
		pTmpDelete    = pTmp;
		pTmp          = pTmp->pNext;
		pHead->pNext  = pTmp;
		free(pTmpDelete);
		pTmpDelete    = NULL;
	}
	free(pHead);           //释放头结点
	pHead             = NULL;
}