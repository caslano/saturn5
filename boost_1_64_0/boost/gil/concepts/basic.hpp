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
c7mueLEwSDK5bRa32N/blypmkzBhJ1IN3DVWGlJJkDOZeHE7pYo0tFtye7t6U/k85CbVuX+T3i9qbofgbuzuV/pDd383JmxFRDmFf3dGf5lUf9XUX74fBN8LSJ1/jftEf3NjI0PKf/pq0R6Ks4Ly4xTFj/hR8ttowInj6SyzH2Dlp6AOT2e6+nMJPz9V9Ze/4CtTWMmPkOiVjCooWCg3Bf3ffPi1QxKSPdZ/t/znMfU3xpSOh/bjtvV2u8aqtq+nmOhpqlNFKGlq76RXy8usd/z35VLpZLInHS1vwhdUCASZx+Z2GFljjqxMtrev0FVoImt6TlmHrHzm4vnejH9jO1oWOiwaGKTB+rJXqY9Kr92hbOB/gC2yqMYCbavDdLZRyTfYrI11ShvRGeU2PWIcp/02RtwZx6E78Z19i+OO49TnTvi85rrpgxdF4cpsKPyDOxxXN922WOLRuulxixOtm95/ic1xddOjDu7qpmuWSjxaN317U47OM33ygdc4D7COXtJK3J1LaJdMLQfHvidL+R0rgUXOfffmO/YCd+e08I2B25En52Gm843E7XlY2vsf3EYOlBnh7/tcfpdFQN9Wbz+PeIAph9+Bw8MrytVplVDmp3ZHcJvP0UzL6TuRh7SE38/chd/9kqTe+HfP6DNd27u70wOOTtT+DxdHP/HTKPbXXBlWf9O6iufc9VEarNYUPcE7HbN52mMIidTDkC7N05HZEukb958uz5aYN3O4q5f0pPv70pmuf1cvoT9M/FkeWa735pqWuF1m5FxNjlv2wmbZAs6c5aDt/zbPLQfGmVsEnix/hTu+4q9zODJGyTuy2OZZMYq11ze/pu3XQRkFJmhh+6vR7q0i8kqm3R37mO1fRhYQ95tvMvVPrzP083yGmM7BwekK4h2lj+O/EG/wW0Pd+VmKk8I7ryWREF3b4t7Y1fey37/ryWS60v1x3wPvlmC/p8FH21EZ5pK+fC7fB4VRhxmeHD3ovJt73OL393bls+lUUvNHJye0Myy+QftVye/sziR7oI7ilk0m4E0Y3imL15fv7y125fBWdZfD+7bFK+Z6YdtH/AMpzeNeu+RBdejLQLXJZRZmM4xYA7Rb8aaKfb2J/nS370t51L0fvkFyu5LxYlK9kNjbG/iaVtsH0H+gAgyjPrboc10XiD59jhdVzUgL9yJcTjD2I9naTBiOEUcbucrOHspqacTrajbc38nJpNPIauTqabUy6rduNl4xpyxyw9hM7qU5PDFY0ca0e3EEJ9itLHOdL/inm/B1T2MAvj+0hHy3r7O8Fi91OW6/Dctr1uei0l2n9XIwUzUmdIU1y0yYKX/nSO1EQax41ygSh1dikIQ97m/kzRkv9aDntoLv+Mbi3u0KYNb4Jt6aIGaNbwx78nY2PiF9UJ8rsGhbDeO5LuAycToi1t3ROwjcqQ/6+Hpu9DiKQwGhbvCcSA7fwLnI8J5HntvADk6MhPvfnWYMf0E0P6I5ejyj9TranWThlmjf8WWiznwK4yzRlvdUhdcgdqZi3rgwWHxWYCpzAut4msDUElLYcc48nGkKrGTmaEiwppnOG989F9jjb76YzfVle1L/7vhr5MXlmIoBv6+Y7Cv2pBPRa0K0bbnsDZZgQ3HVLrFHcC10YlUTG01VpBJDCTVmiTG4tfl8Sx6OpUme21bYNuMtgue0u4uMLMVZUHuiz/UofrDCLO/HgHxFqVKbHBkTYb6twiy4Dep3wRYjjNPG7HNMwKNtslwT7l5Gjr+I0gzGcZa4tCujr3EdB3wBdmUj7+pzyBf9RsxJqyQu1uSYkEFjvOtWg7cA+7SJ9wbBF4MU17VX3U7hY6gdnsNRfa+8d1/g+/k=
*/