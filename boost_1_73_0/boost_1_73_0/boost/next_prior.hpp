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
P/vElO6ZH8XA2JkfhMdHyIL5aP6WWOGzeJ/t9hnrg3CQ+IXe+nNKrINO8LY+i/ZbEHQujezBRxISP8rCRy6ND9B4Ib5A1ymSRLz2toQPahlsNtBjYci63yFvvsdy6TGz7QlL97tdnGSi0HhmO4PJhGUeCBMMPeuDsxy4o7HtsHsvCVBsUxwqeh0oltc+yOE9lwb1LojW0AKgCwSdGHU6XEDTsMM96nkQkAd4+S0JGpQO9xv/uI+D/86HcigJQPMuTtMAx8su9LKbmA8nB1mMDcchuPWiRxDr6Ca43Scejr00h+peYSloNZYGVjMsDMMISh1jVYnvZbILU07snR/u2Gff3wXRLRdh6ubrfQAKIH1MM3/L9juSfITtwofE3+zXwAQviEAtedEaGsIG63WcbAhJrAQDex1UGQzSjIbIne+BhIiav5Wt8L9la2RCyqDFf+YgKHG9dOevg5tgzRBXCnWjAEW+gKfxFLHtd6RRes/72+9IBtJjgaO7jYFx8fV9EO8RBoh7e0yY2T1QAUwR0pb2hUiAStpvQdqIryAu1ztuafhIjjmZ2KjueQKqoqCcj0nC11uNf34I0FxUkn3Ebtdr3pG9m8V4iJ2+BXmKv6C4Q/dh+6DjoVGKNaKzQGtsWBRn/ea6Ef863m5x
*/