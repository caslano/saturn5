/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   logical.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains logical predicates for value comparison, analogous to \c std::less, \c std::greater
 * and others. The main difference from the standard equivalents is that the predicates defined in this
 * header are not templates and therefore do not require a fixed argument type. Furthermore, both arguments
 * may have different types, in which case the comparison is performed without type conversion.
 *
 * \note In case if arguments are integral, the conversion is performed according to the standard C++ rules
 *       in order to avoid warnings from the compiler.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_LOGICAL_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_LOGICAL_HPP_INCLUDED_

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The trait creates a common integral type suitable for comparison. This is mostly to silence compiler warnings like 'signed/unsigned mismatch'.
template< typename T, typename U, unsigned int TSizeV = sizeof(T), unsigned int USizeV = sizeof(U), bool TSmallerThanU = (sizeof(T) < sizeof(U)) >
struct make_common_integral_type
{
    typedef T type;
};

//! Specialization for case when \c T is smaller than \c U
template< typename T, typename U, unsigned int TSizeV, unsigned int USizeV >
struct make_common_integral_type< T, U, TSizeV, USizeV, true >
{
    typedef U type;
};

//! Specialization for the case when both types have the same size
template< typename T, typename U, unsigned int SizeV >
struct make_common_integral_type< T, U, SizeV, SizeV, false > :
    public boost::conditional<
        is_unsigned< T >::value,
        T,
        U
    >
{
};

} // namespace aux

//! Equality predicate
struct equal_to
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left == right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) == static_cast< common_integral_type >(right);
    }
};

//! Inequality predicate
struct not_equal_to
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left != right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) != static_cast< common_integral_type >(right);
    }
};

//! Less predicate
struct less
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left < right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) < static_cast< common_integral_type >(right);
    }
};

//! Greater predicate
struct greater
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left > right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) > static_cast< common_integral_type >(right);
    }
};

//! Less or equal predicate
struct less_equal
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left <= right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) <= static_cast< common_integral_type >(right);
    }
};

//! Greater or equal predicate
struct greater_equal
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, integral_constant< bool, is_integral< T >::value && is_integral< U >::value >());
    }

private:
    template< typename T, typename U >
    static bool op(T const& left, U const& right, false_type)
    {
        return (left >= right);
    }
    template< typename T, typename U >
    static bool op(T const& left, U const& right, true_type)
    {
        typedef typename aux::make_common_integral_type< T, U >::type common_integral_type;
        return static_cast< common_integral_type >(left) >= static_cast< common_integral_type >(right);
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_LOGICAL_HPP_INCLUDED_

/* logical.hpp
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
*/