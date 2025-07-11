#include "list.h"

void ListAdd(List& list, void* data)
{
	Elem* elem = (Elem*)malloc(sizeof(Elem));
	if (!elem) {
		printf_s("������ ������: �� ������� �������� ������ ��� ����� �������\n");
		return;
	}
	elem->data = data;
	elem->next = elem->prev = nullptr;

	if (list.tail != nullptr) { // ���� ������ �� ����
		elem->prev = list.tail;
		list.tail->next = elem;
		list.tail = elem;
	}
	else {
		list.head = elem;
		list.tail = elem;
	}
}
void ListDel(List& list, Elem* elem)
{
	if (list.head == nullptr) { // ���� ������ ����
		return;
	}
	for (Elem* cur = list.head; cur != nullptr; cur = cur->next) {
		if (cur == elem)
		{
			if (cur->prev) { // ���� ���������� ������� ����������, �� next ����������� ��������� �� ���������
				cur->prev->next = cur->next;
			}
			else { // ���� ����������� �������� ���, �� ���������� ������ �� ��������� �������
				list.head = cur->next;
			}
			if (cur->next) { // ���� ��������� ������� ����������, �� prev ���������� �������� �� ����������
				cur->next->prev = cur->prev;
			}
			else { // ���� ���������� �������� ���, �� ���������� ����� �� ���������� �������
				list.tail = cur->prev;
			}
			free(cur);
			return;
		}
	}
	printf_s("������� �� ��� ������ � ������\n");
}
void ListFree(List& list)
{
	Elem* cur = list.head;
	while (cur) {
		Elem* next = cur->next;
		free(cur);
		cur = next;
	}
	list.head = list.tail = nullptr;
}
void ListPrint(List& list)
{
	for (Elem* cur = list.head; cur != nullptr; cur = cur->next) {
		printf_s("%d - >", cur->data);
	}
	printf_s("\n");
}