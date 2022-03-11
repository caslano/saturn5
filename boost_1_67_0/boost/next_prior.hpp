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