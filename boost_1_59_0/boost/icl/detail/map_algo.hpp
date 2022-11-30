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
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
*/