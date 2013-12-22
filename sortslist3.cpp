//gcc sortslist3.cpp -g -O2 -o sortslist3 -lstdc++ -std=c++11 && ./sortslist3
#include <stdio.h>
#include <utility>
#include <memory>

using namespace std;

// bottom up merge sort of sinlgly-linked list
struct ListNode {
  int val;
  ListNode *next;
};

//merge h2 into h1, h2 becomes empty
void merge(ListNode*& h1, ListNode*& h2){
  if (h1 == NULL){
    swap(h1, h2);
    return;
  }
  if (h2 == NULL) return;
  if (h1->val > h2->val){
    swap(h1, h2);
  }
  ListNode* hsmall = h1;
  ListNode* hbig = h2;
  ListNode* tmp;
  while (true){
    tmp = hsmall;
    hsmall = hsmall->next;
    if (hsmall == NULL){
      tmp->next = hbig;
      break;
    }
    if (hsmall->val > hbig->val){
      tmp->next = hbig;
      swap(hsmall, hbig);
    }
  }
  h2 = NULL;
}

ListNode *sortList(ListNode *head) {
  if (head == NULL) return NULL;
  ListNode* pc = NULL;
  ListNode* bucket[64] = {};
  int fill = 0;

  while (head){
    pc = head;
    head = head->next;
    pc->next = NULL;

    int i = 0;
    while (i < fill && bucket[i]) {
      merge(bucket[i], pc);///
      swap(pc, bucket[i++]);
    }
    swap(pc, bucket[i]);

    if (i == fill) ++fill;
  }

  for (int i = 1; i < fill; ++i){
    merge(bucket[i], bucket[i - 1]);
  }
  swap(head, bucket[fill - 1]);
  return head;
}

void print(ListNode *h){
  while (h){
    printf("%d ", h->val);
    h = h->next;
  }
  printf("\n");
}

#define _countof(a) (sizeof(a)/sizeof(a[0]))

int main(int argc, char* argv[]){
  //int a[] = {};
  //int a[]={1}; // SD=2
  //int a[]={10, 5, 7, 6, 40, 25, 50, 13, 21, 16, 19, 9, 23, 8};
  //int a[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  int a[] = { 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  int sz = _countof(a);
  printf("total number of elements:%d\n", sz);

  unique_ptr<ListNode[]> p(new ListNode[sz]);
  for (int i = sz - 1; i >= 0; --i){
    p[i].val = a[i];
    if (i + 1 < sz){
      p[i].next = &p[i + 1];
    }
  }

  ListNode* head = &p[0];
  head=sortList(head);
  print(head);
  return 0;
}
