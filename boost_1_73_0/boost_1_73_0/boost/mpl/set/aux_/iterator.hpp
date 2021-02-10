
#ifndef BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// used by 's_iter_get'
template< typename Set, typename Tail > struct s_iter;

template< typename Set, typename Tail > struct s_iter_get
    : eval_if< 
          has_key< Set,typename Tail::item_type_ >
        , identity< s_iter<Set,Tail> >
        , next< s_iter<Set,Tail> >
        >
{
};

template< typename Set, typename Tail > struct s_iter_impl
{
    typedef Tail                        tail_;
    typedef forward_iterator_tag        category;
    typedef typename Tail::item_type_   type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename s_iter_get< Set,typename Tail::base >::type next;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Set, typename Tail > 
struct next< s_iter<Set,Tail> >
    : s_iter_get< Set,typename Tail::base >
{
};

template< typename Set > 
struct next< s_iter<Set,set0<> > >
{
    typedef s_iter<Set,set0<> > type;
};

template< typename Set, typename Tail > struct s_iter
    : s_iter_impl<Set,Tail>
{
};

template< typename Set > struct s_iter<Set, set0<> >
{
    typedef forward_iterator_tag category;
};

#else

template< typename Set >
struct s_end_iter
{
    typedef forward_iterator_tag    category;
    typedef s_iter<Set,set0<> >     next;
};

template< typename Set, typename Tail > struct s_iter
    : if_< 
          is_same< Tail,set0<> >
        , s_end_iter<Set>
        , s_iter_impl<Set,Tail>
        >::type
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
ak0Ww4/FMzy5kU+1Kx+pfN530n17x0ZaibK1pNF2hPP+sJMGP4lG3JhO2Q3wm2edxaSVVbUaYkiO+TGASqSFHx1AfhQClwCBX20A5+rkXs5WFWdPK7ae6hdQSwMECgAAAAgALWdKUteBahmYAQAAjQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NjRVVAUAAbZIJGBNUl1r4zAQfBf4PywtfTpSNYnjNEaYhHLHlTuIm7qFwr3I0pqY2paR5Ab/+1vbIemLZe3HzM6shEfnlXSYMFE2haHjE/uTsdolLN2nS7ajLxP8GhV8KmS37BZe0X6hnblSIxMW26qnAjcGVa0T9rRLdzBCHH6mfz/ghJUyNcKP/R9Qna1g4ICpASxK3YM30x3EfLNe3G8e19EqXC7m/7ZDw8D/DV9o6WXCfllTx1Dj1hH46YgWA5aZGAr5idvGnCMBy43uh3M2CxhAbzrrwJWNonRFCcEnOMHPUkaNT1WJjT9rVOPlIjJhrWmXl5koXqD0nUUyStm+9YZy1xCIRtY4OTvaArLzRwIslfSlaaiATxUgyKdaNnpiiDm/+71/zZ7T+G5oTveHjD9GIcw66Ig7dqgseiK7tNHvedZRxTvasuhhEAiy8GQ3EcOwfjhK
*/