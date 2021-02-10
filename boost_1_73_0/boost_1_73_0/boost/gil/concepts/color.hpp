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
43O6++tFf2zNP0ipMeNMiBpSoUw9vzSaZt1+qqSGpjdTyC30AwHy19f+jRSGCW+lvz+Yg3efdhMPmf5b6DWh7RBCV5CVnmw32Rq4J5sDpyYrYxwWno4Y11JANZh7IV8JE9HwScPC2wK+0b2qZpAda0iXlMdU1r400CopcrG7vQlIvJqqd6+ZZbOrXh2UA5aGaB6udFAVS6D/SACIaBPSWRvCvGTUeDIhryMhogbvQD8zuShyckdq73fOz9HX4Fb9+Gly4TtoBWrcSCY8po/8XhTHBC1iwTuKY9gbV4RwQcQhM8Wz5AfwQey2Z7emZAV/3eQXma2FApze8RQikIPR6MOnc+vFbnAoDYtZ0tgjjhJ9MZRDAt3MIEQgyLnnEr+lUYf3sZ6DpsBKpK8G99Mppgs7GT8Cr8PyNNSnoKeLAmsSM5jNJaX7KgbteAdlZEkGbGPY7s7xCDiJBNaSVlXqUagF3xyrHgzxb5lZO7SQPKxMhGtl8AabLu4ljUIW/UoqKFi1F5iGXHxKmCYaap3EwzIy2MApHtPwwXhOxdaVj109btIAn6p0XqzqIFFE1bZw2htNB2fDfn/YA0vk9wNfCZlt5ldATjX0e/GaEbzNqCA/I3KXzT93kFeKZfr4Ljy0S17j0LaADConhFmH
*/