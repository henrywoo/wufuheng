//gcc sortslist3.cpp -g -O2 -o sortslist -lstdc++ && ./sortslist3

#include <stdio.h>
#include <utility>

// merge sort of sinlgly-linked list

/**
 * Definition for singly-linked list.
 */ 
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
  ListNode() : val(0), next(NULL) {}
};
/**/

static int STACKDEPTH = 0;
static int MAXSD = 0;

class Solution {
  public:
    void swap(ListNode* h1, ListNode* h2){
      std::swap(h1,h2);
    }

    //merge h2 into h1, h2 becomes empty
    void merge(ListNode*& h1, ListNode*& h2){
      if(h1==NULL){
        std::swap(h1,h2);
        return;
      }
      if(h2==NULL) return;
      ListNode* hsmall=h1;
      ListNode* hbig=h2;
      if(hsmall->val > hbig->val){
        swap(hsmall,hbig);
      }
      ListNode* tmp;
      while(true){
        tmp=hsmall;
        hsmall = hsmall -> next;
        if(hsmall==NULL){
          tmp->next=hbig;
          break;
        }
        if(hsmall->val > hbig->val){
          tmp->next=hbig;
          swap(hsmall,hbig);
        }
      }
    }

    ListNode *sortList(ListNode *head) {
      ListNode carry(0);
      ListNode* pc=&carry;
      ListNode* bucket[64]={};
      int fill=0;
      while(head){
        pc->val=head->val;

        int i=0;
        while(i < fill && bucket[i]) {
          merge(bucket[i],pc);
          swap(pc,bucket[i++]);
        }
        swap(pc,bucket[i]);
        if (i == fill) ++fill;
      }
      for (int i = 1; i < fill; ++i){
        merge(bucket[i],bucket[i-1]);
      }
      swap(head,bucket[fill-1]);
      return head;
    }

    void print(ListNode *h){
      while(h){
        printf("%d ",h->val);
        h=h->next;
      }
      printf("\n");
    }

};

#define _countof(a) (sizeof(a)/sizeof(a[0]))

int main(int argc, char* argv[]){
  //int a[]={1,4,2}; // SD=2
  //int a[]={10, 5, 7, 6, 40, 25, 50, 13, 21, 16, 19, 9, 23, 8};
  //int a[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  int a[]={35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int sz=_countof(a);
  printf("total number of elements:%d\n",sz);
  ListNode *p=new ListNode[sz];
  for(int i=sz-1;i>=0;--i){
    p[i].val=a[i];
    if(i+1<sz){
      p[i].next=&p[i+1];
    }
  }
  ListNode* head=p;
  Solution s;
  s.sortList(head);
  s.print(head);
  printf("stack depth = %d\n", MAXSD);
  return 0;
}
