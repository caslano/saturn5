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