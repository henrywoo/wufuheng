template<typename _Tp, class _Alloc>
template<typename _Comp>
void
forward_list<_Tp, _Alloc>::
sort(_Comp __comp)
{
  // If `next' is 0, return immediately.
  _Node* __list = static_cast<_Node*>(this->_M_impl._M_head._M_next);
  if (!__list)
    return;

  unsigned long __insize = 1;

  while (1)
  {
    _Node* __p = __list;
    __list = 0;
    _Node* __tail = 0;

    // Count number of merges we do in this pass.
    unsigned long __nmerges = 0;

    while (__p)
    {
      ++__nmerges;
      // There exists a merge to be done.
      // Step `insize' places along from p.
      _Node* __q = __p;
      unsigned long __psize = 0;
      for (unsigned long __i = 0; __i < __insize; ++__i)
      {
        ++__psize;
        __q = static_cast<_Node*>(__q->_M_next);
        if (!__q)
          break;
      }

      // If q hasn't fallen off end, we have two lists to merge.
      unsigned long __qsize = __insize;

      // Now we have two lists; merge them.
      while (__psize > 0 || (__qsize > 0 && __q))
      {
        // Decide whether next node of merge comes from p or q.
        _Node* __e;
        if (__psize == 0)
        {
          // p is empty; e must come from q.
          __e = __q;
          __q = static_cast<_Node*>(__q->_M_next);
          --__qsize;
        }
        else if (__qsize == 0 || !__q)
        {
          // q is empty; e must come from p.
          __e = __p;
          __p = static_cast<_Node*>(__p->_M_next);
          --__psize;
        }
        else if (__comp(*__p->_M_valptr(), *__q->_M_valptr()))
        {
          // First node of p is lower; e must come from p.
          __e = __p;
          __p = static_cast<_Node*>(__p->_M_next);
          --__psize;
        }
        else
        {
          // First node of q is lower; e must come from q.
          __e = __q;
          __q = static_cast<_Node*>(__q->_M_next);
          --__qsize;
        }

        // Add the next node to the merged list.
        if (__tail)
          __tail->_M_next = __e;
        else
          __list = __e;
        __tail = __e;
      }

      // Now p has stepped `insize' places along, and q has too.
      __p = __q;
    }
    __tail->_M_next = 0;

    // If we have done only one merge, we're finished.
    // Allow for nmerges == 0, the empty list case.
    if (__nmerges <= 1)
    {
      this->_M_impl._M_head._M_next = __list;
      return;
    }

    // Otherwise repeat, merging lists twice the size.
    __insize *= 2;
  }
}
