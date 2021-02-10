
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
t8R/sBLlMaGpKlVCN7SJMTXSVBiQbN1LRcAIVOAi7tKWf19zkGSt9tAHjjv78+fP9p3QpHSWKnJhvudfjrIocDDi7foaRNUW0gXxRP2L7HLlwo8khPBbvIPITyK4S/g4LOgF9/e+l8Chk6+9PrYt1eBto59BmDxOvsckAGFfqIQ9ss9hjjF1z9QtVZUTiI4Odc/+TDJNpl2TwV6v1nh9dYXeaK1kiywz3deVKikHpjvjQeSpTrGVWUnZ05dZT2rmgqrqukcGaWo1wwfMCWuAn0z0KdD/kk1JhD0VaCr36ooRU+WZOTBEmX64UOgDlFoflqavHHpyiIJSfeyI+zj44eS/mFG0aUNmYliQzkp8qXSJy5EKFWnUEodgx7YxbfOTf2rjUkvmsEcS5GE0DYOMJA7gdUWvaXOoacWu1e36xubvXTg6znT4CHUWrCoMouQkZ7wxZ3GTqsVdECeb0FmEUfDnweDNmCclvJ36ZTq5o64qejSjTwtNHeqSxrtcpgr3RC3OVCn1DMSzwTIF59Myk7UL29iPuA2y7Rt5VNZwy2PkMr/+o52tv79b4IfxzoLkIfRxY0G8+evza7mxzJsYd7+2m8RigRd6YZ9z2pdH9wZQSwMECgAAAAgALWdKUgadO5LtAQAApgMAAB4A
*/