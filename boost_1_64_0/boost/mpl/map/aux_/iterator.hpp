
#ifndef BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< 
      typename Map
    , long order
    , long max_order
    >
struct next_order
    : if_< 
          is_void_< typename item_by_order<Map,order>::type >
        , next_order<Map,(order+1),max_order>
        , long_<order>
        >::type
{
};

template< 
      typename Map
    , long max_order
    >
struct next_order<Map,max_order,max_order>
    : long_<max_order>
{
};


template< typename Map, long order, long max_order >
struct m_iter
{
    typedef forward_iterator_tag category;
    typedef typename item_by_order<Map,order>::type type;
};

template< typename Map, long max_order >
struct m_iter<Map,max_order,max_order>
{
    typedef forward_iterator_tag category;
};


template< typename Map, long order, long max_order > 
struct next< m_iter<Map,order,max_order> >
{
    typedef m_iter<
          Map
        , next_order<Map,order+1,max_order>::value
        , max_order
        > type;
};

template< typename Map, long max_order > 
struct next< m_iter<Map,max_order,max_order> >
{
};

#else

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order;

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order_impl
    : if_< 
          is_void_< typename item_by_order<Map,order>::type >
        , next_order<Map,(order+1),max_order>
        , long_<order>
        >::type
    {
    };

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct next_order
    : if_c<
          (order != max_order)
        , next_order_impl<Map,order,max_order>
        , long_<order>
        >::type
{
};


template<
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter;

struct m_iter_empty_base {};

template< 
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter_base
{
    typedef typename item_by_order<Map,order>::type type;
    
    typedef m_iter<
          Map
        , next_order<Map,order+1,max_order>::value
        , max_order
        > next;
};

template<
      typename Map
    , BOOST_MPL_AUX_NTTP_DECL(long, order)
    , BOOST_MPL_AUX_NTTP_DECL(long, max_order)
    >
struct m_iter
  : if_c<
          (order == max_order)
        , m_iter_empty_base
        , m_iter_base<Map,order,max_order>
        >::type
{
    typedef forward_iterator_tag category;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_MAP_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
dJPrr1yXlfz68TpV/l/ZW/I7DMMwWvKLwViMxQHYF1MwDnOwHx6HCViAiXgy9sfTcABehIfjJTgQl+EgvAZT8B4cjA/iEHwRh+KreAS+hcOwDY+UdqA03B+HYzSOwHgciRl4NBbhMXgyjsZKHIMzMQsXYzZeiePwdhyPD+Cx+ATm4iY8Tv09SPCtHactwXP7TLGq3WXyhZ37DLDe7tJ57S5rL957j7W9/BfbXXxtc+loe8scfjvLSWtJW0k7SMHzgwxJ8/V2FX359yyBpMourf+zYsVpuz323wAZ+z/CUifOyyosGDMqP8s4Jmsi881lTZiUlTcmS4b/Z932OEGKp3UlaqDEDG5VzSk4x03MIF+pt/S11Fs0NqZEELzX6631mJoEW/zAlu8ujfhBcJynfKvMvsQtrPGEIqd4gjr/cjfxhAnsd4zH/Iku+JC/w37u5Vo/LSCfjDhb/dR9Xj7kYz2+tQm+11dtc0kGuNZXJ1EuU5y1vrr75apJ8D6GepHUm4dK/CXZOoZ6+/fP8mNiEHWvcZeuGEN9AQemMLD9t7FRKQ9ax3JT9s1SOD5Tj6M+rZtWnVyrzux/nUqj7qpRl/a/7qpRh9eoS2vVUbXqkFp1bO1Yww5L3TUy7pCfp05eumSjadfct7NDD7PWLeVaJdew/G7a43wH2+uWrKfV54ukqltqb09+wxjtZT2TrBfpYb0cg3zncaistw+my3qHqOY7DMUeGIk9cQBGYDIeirlK30Xuy9aSGPtYGYPa77qNul6jrtNQn5G6jEM9RuouvtVbDPb6CnUV8iflkla6qZdsJqnrI4WqeojUQaT+4bnOUUxy18cr8Om9DUkYJXUJp3qERh3Cuf6gWXdQ1xmkvqCuKzjVEzTqCFp1gjUYU+RbHUB9/59Kst/r2+/zW/m+dF8QZEglFZOaSC0L9Pt7fdEXfdEXffn3L13f/l9jmfKrM9r/rTGA7VMc6vXUwpQBuLMyjfnMayVBgEESA9jlaV3VuACxrH8A284wqteXtVRzC9yhihWschMrOFV59jJW6sxuM/XvefhT0lWxAqkjJu7lPlZg8pivf8/Gxxm1YwWL3cQKpiht7R7z9/05eWnTZ+Oux7eUfJolH/VJ8nd8hmI3Y8ubAzT6cLjJz58xGuYYtceWf9XNOANllG2rmzz9GafBeq6q3fQHqGT7bbHO8Rbn8+U9H+uxLPejf4B1v3e5KVcV24np61Qu2Xdf9ttanql+lMcW/9nbNf4zU/kt97XGf3b/OM1I14j/qI5LoJt5/E5Tflu2cnT8uNSme+8/4b792//+B/72h9CIdWjEjjqvX4L7GJH//RI6q7+Fv/0Y3Per8L+/i0bMSrMfTO8Vyuel885a9sLzm85auubokXctPWhm5/WT0OofY3sOMVa7/0SKOtYUq91/Ikn9vKKsF+ple80e8h2ubq/3kO8wdb8Np3y1ttcm60V7Lh/XT1nPy/byZb1IL9tr8LDecNVznN0XBhnSSEW8nrawc/sVNC0M0vsW+Nm3wN853oiJ6v0LuqB/weqFQR3uY7CJv20jRTUFGXJI1aQm0mrSNtLPpLhFejxSXzq+dH39X7llNZ3eGfV/pf59p61/v33Oj1ukrfRGUvdIZZAGex/j00urq8qOrTjTn77qE0Jc75NNJvscVRl7oJ/xP61/sL/31f+0/r7HW+5X5wSW/FQe8mSfnCxT97i+v+7wv79vZ7VZf2fpTyvfVfkOr+HFfpgrX8ow1Zy8QzEC8zAKqzAGG7EvXo9xeCPGY9pe9n6e2vdizvdf7vpyer7X2jnCt/urMLmnWkNyvpdKxUKS3D9p3Dup75vc3y8tR7lHcrk/mkzSuh8=
*/