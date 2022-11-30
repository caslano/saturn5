// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_FUNCTORS_HPP
#define BOOST_PFR_FUNCTORS_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/ops.hpp>

#include <boost/pfr/detail/functional.hpp>

/// \file boost/pfr/functors.hpp
/// Contains functors that are close to the Standard Library ones.
/// Each functor calls corresponding Boost.PFR function from boost/pfr/ops.hpp
///
/// \b Example:
/// \code
///     #include <boost/pfr/functors.hpp>
///     struct my_struct {      // No operators defined for that structure
///         int i; short s; char data[7]; bool bl; int a,b,c,d,e,f;
///     };
///     // ...
///
///     std::unordered_set<
///         my_struct,
///         boost::pfr::hash<>,
///         boost::pfr::equal_to<>
///     > my_set;
/// \endcode
///
/// \b Synopsis:
namespace boost { namespace pfr {

///////////////////// Comparisons

/// \brief std::equal_to like comparator that returns \forcedlink{eq}(x, y)
template <class T = void> struct equal_to {
    /// \return \b true if each field of \b x equals the field with same index of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::eq(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct equal_to<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::eq(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond

/// \brief std::not_equal like comparator that returns \forcedlink{ne}(x, y)
template <class T = void> struct not_equal {
    /// \return \b true if at least one field \b x not equals the field with same index of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::ne(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct not_equal<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::ne(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond

/// \brief std::greater like comparator that returns \forcedlink{gt}(x, y)
template <class T = void> struct greater {
    /// \return \b true if field of \b x greater than the field with same index of \b y and all previous fields of \b x equal to the same fields of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::gt(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct greater<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::gt(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond

/// \brief std::less like comparator that returns \forcedlink{lt}(x, y)
template <class T = void> struct less {
    /// \return \b true if field of \b x less than the field with same index of \b y and all previous fields of \b x equal to the same fields of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::lt(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct less<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::lt(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond

/// \brief std::greater_equal like comparator that returns \forcedlink{ge}(x, y)
template <class T = void> struct greater_equal {
    /// \return \b true if field of \b x greater than the field with same index of \b y and all previous fields of \b x equal to the same fields of \b y;
    /// or if each field of \b x equals the field with same index of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::ge(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct greater_equal<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::ge(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond

/// \brief std::less_equal like comparator that returns \forcedlink{le}(x, y)
template <class T = void> struct less_equal {
    /// \return \b true if field of \b x less than the field with same index of \b y and all previous fields of \b x equal to the same fields of \b y;
    /// or if each field of \b x equals the field with same index of \b y.
    bool operator()(const T& x, const T& y) const {
        return boost::pfr::le(x, y);
    }

#ifdef BOOST_PFR_DOXYGEN_INVOKED
    /// This typedef exists only if T \b is void
    typedef std::true_type is_transparent;

    /// This operator allows comparison of \b x and \b y that have different type.
    /// \pre Exists only if T \b is void.
    template <class V, class U> bool operator()(const V& x, const U& y) const;
#endif
};

/// @cond
template <> struct less_equal<void> {
    template <class T, class U>
    bool operator()(const T& x, const U& y) const {
        return boost::pfr::le(x, y);
    }

    typedef std::true_type is_transparent;
};
/// @endcond


/// \brief std::hash like functor that returns \forcedlink{hash_value}(x)
template <class T> struct hash {
    /// \return hash value of \b x.
    std::size_t operator()(const T& x) const {
        return boost::pfr::hash_value(x);
    }
};

}} // namespace boost::pfr

#endif // BOOST_PFR_FUNCTORS_HPP

/* functors.hpp
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
*/