//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_PIXEL_BASED_HPP
#define BOOST_GIL_CONCEPTS_PIXEL_BASED_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/channel.hpp>
#include <boost/gil/concepts/color.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>

#include <cstddef>

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

/// \ingroup PixelBasedConcept
/// \brief Concept for all pixel-based GIL constructs.
///
/// Pixel-based constructs include pixels, iterators, locators, views and
/// images whose value type is a pixel.
///
/// \code
/// concept PixelBasedConcept<typename T>
/// {
///     typename color_space_type<T>;
///         where Metafunction<color_space_type<T> >;
///         where ColorSpaceConcept<color_space_type<T>::type>;
///     typename channel_mapping_type<T>;
///         where Metafunction<channel_mapping_type<T> >;
///         where ChannelMappingConcept<channel_mapping_type<T>::type>;
///     typename is_planar<T>;
///         where Metafunction<is_planar<T> >;
///         where SameType<is_planar<T>::type, bool>;
/// };
/// \endcode
template <typename P>
struct PixelBasedConcept
{
    void constraints()
    {
        using color_space_t = typename color_space_type<P>::type;
        gil_function_requires<ColorSpaceConcept<color_space_t>>();

        using channel_mapping_t = typename channel_mapping_type<P>::type ;
        gil_function_requires<ChannelMappingConcept<channel_mapping_t>>();

        static const bool planar = is_planar<P>::value;
        ignore_unused_variable_warning(planar);

        // This is not part of the concept, but should still work
        static const std::size_t nc = num_channels<P>::value;
        ignore_unused_variable_warning(nc);
    }
};

/// \brief Concept for homogeneous pixel-based GIL constructs
/// \ingroup PixelBasedConcept
/// \code
/// concept HomogeneousPixelBasedConcept<PixelBasedConcept T>
/// {
///     typename channel_type<T>;
///         where Metafunction<channel_type<T>>;
///         where ChannelConcept<channel_type<T>::type>;
/// };
/// \endcode
template <typename P>
struct HomogeneousPixelBasedConcept
{
    void constraints()
    {
        gil_function_requires<PixelBasedConcept<P>>();

        using channel_t = typename channel_type<P>::type;
        gil_function_requires<ChannelConcept<channel_t>>();
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

/* pixel_based.hpp
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
*/