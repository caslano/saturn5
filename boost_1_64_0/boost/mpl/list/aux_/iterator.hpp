
#ifndef BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
};

template< typename Node >
struct deref< l_iter<Node> >
{
    typedef typename Node::item type;
};

template< typename Node >
struct next< l_iter<Node> >
{
    typedef l_iter< typename Node::next > type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
    typedef typename Node::item type;
    typedef l_iter< typename mpl::next<Node>::type > next;
};

#endif


template<> struct l_iter<l_end>
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef na type;
    typedef l_iter next;
#endif
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, l_iter)

}}

#endif // BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
aUDGKts/qwyKpGbPUzE2lztHt1WhfJ7Lhafiz/nmm4yl3m+6CAzLkR+Sp5u6uG2yVLq1+maVscBYoobfT1+nF3wp3jLP2sPjS+Jo+2sH8hRv4uoyBFj8CqmFCRYxs3ONEUFfcQLJ09aM4XLwnk7sZbDGhdKc6b3WsxPYMCINN9RPZhhWJUFJatXCZ648ZE5aK7rZ+Ww5MIHrg5gCiKPArqBIZ5/sgNLFh72I32IOrx3Y4xKLd/zEswa0WndhhbVtuMQ2H1p6WV0CC5IOWrdUuWeEoDp9n+8feR2OyPNhhYf/81yL8GLK4JtZ2xbE/rTLvwOVxGul6kXADfDwxCRK4tWrOcCJLuhKA2gg1OLn3T/ny26GOtJTAxer+0EQC4ikWsf2CcyGItrNkTB32b8Yowri2XBaJmCdWnnoqAyWSGW4PWD8rK48ZTpKw9HKuKKn4AUlMW68EMgztFfd6NDz8zsMuSjEWWWD+VexHin/UtcT4bdtRH94AdOKcy/iPvBFB2Q70yhb+16RN4wwaFmrajemmiyHT1NGsRml5Xl8yeBhT20Ks2EIXiQ56A==
*/