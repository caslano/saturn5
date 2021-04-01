
#ifndef BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED

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

#include <boost/mpl/apply.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl { 

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator
    , typename LastIterator
    , typename F
    >
struct transform_iter
{
    typedef Iterator base;
    typedef forward_iterator_tag category;
    typedef transform_iter< typename mpl::next<base>::type,LastIterator,F > next;
    
    typedef typename apply1<
          F
        , typename deref<base>::type
        >::type type;
};

template<
      typename LastIterator
    , typename F
    >
struct transform_iter< LastIterator,LastIterator,F >
{
    typedef LastIterator base;
    typedef forward_iterator_tag category;
};

#else

template<
      typename Iterator
    , typename LastIterator
    , typename F
    >
struct transform_iter;

template< bool >
struct transform_iter_impl 
{
    template<
          typename Iterator
        , typename LastIterator
        , typename F
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
        typedef transform_iter< typename mpl::next<Iterator>::type,LastIterator,F > next;
        
        typedef typename apply1<
              F
            , typename deref<Iterator>::type
            >::type type;
    };
};

template<>
struct transform_iter_impl<true>
{
    template<
          typename Iterator
        , typename LastIterator
        , typename F
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
    , typename F
    >
struct transform_iter
    : transform_iter_impl<
          ::boost::is_same<Iterator,LastIterator>::value
        >::template result_< Iterator,LastIterator,F >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::transform_iter)

}}

#endif // BOOST_MPL_AUX_TRANSFORM_ITER_HPP_INCLUDED

/* transform_iter.hpp
CUOHqoKHNCS8bnErBYVVD3Rzh7imzjWbHHqG0uI9MqTVR4tDr7Nj+ugHj/B49ExyN+nqy/vLDrIK2KcgJ9A35fVdkWPVjCBc23QxCFu3srXDB5L6IiPmdpaxD/tduL2AGeMP3DRd6ZcQ7FbV2Il16lXC6GffipBMJnqSbO5ITxtLJ8+R2iZIJFBU/awc6Dx0Zs4AysSzDi2MQhTAn6EgMEv4hLezYDCtH40+eI3eNkO8Yw5crVMfShh4+7gPKdLbU1fuyXAYF0qRQxXlCroQE7Oo83pRbaxNKdUz9TCfm1gKOVPLuiGMoxVjT65QHrD+/t+MsFfy+GiY5Y9gERS9txnhh/Z9f5FrgOE0UN0zbxIGVQxUHbaZ9s+/N2wujzV6JW7BT38IYuA2kofGfDKpEZUip+Mfoak4LjKAyFkEqa2ugKS0BMjF6azfIt49SVpI90cmxwX009E7w5SkFInHkjRurAgs0EdrpNIWAzOb1xL1Z5/UFiEI/ASzDTH/P7MJNqolr6Lj9TRc9hKq+kAAxc26YoyDORaSOCgIFoPjIFQjfYJQv809jbATJQ==
*/