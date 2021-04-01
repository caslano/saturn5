//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_COLOR_HPP
#define BOOST_GIL_CONCEPTS_COLOR_HPP

#include <boost/gil/concepts/concept_check.hpp>

#include <type_traits>

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

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Color space type concept
/// \code
/// concept ColorSpaceConcept<MPLRandomAccessSequence CS>
/// {
///    // Boost.MP11-compatible list, whose elements are color tags.
/// };
/// \endcode
template <typename CS>
struct ColorSpaceConcept
{
    void constraints()
    {
        // Boost.MP11-compatible list, whose elements are color tags

        // TODO: Is this incomplete?
    }
};

// Models ColorSpaceConcept
template <typename CS1, typename CS2>
struct color_spaces_are_compatible : std::is_same<CS1, CS2> {};

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Two color spaces are compatible if they are the same
/// \code
/// concept ColorSpacesCompatibleConcept<ColorSpaceConcept CS1, ColorSpaceConcept CS2>
/// {
///     where SameType<CS1, CS2>;
/// };
/// \endcode
template <typename CS1, typename CS2>
struct ColorSpacesCompatibleConcept
{
    void constraints()
    {
        static_assert(color_spaces_are_compatible<CS1, CS2>::value, "");
    }
};

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Channel mapping concept
/// \code
/// concept ChannelMappingConcept<MPLRandomAccessSequence CM>
/// {
///     // Boost.MP11-compatible list, whose elements
///     // model MPLIntegralConstant representing a permutation
/// };
/// \endcode
template <typename CM>
struct ChannelMappingConcept
{
    void constraints()
    {
        // Boost.MP11-compatible list, whose elements model
        // MPLIntegralConstant representing a permutation.

        // TODO: Is this incomplete?
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

/* color.hpp
akkhISQ68koSA46LOQh4HR/KER7SFR3naX4WvB/z9EpzrmPQV1MfzvyzpLWyHgwctE2YGhIjSIXFPFwYn6rxXO4xPbWFvDdSDw9ao63U9I/aVO1dGcLPJgDNU8MCL4dfqDUT9JcfdoFBE++xiTOvG6znWuWbwfOHBPT4hOxHUt7ormJnPIEhAfFYOJPtzGuF1yZfrWlRc5hPifIJy5/KkoLHcQKypgBM+Ip4xWptQJ0p0to66mtcLKjArT0VKPPlQvHyWSqS5CxyBNUpM4XcHiZ3tucHs0eCAqeoT+kYdZUhkc1pJsFUhAQJFSmahPx66HZs3u5CQmDwqY3W3MVgicErAajfMIIcOhNtRQuHdzWkV5P0y6DclwBl47dAB8a0dzJSxnuXTLlxpJNzX8Y0t6cw+lGrn5PmCgOO/c4fpM4GiznLWrnzf+8xrx01SpCIur8+kLA05qTRbX6bV4LXBO1Ka4n9eXOrQfaPn2SDd9WI27vw65FhnMo0ufBKcQmsFe5uBWfrd1EfIKKqeNYgFAZa2ORwSnralXnQP98OZIfz+cVD1ALwmRBQIw==
*/