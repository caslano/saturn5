
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