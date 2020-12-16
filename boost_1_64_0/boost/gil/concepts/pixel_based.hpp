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
qeszeNBmVq+V7oLfv/iZzR/yQViHx1YF/zrR+t+o63/xdh9gNl1bHMD3rTqjRC9XfeqYwWgRrt7lEt1gMKOXMTNESRiiE+aJIFpGiUQfIfqTESJEMHpnRO9DRER968zc+Z917stdee99rnzf+yLvZ++z125nn3PP2YcenvbVfIas9bj9LlrUGff1sXZDZF5QXN4UzZv8bbvk21Rp3kbcUcN8FTbljKhfv1Yp/6Z/8N/4J0/yXjSp30st5POYaXN/XwWNrNl8dsui6rvHdn6thZuMWuZelSmXX8qfGmX1eVtrL88McP/LF8H/R/5Yp5msiL8Aj5/uFFSqlfKnYe/5fG7j5aMt6wf6pAd4HsSzLyTMsao87ms+7TeLGxM69k7RnGrSO+75Ludb7QtdQ6P6+2TG/8uD8DXdCSt+h6ZTG36HVuodNS27ez7I/nbrwkeru788Bu6fv9bHh8MwPnKopAYpf9pS5+2Oj8iIoT65pPmrg/A+4VpmU33d6wHt3mSbPv77UjS72udeD7gy+bpPRAVq7yv6IH5kbIh5n01NdLd/EW3dv3Jb+hTNpm66/xTu8zWQVjSfLAWQMY85+rhNfe2OWdtLtseBeUdTNKta1iPlT08/oDs3vo7ZNwMeGfOYY9fY8ftTMe3Kta/LnqJ+ys99Pdfe52s+Kho9pB7WyzdR61mr/2Ldl+UtrvuocFGUj2/CRs4Y0/Tj1zF3W5fQ3mOwXz2XElUmNS6z+z5NFl/P6XTOpUk23Bcxp+T8X67vK9P9ePaPR8z8QzP+9ID5GyyqIWv6D7RPPH2DoVvyXTNXSElD2aqrLfQXUvcWtrrLWsWtPasHd+9DT2D3CYsMbjxQe0A9LLQPncyCh/aIohfrI4MHRGov7/unbFdA2x/17Vo5oEqlSlUCKgYEU2WFBncbEFq5UrD7Qw5dU5smNGxosLvMbesGt07OqvkH9MfASv6BAf4VgtzRBFOkydCqdT13QIjJmWjH72Tab3f9rp94L0Vr0Phy30Og/6VJrf83HVOvSPcbGG8mrOT18mW7CnS3U2lDO1VTiX/RTqY3HRP9i3YE6BX5ZkL6m3HynnIvdpKfpUzvo3aiYFI2t34zIf1NTA3VMv6fPorJvdHoG4nIpJL37MfzguW0S/jmce5992omf18/9V3KzD6Kp1eke8v3NxKR+3rrhh3rTP/kb8L0KZSijZWDfjVP/b7sOz6Kiab21G0a3khUJvce9dncv4doP6ifnNjiVEqpa6mN9P+nfrMug49ionaKHBL+5hrKlLKnKX4vD9BGUPtt7hHVRMVpf0H7O2a6OvRRTKydkl+pfzORudf9FFtOd2zavB56+usMKdoI83m42Xd9MGpg8keAh4S/oaBM7n2m07pj0h4iOebKUztFG6i5Zvd8Tv/O7aOYhP2Y30iUppS9tPDsR0VtRZHWvbRQzVRV98xYNb3v+uSQqD796dMMbywe2hcebVbJ0GZ1VVWTu0f6cN5gW8K/oZmD4nLvHZHFHZd2/iq5eVmTFG2hQt3nrW+sPm8n7d3dflGD3swoM6V8Bw/PAlXW7pYeyrDI3etURvcYS6C/mN1HcSU3lLY11BtaB5rc3+bL445Ju76oe6BoUIo6lUv7C8n3zn23xkj+skSPnr3eTER/tw5sisX5TZPv+p/+mm/Em5n8UscVtVW0+759NW1Pk+nP3OWvQvvku+/d+LCtuvYIH5K88+0b7H/0XQc866ddNy4pM2t/itanbwq4Y9L+ro9iSv3gw5u6DjG5v5FR3B0Tna/oeb9eHVO0nsrxFmJK2a4pLCp5E7k3s8xNuR4x622lvb/WocnhkSlaG2vCYT48XyV/G+bNLnVT2os=
*/