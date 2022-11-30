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
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
*/