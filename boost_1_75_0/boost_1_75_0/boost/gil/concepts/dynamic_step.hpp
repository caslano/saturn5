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
PKKKvyV/j/AFC4HUbwxGk0S68oMITCVCrQ9EvInv+4SZcONZLjUh68ZRSIDWEXoHdpDBLYCMmyVx/xLciYgmoRrk2ddk0Q+3XHiDtgaPC8bJntBDfkPPJ16gfSRsBjdmvSERmTaTEUcN+TCNaergIbkUzXRvzY4Ai6FPHrsbDnkuVLdGaAkXGI4xk6Ix4A7NnnQB43uu9hZLDI3hbrUgOKU5EBnDhOZr6BGN4t0hTTqcxKc40RFdHlk9FOcfpSAuLYIUQTaHn8fnBfuVTC87xNMKqY3YxPjaQE4bjnM+hTaUjwBqndQC+rukD6RXhVUkCK+90gQDD4kFdAVEQVoP5FmsHyxcnFcvOnYBLBivNTzyw9o7hjBkVJyenFSMN3WvbMNaABs1exG7qfISLvg4XzeYIguZXo5/kZhRmro4yCmFkZTicxAuAAbrFQ//2xmwVra25EMgfztNV4o5EGFPHTyVQj/gf1QeRrFsEtJ/X4IE2+YNgkhCaeKJu68D59KPmBvlSAJeyj7YYLxql+kYkDkcu3gwCkkEu9BMm8Qb2hWdOXMa9nB1uqySlSuOFxJZxuP9d0wmVrT88SZMm65+YY3axEesCuzngzjld5V4Kl0/gOkqfHFJBQqPJDNLzs1NdRqkWg2fcTU2RYxctfq4RQBAs3IyCizbRkMBsTG0EQ0BKFpRjKgxmi/+OvCPlEcvWYmllFz0x2hclltx
*/