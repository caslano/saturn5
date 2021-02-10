//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_RGB_HPP
#define BOOST_GIL_RGB_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{

/// \brief Red
struct red_t {};

/// \brief Green
struct green_t {};

/// \brief Blue
struct blue_t {};
/// \}

/// \ingroup ColorSpaceModel
using rgb_t = mp11::mp_list<red_t, green_t, blue_t>;

/// \ingroup LayoutModel
using rgb_layout_t = layout<rgb_t>;

/// \ingroup LayoutModel
using bgr_layout_t = layout<rgb_t, mp11::mp_list_c<int, 2, 1, 0>>;

/// \ingroup ImageViewConstructors
/// \brief from raw RGB planar data
template <typename IC>
inline
auto planar_rgb_view(
    std::size_t width, std::size_t height,
    IC r, IC g, IC b,
    std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t> >::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t>>::view_t;

    return view_t(
        width, height,
        typename view_t::locator(
            planar_pixel_iterator<IC, rgb_t>(r, g, b),
            rowsize_in_bytes));
}

}}  // namespace boost::gil

#endif

/* rgb.hpp
FhHh6XHICPDvX/UuBkNWpXxo5og1ZUvidU3AtryLLavQ43kmjba511r2FrclKSMAIigoyjnwRuMIm5vLyal+iNjj8JyFCEZIOEEEDCUlDckV4naUEx7kLqHIGqxh22MVG2li6lKk+a/8StyxAXqR4EIr69DujJMbW2mKhqwREZ75nUtSIsf2z7bmd1coxxrXVNWUGXTHOnLkNn3VYIFqMeCLYyIbXK6OidA24js+EGTGtPIKO3I5XzZYlstQWMcuHZdRO2uG7KyNgI7tRbTCKSCRNcNTbovqkrpmdhmuSFYkJtb6KJ+RDBwbXy/yjBjzfRS92w5J8dS2qmDmvLUqTkvo9HT/FyNEz5h/H5LGmC6t3FkJGO9UhA2XrXMmz7TYJw8LUI/V9t66KcAPvUO431SCakSa41KYXMAw2ZizV6v/RXfVYwm1spzLycpKdvtnw+5usPkA2ulVVhhhiDAuMq8HJGJYleL3i0wU6gQHu3bjVje+p41Ck5BiVVmEEcMd+oaGJHRj/rIHWURWSWvtpqgSZVCKNJ7yQxLexmk5T+degfhNzeJP7HTgDKJlojNYYRrV1RA7PqrQCnor8zKeru6uUiXob6tqGABfHGj3nr2vt9g45hj7FHYfZ0Jfv4FphuRtZSJvH/agYsYv
*/