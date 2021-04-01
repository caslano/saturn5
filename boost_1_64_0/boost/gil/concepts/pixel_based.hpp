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
LWtb8gweO1xT7CJoKWXs22c2rQMnlhrT0W58Wgn0n80/D6fRm9ztTf0k9d9ZV4A6gUKDHipfKOwxhk9IeAQssFlTf2d6rpb+ueNKWQHMkWWVF9zUtwmkDGbrDgiEn8bsk1lO7jgL/sX7vKPS5KwQFpk9UVkAgz6uST7oPKTaeS7ZqTrj8YMRsJVMxBsa9Kezoibw/K5yF1O0+gT/ZYPCbsYoMaAj1y0/I2HlynTWC542vcfh9WKCPt4gPiOBd1goUf0IMkQgCsKwo7ZMtgXNuo7mFaLMcMXJcBYS4YpmnMRC9J+2l18TICV50A4cC1vrgHhCNlaIg+8eYLraxamZPWYNj2zMhIFC2hChMyKJqPepyySMmghYJlc+cYoqf54rHgoojqghpdyHhNxItWRcWVajK839J2ej1p5O/Q1iHbwhsNTcqZryAw8dTaAKJ/uPzUjjrOv2Fszcn2W8pqfJBy5faBOPqg/P6KAFQRMzwzElsl2M0uwX22H3giQ1qnoK4kSOIxogl7YG47Ysa1ePon62TOWiKpZ3lpxVJDO4jLovmHtkUiudR9a53w==
*/