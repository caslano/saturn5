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
rHjhzg+bfzHDZw7aNG+Jmm6mospuGwMitsvcEyUYrOh+MUs18KYgnssnanH7q4v8bpvNzeuec1fLg7zx/12JeWmg2lC5zmUpfUZUsPfGpcydkIQKgx18HqmCTiNaYFDbF3L4Vz3cMA8SyyLfo6ujnvy6qy3VTePxZvUtfN2rJT1PnMS70WMYeDwTNp+niHdxwXhq7iGKk4ph8T5JXLu9h2ot5lL5cRh8bsUKdaM+6LJhhTj9YiSdGwtwKOQEf6UdlDHmVqgwdZFLtxqj11TFvuu5zWzl3klOyV7CSuGFFYo+711ugbCsbRwVd1xGKM3gybuuYvblzbCIeyuMqz7TpVNnVqS6srX/HzlXOwuvL/yTVi3LcKdssrjiEc9hlcfFJsMhsGnjz9s3RmNoig+3avZEP+VgoTG8E7+1PkePURHw2VMjDi/25QjbqXh8pR2HNLOktdds3tYfLxzVDNhyaTBUVlpydGwDwrVzMeioj9RfngVhnkhPjwTEzeonpxZ9xuiXj3naJZL9yrzFubLvsKi/LEJtd9Jk3W+5p5UPz6dsl5N/78FXxQw36/SbemONGF+nhN6jjMTSh7OwKTIfSm7KtNoxjq4zFrEopRf1g63oEb1Zetqege39KfKPsRdbvkwTrS47o7pLS3nq8Rvc+RiCBVOrWGrfWdi87sv3N+6L4hx/zkxvybBxT5CWZyf//htM93keovF6HMOL4nj05wgaXnYQHXOyGNFrlXgqiC/LBjLZoAKHP/6H4d074e9/XcS4SDtOX38X4+6WcOogdTH7uzkeXq7nuIICtuoVIyYZz0BqljF3WbbCoqN1KM83gnGnKXJGVhbaNc2RR4+sxtY9v4Wn4yiOrmotgt+GcN2xFWL9wBtsuP5Ezrhkyfxf74S6SSvE5/XBrpX2eNn2OUOtPbDgmDs7zvDn2bTLInBPMwVjtZFFaqp0qe4l4vaVMzDIjMP5jGa7vsrDI9/Ru28dbmX+5YephlhgO5NnH5nKSP2RzP1yEwb36jB34HPZ5aYfMj/FYPzMeDjcPir+lq3F+pGluKJuiW0nlKVGSCz7d3Lj0IejcTVqJjODa/Dl4nVZvDOTVkNtMPjVR1xvbID+RxU+33VTbKrrxJOf1sk5Q65z62VN6qbt5/Dtjcix7gGNpfrYbAJsPWYvNT9dw63pNTi85Dhv2XQQWhfd+K3VZ4j1x7mtEnz44wdMrv7Ed7X7fLcmTt4MsOe7OXnw1/3EslbZbHuwhv4VxXKKlw2cVUbJ4UVLue+Nq7i/QAexT1WkcoEBihW+reBUBV92UPDwvyE4vDBQiif9EaVjIUbcfUC7NZBfTu9Hl2Of8TDkAvKdIdfHOuKy2RRs/3IJue/Jop3P2GR1S3ZT8YRBrEBjxwbqJvaQKpufY1k7QzlgYQzaFJvKl60dmHPPS0b2uQ+df2vl8pPTINYfYd6UJTiWeheDxDesvXpOqi6YyqoN31kRkckcl3fI7dEf+Tmq6Pjehamxd/E7fyPMrtTJJqdnYvbqOIwYq8f2O7wRMukxyoZEilefxqPxaVfUtT1Lpba+Um1/PjM09DnHK49TVr0QYyIGstn79rJM04xtWCT1Wj6m3b1o+czmBX/++c1Nfyzw/rcd5q+1QOFPB6huK8WQi82Fw7GlVOq+TVakmbI8SovthsXhwyJTuaa2gdOmOIiZryM59ZiUuwp/oUL3gHQdtAgPdPVFQd0opJy+zHorLyTFdsfb/1xZ6zhZNixexJfFjpQ7rnH3DQMaPzrPHCcDrPaOY+IBd7FxYSl9D9eJ5TlquD3/I/yV5iK2p6MM+P6cbaoOMzGmI6+80+BfrQNcNa0Hfp/WZNX5XBps38s=
*/