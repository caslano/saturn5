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
+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
*/