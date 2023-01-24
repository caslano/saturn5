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
sQPP+6spoEOhAg5cadRBriCuWZ5GrUWE9UnBFTYHdEIn5LVpvSwd40Yu/AfwKTvQ2WRNJ7fPaXG4rXgr3UussQyby6v62jZgwFzkR/cCZAC/R3p+Iki01fQ8Xtg3sJPfdR544/FwC3Ci1Hu6adb0gKwCAvO3MjVtbzcTto56IvfzN0tor65FpW4/X0Nor96DAbfKDQVjXX1a9FdvA4qb8Avr282rz/RXqIkcvmJPHKnQGW5f0NOnVO8YAIdv/RNzgaHPZ+hsdzgIvthc09GtNuZW8TF2mWH3pUCHjDJLdV6c3HnvMSRAS9hW6n5TisuMp8nToZgh75hnNHOkPqoWeTL5h8h4faHHs3jpIxZG9mDE/uhVlSYP+JbfbkjJ0OCXj0ZKwpbvg86TTfTaKN7TkKe0g2968erPwLwOXJ496by0QJrTk02w2hzZlbezKu+tflo8lNCSBvxtRcc/1k3+9Ga47GU8YkZ09IkfCrSg+xhYcWCpjB9Gco/wd+y+TqyJusezsjgb9CKjNOo0hQghBMLKGCIrOpOWaUd27Jfn1hc6lcYmfdkiPkICVPP14qD+VWY1ZpN4nrWVhpWZ6vUlI5m3ZZfE9sRCCJ9IupB/Yi/EqjOoV4vzMLR+bv3Ls9kTHp4OU4HlgD2X6qKUiPrFHluPqiJPH2+T1aG5wrK8l0gXwrPfztgiI7tKgqEGEshlg4AjAP7xOFGEivHL
*/