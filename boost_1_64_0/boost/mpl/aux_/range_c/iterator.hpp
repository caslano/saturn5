
#ifndef BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

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
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// theoretically will work on any discrete numeric type
template< typename N > struct r_iter
{
    typedef aux::r_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef N type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef r_iter< typename mpl::next<N>::type > next;
    typedef r_iter< typename mpl::prior<N>::type > prior;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename N
    >
struct next< r_iter<N> >
{
    typedef r_iter< typename mpl::next<N>::type > type;
};

template<
      typename N
    >
struct prior< r_iter<N> >
{
    typedef r_iter< typename mpl::prior<N>::type > type;
};

#endif


template<> struct advance_impl<aux::r_iter_tag>
{
    template< typename Iter, typename Dist > struct apply
    {
        typedef typename deref<Iter>::type n_;
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
        typedef typename plus_impl<integral_c_tag,integral_c_tag>
            ::template apply<n_,Dist>::type m_;
#else
        typedef typename plus<n_,Dist>::type m_;
#endif
        // agurt, 10/nov/04: to be generic, the code have to do something along
        // the lines below...
        //
        // typedef typename apply_wrap1<
        //       numeric_cast< typename m_::tag, typename n_::tag >
        //     , m_
        //     >::type result_;
        //
        // ... meanwhile:
        
        typedef integral_c< 
              typename aux::value_type_wknd<n_>::type
            , BOOST_MPL_AUX_VALUE_WKND(m_)::value 
            > result_;
        
        typedef r_iter<result_> type;
    };
};

template<> struct distance_impl<aux::r_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
        : minus<
              typename Iter2::type
            , typename Iter1::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

/* iterator.hpp
nUMNW57gmMz0TQqzz+Jy6QaMAuS6nIZKxqiCb59s6XKZ+BcPP9lgJG3dRVlAnXaLtvj7Z4WUJrNmp2a3tr1Nxu1oHh7nDfIrILk9Yb1tpMF6PbaoJlxz7ASirwQdhQaKoLOefMiswEV4N/WE6ATFG/xEe2l7sij9dnoyZH5R9VrAxvPs7lVdboEoZobWe9bAra987E07Eq69M7/WywOhoIARLwUYmuhkTqsvpiHPRiVplRSz1xa3LYLgycnrrSMgxwWjzMl0b54Sy2dvULTO9FSbRUZq/LYxo70tl+f+71ucmMIO7MkK2KbGuVtSHgTMBR2ttVgmWT+7wnWWDTl9LPCKl+C2vVsDH1IsqOLrT8i8rspqX1eB77t3IUK7u4O+rFwioBJYVC+BHJoBBk09uK3Lr3UoAUNr/xgdzvYCMKWnYyZd7YvX/Nf78dhwVgwG7ZQmBIOG4JzrBmBHLz7mo5nZadfIo3Glni7hB35U79U145qxrBzuE04whXLegLmZdjOuCDzVbkh9idJB4R1GBLmiJKbjbUcA/A2pR0WAi0AH9G3mJRn+kges8w==
*/