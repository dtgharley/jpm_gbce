// ext.h
//
// Definition of indexed extension to std::for_each.
//

#ifndef CLASS_RSEXT
#define CLASS_RSEXT

template <typename IteratorT, typename FunctionT>
FunctionT for_each_indexed(IteratorT first, 
                    IteratorT last, 
                    FunctionT func)
{
    for (typename std::iterator_traits<IteratorT>::difference_type initial=0; first != last; ++first, ++initial)
        func(initial, *first);
    return func;
}

#endif

