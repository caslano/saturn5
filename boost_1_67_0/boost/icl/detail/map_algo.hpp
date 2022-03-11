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