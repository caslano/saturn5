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
ATil9CDy2w1aeSazrRKKdvmdqQwJ/LM8KUQOzpOQD2TwsQlI7MNOll6HZeCnIvqf1qVznNRCuiZ/8psegllXuakVovGJiDojPEG8MzqTpwCn35iW9/KWW+wIfnONd3/1HTk9aX1eMr/K4vM3RFFf5zQYObl/tfwU7TA37BjdufW1htX3ziKJtWA+0zPvVPktcSBOEzlC4ner4tAOLMxszIV5IsDHhkGRE0Cn4J79DU6RyWlRHOmsVRpyWyEcnaAqiT455EKj/0uauiI8i2hqYznryt5WLpmozzu2pUneDdGba6dWtKK3pC0li9JIGZmfLWtmReTPqlGx1dKOTJKw6IlX0hEyJmtuzeepamux96ngeKSK5WjLM6eKso3j5phvtjASppCUQ11tCfvzNSbOC0Ekf4WTzQCHwzg1tFkOunkfWx9q2j/DL6SI6cDD80kNmMu+8/H9KZYPunn8gWK8aHKV8aqrT2FxZbdqGkcD0V579w8dFHANASkyXHN4IG7MlI3v77/j7eHbMyCj7EYdbYfjxeG/05frmKZW45pUdRYVzYyYjMW6cKfGRHrx8kjDuYYhiIfSOEWlvDSLtgBbhVeIZlHwYnm/h+tNqodIyhnNB8xa/zpotn7STuCrqnMeGHyIktgpViR6hswj8nx7X4XSBzW8C3vVt1ryD7BSjyfH85pcA/J6cO/z5YGA1Qnwi+iK7mLdtyd3hPQg
*/