
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
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
*/