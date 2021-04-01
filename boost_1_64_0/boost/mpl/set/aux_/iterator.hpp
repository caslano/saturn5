
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
yWenqJvWae/Q7ynDy4hyggnZQxYpWb5ABFM9uwPJ2zosfZf4LFcNg8rwErCYdcYYVrpdinQ+7rDhvFqwt+B4no77/VD4zXHZog4D+61wAUredLsdHo/r6Rl+vcyXsTFfHeUE+PCjXoOCWZjATaHgBURiPvabCD2lQOPfYXe0tr63Kkf09n8QALjgQfse6u39KXNutnt29JiEnp2lrR9UQ3p7hVATrLw2L6gTjquAtblVmt/SdmWLLRgC2QCv2qShyhwxUBla6zACooDr8r0+n9OnANd9CCKBnOHe4YutDu4v7vnP+Tdl1gQI4VV9MwGGbz/nLWotcdGmpzNsoKCJKgqfNLYLJ9GoPj3rG+t3HT5UQs1SLAo9QUaDUuP9ijag8nDnZT6q0Sx3Wv2BG8kCGEOLzJuHd35qselC0vp1PWxbFBcgF1C4plmN5MMivij3ccxEnkF87ZpHaf+PfvQgjUIbujK9LjG3A93Gq0xOTjkxjhdmolz1q206Ie80HZo95Q8SUqkOoz6mhS+QkDHMq4azeJ6pKxjPcnyl+s2akGyds8TjRNCSkVRdVA==
*/