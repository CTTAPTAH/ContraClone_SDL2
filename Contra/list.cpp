#include "list.h"

void ListAdd(List& list, void* data)
{
	Elem* elem = (Elem*)malloc(sizeof(Elem));
	if (!elem) {
		printf_s("Ошибка списка: не удалось выделить память под новый элемент\n");
		return;
	}
	elem->data = data;
	elem->next = elem->prev = nullptr;

	if (list.tail != nullptr) { // Если список не пуст
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
	if (list.head == nullptr) { // Если список пуст
		return;
	}
	for (Elem* cur = list.head; cur != nullptr; cur = cur->next) {
		if (cur == elem)
		{
			if (cur->prev) { // Если предыдущий элемент существует, то next предыдущего указывает на следующий
				cur->prev->next = cur->next;
			}
			else { // Если предыдущего элемента нет, то перемещает голову на следующий элемент
				list.head = cur->next;
			}
			if (cur->next) { // Если следующий элемент существует, то prev следующего указыват не предыдущий
				cur->next->prev = cur->prev;
			}
			else { // Если следующего элемента нет, то перемещаем хвост на предыдущий элемент
				list.tail = cur->prev;
			}
			free(cur);
			return;
		}
	}
	printf_s("Элемент не был найден в списке\n");
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