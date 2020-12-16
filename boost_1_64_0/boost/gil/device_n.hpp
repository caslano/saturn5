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
nS6XpOmWKurP4u3AdfLT37p7DusyOJ7oqot8YLKl+SdzXfnoFmCExuXHttGRh/rzmQQ7/Q34yW7y0YXOGLmJF/jLRQqXNlrfcT/f0lrk5fERT3n6Ax3mM2ijHXFAGcp7cQYtfI/Dk4+cg8drJbvcvLAsEr1CPaPXFPZbawq1RCqshpVMJrWsNYW499jTn8AeCc4h5eFbQ7dZDtdT2VxtEP5t9H2F/l7DveD07U7629Bj64VsENTgD4LtHMbXM47lsqA6HJNQzwm/c0/GFUBPc0DO3vghAZIF/ZgKcfsGtay7Er5R4OSvy2E3CQyGMbxJ0gWJ38UJS8kgHHG4cWfgSdpj4r6bSKcb93UG88Z9dydsfd9g7nGM42+BV+EGE93LKNJ9Txkel6TmsyZsn8ByxWpxqBC/U7KZ8HuZdDn3l2oZ4Lp5o96v2jvE8d9b4G78WwTG8VO+PfWu6rfKUF4lKPLxxD0BtUHUjRhbaWHqnulidW9Wf6D3yoi7ystFKSYzIMZ1+7HQJ3rppkwRqTym7yvi71pFaFwLKZ+AQxcH1zGAQrKhQ8ypoM3Uk+L7avE9RWmfhs7QBY/24QkNPB2qNboHYSsEJiIjHPoIXGQscPKRwc+9XP9PgYcrgC/h13mZcJ9f5/6VhHl8Ny8T1s13s7mKcI/v5i2EdfPdPLoa+DJ9Nw+sAXeZvpvbbuNwZ/Aj8FM+fIfw2biK8CV8Oy8SR/h2svyXrxWY8u2jwtJhbyXc5/t55LbAlvD9vO5q4Mvw/Tzj8igTNJ65nQ/fwfHcpPBl+IY214G3hG/oIuGub+gGwsevAW58Njncr6Lv0Xg5OhP7MKBqCp/Fa314fUD6SC76OZP4HTwja/z2nTx6wpdlXejOgTCT3qC3kzfdOmh8Gjx4qzGFhVKjd3iHLhzSu1/vvyve8uxEXt8+fkeEWXrOyPKffSdwlz1fisP8aj3CLHO+tJvC3HpnhFn+3IfTcmIDwi0992Pu/o3gLj2nRBpI7iZwlzl/02FuvgvCLHtuTHvOd0OYZc6Ndf1afXeEcXyPZZ0/GuHq6huvec68W5nnM/uF7/c9wHP8etGEuT7/3YPTFgfHNXXPTg67PYu0nSdeNx/jTF8nTq7MzLmJOD4/ZPYxuZfkYCtcxSLwr7k4SeA2vhn4Er7JZzpwVsH0v/eWHM4N47MucUe/dVskxt7THPZ1Eqcc0tj6+wiMNps0doPESGVdhmvvqzBU1XiowdIgTe3Jj0mP06fvB570HZ5rRq4Q6WjCVVDdDe8FHtgK7hJz94ewjzF4y5h76rZ+6gHgLz3XZtmPfCC4V56bMf+9Dwb/yvNsTuPOhxDfPw82/jPE67qWIHQ++1BwlzF317J7d4C/9JoG90kjO8Fd3nyZ0/hXCuOdL4u2mXiYy0PeYp25ITjtAR+nMQYWc952vY9zeFbWw9c9wsdponI30SNPwyPZxPmmR/q4c61RodfLH+3joHaLcinsAWcZaxmcbwnie4tE1NEseMtY89ByV+eI71uXkPduPbcnXpd42naqP5FX0+y44GwzHIq1k3PLcwzHkcSc85JDklxOn4irv4ucHovjl3M2imvclzDmHCeOL2F8nxhz6gcxiENMRxaY9UXiepUX96M2iedNgLhj9ZVyX5/uCuR1/zPu3lu8d4J9tw5frN6/9NB+SGxV0Exhjsvu9+5+2ujYWKPZBlTXnMQfXA76nRmYo+BwPE/Ue1vz0QY1vdIzxuX23xXyjiW5d1PXaT7+g9WkK/rGWF1Ox8gLVxAmvTtMnvT9DLgO618D57If+Y3YZ3M8CrW8I78ExznLQIMIBRL1X3JZ5sHZ+Zlxs+b9M2ePiEQSm+M9vtc=
*/