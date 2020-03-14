#ifndef MY_STACK_H
#define MY_STACK_H

//��������� ����� ListNode (���� ������������ ������)
template <class INF, class FRIEND>
class ListNode				//���� ������
{
private:
	INF d;             			     //�������������� ����� ����
	ListNode* next;   		         //��������� �� ��������� ���� ������
	ListNode(void) { next = NULL; }  //����������� 
	friend FRIEND;
};

//��������� ����� MyStack �� ������ ������������ ������.
template <class INF>
class MyStack
{
	typedef class ListNode < INF, MyStack <INF> > Node;
	Node* top;
public:
	MyStack(void);		// �����������
	~MyStack(void);         	// ���������� ������������ ������
	bool empty(void);		// ���� ������?
	bool push(INF n);		// �������� ���� � ������� �����
	bool pop(void);		// ������� ���� �� ������� �����
	INF* top_inf(void);		//������� ���������� �� ������� �����
};

#endif
