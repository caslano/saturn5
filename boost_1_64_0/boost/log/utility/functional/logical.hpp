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
eoy9302rB1vzaetJsR6t2XudgCpAOwP1ZvVh5bK1F8qGP7HcMvb+YqBdgC7RvVfG3vM1eK8/e28YUB+3eq5n7wUZvBfL3osDGgg0GeghG7R7T1mqPOcjXYCUDv+/HNJ5SD9BiuglS/GQNkBqBs+XgUq9ZSkP0hZIVZDOQroM6Qak4EhZagVpEKTxkFIhrYRUDukEpGuQ1D6y1AhSJKS9Az2laKDxkAohrXHyIJ2AdA3SLUjt+kJeSGWQDkE6DekKpBuQwvpBWZASIRVCWgNpC6QDkM5C2vKqj3QTaKMokAMpFVLkWx5SIdBlkDZAOgHpEqSbkJT+IBNSBKQoSFmQyiCVQ7oFSR0AsiC1gxQFaTykVEjXoe1WAq2CdBbSZUheA6HNIHWFNAhSHqQySOshnYaUfkyWLgC9Akl5zUcKgxQJKR5SKaRySCcgXYF0C1LA6z5SK0h3/u783fm78/ev+lMgZUq2QJxbe8Xn5qXlFOQW5aekVf/fgqz2yUUZWantO3Xo1CFiRvvigs4Rne7Vfivp0b19QXpSflpq+/y0rLSkgjSeIyV/bl5hbnxyBqSCgoQC2BbqkJucCXtwkYFSmCQ5JOe+9fNJkkZHZaTk5xbkzigMazWuddiYvMKM7Ix5GTkzwwbmZudlZKXlSw3hZMY7HWF9US5JspSdVpiem1ot2rmHHh1YEC7BPmQA1uW6jZ01gGRj8/Z7sPi40QZx/YDhYxJy0ubgy2mFbE8IKPw2I1Uy3Ktg78J/QrW8KVm5BWkJM7KSZsKj4X4eewflZwfgriOWF8T2EH/G3++BvJAH9vBk4E2FlwtrsY/H9wMKIYUwvRsCz0vjifrJoGFn1j6D2PrfzgR6QvoN2CWirdY+Bax1mB6GfyMCmdy+TG47D/YNKMlFvwyFdYYmF6Um5OTmJMxIKkzKSkjLz8/N17U/PLP2CQQ6CN9rCj5S19AmINd6X07b81RRv5XO/LrnMu3ZM3BO9f9vFj26q1vbgk5u9azPjHEPKySU1TOinVjPgvTcoqzUBDB6/ly2L8rqmaHVsSu+EwTrPZtRHZlMm9ZGEtPHj70/BH/3lvgecFG4VKPN/IT6ZcBzz8Aohv8/7Ml8he2RNbKzs0iSi55z+kprrCvWM6UwPwvrx/zcJiVre2TzMN9d2r75GHxuYVzX1mJdoY9lpxr1Lbe8QZg3pygbqNE+qD6vB+7j5RXyNqwLdBn+XgffDdC9G6B7l7dvcS36Jvev861Ff6tkz0Hgb3tbc3/r1ElivK0uXoTE/HKjxuuJz8Xaczd8HqE9d9Xs6rRBCNggSD8esLYEHmsf4LE2Ax7W20MBHmsbvQ+ct2v4TbIxfPR5MMRG27h8YEZ+WproA0naOLcb83WRHMY+DnLENp5TqzbW1zVJ2NfNc0j414K90Jzpm6fTFyYAkKH5a4ak61OFmK+JcWynTe3GnCBBP5Dv1qY7vDQsKTkgtYJ0ERrrRiuXjnlFhQXA1uuZZzw/sfeYjwdi3gLBx2/i72HG81Qrfb/T5imtPYLRxzwlH+33HO237/DdOprtSmphO7FtsE6arwYir8DNBxnghb805oM44TUFe+jaKz8tKdVoHKoPvBWYb6ixTXX1z8PxIbdIP08X4e8J4E/djeN2Qvux97OMx6I8i7auB/Qx/L2b5IxBV4Dwz7xhTxba1ONe35Z2RfWGrqgf603nhcpWrm9d87XFuLslaU19ySIehPYxHUfygBmitQ2MI9rYgvXFeaQUy4W90J7Vz+vZ8yfs+WAr43kmWmXf7YaE6yBIr3QE32zpsu+c/IzCNBP73sZ8I4z7Rkv3vpGRY7pma+lmS8ibZTyvQF5rW4bqbLkM/Pc=
*/