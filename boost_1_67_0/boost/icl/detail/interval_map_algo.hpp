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