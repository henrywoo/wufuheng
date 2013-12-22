//gcc sortslist.cpp -g -O0 -o sortslist -lstdc++ && ./sortslist

#include <stdio.h>
#include <utility>


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

    ListNode* lastnode(ListNode* h){//h=2
      if(h==NULL) return NULL;
      while(h->next!=NULL){
        h=h->next;//h=1
      }
      return h;//h=1
    }

    // return pivot
    ListNode *partition(ListNode *head,ListNode *tail){//2,1
      if(head==NULL || tail==NULL) return NULL;
      if(head==tail) return head;

      ListNode *pBBhead=NULL, *pSBtail=NULL;
      ListNode *tmp=head->next;//1

      while(tmp!=tail->next){// compare with tail->next
        if(tmp->val < head->val){
          pSBtail= tmp;//1
          tmp = tmp->next;
        }else{
          pBBhead = tmp;///2
          break;
        }
      }

      if(tmp==tail->next){
        std::swap(head->val,tail->val);
        return tail;//2
      }

      while((tmp=tmp->next) && (tmp!=tail->next)){///tmp=NULL
        if(tmp->val < head->val){
          std::swap(tmp->val,pBBhead->val);
          pSBtail = pBBhead;
          pBBhead = pBBhead->next;
        }
      }

      if(pSBtail){
        std::swap(head->val,pSBtail->val);
        return pSBtail;
      }else{
        return head;///1
      }

    }

    void SortRec(ListNode *head, ListNode *tail){
      if(STACKDEPTH>MAXSD){MAXSD=STACKDEPTH;}
      if(head==NULL) return;
      if(head==tail) return;
      /*if(head->next==tail){
        if(head->val > tail->val){std::swap(head->val,tail->val);}
        return;
      }*/
#if 0
      while((head!=NULL) && (head!=tail)){
        ListNode *p = partition(head,tail);
        ++STACKDEPTH;
        SortRec(head,p);
        --STACKDEPTH;
        head=p->next;
      }
#else
      ListNode *p = partition(head,tail);//
      //if(p!=head)
      {
        ++STACKDEPTH;
        SortRec(head,p);//1,2|1,1
        --STACKDEPTH;
      }
      //if(p!=tail)
      {
        ++STACKDEPTH;
        SortRec(p->next,tail);
        --STACKDEPTH;
      }
#endif

    }

    ListNode *sortList(ListNode *head) {
      if(head==NULL)
        return NULL;
      SortRec(head,lastnode(head));//2,1
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
