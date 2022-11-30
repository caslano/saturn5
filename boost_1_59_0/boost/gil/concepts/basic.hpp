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
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
*/