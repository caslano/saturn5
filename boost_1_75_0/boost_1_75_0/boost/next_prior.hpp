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
M2uuJ6Re2AveMQ303hNdr2dEaC/CudLbsnOhbHks0LJUYELutOM+mN/sVO0L9Frb8vhNeCoJ68PMm1CAMEA2kJtjf8TF0gccj4Zd0/XyjdQ6zcLVuOnBqYK2ND7bLq7mWzR9aiqqrOgmhdPxhNJH171a3HxIN0nLX8biNxpN3rgf1SXPQg9G2+TXv8MtrDZuI4BVrkawGmPabQTEKyyME8KSdWR7XZXShrYizpMw0fjfQfRR8OTJvxsOsqz3m62XlTkJy0xv4xfbdNyqPZ1AJyKWLOFRqjmJP2rEogFLqw+VS8lDFyw85MJ16L3hFBJ7/k3w5kqxCZ22G/PE8fJAnPl4uzRXXuMBPB4g+ZyzEMEbCosKkBlUxgAzOO2GaT5zEz7MIw2eUWC2CBllnDBuqRFvb/7Wo13vvAdtZlwpczPlpfRUrBeXuJOwnZbhS/FVH7nFTe9wXolfvPL3EAuUfd6NnCnLNSXaGNN4g7uz6dZGaettpA20m0ZuGX87MABP/ssSEY3RFMoU08gf5QyeG7YP8uS3NmhnmjaOl01V47/7DinimbUG9lhi0JH7dS8ze7aRLxPtyH0YRkHScIxiR+7KKUPgyB2W5Ad1JObsSuPIasODTu3ovE3YY9dXD8Ojd84ZkYnWFjC/19JOS4ZO++chvMAKzRRDve+gf2ANTqj4akoor7jZOSMuv6siBTw+R4klMzCZNm43ESZy
*/