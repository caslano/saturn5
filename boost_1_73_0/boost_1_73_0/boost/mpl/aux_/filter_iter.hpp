
#ifndef BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED

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

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    > 
struct filter_iter;

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct next_filter_iter
{
    typedef typename find_if<
          iterator_range<Iterator,LastIterator>
        , Predicate
        >::type base_iter_;
 
    typedef filter_iter<base_iter_,LastIterator,Predicate> type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct filter_iter
{
    typedef Iterator base;
    typedef forward_iterator_tag category;
    typedef typename aux::next_filter_iter<
          typename mpl::next<base>::type
        , LastIterator
        , Predicate
        >::type next;
    
    typedef typename deref<base>::type type;
};

template<
      typename LastIterator
    , typename Predicate
    >
struct filter_iter< LastIterator,LastIterator,Predicate >
{
    typedef LastIterator base;
    typedef forward_iterator_tag category;
};

#else

template< bool >
struct filter_iter_impl
{
    template<
          typename Iterator
        , typename LastIterator
        , typename Predicate
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
        typedef typename next_filter_iter<
              typename mpl::next<Iterator>::type
            , LastIterator
            , Predicate
            >::type next;
        
        typedef typename deref<base>::type type;
    };
};

template<>
struct filter_iter_impl< true >
{
    template<
          typename Iterator
        , typename LastIterator
        , typename Predicate
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
    };
};

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct filter_iter
    : filter_iter_impl<
          ::boost::is_same<Iterator,LastIterator>::value
        >::template result_< Iterator,LastIterator,Predicate >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::filter_iter)

}}

#endif // BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED

/* filter_iter.hpp
iLEUD71wLm3Y93isUWtAs16Hmx+DM+5kDIPx9BCaDfhhqnGj0YTGcXx0HDeP4eP1IKjAYyDWkfULlvEHGZwa7aR20ZXUIzeOodUgk5bCKaNjELmxa6fBvJCE8eTY2E3ylf1M2cJYVR3JVC41n8gefSCT+lsQY15a6XrZVOv5WzAFefasK7keyeADWaOx5GkMeEP8C5bIFlKZKyQrU8hKMwGuwctZSmumpUClGElEUi4k81qe5op4VVoKv0CXTHI3xZP9gDius5Sw9U5SidMPxs4VuLNcQkLXWacWciN4Dr9eX/kLH27TOoSpVXoEkYGMzkF05t0QhlU4iTCTCdfpUoxQm8hMXTF1h/hLaZFPU4nJjqLJMiIBxIzt3v5yxnIzYpRL0re28sBwtIE45Et7FJhMpK4lA15pEbmPOlWX2IoAs1I51B6GMjOl9BUDS7LlVFvUkdx8isOv8kDaybunSQ6onPWXa9TqIUgtTIqq9ELkF52E79BtFXrlekSueFjbXkg5wBvPZrMVtixrphyxkDJCPDBlAM8ZpWamc8NTYkWe6IH4KlOCk9jeAsmY2zE4LOleOEnbYX8mI6PzeeSbLXJjGWGFGqxQbBnyjYrSPGJFpQmj5UsUO+bNdifsN7qpGLZkk3e7w65I601x
*/