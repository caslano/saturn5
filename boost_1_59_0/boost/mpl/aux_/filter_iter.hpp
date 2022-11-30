
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
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
*/