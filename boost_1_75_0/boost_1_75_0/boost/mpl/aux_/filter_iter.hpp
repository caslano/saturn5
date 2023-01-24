
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
FmiDE/xhv961QlJi67YLR4QYRa++CsVdgc3YMoxt7zENtc6PNJGNyzRw/XIIKhATXLDWWBVM3Sb7xUrhs9/i2JOOp8sFbIU5q8Nv94YlVQGbQXqZ15GsrDi7/ep3gyXofKOPZl7mJLOz5/oh3BddfxiWJ7ni1K/NEUWVnPiWa1nvwnZs0K7ig7XKTfJ3MuXYwTRsK3j36y6538aFhJm1/rXuuIGhYAtoos9N8rues4aCmcEyINVlW2Ere3it+MJVqUHFq74uNlRFPeOz17Ztvbi4x3qrMGvWcBQ5hUdRsrc5fdkw5IfN/evt3H8SGlE4j9k//rW1XZH1fykD+L/KoO5o7eXu7W7nw2ng6O0LcdH18bVxdOdUdvP2gbi42Hppebk72Vr7eHPauLhc9qIGE4yvMot0s2bbmrQdA9rwzDoa00VH9zBQTGHq4yCj9CSp7ER6xDGQy+JH9DBcGbB4JAAeoaQdSQlNPHMOneM+XQrhqDDX7DtPDv1uyO7T36ftXcL5dWHb2QJh75Ppiwtj5XNxxFtcmeA/fx+IZSzoHhcp339/RehLR9lkOGUbpyL9pO77XAKZhSs0MnDhIcrTk+dpnbQEG9s8G+dWj1Avktgok6w30ZYpkJ0c0LoN/ZpQU6jCHJUdLnKRtF/+SMifLqyNJfMOh9fYEo4HZ2NahtaZxjOzkSQp43wszl64kQK1eB+30n6zmFn2o6Hy
*/