//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_BASIC_HPP
#define BOOST_GIL_CONCEPTS_BASIC_HPP

#include <boost/config.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#pragma clang diagnostic ignored "-Wuninitialized"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

#include <boost/gil/concepts/concept_check.hpp>

#include <type_traits>
#include <utility> // std::swap

namespace boost { namespace gil {

/// \brief Concept of default construction requirement.
/// \code
/// auto concept DefaultConstructible<typename T>
/// {
///     T::T();
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct DefaultConstructible
{
    void constraints()
    {
        function_requires<boost::DefaultConstructibleConcept<T>>();
    }
};

/// \brief Concept of copy construction requirement.
/// \code
/// auto concept CopyConstructible<typename T>
/// {
///     T::T(T);
///     T::~T();
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct CopyConstructible
{
    void constraints()
    {
        function_requires<boost::CopyConstructibleConcept<T>>();
    }
};

/// \brief Concept of copy assignment requirement.
/// \code
/// auto concept Assignable<typename T, typename U = T>
/// {
///     typename result_type;
///     result_type operator=(T&, U);
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct Assignable
{
    void constraints()
    {
        function_requires<boost::AssignableConcept<T>>();
    }
};

/// \brief Concept of == and != comparability requirement.
/// \code
/// auto concept EqualityComparable<typename T, typename U = T>
/// {
///     bool operator==(T x, T y);
///     bool operator!=(T x, T y) { return !(x==y); }
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct EqualityComparable
{
    void constraints()
    {
        function_requires<boost::EqualityComparableConcept<T>>();
    }
};

/// \brief Concept of swap operation requirement.
/// \code
/// auto concept Swappable<typename T>
/// {
///     void swap(T&,T&);
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct Swappable
{
    void constraints()
    {
        using std::swap;
        swap(x,y);
    }
    T x,y;
};

/// \brief Concept for type regularity requirement.
/// \code
/// auto concept Regular<typename T>
///     : DefaultConstructible<T>
///     , CopyConstructible<T>
///     , EqualityComparable<T>
///     , Assignable<T>
///     , Swappable<T>
/// {};
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct Regular
{
    void constraints()
    {
        gil_function_requires< boost::DefaultConstructibleConcept<T>>();
        gil_function_requires< boost::CopyConstructibleConcept<T>>();
        gil_function_requires< boost::EqualityComparableConcept<T>>(); // ==, !=
        gil_function_requires< boost::AssignableConcept<T>>();
        gil_function_requires< Swappable<T>>();
    }
};

/// \brief Concept for type as metafunction requirement.
/// \code
/// auto concept Metafunction<typename T>
/// {
///     typename type;
/// };
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T>
struct Metafunction
{
    void constraints()
    {
        using type = typename T::type;
    }
};

/// \brief Concept of types equivalence requirement.
/// \code
/// auto concept SameType<typename T, typename U>; // unspecified
/// \endcode
/// \ingroup BasicConcepts
///
template <typename T, typename U>
struct SameType
{
    void constraints()
    {
        static_assert(std::is_same<T, U>::value, "");
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* basic.hpp
SUo7cCKd4ApXZGRtl1nClExcNMNWblaYG81uyyygCbeNnsFgyJk862Az0yH2lBo1mANLGLUvPNip2Sg0WxyEW8bJ5u8Rf9H1WOieU6ENBaYJLCYNKaMUY6z70kr/7PE84syYdx696Aaz43vmzL8pA0jfxAoR3pWP1vHIYb2mCC8yFudSbCEq3fH1za+c9bJU2dZbRrWZavYGRoyp8o0hsuGvEbyoJRnH+/Uj7iyUFwPZ64mOByR4saN2Fy+Vn572G9ondrPFTAHtRc+jWMTlNRHhFaGuf2q4WB3aErvS7okx3nD3BGRQ2H1eeTA6CAtMeEO4Oe87pJ9zp5QoyVMHn7LQVXfZB1h77pKyUfIYiPTn9iUGhJwI6intI1g3m65do9W/j5hd+KW/ld48w5c1vWvpjDscN+3ZhBl0ZThsQ4zF8Y9PWU1Ypof/VR9wXr/Ivr5r4Ls5bLuD6dTR3nIChtLEdba0EgGFz07iG8dc3ImK2bi5R1S/0E+L5cgGgzNdbrWH+NWJwjJz1X3xjFfZDz38Xm0bqlN+/cln1b11cx7uxDlzbavyOw6pYg==
*/