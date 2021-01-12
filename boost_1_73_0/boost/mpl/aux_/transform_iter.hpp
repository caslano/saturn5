
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
bVy+5ldHhvFB7dzmh2aPfRfWF/ZX/D6Qj7H515p/pRlDmvd5H2JzThkelha6RXP32bZo3jB2bRiXL65st7KONULUH3bU362Hh4ZrOrNljT85MuduT0hf3jQWs6+7mR7yP7RlE7YptAEvDN//TOgruy0sc3OI9w77uNdB8eeVBaE89Qj113FCT5/MMr//wiHUP9ko279bf5UN+7JoGJsw1Au56U3oo5oUXmbcqKi8ZlVuN++2
*/