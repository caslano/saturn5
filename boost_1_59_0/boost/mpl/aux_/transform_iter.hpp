
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
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
*/