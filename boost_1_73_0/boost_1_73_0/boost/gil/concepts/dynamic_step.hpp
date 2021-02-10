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
NUhlZSHJG9E05ZHXNExJ+cQ7cU5u7QP2s21lLytUfEHuu7wDPXmHnkxs02v+RnWr+Ml62ugEXJvNhKWfdo9YI2CSbj+tQeU5JeuSZfeL4K4eq0bhfU6sOzfM94P/AlBLAwQKAAAACAAtZ0pSjR7qS5AEAADUDAAAFQAJAGN1cmwtbWFzdGVyL2xpYi91cmwuaFVUBQABtkgkYL1XbW/bRgz+7l/BJkARG4qddv3Qri+Y6ziL0cAOLGedsQwHWUdHt8l32t0psYf8+JGS32I5TTsUVWDLosjneY7kUcqhmmqJUzjvtk+7Q9G5Gl4I/pzXDsmsNO6502p8v6MGDXjyEMVH0EHnIuLSmr8w9vu9hbiH8o+irun8FEkLNiH3og5Ph9zDUREilizv+LcQTxFdszb+anHkteCfZKEwjuyYbGHVTeLhqFOHF2/evIZjeHny8kUAp5FWmELoUU/Q3gTwThaWX5JoPm86/BAAeojS5hJqlCgHzkz9XWQR6HeqYtQOJUQOJLrYqgldKA0+QZiqFKEzuBz3+r8GcJeoOGGQhcnBJSZPJSTRLYLFGNVtiZFF1oOZUjiBS+U8AeZeGd0kbgSPduYYg+mj1BmIbiOVRhMiijwk3mfu51Yrzm1K6lvSxK4Vr5bfTPxsvZIx
*/