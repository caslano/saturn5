
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
zvLJHqFSHboTkTv12LhRM2+YVlPkDK41VZCjnIUE6VYGzZOWpQpfF7NwhSe3YbNmZjHM7nMDqavuK0wxZ3PtiawQ2Z9yKYzXXMqSSxG1lJe4qN6YTuk+7rP05UQ6XafLhawFaMWn8DO9XI83Q41309g2bLTgQB7vX0UAAqHVVbHoIDWdV15RixE7OjJvf1E9uq0X3c7rL78kL8oX2rG0F2oB9vXZykPzQiHU5FJCDPig8ceolaBlRIMVZ7qcHGkZOGvTmOjtw33A//ufdH1d+jLc0bxTpLMf7BB2NWY80Xgl/zimDZCZfhwHpQfAKcZkZ/a+tolaj93Q9QJUFbcdbHJDf703ekPXt7yhryFiQ8Hzw07oU8KRPGysb7za72a3YU6/HYA5wR93aLkTm3B+M/iEAy154AU7kazx9zJfYJE4kMYWNRCegosPdcXZHme+ddS+HN0kNkD+bQDeVE852svTG70x/J7d0xaEEJ5nvNV4q4w7vsWt8k7jrTJ/dBvAevyxDNZH2M/2HtUcAkNr/N+WFvf2Z8eM0yXYCicb+xoP8oNRbWjyBtlke1Zy6lP6QjUWpAcASL4lJ0oVKz9DZdh6NhjoOumHMhj4/99/1Z/id0yb3Dq/Y9gZLfM7Nk1qWj9n9aZo/YXIsUo++9ApTdkj18eU3yHKm784pzn9+8+maP3/ptozd02B/n+z9X91bCP7v1Nb0t9fMKWR/V+L5ZPRvoLSBee0pl9/zBR7+SGtlV97cDPgFRP/f5zSXxHeAyQbYP6WDJ/pztBOBVRMgaUivba3JMIQNKs1fmzuOMs/3l99ByKWc7NxxtotQIi3MEJ8dbhSKh3qbMpzHjhIG23OYbaywgmLtV9zakn50C2WS7yVdD1oX7wsKDRPy7F89z4j+ig2zqQqyh3+lbpKLw7oyqoQPlutBdBpCJzJMwioGXiGK5sbG0pvsKH0BhtKfyaDUfrIUBp0gzkkZD/2mk02TdPQOGha1f7Dw5hrkAj3e9CbHHnWD6MUBXuZHjr+3ZimztPpPRD/Lr+Z84SaCae1jk9um9gyfxTqENgdG06280fHB7zG0q2SxflpO+xaFm4gpRwHRkjvwcvsFnAZQcXqfIlL0xCgwtA/0NFYRS2hkxWcJ+VRSBrHTR0BXxP+S7dG47OFAzX+G90UfGeKfHPO1Obw1cSBjeK/ndwS/vGjvIL6h1NbwydnbsN4o+Xh548R5722sX6lckK+nx4ryqNL78Bko3obkMDN8v0zVCGBpUACpkICJpCACXBfmGDFPsthH828pJc0ci/Tgdm2RIMF8rmrK1RX04e2IXZKh55MJX4ASzzJOaV3YY1Udgro4GQfqbQGBAhrBybg6YHpMb3vOb4N/NjydMYVM8wb21tKqmmBGTHQu54bDY8k7jZ4ioQ8hVbmJOb5caiZgjrB3QaP8CHp8OZeKGPWhrPAWLyRHa5BPWw+fzfu6Ovwocq0fz/bP00/QP43Kta/zqKzhcOuRefRp3QzXCG+C142vpTfJgrkmz+RVwtKFgfK6V+8pUXuVPMeeb8sykMVfLryyDS54mfI/zHrcHMObSKRlbuKgktxekWBDzbHqngNX64Q7GsXPTPHHDa1Dn5m9Hk0356o9T9Pagp/PDUR+p+5LeHnX4xrHT9/cXIz+t+nNqH/HUd7n49rxf6vfyv2fye3pP/9I5u8qDpKXlTvVN7r+mSpOI4QYmROlT9rIfQYm6ksrFDY/EeN3Z6pb8BhKQHX4ZwB934DLZFUhCaUQqNgBh//yJt5oqiQfJApVt9RyjBYuKaqg1qljH7sj7ypjYRET05Ln7jOCkG1hHtCtGWgv3T4wWyAOAVoKj2y0xbf2Ss=
*/