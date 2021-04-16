#include <stdio.h>
#include <malloc.h>

typedef struct Item {
	char c;
	struct Item* next;
} Item;

int getList(Item**);
void putList(Item*);
Item* delList(Item*);
void ch(Item** str1, Item* str2);
Item* skipSpace(Item* str);
int Checkword(Item* h, Item* p, int j);
int getword(Item* str);
void SkipL(Item* prev, Item* t, Item** str1);

int getList(Item** pptr)
{
	char buf[81], * str;
	Item head = { '*', NULL };
	Item* last = &head;
	int n, rc = 1;
	do {
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0) {
			delList(head.next);
			head.next = NULL;
			rc = 0;
			continue;
		}
		if (n > 0) {
			for (str = buf; *str != '\0'; ++str) {
				last->next = (Item*)malloc(sizeof(Item));
				last = last->next;
				last->c = *str;
			}
			last->next = NULL;
		}
		else
			scanf_s("%*c");
	} while (n > 0);
	*pptr = head.next;
	return rc;
}
void putList(char* msg, Item* ptr)
{
	printf("%s: \"", msg);
	for (; ptr != NULL; ptr = ptr->next)
		printf("%c", ptr->c);
	printf("\"\n");
}
Item* delList(Item* str)
{
	Item* tmp = NULL;
	while (str != NULL) {
		tmp = str;
		str = str->next;
		free(tmp);
	}
	return str;
}

Item* skipSpace(Item* str) {
	while (str != NULL && (str->c == '\t' || str->c == ' ')) {
		str = str->next;
	}
	return str;
}




int getword(Item* str) {

	int k = 0;
	while (str != NULL && (str)->c != '\t' && (str)->c != ' ') {
		k++;
		str = (str)->next;
	}
	return k;
}
int Checkword(Item* h, Item* p, int j) {
	Item* k = h, * prev = NULL;
	int i = 0;
	while (p != NULL) {
		if (k->c != p->c) {
			while (p != NULL && p->c != ' ' && p->c != '\t') {
				p = p->next;
			}
			p = skipSpace(p);
			k = h;
			i = 0;
		}
		else {
			k = k->next;
			prev = p;
			p = p->next;
			i++;
		}
		if (i == j) {
			if (p == NULL || p->c == ' ' || p->c == '\t') {
				break;
			}
			else {
				while (p != NULL && p->c != ' ' && p->c != '\t') {
					p = p->next;
				}
				p = skipSpace(p);
				k = h;
				i = 0;
			}
		}
		else {
			if (p == NULL) {
				i = 0;
			}
		}
	}
	return i == 0 ? 0 : 1;
}
void SkipL(Item* prev, Item* t, Item** str1) {
	if (prev) {
		prev->next = t->next;
	}
	if (t->next == NULL && prev) {
		t = prev;
	}
}

void ch(Item** str1, Item* str2) {
	int l, r = 0, w = 0;
	Item* prev = NULL, * p = NULL, * tmp = NULL;
	Item* h = *str1;
	while (h != NULL && (h->c == '\t' || h->c == ' ')) {
		tmp = h;
		*str1 = h->next;
		h = h->next;
		free(tmp);
	}
	str2 = skipSpace(str2, prev);
	if (str2 != NULL) {
		while (h != NULL) {
			r = getword(h);
			l = Checkword(h, str2, r);
			if (l == 0) {
				if (prev == NULL) {
					while (h != NULL && h->c != '\t' && h->c != ' ') {
						tmp = h;
						*str1 = h->next;
						h = h->next;
						free(tmp);
					}
					while (h != NULL && (h->c == '\t' || h->c == ' ')) {
						tmp = h;
						*str1 = h->next;
						h = h->next;
						free(tmp);
					}
				}
				else {
					while (h != NULL && h->c != '\t' && h->c != ' ') {
						tmp = h;
						SkipL(prev, h, &str1);
						h = h->next;
						free(tmp);
					}
					while (h != NULL && (h->c == '\t' || h->c == ' ')) {
						tmp = h;
						SkipL(prev, h, &str1);
						h = h->next;
						free(tmp);
					}
				}
			}
			else {
				prev = NULL;
				while (h != NULL && h->c != '\t' && h->c != ' ') {
					p = h;
					h = h->next;
				}
				if (h != NULL) {
					h->c = ' ';
					prev = h;
					h = h->next;
				}
				while (h != NULL && (h->c == '\t' || h->c == ' ')) {
					tmp = h;
					SkipL(prev, h, &str1);
					h = h->next;
					free(tmp);
				}
			}
		}
		if (prev != NULL) {
			tmp = prev;
			SkipL(p, prev, &str1);
			prev = prev->next;
			free(tmp);
		}
	}
	else {
		*str1 = delList(*str1);
	}
}



int main()
{
	Item* osn_str, * ch_str;
	while (puts("enter string 1"), getList(&osn_str), puts("enter string 2"), getList(&ch_str)) {
		putList("Entered string 1", osn_str);
		putList("Entered string 2", ch_str);
		ch(&osn_str, ch_str);
		putList("Result string", osn_str);
		osn_str = delList(osn_str);
		ch_str = delList(ch_str);
	}
	return 0;
}