#pragma once
#include <iostream>

struct Elem {
	void* data;
	Elem* prev = nullptr;
	Elem* next = nullptr;
};
struct List {
	Elem* head = nullptr;
	Elem* tail = nullptr;
};

void ListAdd(List& list, void* data);
void ListDel(List& list, Elem* elem);
void ListFree(List& list);
void ListPrint(List& list);