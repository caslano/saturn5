/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_MAPALGO_HPP_JOFA_080225
#define BOOST_ICL_MAPALGO_HPP_JOFA_080225

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/set_algo.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        

namespace boost{namespace icl
{
namespace Map 
{

template <class ObjectT, class CoObjectT>
bool intersects(const ObjectT& left, const CoObjectT& right)
{
    typedef typename CoObjectT::const_iterator co_iterator;
    co_iterator right_common_lower_, right_common_upper_;
    if(!Set::common_range(right_common_lower_, right_common_upper_, right, left))
        return false;

    co_iterator right_ = right_common_lower_;
    while(right_ != right_common_upper_)
        if(!(left.find(key_value<CoObjectT>(right_++))==left.end()))
            return true;

    return false;
}


template<class MapT>
typename MapT::const_iterator next_proton(typename MapT::const_iterator& iter_, const MapT& object)
{
    while(   iter_ != object.end() 
          && (*iter_).second == identity_element<typename MapT::codomain_type>::value())
        ++iter_;

    return iter_;
}

/** Function template <tt>lexicographical_equal</tt> implements 
lexicographical equality except for identity_elementic content values. */
template<class MapT>
bool lexicographical_distinct_equal(const MapT& left, const MapT& right)
{
    if(&left == &right)        
        return true;

    typename MapT::const_iterator left_  = left.begin();
    typename MapT::const_iterator right_ = right.begin();

    left_  = next_proton(left_,  left);
    right_ = next_proton(right_, right);

    while(left_ != left.end() && right_ != right.end())
    {
        if(!(left_->first == right_->first && left_->second == right_->second))
            return false;

        ++left_;
        ++right_;
        left_  = next_proton(left_,  left);
        right_ = next_proton(right_, right);
    }

    return left_ == left.end() && right_ == right.end();
}

} // namespace Map
}} // namespace boost icl

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif


/* map_algo.hpp
OQEFMWgC3XKRqn34m/2nHSltpKKcZ6/uOuPLCofESIng3pWMHHdgmHn2kMW6/4XgPHt6fLd738zY3OhiwtNXEWL9o9Wp+68YLQIttD+TBswQXi4gj6YWrrLG+Ey8NfvTU+eryfH/WO35DH853jNGDn381mYTcu506UgJUYQSW0JSo7ry2N9Bh6UWZX+w3ORtQ8P74Xzrxe8YBPxrChVvbV7RzVQJaj3hUbdpoQjGA29f51ntNa9Kv9t3zqSA/UE/0oawL0+FBVJovz1/37JhBesmkACvv0maDR1bGfKDm4axHm3FhuQJR2myJXwxrEnVOZhoTHTb87NesnkXLLVtIvlyW/wfP+noYmCgcPCBdiw49gU/EUQu+FAisQc9iEKjE0sUuQ6o9V5lTYl7V+9fFowc9ZagewJ/dQwjr7gUzeh3aNI9fR8903mllO+M3w0YSihwwjqcxjy+y2NbKF/dKAlcaNu7OuIS2JOpOnLUs55wXPDLwzCMnzxR6C6j1nA4eWEV4/Zh3hQQcWLQ22fg+OVkVF3qY0Gjv5Ej38+r6YZjbY8fbbK41N8qFG9p5xXRUs5/srbm3+N/NlxT5cCWpB9zknbD5Q9cAZFzXhzJDjv293rF9AJ40kDneNT1vA4mDg7GEFWE+1xrbWrnVjOIul+m/I78uOtfFSIDr6CcA5W1Z4Jqui+3KCVklgRDxAKAFw7an07fuGbX49FX
*/