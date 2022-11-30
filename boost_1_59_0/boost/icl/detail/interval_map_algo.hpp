/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_MAP_ALGO_HPP_JOFA_100730
#define BOOST_ICL_INTERVAL_MAP_ALGO_HPP_JOFA_100730

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>

#include <boost/icl/type_traits/is_total.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/relation_state.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/interval_combining_style.hpp>
#include <boost/icl/detail/element_comparer.hpp>
#include <boost/icl/detail/interval_subset_comparer.hpp>

namespace boost{namespace icl
{


namespace Interval_Map
{
using namespace segmental;

template<class IntervalMapT>
bool is_joinable(const IntervalMapT& container, 
                 typename IntervalMapT::const_iterator first, 
                 typename IntervalMapT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalMapT::const_iterator it_ = first, next_ = first;
    ++next_;

    const typename IntervalMapT::codomain_type& co_value 
        = icl::co_value<IntervalMapT>(first);
    while(it_ != past)
    {
        if(icl::co_value<IntervalMapT>(next_) != co_value)
            return false;
        if(!icl::touches(key_value<IntervalMapT>(it_++),
                         key_value<IntervalMapT>(next_++)))
            return false;
    }

    return true;
}

//------------------------------------------------------------------------------
//- Containedness of key objects
//------------------------------------------------------------------------------

//- domain_type ----------------------------------------------------------------
template<class IntervalMapT>
typename enable_if<mpl::not_<is_total<IntervalMapT> >, bool>::type
contains(const IntervalMapT& container, 
         const typename IntervalMapT::domain_type& key) 
{
    return container.find(key) != container.end();
}

template<class IntervalMapT>
typename enable_if<is_total<IntervalMapT>, bool>::type
contains(const IntervalMapT&, 
         const typename IntervalMapT::domain_type&) 
{
    return true;
}

//- interval_type --------------------------------------------------------------
template<class IntervalMapT>
typename enable_if<mpl::not_<is_total<IntervalMapT> >, bool>::type
contains(const IntervalMapT& container, 
         const typename IntervalMapT::interval_type& sub_interval) 
{
    typedef typename IntervalMapT::const_iterator const_iterator;
    if(icl::is_empty(sub_interval)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior = container.equal_range(sub_interval);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = prior(exterior.second);

    return
          icl::contains(hull(exterior.first->first, last_overlap->first), sub_interval)
      &&  Interval_Set::is_joinable(container, exterior.first, last_overlap);
}

template<class IntervalMapT>
typename enable_if<is_total<IntervalMapT>, bool>::type
contains(const IntervalMapT&, 
         const typename IntervalMapT::interval_type&) 
{
    return true;
}

//- set_type -------------------------------------------------------------------
template<class IntervalMapT, class IntervalSetT>
typename enable_if<mpl::and_<mpl::not_<is_total<IntervalMapT> >
                            ,is_interval_set<IntervalSetT> >, bool>::type
contains(const IntervalMapT& super_map, const IntervalSetT& sub_set) 
{
    return Interval_Set::within(sub_set, super_map);
}

template<class IntervalMapT, class IntervalSetT>
typename enable_if<mpl::and_<is_total<IntervalMapT>
                            ,is_interval_set<IntervalSetT> >, bool>::type
contains(const IntervalMapT&, const IntervalSetT&) 
{
    return true;
}


//------------------------------------------------------------------------------
//- Containedness of sub objects
//------------------------------------------------------------------------------

template<class IntervalMapT>
bool contains(const IntervalMapT& container, 
              const typename IntervalMapT::element_type& key_value_pair) 
{
    typename IntervalMapT::const_iterator it_ = container.find(key_value_pair.key);
    return it_ != container.end() && (*it_).second == key_value_pair.data;
}

template<class IntervalMapT>
bool contains(const IntervalMapT& container, 
              const typename IntervalMapT::segment_type sub_segment) 
{
    typedef typename IntervalMapT::const_iterator const_iterator;
    typename IntervalMapT::interval_type sub_interval = sub_segment.first;
    if(icl::is_empty(sub_interval)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior = container.equal_range(sub_interval);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = prior(exterior.second);

    if(!(sub_segment.second == exterior.first->second) )
        return false;

    return
          icl::contains(hull(exterior.first->first, last_overlap->first), sub_interval)
      &&  Interval_Map::is_joinable(container, exterior.first, last_overlap);
}


template<class IntervalMapT>
bool contains(const IntervalMapT& super, const IntervalMapT& sub) 
{
    return Interval_Set::within(sub, super);
}

} // namespace Interval_Map

}} // namespace icl boost

#endif 


/* interval_map_algo.hpp
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
*/