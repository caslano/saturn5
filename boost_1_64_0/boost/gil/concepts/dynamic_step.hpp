//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DYNAMIC_STEP_HPP
#define BOOST_GIL_CONCEPTS_DYNAMIC_STEP_HPP

#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/concept_check.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

/// \ingroup PixelIteratorConcept
/// \brief Concept for iterators, locators and views that can define a type just like the given
///        iterator, locator or view, except it supports runtime specified step along the X navigation.
///
/// \code
/// concept HasDynamicXStepTypeConcept<typename T>
/// {
///     typename dynamic_x_step_type<T>;
///         where Metafunction<dynamic_x_step_type<T> >;
/// };
/// \endcode
template <typename T>
struct HasDynamicXStepTypeConcept
{
    void constraints()
    {
        using type = typename dynamic_x_step_type<T>::type;
        ignore_unused_variable_warning(type{});
    }
};

/// \ingroup PixelLocatorConcept
/// \brief Concept for locators and views that can define a type just like the given locator or view,
///        except it supports runtime specified step along the Y navigation
/// \code
/// concept HasDynamicYStepTypeConcept<typename T>
/// {
///     typename dynamic_y_step_type<T>;
///         where Metafunction<dynamic_y_step_type<T> >;
/// };
/// \endcode
template <typename T>
struct HasDynamicYStepTypeConcept
{
    void constraints()
    {
        using type = typename dynamic_y_step_type<T>::type;
        ignore_unused_variable_warning(type{});
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

/* dynamic_step.hpp
P1ZEK+PEWxSXYKEKF9R4D2x59JcCT1l+1odCQZPzmkXg+04BLxXIZngj5Gdu4Yo8E4jh4/eH8rafzvy55sbrHzWN46Vh2cpfcWiQSnVbXUTnyMRXnJ9mMPZaRXzVHfHrixXL+zlRaJoSTgnKS1fwSoNuPJWRlSGFvly1cBovKtWKPTrXBTu+jkN7mLct7rYztzrs1XfhwdJthW9qlg/agzCiWE3jdvcjRa/OFOWGCD2kcSFOMT7SkcyBkiGfQllrgBgwBe6Tngi7MhrEdPjH41V/pjur5AOp9YO/MONJ1jKNbUk3duC+a0NW652zOszcKkAqnt7G/A0LfBbD4WaWQdRIEOdiPsV/EskcwyoLjdXjtWq7vLAVGOJKQmvzuIsyFv9J4sA5ARlHGYhJ2FTQ6UYlO4SYYbTjmmTodxYpnBu3skn/4DCFEFpnv0gvkqmFKc0boASOd5ckWcYMj1AIg1B0kO/X4/KRTaCxZjnkDVJX2QnGMoHa+ap/LD3/tYOM5MyVbJ7hT0Rk2QxwEDQcisVVYE1yiYrMjZzghOP08ejrBvuZ1DSeGz2WNA==
*/