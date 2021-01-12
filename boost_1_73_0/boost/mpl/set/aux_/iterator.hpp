
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
/biTfd9m99ReHt+xx9W040iMmzPrPuO7M+jR6lrrHvh7M+j45+Za6IolWWMczfRYceJX2bHAWB6a/CJIW0niqD3++nt9eE4uMLR4eGfA52kwGa9OrI9UNmbPnz5o29CaP/Pov7Xp7piZ8Xi5T/9dTvr10OUTHl0rwmSBwBds++BSlevNxo2xrDb2s1w8jN3tsfDPfR52ATBD9lVlZfbQzJPnbHY/pwnloD4eCM01c+bL8Wcv
*/