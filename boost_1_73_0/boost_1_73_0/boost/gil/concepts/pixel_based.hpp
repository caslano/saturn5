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
eSfUy2+Pi4lZySeYxCR4FOm0EEUqZrlsCazZEpN0GI3wLwAECqez2zjKxy07GxgqGXbSTOQyjrEvaBfJnKctxYUCTwuriSnMOCrwT54mOQ71ME4nXkWAI/YymmUJDARwgErDFMDcErNkKDOqTCvXQyiYEoAXbo2d71CkCUxG1HoX4viiJm6DPMpb4uPx5bvTq0vxsXd+3ju5/CRO34jeySfs7LfjkyPY+ggGy4T8Ms1kDoNnIppM40gO1Zj/ez+dtbVvoiSMZ0Mparh7g1wWs2l7XHMfQPkwKAIs9QqDabQTJYVfDosPg1z6hcO0gP/nOvALAI2DaakhzSksHsvlUSKLwbQA/MSpdrYIS+MgL8QLYWrhNuUa5W8lk0eEAMXdhcWXxplmsJpRxQQmcpJmj/4DKBvK29kdTQB4zpb4cHF0etH5GCXD9AGGLR6BOIYZUJiAfRxFX2Bj70S4j9MI90dpSjMYwpMEcPKyd355MUDUGBydH/9Hf3B23n9z/LcGgLMpfocBGo1GPaiLn19Cz9n17o3Y3NSfoKz+jzrwuT+oJtSt9xbX/M96s4lFVBX7v+7eiJfwYB8erLwUoF/gDkEcP4oHQFfsC7iDqP9Rh/XlhQyGSDTQZ0uM0jhOH4Aabh+hRg67NEacPrl6
*/