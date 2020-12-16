
#ifndef BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct v_iter
{
    typedef aux::v_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef typename v_at<Vector,n_>::type type;

    typedef Vector vector_;
    typedef mpl::long_<n_> pos;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    enum { 
          next_ = n_ + 1
        , prior_ = n_ - 1
        , pos_ = n_
    };
    
    typedef v_iter<Vector,next_> next;
    typedef v_iter<Vector,prior_> prior;
#endif

};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct next< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ + 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct prior< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ - 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , typename Distance
    >
struct advance< v_iter<Vector,n_>,Distance>
{
    typedef v_iter<
          Vector
        , (n_ + BOOST_MPL_AUX_NESTED_VALUE_WKND(long, Distance))
        > type;
};

template< 
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , BOOST_MPL_AUX_NTTP_DECL(long, m_)
    > 
struct distance< v_iter<Vector,n_>, v_iter<Vector,m_> >
    : mpl::long_<(m_ - n_)>
{
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<> struct advance_impl<aux::v_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        enum { pos_ = Iterator::pos_, n_ = N::value };
        typedef v_iter<
              typename Iterator::vector_
            , (pos_ + n_)
            > type;
    };
};

template<> struct distance_impl<aux::v_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        enum { pos1_ = Iter1::pos_, pos2_ = Iter2::pos_ };
        typedef long_<( pos2_ - pos1_ )> type;
        BOOST_STATIC_CONSTANT(long, value = ( pos2_ - pos1_ ));
    };
};

#endif

}}

#endif // BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

/* iterator.hpp
yXMF7oLxgimCWEG2YK1gi6BWcFDQLhj8uPRb4C9IFOQJNgj2CpoFZwT2T8hzBUGCRYJNgj2CJkGbwDJTnitwF4wXhAnmC5YK1gp2Cw4K2gXnBI5Z0lfBOEGIIFWQKdgg2CtoFpwR2C8XeRJECFYINgnqBacFuiflmQJ3wRRBrGC+IFuwWnBQ0C5wzJZnCaIEqYI8wU7BCcEZgWeO9E0QIcgQrBFsEmwT7BG0CU4LdE9JPwVDBO6CMEGsIFuwWnBQ0CpoF5ielucKXAXjBCGCREGmYINgp+CA4IzAfoXIk8BTECSIF6wQbBPUC5oEpwWWufJcQZggVpAt2CjYItgtaBecEzg+I88U+AtSBXmCQsEBwQnBGYH9SumzIEiQIVgv2CZoErQJdHnyLMF4wXxBtmCtYLfgoMC0Sp4jcBX4C0IEUYJEQapgp2Cv4ICgWXBCYP2s9FPgKYgQxAsyBJsETQLdc/I8QZhgqWC1YLegVmBaLc8RJApSBZmCQsEGwV5Bs8CQL88Q2AviBSsE9YLTghHPi4wIYgXZgtWCjYItglpBuyDqn3JfQblgr8CwRtor8BQsEqwRrBdsEmwTtAl0BTJOgvGCKYJYwXzBasFGQavgnMD0gsyJIESQKdgg2CloFox+UeZCECHIEKwRbBLsEZwWWBbKvQWxgvmCtYKNgt2CWkGroF1wTuBYJM8QpAoKBTsFzQLrl2RcBKMFnoIIwQpBvaBNcFpg+bLItmCEIEwQK8gWbBRsEewWtAsc18q8C6IEqYINggMC63UiT4J4wQrBJsEeQZvgtED3ijxD4C6YIpgvWC3YImgVtAsGvyryKigUbBCUC5oFZwSG9dJ2ga8gQrBIsEKwRtAmcC+WeRBkCzYKtggOCs4JBr8m7Ra4CsYJ/AVRgkxBoWCDYK/gyr8r/678u/Lvyr8r/678u/Lvyr8r/678u/Lvyr8r//6f/o3UXWXTTz4X1dpJZVaM36RJATNmxPgHzJg0PTAkLHDa1Ji5ixMSeq8Luex1SakX3m/1Za9bkHB+q98NXFcv9cTnrwuYETM7KSZpXkJMwoI5i9MXyc0ShnFNc3nPNXNmz9EukHIMrU0Vvd/Pne1xy7g+7rH6v6/puUL7vv6/vu+9w/V8b7255/v4BPXVYu237r19SJgzu/fh2m9123u/57t07bfl32jf/Xfntb6VN/d8v/Divmn3X3/BNYtSkxYuWKJboP3eXWry+W5JQqrW9piHEtJ1CT3j9+mF1/AArtHa2d77jLQFjyyOW3T+a8lsaG1wbOn5vufbnvEJV7IwIzB+2uLpcQukn+eFquf72OmXfH9emOR72nfp70WIemUtc1bP9wkLUpPmJiUsnpS4MGkOj+E6+TfjMtddLLvRl7nuItktv/S6JTyScTu/T//Sa+RxvfLfxz14jMwv/V/fT10z1SPGb2rk+Z8v6VmP58ed7yYGhsXMCJseOHVyzJzEhDkP6S5oayz3uOi6862VfjOHh/u81zyRidnyTLkX4933vc5fMnuMdq87+7xmQVxyQsyixUkLUuVR2v1W932/86MQo7Wt/TL3S0uOiVsyp1fed/fdB5FrXVyPrhvf7zLXqHtp1zVf5l6MhzwTObiw/cEhFw7t7J55vvQahqz3muZLrmEY5BrkSV5od8E106YFBfid17y9a9n6gu8DpoYHB0z3CwvwV43peU4/fV/XyDyff6UOc9L/ctfEyOTd5qm7YP7c+37m+c4ladf49n2NdK73mvK+n3l+7pK0dtVf9predvWsd0Of16YujJk4Vb717NE/F7Tt7gsGVbtP7G+9cjA5YKrcJihwVoB/WGBwQExc/IMyZlzXefnrWJB67do=
*/