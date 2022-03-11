//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DEVICE_N_HPP
#define BOOST_GIL_DEVICE_N_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/config.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {


// TODO: Document the DeviceN Color Space and Color Model
// with reference to the Adobe documentation
// https://www.adobe.com/content/dam/acom/en/devnet/postscript/pdfs/TN5604.DeviceN_Color.pdf

/// \brief unnamed color
/// \ingroup ColorNameModel
template <int N>
struct devicen_color_t {};

template <int N>
struct devicen_t;

/// \brief Unnamed color space of 1, 3, 4, or 5 channels
/// \tparam N Number of color components (1, 3, 4 or 5).
/// \ingroup ColorSpaceModel
template <int N>
struct devicen_t
{
private:
    template <typename T>
    using color_t = devicen_color_t<T::value>;

    static_assert(
        N == 1 || (3 <= N && N <= 5),
        "invalid number of DeviceN color components");

public:
    using type = mp11::mp_transform<color_t, mp11::mp_iota_c<N>>;
};

/// \brief unnamed color layout of up to five channels
/// \ingroup LayoutModel
template <int N>
struct devicen_layout_t : layout<typename devicen_t<N>::type> {};

/// \ingroup ImageViewConstructors
/// \brief from 2-channel planar data
template <typename IC>
inline typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<2>>>::view_t
planar_devicen_view(std::size_t width, std::size_t height, IC c0, IC c1, std::ptrdiff_t rowsize_in_bytes)
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<2>>>::view_t;
    return view_t(width, height, typename view_t::locator(typename view_t::x_iterator(c0,c1), rowsize_in_bytes));
}

/// \ingroup ImageViewConstructors
/// \brief from 3-channel planar data
template <typename IC>
inline
auto planar_devicen_view(std::size_t width, std::size_t height, IC c0, IC c1, IC c2, std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<3>>>::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<3>>>::view_t;
    return view_t(width, height, typename view_t::locator(typename view_t::x_iterator(c0,c1,c2), rowsize_in_bytes));
}

/// \ingroup ImageViewConstructors
/// \brief from 4-channel planar data
template <typename IC>
inline
auto planar_devicen_view(std::size_t width, std::size_t height, IC c0, IC c1, IC c2, IC c3, std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<4>>>::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<4>>>::view_t;
    return view_t(width, height, typename view_t::locator(typename view_t::x_iterator(c0,c1,c2,c3), rowsize_in_bytes));
}

/// \ingroup ImageViewConstructors
/// \brief from 5-channel planar data
template <typename IC>
inline
auto planar_devicen_view(std::size_t width, std::size_t height, IC c0, IC c1, IC c2, IC c3, IC c4, std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<5>>>::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,devicen_t<5>>>::view_t;
    return view_t(width, height, typename view_t::locator(typename view_t::x_iterator(c0,c1,c2,c3,c4), rowsize_in_bytes));
}

}}  // namespace boost::gil

#endif

/* device_n.hpp
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
*/