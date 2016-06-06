
/*******************ͷ�ļ�����****************/
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
	_list = (LNode*)malloc(sizeof(LNode)); // ����ͷ���
	MALLOC_FAIL_NO_RETURN(_list);

	_list->data = 0;
	_list->pNext = NULL;

	_size = 0;
}

LkLinearList::~LkLinearList()
{
	LNode *insertNode = _list->pNext; 

	while (!NULL_PTR(insertNode)) // ��ͷ���뷨���ƣ�ÿ��ɾ��head����ֱ�Ӻ���
	{
		_list->pNext = insertNode->pNext; // �޸�head����ֱ�Ӻ���Ϊ��ɾ������ֱ�Ӻ���
		free(insertNode);              // �ͷ�ɾ�����
		insertNode = _list->pNext; // �����ж���һ����ɾ�����
	}

	free(_list); // �ͷ�ͷ���
}


void LkLinearList::insertList(ElemType &e)
{
	LNode *newNode = (LNode*)malloc(sizeof(LNode));
	MALLOC_FAIL_NO_RETURN(newNode);

// ͷ���뷨��ÿ�ΰ���Ԫ�ز��뵽��һ��λ��(����Ϊ�����ͷ����ֱ�Ӻ���)����ʱԪ����������˳��Ͳ���˳�����෴��
	newNode->data = e;
	newNode->pNext = _list->pNext; // ���������ҵ���
	_list->pNext = newNode;  //��Ԫ�ز��뵽��һ��λ��(����Ϊ�����ͷ����ֱ�Ӻ���)
	_size++;

// β���뷨��ÿ�ΰ���Ԫ�ز��뵽β���ĺ���(����Ϊ�����β����ֱ�Ӻ���)����ʱԪ����������˳��Ͳ���˳����һ�µ�
	//newNode->data = e;
	//newNode->pNext = NULL;
	//LNode *loopNode = _list;
	//while (!NULL_PTR(loopNode->pNext))
	//{
	//	loopNode = loopNode->pNext;
	//}  // �����������ҵ�β���(��pNext == NULL)
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
		return _list->data; // ��Ĭ�Ϸ���ͷ����Ĭ��ֵ0
	}

	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key)
		{
			//find data��ΪkeyԪ��ɾ��֮
			isFound = true;
			LNode* delNode = loopNode->pNext; // �ȱ���ɾ������ָ�룬�������ͷ��ڴ�
			e = delNode->data; // ����ɾ�����loopNode->pnext��dataֵ
			loopNode->pNext = delNode->pNext; // ֱ���޸�delNode��loopNode->pnext����ֱ��ǰ��loopNode����ֱ�Ӻ���
			free(delNode);
			_size--;
			return e;
		}
		loopNode = loopNode->pNext;
	}
	if (!isFound)
	{
		std::cout << "not found key: " << key << std::endl;
		return _list->data; // δ�ҵ�Ĭ�Ϸ���ͷ����Ĭ��ֵ0
	}
}

bool LkLinearList::isListEmpty(void)
{
	return (NULL == _list->pNext); // or _size == 0
}

// ��ȡ����Ϊindex��Ԫ�أ���0��ʼ���Ҳ�����head��㣬����head��ֱ�Ӻ�����㿪ʼ����
ElemType& LkLinearList::getListByIndex(int index)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return _list->data; // �����Ĭ�Ϸ��ص�һ������data, Ĭ��ֵΪ0
	}

	if (index > _size-1)
	{
		std::cout << "index is out of range[0," << _size-1 << "] " << std::endl;
		return _list->data; // Ĭ�Ϸ��ص�һ������data, Ĭ��ֵΪ0
	}

	int loopIndex = 0;  //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopIndex == index)
		{
			return loopNode->pNext->data; //loopNode->pNextΪ��ǰ��㣬���ظý���ֵ
		}
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
}

// ��ȡ��һ��Ԫ��ֵΪkey������index����0��ʼ
int LkLinearList::locateList(ElemType &key)
{
	if (isListEmpty())
	{
		std::cout << "list is empty" << std::endl;
		return -1; // -1
	}

	bool isFound = false;
	int loopIndex = 0; //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		if (loopNode->pNext->data == key) //loopNode->pNextΪ��ǰ��㣬���ظý�������
		{
			isFound = true;
			return loopIndex; 
		}
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}

	if (!isFound)
	{
		std::cout << "not found key is " << key << std::endl;
		return _list->data; // δ�ҵ����Ĭ�Ϸ��ص�һ�����data, Ĭ��ֵΪ0
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
	int loopIndex = 0; //loopIndex��0��ʼ
	LNode *loopNode = _list;
	while (!NULL_PTR(loopNode->pNext))
	{
		std::cout << "listNode[" << loopIndex <<"]: " << loopNode->pNext->data << "  "; //loopNode->pNextΪ��ǰ��㣬���ظý�������
		loopNode = loopNode->pNext; // ѭ����һ�����
		loopIndex++; // ��¼��Ч���(��head�������)��Ŀ+1
	}
	std::cout << std::endl;
	std::cout << "_________end traverse____________" << std::endl;
}






/*******************�궨��****************/

/*******************�������Ͷ���****************/

/*******************��������****************/

/*******************�ڲ���������****************/

/*******************�ⲿ��������****************/


/*******************����ʵ��****************/
/**********************************************
Function Name: CreateList_Lk_Reverse 
Function Ref�����򴴽�������
Input��aeInput[], wLen
OutPut��ptLkList
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL CreateList_Lk_Reverse(LNode **ptLkList,ElemType aeInput[],WORD16 wLen)//�� pLNode &node
{
	int nLoop = 0;
	*ptLkList = NULL;  //������
	LNode   *ptNewNode = NULL; //ÿ���¹���������ڵ�

	for (nLoop = wLen - 1; nLoop >= 0; nLoop--) //�������������Ŀ�ʼ������
	{
		ptNewNode = (LNode *)malloc(sizeof(LNode));
		if (NULL == ptNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptNewNode->data  = aeInput[nLoop];
		ptNewNode->pNext = (*ptLkList); //ÿ�β��뵽����ͷ֮ǰ
         *ptLkList       =  ptNewNode; //�ı�����ͷ
	}
	return TRUE;
}
/**********************************************
Function Name: CreateList_DbLk_Reverse 
Function Ref�����򴴽�˫����
Input��aeInput[], wLen
OutPut��ptDbLkList
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL CreateList_DbLk_Reverse(DbLNode **ptDbLkList, ElemType aeInput[], WORD16 wLen)
{
	int nLoop = 0;
	*ptDbLkList = NULL;  //������
	DbLNode   *ptDbNewNode = NULL; //ÿ���¹���������ڵ�

	for (nLoop = wLen - 1; nLoop >= 0; nLoop--) //�������������Ŀ�ʼ������
	{
		ptDbNewNode = (DbLNode *)malloc(sizeof(DbLNode));
		if (NULL == ptDbNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptDbNewNode->data     = aeInput[nLoop];
		ptDbNewNode->pPrior   = NULL;
		ptDbNewNode->pNext    = (*ptDbLkList); //ÿ�β��뵽����ͷ֮ǰ,��Nodeǰ������������
		if (NULL != (*ptDbLkList))
		{
		    (*ptDbLkList)->pPrior = ptDbNewNode;  //ͷNode��ǰ������
		}
		(*ptDbLkList)         =  ptDbNewNode; //�ı�����ͷ
	}
	return TRUE;
}
/**********************************************
Function Name: CreateList_CircularLk_Reverse 
Function Ref��˳�򴴽�ѭ��������
Input��aeInput[], wLen
OutPut��ptLkList
Return��BOOL
Author:By Frank_tly
PS��ѭ������ͨ���ڱ��еĵ�һ�����֮ǰ����һ����ͷ��㡱�����ͷָ�롱ָ�����һ�����
**********************************************/
BOOL CreateList_CircularLk(LNode **ptLkList,ElemType aeInput[],WORD16 wLen)//�� pLNode &node
{
	int nLoop = 0;
	*ptLkList = NULL;  //������
	LNode   *ptNewNode = NULL; //ÿ���¹���������ڵ�
	LNode   *ptHeadNode = NULL;

	ptHeadNode = (LNode*)malloc(sizeof(LNode));  //����ͷ���
	if (NULL == ptHeadNode)
	{
		printf("Malloc Failed\n");
		return FALSE;
	}
	ptHeadNode->data  = INVALID_VALUE;
	ptHeadNode->pNext = ptHeadNode;
	(*ptLkList) = ptHeadNode; // �յ�ѭ�������ʱ�� *ptLkList��ͷָ��ָ��ͷ��㣬ͷ���Ҳ�����һ������ʱ)
	for (nLoop = 0; nLoop < wLen; nLoop++) //�������������Ŀ�ʼ������
	{
		ptNewNode = (LNode *)malloc(sizeof(LNode));
		if (NULL == ptNewNode)
		{
			printf("Malloc Failed\n");
			return FALSE;
		}
		ptNewNode->data    = aeInput[nLoop];
		ptNewNode->pNext   = ptHeadNode;  //ptNewNode->pNextָ���ͷ��㣬�γɻ�
        (*ptLkList)->pNext =  ptNewNode; //��ptNewNode ���뵽*ptLkList��ͷָ�룩��Ҳ�����һ�����֮��
		(*ptLkList)        = ptNewNode;  //ÿ��ʹ*ptLkList��ͷָ�룩ָ�������һ�����
	}
	return TRUE;
}

/**********************************************
Function Name: LocateElem_Lk 
Function Ref���ڵ������У����ݸ�����data�����Node
Input��ptLkList, element
OutPut����
Return��LNode* //��δ�ҵ����򷵻�NULL
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
Function Ref����˫�����У����ݸ�����data�����Node
Input��ptDbLkList, element
OutPut����
Return��DbLNode* //��δ�ҵ����򷵻�NULL
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
Function Ref����ѭ���������У����ݸ�����data�����Node
Input��ptLkList, element
OutPut����
Return��LNode* //��δ�ҵ����򷵻�NULL
Author:By Frank_tly
**********************************************/
LNode* LocateElem_CircularLk(LNode *ptLkList,ElemType element)
{
	LNode *pHead = ptLkList->pNext; //ͷ���
	LNode *pTmp  = pHead->pNext;  //��һ�����

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
Function Ref���ڵ������У������Ƿ���ڸ�����Node
Input��ptLkList, ptTargetNode
OutPut����
Return��BOOL
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
Function Ref����˫�����У������Ƿ���ڸ�����Node
Input��ptDbLkList, ptDbTargetNode
OutPut����
Return��BOOL
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
Function Ref����ѭ���������У������Ƿ���ڸ�����Node
Input��ptLkList, ptTargetNode
OutPut����
Return��BOOL
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
Function Ref���жϵ������Ƿ�Ϊ��
Input��ptLkList
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_Lk(LNode *ptLkList)
{
	return (NULL == ptLkList)? TRUE : FALSE;
}

/**********************************************
Function Name: IsListEmpty_DbLk 
Function Ref���ж�˫�����Ƿ�Ϊ��
Input��ptLkList
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_DbLk(DbLNode *ptDbLkList)
{
	return (NULL == ptDbLkList)? TRUE : FALSE;
}
/**********************************************
Function Name: IsListEmpty_CircularLk 
Function Ref���ж�ѭ���������Ƿ�Ϊ��
Input��ptLkList
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL IsListEmpty_CircularLk(LNode *ptLkList)
{
	LNode  *pHead = ptLkList->pNext;
	return (pHead == ptLkList)? TRUE : FALSE;
}
/**********************************************
Function Name: GetLength_Lk 
Function Ref���õ�������ĳ���
Input��ptLkList
OutPut����
Return��WORD16
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
Function Ref���õ�˫����ĳ���
Input��ptLkList
OutPut����
Return��WORD16
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
Function Ref���õ�ѭ��������ĳ���
Input��ptLkList
OutPut����
Return��WORD16
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
Function Ref����������ReferNode֮�����InsertNode
Input��ptLkList,ptReferNode,ptInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_Lk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pTmp = ptLkList;
	while ((pTmp != ptReferNode) && (NULL != pTmp))  //�ҵ�ptReferNode�������е�λ��
	{
		pTmp = pTmp->pNext;
	}
	if (NULL == pTmp)    //�Ҳ���ptReferNode�������е�λ��
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //��ptReferNode��==pTmp��֮�����Node
	{                          
		//ptInsertNode->pNext = pTmp->pNext; 
		//pTmp->pNext = ptInsertNode;
		//OR pTmp ��ptReferNode���棬����һ����ptLkListҲ����������
		ptInsertNode->pNext = ptReferNode->pNext; 
		ptReferNode->pNext = ptInsertNode;
		return TRUE;
	}
}

/**********************************************
Function Name: BehindInsertNode_DbLk 
Function Ref��˫������DbReferNode֮�����DbInsertNode
Input��ptDbLkList,ptDbReferNode,ptDbInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbReferNode,DbLNode *ptDbInsertNode)
{
	DbLNode *pDbTmp = ptDbLkList;
	while ((pDbTmp != ptDbReferNode) && (NULL != pDbTmp))  //�ҵ�ptReferNode�������е�λ��
	{
		pDbTmp = pDbTmp->pNext;
	}
	if (NULL == pDbTmp)    //�Ҳ���ptReferNode�������е�λ��
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //��ptDbReferNode��==pDbTmp��֮�����Node
	{                          
		//OR pDbTmp ��ptDbReferNode���棬����һ����ptDbLkListҲ����������
		if (NULL != (ptDbReferNode->pNext)) //�������һ��Node
		{
           (ptDbReferNode->pNext)->pPrior = ptDbInsertNode;    //�Ȳο�������ǰ��  !!!!!ע��˳�򣬴Ӻ��浽ǰ���˳��д����ȻptDbReferNode->pNextֵ��䣬1,4˳��
		}
		ptDbInsertNode->pPrior = ptDbReferNode;
		ptDbInsertNode->pNext = ptDbReferNode->pNext;  //����Node��ǰ��������		
		ptDbReferNode->pNext = ptDbInsertNode;    //�ο���ĺ���
		return TRUE;
	}
}

/**********************************************
Function Name: BehindInsertNode_CircularLk 
Function Ref��ѭ����������ReferNode֮�����InsertNode
Input��ptLkList,ptReferNode,ptInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BehindInsertNode_CircularLk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp  = pHead->pNext;
	if (ptLkList == ptReferNode) //���ο��������һ�����
	{
		ptInsertNode->pNext = ptReferNode->pNext;
		ptReferNode->pNext  = ptInsertNode;
		ptLkList            = ptInsertNode;
	}
	while ((pTmp != ptReferNode) && (pHead != pTmp))  //�ҵ�ptReferNode�������е�λ��
	{
		pTmp = pTmp->pNext;
	}
	if (pHead == pTmp)    //�Ҳ���ptReferNode�������е�λ��
	{
		printf("Refer Node is not included in LkList!\n");
		return FALSE;
	}
	else              //��ptReferNode��==pTmp��֮�����Node
	{                          
		//ptInsertNode->pNext = pTmp->pNext; 
		//pTmp->pNext = ptInsertNode;
		//OR pTmp ��ptReferNode���棬����һ����ptLkListҲ����������
		ptInsertNode->pNext = ptReferNode->pNext; 
		ptReferNode->pNext = ptInsertNode;
		return TRUE;
	}
}
/**********************************************
Function Name: BeforeInsertNode_Lk 
Function Ref����������ReferNode֮ǰ����InsertNode
Input��ptLkList,ptReferNode,ptInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_Lk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pTmp = NULL;
	if (ptLkList == ptReferNode)  //���ο�Node�������ͷ���
	{
		ptInsertNode->pNext = ptLkList;
		ptLkList = ptInsertNode;
		return TRUE;
	} 
	else
	{
		pTmp = ptLkList;
		while ((pTmp->pNext) != ptReferNode && (NULL != (pTmp->pNext))) //�ҵ�ptReferNode�������е�λ��(ֱ��ǰ��pTmp),�˴��ǵ�����������pTmp->pNext���ж�
		{
			pTmp = pTmp->pNext;
		}
		if (NULL == pTmp->pNext)    //�Ҳ���ptReferNode�������е�λ��
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //��ptReferNode��==pTmp->pNext��֮ǰ(pTmp֮��)����Node
		{
			//ptInsertNode->pNext = pTmp->pNext;
			//pTmp->pNext = ptInsertNode;
		    //OR pTmp->pNext ��ptReferNode���棬����һ����ptLkListҲ����������
			ptInsertNode->pNext = ptReferNode;
			pTmp->pNext = ptInsertNode;			
			return TRUE;
		}       
	}
}

/**********************************************
Function Name: BeforeInsertNode_DbLk 
Function Ref��˫������DbReferNode֮ǰ����DbInsertNode
Input��ptDbLkList,ptDbReferNode,ptDbInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbReferNode,DbLNode *ptDbInsertNode)
{
	DbLNode *pDbTmp = NULL;
	if (ptDbLkList == ptDbReferNode)  //���ο�Node�������ͷ���
	{
		ptDbInsertNode->pPrior = NULL;
		ptDbInsertNode->pNext  = ptDbLkList; //Insert Node��ǰ��������
		ptDbLkList->pPrior = ptDbInsertNode; //Refer Node��ǰ��
		ptDbLkList = ptDbInsertNode;  //�ı�ͷָ��
		return TRUE;
	} 
	else
	{
		pDbTmp = ptDbLkList->pNext;
		while (pDbTmp!= ptDbReferNode && (NULL != pDbTmp)) //�ҵ�ptDbReferNode�������е�λ�ã�����Ҫ������ǰ����
		{
			pDbTmp = pDbTmp->pNext;
		}
		if (NULL == pDbTmp)    //�Ҳ���ptDbReferNode�������е�λ��
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //��ptDbReferNode��==pDbTmp��֮ǰ����Node
		{
		    //OR pDbTmp��ptReferNode���棬����һ����ptDbLkListҲ����������
			(ptDbReferNode->pPrior)->pNext = ptDbInsertNode;  //�ο���֮ǰNode �ĺ�����1,4˳��
			 ptDbInsertNode->pPrior        = ptDbReferNode->pPrior;
		     ptDbInsertNode->pNext         = ptDbReferNode;  // �����Node��ǰ��������
			 ptDbReferNode->pPrior         = ptDbInsertNode; // �ο����ǰ��	
			return TRUE;
		}       
	}
}

/**********************************************
Function Name: BeforeInsertNode_CircularLk 
Function Ref��ѭ����������ReferNode֮ǰ����InsertNode
Input��ptLkList,ptReferNode,ptInsertNode
OutPut����
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL BeforeInsertNode_CircularLk(LNode *ptLkList,LNode *ptReferNode,LNode *ptInsertNode)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmp = NULL;
	if (pHead == ptReferNode)  //���ο�Node��ѭ�������ͷ���
	{
		ptInsertNode->pNext = pHead;
		ptLkList->pNext     = ptInsertNode;
		ptLkList            = ptInsertNode;
		return TRUE;
	} 
	else
	{
		pTmp = pHead->pNext; //��һ�����
		while ((pTmp->pNext) != ptReferNode && (pHead != (pTmp->pNext))) //�ҵ�ptReferNode�������е�λ��(ֱ��ǰ��pTmp),�˴��ǵ�����������pTmp->pNext���ж�
		{
			pTmp = pTmp->pNext;
		}
		if (pHead == pTmp->pNext)    //�Ҳ���ptReferNode�������е�λ��
		{
			printf("Refer Node is not included in LkList!\n");
			return FALSE;
		}
		else                      //��ptReferNode��==pTmp->pNext��֮ǰ(pTmp֮��)����Node
		{
			//ptInsertNode->pNext = pTmp->pNext;
			//pTmp->pNext = ptInsertNode;
		    //OR pTmp->pNext ��ptReferNode���棬����һ����ptLkListҲ����������
			ptInsertNode->pNext = ptReferNode;
			pTmp->pNext = ptInsertNode;			
			return TRUE;
		}       
	}
}
/**********************************************
Function Name: DeleteNode_Lk 
Function Ref��������ɾ��DeleteNode
Input��ptLkList,ptDeleteNode
OutPut��pelement ��ɾNode��������
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_Lk(LNode *ptLkList,LNode *ptDeleteNode,ElemType *pelement)
{
	LNode *pTmp = NULL;
	if (ptLkList == ptDeleteNode) //��ɾ��Ϊͷ���
	{	
		*pelement = ptDeleteNode->data;
		ptLkList = ptDeleteNode->pNext;//���¸�ֵͷ���
		free(ptDeleteNode) ;
		ptDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pTmp = ptLkList; 
		while (((pTmp->pNext) != ptDeleteNode) && ( NULL != (pTmp->pNext))) //�ӵڶ���Node��ʼ,�ҵ�ptDeleteNode�������е�λ��(ֱ��ǰ��pTmp)
		{
			pTmp = pTmp->pNext;
		}
		if (NULL == (pTmp->pNext))    //�Ҳ���ptDeleteNode�������е�λ��
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //ɾ��ptDeleteNode��== pTmp->pNext��,
		{                          
			//pTmp->pNext = pTmp->pNext->pNext; 
			//OR pTmp->pNext ��ptDeleteNode����(DeleteNode֮ǰNode��pTmp)������һ����ptLkListҲ����������
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
Function Ref��˫����ɾ��DbDeleteNode
Input��ptDbLkList,ptDbDeleteNode
OutPut��pelement ��ɾNode��������
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_DbLk(DbLNode *ptDbLkList,DbLNode *ptDbDeleteNode,ElemType *pelement)
{
	DbLNode *pDbTmp = NULL;
	if (ptDbLkList == ptDbDeleteNode) //��ɾ��Ϊͷ���
	{	
		*pelement = ptDbDeleteNode->data;
		ptDbLkList = ptDbDeleteNode->pNext;//���¸�ֵͷ���
		free(ptDbDeleteNode) ;
		ptDbDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pDbTmp = ptDbLkList->pNext; 
		while ((pDbTmp != ptDbDeleteNode) && ( NULL != pDbTmp)) //�ӵڶ���Node��ʼ,�ҵ�ptDbDeleteNode�������е�λ��
		{
			pDbTmp = pDbTmp->pNext;
		}
		if (NULL == pDbTmp)    //�Ҳ���ptDbDeleteNode�������е�λ��
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //ɾ��ptDbDeleteNode��pDbTmp��, 
		{                          

			//OR pDbTmp��ptDbDeleteNode���棬����һ����ptLkListҲ����������
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
Function Ref��ѭ��������ɾ��DeleteNode
Input��ptLkList,ptDeleteNode
OutPut��pelement ��ɾNode��������
Return��BOOL
Author:By Frank_tly
**********************************************/
BOOL DeleteNode_CircularLk(LNode *ptLkList,LNode *ptDeleteNode,ElemType *pelement)
{
	LNode *pHead = ptLkList->pNext;
	LNode *pTmpDeletePre = pHead->pNext;
	LNode *pTmp = NULL;
	if (ptLkList == ptDeleteNode) //��ɾ��Ϊͷָ��ָ��Ľ�㣬�����һ�����
	{	
		*pelement = ptDeleteNode->data;
		while ((pTmpDeletePre->pNext) != ptDeleteNode) //�ҵ�DeleteNode��ǰһ�����pTempDeletePre
		{
			pTmpDeletePre = pTmpDeletePre->pNext;
		}
		pTmpDeletePre->pNext = ptDeleteNode->pNext;//ptDeleteNode->pNext == ptLkList->pNext == pHead
		ptLkList = pTmpDeletePre;//���¸�ֵͷָ�룬���һ�����
		free(ptDeleteNode) ;
		ptDeleteNode = NULL;
		return TRUE;
	} 
	else
	{
		pTmp = pHead->pNext; 
		while (((pTmp->pNext) != ptDeleteNode) && ( pHead != (pTmp->pNext))) //�ӵڶ���Node��ʼ,�ҵ�ptDeleteNode�������е�λ��(ֱ��ǰ��pTmp)
		{
			pTmp = pTmp->pNext;
		}
		if (pHead == (pTmp->pNext))    //�Ҳ���ptDeleteNode�������е�λ��
		{
			printf("Delete Node is not included in LkList!\n");
			*pelement = 0;
			return FALSE;
		}
		else              //ɾ��ptDeleteNode��== pTmp->pNext��,
		{                          
			//pTmp->pNext = pTmp->pNext->pNext; 
			//OR pTmp->pNext ��ptDeleteNode����(DeleteNode֮ǰNode��pTmp)������һ����ptLkListҲ����������
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
Function Ref����ӡ�����������������
Input��ptLkList
OutPut����
Return����
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
Function Ref����ӡ˫���������������
Input��ptLkList
OutPut����
Return����
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
Function Ref����ӡѭ�������������������
Input��ptLkList
OutPut����
Return����
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
Function Ref����������

p1 ----> p2 ---->p3 ....->pn

pn ----> pn-1 ---->pn-2 ....->p1
Input��ptLkList
OutPut����
Return����
Author:By Frank_tly
**********************************************/
void InvertList_Lk(LNode **ptLkList)       //�ı���ptLkListָ���ַ��ֵ������Ҫ��ָ���ָ��
{
	LNode *pTmp = (*ptLkList);
	*ptLkList = NULL;  //�趨���ú�������̬ΪNULL
	LNode *pRemoveLNode = NULL;	
    while (NULL != pTmp)
    {
		pRemoveLNode        = pTmp; //��ǰ�ƶ���Node 
		pTmp                = pTmp->pNext;              //ע��λ�ã����ܷ��ں��棬��Ȼ�Ҳ���pTmp->pNext��
		pRemoveLNode->pNext = *ptLkList; //���뵽��ͷ
		*ptLkList            = pRemoveLNode;	//��ͷʼ������ǰ��   ,���������򴴽�����
                     
    }
}

/**********************************************
Function Name: InvertList_DbLk 
Function Ref������˫����
����ǰ��
p1 ----> p2 ---->p3 ....->pn
�����
pn ----> pn-1 ---->pn-2 ....->p1
Input��ptDbLkList
OutPut����
Return����
Author:By Frank_tly
**********************************************/
void InvertList_DbLk(DbLNode **ptDbLkList)
{
	DbLNode *pDbTmp = (*ptDbLkList);
	DbLNode *pDbRemoveLNode = NULL;

	(*ptDbLkList) = NULL;	
    while (NULL != pDbTmp)
    {
		pDbRemoveLNode = pDbTmp; //��ǰ�ƶ���Node
		pDbTmp = pDbTmp->pNext; // �ڵ�4���޸���ָ����¸�Node����ָ���ƶ����ڴ˴�
		pDbRemoveLNode->pPrior = NULL;       
		pDbRemoveLNode->pNext  = (*ptDbLkList); //���뵽��ͷ����ǰ�ƶ����ǰ���ͺ���,
		if (NULL != (*ptDbLkList))
		{
			(*ptDbLkList)->pPrior     = pDbRemoveLNode; // �ǵ�һ��Nodeʱ���ο��㣨��ͷ����ǰ��
		}    
		(*ptDbLkList) = pDbRemoveLNode;	//��ͷʼ������ǰ��   ,���������򴴽�����                             
    }
}
/**********************************************
Function Name: InvertList_CircularLk 
Function Ref������ѭ��������
 ����ǰ��
   -----------------------------------
  ��                                 ��
pHead ---> p1 ----> p2 ---->p3 ....->pn <----ptLkList  

�����
   -----------------------------------
  ��                                 ��
pHead <--- p1 <--- p2 <--- p3....<---pn
           ��
		   ptLkList

Input��ptLkList
OutPut����
Return����
Author:By Frank_tly
**********************************************/
void InvertList_CircularLk(LNode **ptLkList)       //�ı���ptLkListָ���ַ��ֵ������Ҫ��ָ���ָ��
{
	LNode *pHead        = (*ptLkList)->pNext; //ͷ��㲻��
	LNode *pTmpPre      = pHead;              // ��ѭ�������һ�����λ��ָ��
	LNode *pTmp         = pHead->pNext;       //�ɵ�ѭ������ı����ĵ�ǰλ��ָ��
	LNode *pRemoveLNode = NULL;	
	(*ptLkList)         = pHead->pNext;      //��һ�����������������һ�������      
	
    while(pHead != pTmp)
    {
		pRemoveLNode        = pTmp; //��ǰ�ƶ���Node 
		pTmp                = pTmp->pNext;              //ע��λ�ã����ܷ��ں��棬��Ȼ�Ҳ���pTmp->pNext��
		pRemoveLNode->pNext = pTmpPre; 
		pTmpPre             = pRemoveLNode;	//ÿ��pHead���µ��µ�λ��                 
    };
	pTmp->pNext             = pTmpPre;     // ��ʱpTmp == pHead�����ɱջ�
}
/**********************************************
Function Name: DestroyList_Lk 
Function Ref�����ٵ�����
Input��ptLkList
OutPut����
Return����
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
Function Ref������˫����
Input��ptDbLkList
OutPut����
Return����
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
Function Ref������ѭ��������
Input��ptLkList
OutPut����
Return����
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
	free(pHead);           //�ͷ�ͷ���
	pHead             = NULL;
}