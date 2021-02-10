
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
dGVyL3Rlc3RzL2RhdGEvdGVzdDY2OVVUBQABtkgkYK2UXWvbMBSG7wX+D4eMUAjz5IRQFlcJlH4soUsTEq83YwPFlmtTxzLScUP26ydZSd0xuvRixtg+zuvnvOeDMBQaY67FhLC8TKW5PYn9TqpET8g0ipbNBZaLdeSe5rP5zavwdrGaNxGj7XeMOtQHWAv1LJSv80QQpkRV7M2vCUfu4LT/KYBBEMDiDvROx4XUglxzFCFEtfgIwQju5bNR9APoD8PhKDTaL/OIOG4I1r2vm4Cm/EkQsim4O4mx4TIxeshsDF0VuSjxYChuAiNwhAnJECsjP4bASr4VzirEtUa5hStZoiVE+0rALscMKq6MCoUyeuo+ABbL7ZaXiUOGlHanpkmzZdi1rOViFdGdoDteIj0/H4E/hbMjGA04hG1dYG7ISFOptr4t5ALijCstcFxj6n8+A/8WbLpxwstcFDZEKYtxXKvCFPHiwDwe6jT1PwiVp3uwPOCpMQ2YiaaNkHENGyFK6OhMYoew50Zr24Mqr6yZCdH0p//m8Z37vwJ/9KNH39bYgxrMRtZlwtV+fBp2UuqYZm6tT1YpiTKWxYTY9YQ/2n1Yvb5HplJjCH8NxyPfzA74l4+mbSHYhtLuw81qPVvce+QyjkVlXvdo
*/