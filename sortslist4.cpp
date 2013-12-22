#include <list>
#include <iostream>

using namespace std;

template <typename T>
void sort_list(list<T> &lst){
  if (lst.size() < 2)
    return;
  list<T> carry;
  list<T> counter[64];
  int fill = 0;
  typename list<T>::iterator it;

  while (!lst.empty()) {
    carry.splice(carry.begin(), lst, lst.begin());

    cout << "carry: ";
    it = carry.begin();
    while (it != carry.end())
      cout << *it++ << " ";
    cout << endl;

    int i = 0;
    while (i < fill && !counter[i].empty()) {
      counter[i].merge(carry);
      carry.swap(counter[i++]);
    }
    carry.swap(counter[i]);
    for (int i = 0; i < fill + 1; i++)
    {
      it = counter[i].begin();

      cout << "counter" << i << ": ";
      while (it != counter[i].end())
        cout << *it++ << " ";
      cout << endl;
    }
    if (i == fill) ++fill;
    cout << endl;
  }
  for (int i = 1; i < fill; ++i){ counter[i].merge(counter[i - 1]); }
  it = counter[fill - 1].begin();

  cout << "counter" << fill - 1 << ": ";
  while (it != counter[fill - 1].end())
    cout << *it++ << " ";
  cout << endl;

  lst.swap(counter[fill - 1]);
}

int main(){
  int arr[] = { 10, 88, 45, 87, 65, 96, 84, 8, 86, 53, 67, 5, 48, 74, 4, 35, 71, 25, 32 };
  list<int> lst(arr, arr + sizeof(arr) / sizeof(int));
  list<int>::iterator it = lst.begin();
  while (it != lst.end())
    cout << *it++ << " ";
  cout << endl;
  sort_list(lst);
  return 0;
}
