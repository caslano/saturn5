
#ifndef BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>

namespace boost { namespace mpl {

template< typename T, typename Base >
struct s_item
    : Base
{
    typedef s_item<T,Base> item_;
    typedef void_       last_masked_;
    typedef T           item_type_;
    typedef typename Base::item_ base;
    typedef s_item type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    BOOST_MPL_AUX_SET_OVERLOAD( order_tag_, ORDER_BY_KEY, s_item, aux::type_wrapper<T>* );
    BOOST_MPL_AUX_SET_OVERLOAD( aux::no_tag, IS_MASKED, s_item, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_mask
    : Base
{
    typedef s_mask<T,Base> item_;
    typedef T       last_masked_;
    typedef void_   item_type_;
    typedef typename Base::item_ base;
    typedef typename prior< typename Base::size >::type  size;
    typedef s_mask type;

    BOOST_MPL_AUX_SET_OVERLOAD( aux::yes_tag, IS_MASKED, s_mask, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_unmask
    : Base
{
    typedef s_unmask<T,Base> item_;
    typedef void_   last_masked_;
    typedef T       item_type_;
    typedef typename Base::item_ base;
    typedef typename next< typename Base::size >::type  size;

    BOOST_MPL_AUX_SET_OVERLOAD( aux::no_tag, IS_MASKED, s_unmask, aux::type_wrapper<T>* );
};

}}

#endif // BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

/* item.hpp
s+VWGnGmrm8O/ToFIiVxxDASBTFAPKGwEXoaTQtVrrIBanFgmDMl3iYzZZ7b3hfj3Wnu6JmQrtqTiH7Pcn0SjlGH99KX8HdTfwbCDp0eK+0yXQF46zSl9lnssZfxXHNEAUWO5Xqhz93R5tkpU7N9G5AXfxTzbjQo0v6Z0+DAGPJav/BSh402zg9XRgeQYR+f3JSAKtqOC0Rt97LVcKPSkDhgXqhVLjc3wEyPd7evkDY9yGUqDiLac59zt0qiiBDjXIrD1YCpYGPQFSCr/GKldRfS9tfmtpp5AWPAfphAkWQSY8lXSJA/83V9yhKOBh+NdKgHOF3j65BLNueLfHi2pUUMqR5JqsGrPZjSPlAyxZ1u/323yZlj1s5CNd46QYb1YATZ8m/bm7V6aS0oYm9hJhfDLM95S7GdhRhSL7WqEAwwG9wA63wI170CH3qpsTPuYvarEsFROw4jTgncROlAueGA2Fw1esx/6VEVltVP5FwZL/mJYUIAVJCesDKi6unnx5y0+GSo/uOeCif6+jVbGOUBRXkeJj1zG0qdurLYDES53H/tpVHN6b7Gcw==
*/