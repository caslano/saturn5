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