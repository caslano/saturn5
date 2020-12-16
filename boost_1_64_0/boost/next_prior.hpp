//  Boost next_prior.hpp header file  ---------------------------------------//

//  (C) Copyright Dave Abrahams and Daniel Walker 1999-2003.
//  Copyright (c) Andrey Semashev 2017
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.

//  Revision History
//  13 Dec 2003  Added next(x, n) and prior(x, n) (Daniel Walker)

#ifndef BOOST_NEXT_PRIOR_HPP_INCLUDED
#define BOOST_NEXT_PRIOR_HPP_INCLUDED

#include <iterator>
#include <boost/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_minus.hpp>
#include <boost/type_traits/has_minus_assign.hpp>
#include <boost/iterator/advance.hpp>
#include <boost/iterator/reverse_iterator.hpp>

namespace boost {

//  Helper functions for classes like bidirectional iterators not supporting
//  operator+ and operator-
//
//  Usage:
//    const std::list<T>::iterator p = get_some_iterator();
//    const std::list<T>::iterator prev = boost::prior(p);
//    const std::list<T>::iterator next = boost::next(prev, 2);

//  Contributed by Dave Abrahams

namespace next_prior_detail {

// The trait attempts to detect if the T type is an iterator. Class-type iterators are assumed
// to have the nested type iterator_category. Strictly speaking, this is not required to be the
// case (e.g. a user can specialize iterator_traits for T without defining T::iterator_category).
// Still, this is a good heuristic in practice, and we can't do anything better anyway.
// Since C++17 we can test for iterator_traits<T>::iterator_category presence instead as it is
// required to be only present for iterators.
template< typename T, typename Void = void >
struct is_iterator_class
{
    static BOOST_CONSTEXPR_OR_CONST bool value = false;
};

template< typename T >
struct is_iterator_class<
    T,
    typename enable_if_has_type<
#if !defined(BOOST_NO_CXX17_ITERATOR_TRAITS)
        typename std::iterator_traits< T >::iterator_category
#else
        typename T::iterator_category
#endif
    >::type
>
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};

template< typename T >
struct is_iterator :
    public is_iterator_class< T >
{
};

template< typename T >
struct is_iterator< T* >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};


template< typename T, typename Distance, bool HasPlus = has_plus< T, Distance >::value >
struct next_plus_impl;

template< typename T, typename Distance >
struct next_plus_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        return x + n;
    }
};

template< typename T, typename Distance, bool HasPlusAssign = has_plus_assign< T, Distance >::value >
struct next_plus_assign_impl :
    public next_plus_impl< T, Distance >
{
};

template< typename T, typename Distance >
struct next_plus_assign_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        x += n;
        return x;
    }
};

template< typename T, typename Distance, bool IsIterator = is_iterator< T >::value >
struct next_advance_impl :
    public next_plus_assign_impl< T, Distance >
{
};

template< typename T, typename Distance >
struct next_advance_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        boost::iterators::advance(x, n);
        return x;
    }
};


template< typename T, typename Distance, bool HasMinus = has_minus< T, Distance >::value >
struct prior_minus_impl;

template< typename T, typename Distance >
struct prior_minus_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        return x - n;
    }
};

template< typename T, typename Distance, bool HasMinusAssign = has_minus_assign< T, Distance >::value >
struct prior_minus_assign_impl :
    public prior_minus_impl< T, Distance >
{
};

template< typename T, typename Distance >
struct prior_minus_assign_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        x -= n;
        return x;
    }
};

template< typename T, typename Distance, bool IsIterator = is_iterator< T >::value >
struct prior_advance_impl :
    public prior_minus_assign_impl< T, Distance >
{
};

template< typename T, typename Distance >
struct prior_advance_impl< T, Distance, true >
{
    static T call(T x, Distance n)
    {
        // Avoid negating n to sidestep possible integer overflow
        boost::iterators::reverse_iterator< T > rx(x);
        boost::iterators::advance(rx, n);
        return rx.base();
    }
};

} // namespace next_prior_detail

template <class T>
inline T next(T x) { return ++x; }

template <class T, class Distance>
inline T next(T x, Distance n)
{
    return next_prior_detail::next_advance_impl< T, Distance >::call(x, n);
}

template <class T>
inline T prior(T x) { return --x; }

template <class T, class Distance>
inline T prior(T x, Distance n)
{
    return next_prior_detail::prior_advance_impl< T, Distance >::call(x, n);
}

} // namespace boost

#endif  // BOOST_NEXT_PRIOR_HPP_INCLUDED

/* next_prior.hpp
zbDaq1cFrqNEwBodb8Kp5vd9paFT2tcLcwkykXO/Kt7yrNVawPfa7FMBj2pvr1GebG+pucK3tdIQvOIwhj/oe6uiGERqYUS2ixuo+xMp1PrlXEXrFQozNAFQtoKuo5tkd4kuxCuS4IJdGPDtrvAeVtfSTnVR7futctzRpJJ9rMRvPi9DGBsPST7hQG3WDF4hlQldG7niUCSrYMAdbKWQMRb8C2L/FvLNSTbhhBW9ExneLYkuSGQVHNVokdr9fSuT3FIxcSpwXAGUYsD1iIrBxqtEMeDClfK7+TiL7ee//7jfh99fpE4WnlpsnVTfIdtjy+C6jfuMvKZx42h1kmhAN/lL40RfPCq7BM7rgoJvAT8lr7xpkPJdHhVSTpcjrfcAzhooO0FsFmLhDJUlr6vGNeFd1qNMCN/k6qbYdxO5cw/1tSyx7uB+wjC4m+W8q45uj+3kw5vzqV5uUnKtOpbn8Ale5PibckK+GY6wougD9PL+i+6wRK2oErUCmylqfQ+i1iFj/dkEt54n844py3N8Dt/P7OhRPIHATLtUgJHhwc0AhneL8cy1alLf40r51VaqR47UnclUw7jN1cEL9/pk+nZjZLJ0qxFwWTZwjyWXUsmheptuvEnxlasHx4tFdtstoxZNsE9jLVY7jU/gCSueKDoc1PAFVpW0wmpqSS9Emne3pP6aS1XsDk/RHZ4Kt0VFP7pIVvxC2kxLjE296cdCGUre6Qt7LXQluplg37YE4gC/mUybF8+A2aXZ6ErTiBYrrxn2Afxf1aZ3ro2+iem0tIlxJk5Wa7kbcFfp3ED7th75b2FIfIRxcgutixTxnvGOJSRtSrmhk/AbrdR6SX0DEIX0g/u2Yj/UeNOnsr5iwnVh98yz1EFabsOqGqwzgcMEehW+KeFK5hN7++2yaoToQFSRaxWfOFjmVG9Vm5p9a85T5xeyJREgE3blUVQyQuoYqGGDtniRblHw+DSh4K9v6Gn7u0NFG9ph9MQ2o1SAEcPW3sNqa4/1P5uvKO+hDJRIbvvqS0DtE/w3/dcvG+3nZS0GeeDi9iBRB7Cie/caOZcqEqPPLjHyVVtyx/4C42abEtDbiaJclV7wdZRWSYk+amc14TYuRHGViI/6G4ks+fp6ayhvEnmMxFKv0QramjjFaFRFLrE2Z/+uXvPMpXy7u0i1NdGUy/5yAxh3BcXSgwcoOfX01iha4eF/dXpbHtkC0z/5ge6j+Wt0sLUphvaLiyykHiA89ysi57khg3jG2f20WFrqoMgd+Qrde9LpaeEk47nBSnoJSTAlJT0paIAbK6HsjJ9Yx94mOeQv+eM49UgF9Jrk40ZjWLJAq1GsHskdB/HR2pQmQz2D7ykls0+64pMLU3xy8RUqv1DydyWPRhDzPxhGJklY4nhSpmxj4LnJQ0koaqk82cm0B5Dmt/Yio3DPFBbJr6YXCIsEcSnIIqnDRxOHq4EfL9WtpOXfxM9Yi2FnOjWREFVB1HCZzQXW+K1bkcRPr7lE4TLq4HlZ2T3A8h/oIZL2TeiB2WDoqIZLNLifRU+nExSuB/jKSjq/p2ViR5LqpekR4nwKJnH4wDZYsH6td/uJ4KAXuEHnIU0bazzJJlehyewOTaoF4jcXqO8q2aRKeopQUuGSJkVv7Nyk5eN+KEuV40EOC5f5UtuMM8KpKXKVVf9pjg6YTcCJrt5q7VyrwAeiVS6x6r7H2sV8PU3hM+1iq3uQ5ZsHWYm7L1JIPj1ZSJ2qAdG14nNfQ0We0Av56m1B9f13U61QKjoftTa/Zymci8+Xr+Mz7Mbf5XN3FfciVUQQ5VZ6ybmqlggbVKgpEkBntrd0MGCdYunU0mKA2vxNtSpZSX8i9DQ=
*/