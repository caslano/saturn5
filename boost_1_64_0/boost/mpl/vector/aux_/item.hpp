
#ifndef BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< 
      typename T
    , typename Base
    , int at_front = 0
    >
struct v_item
    : Base
{
    typedef typename Base::upper_bound_ index_;
    typedef typename next<index_>::type upper_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    // agurt 10/sep/04: MWCW <= 9.3 workaround here and below; the compiler
    // breaks if using declaration comes _before_ the new overload
    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

template<
      typename T
    , typename Base
    >
struct v_item<T,Base,1>
    : Base
{
    typedef typename prior<typename Base::lower_bound_>::type index_;
    typedef index_ lower_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

// "erasure" item
template< 
      typename Base
    , int at_front
    >
struct v_mask
    : Base
{
    typedef typename prior<typename Base::upper_bound_>::type index_;
    typedef index_ upper_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

template< 
      typename Base
    >
struct v_mask<Base,1>
    : Base
{
    typedef typename Base::lower_bound_ index_;
    typedef typename next<index_>::type lower_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

/* item.hpp
xufjuaQv4cMjxGfh7Zl7lLLa19/rkjIh1yPqmpVUE8LdomdRuoHYHd4saNL1KBdFkV/5e0WWbSrqgbSyrocAzcim1siltVmE+zXZs07oSXxcq3xNzBFrdpRZ6wl8DWKPW5UzniImR4yxz0rpg9qyWRhSBNP0OscL/gAqF5F2qPa/j9RMbFu+pYn8L4t7Q0OnPDNsmWRNs1P0p+31GSyGoBq+/q/5KfcmZxRhLSVSj5hJQDUmfc/4ggPht+lX3DCt/AnwLz6m04h90iHyzzG2wTxjAIbsnnfKARv1xnfG+0S6Z2TUsrGWbe5reUiuTnUQtiax5t66XfwOA1GrWZiIov4Yehh+N4vF28fQVg+N8z0gY1VDXtZMq+A+WMJxHYxz6DTWUo0WvBSmykxfHhG+tHkpPSp+VvyuNAqo/nPxqtLf6wbqkYkCfzTJSeuvADKEES6OYORS8Q+BnRv8ie3zDTnviEiSQ1bR2Dd8uLiV2OpRRc0+p/KANXm/19oMA/mH0ljTSqaKmBma7iVH/9spwffCx21yZRRHoSQcxbET0XhdXp5eOyJQlqkm2g==
*/