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
45rA92TkrTk1U6F+4wKXGHmQHcsd1knDMOjqFqOqoemfXPhEVc8rl9yRR0YaIdXIzoXpTT9elqCbUouw/yMjUKbevY5JbAtKKS85LTgtWZ2+SCJ8lUYn+0h8UqI+3PO86Gnz98n/iDaaSL4qvzPniwdx2DAMHjLvIRw0MrPhBrFiBt3xXJpgRhmoNc+NaSjclcbSG2q5rMNhKl8B7gASI+q9dEL8JQcs0iMmylXeV7SYjQFSI3bMLLxCSZy7Ni7aLvqAfKCvrVOOgCb9H3NGOk7F+9tU7DRCv8fyrkaBuYrYh5o2yk1Xh/J2gF59/Zpms1tr5Mzgrt08N8rYjnKeKpaF4qbSZiliWhGjWEz11drvVulWpHo8/mWdK8MrTby5u3dk653Nclk76qmCMmTbn62vsY+vwe2GWoM5iEaXww7Fv96+RlDpvr+GxUu0hudmzzuoBWZOXpg/K7kc6sIDuwl199rKppBm4gMFbeLnBIWQG7OEqFWl0c+Car4y92v/ekVE+flCLLrAZC/eg/UvFglqz8yqhnrk3WnBnb8h4Z2j/MoY5B7aQ+jnHd7b8bYhOn3wOcsD/TKgCMojO5P/CaJ5XBqkDrMa0hpWjvxk3zeHPX1oy5gJ/lZKtbNj/cLcyRrm/+3pPrcMjj039LMle40t8PXvpj6TQ/w9L+T/N02P9s9X93Fzt3BgEvOwtLRwdWMyt7e/8oPWBsj+
*/