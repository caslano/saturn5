
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
OjTyOIUthXQomuoIHEbfECm09FmIO3BVQlMF2FMYGGGY6I2EQyMl9Dam92EjzBQW74KJ7rPRe1RQ6wNSrfAunnnX+eYUgC1UABjCrEDFTaOHON3LMiQOQdQJx+Xev7o3gYgNHQ3F1lSL9Cm4g+cjhPY2akfJXQ1Wt0hdJTHaNelGDhYEV9CrEo11BDKFZURnER24lPpgqYuit063cEApCA9atJbv8Cuhk25oEKFXyF0Y1jA5Qvf8WaAUXYRWjjfKepuvI5o+e4p76LQ87qR2X6i9sTt+/caRUSb8Q4N1J7MxSAkV3N4Xd7On7WxR/Hhaz4qHWfFUzFZ3vweCYaMqbSKFIUboEqe0w7SJsVzRljmLYWOhnn16Ob2Eq4sLWP56NI/qlgpA5ZI7VDtXX8PVpdf63zfy2WJjysC28IXRGZxgZ+mw+uEmbmXjceJNiCCQy9BCuiClFRnSN8VAM2eV616BSa14Sye6Rhc69s/C0zAoIJTPac1qbFHS/IBaRigxOKNqW9qAnCVzmNwTdHKzI0LXE/CKubbj540Q2AXhwzH6HOfz5XqzWF2fUwNWy2JD+K/A9DnUGKp/QOMPtOSOA68cmkA+DKrmdExINzGxtXYTlr0E39z37H9zpvtDY6hEP1X4zrIgeSFnJKUn
*/