//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CMYK_HPP
#define BOOST_GIL_CMYK_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{

/// \brief Cyan
struct cyan_t {};

/// \brief Magenta
struct magenta_t {};

/// \brief Yellow
struct yellow_t {};

/// \brief Black
struct black_t {};
/// \}

/// \ingroup ColorSpaceModel
using cmyk_t = mp11::mp_list<cyan_t, magenta_t, yellow_t, black_t>;

/// \ingroup LayoutModel
using cmyk_layout_t = layout<cmyk_t>;

/// \ingroup ImageViewConstructors
/// \brief from raw CMYK planar data
template <typename IC>
inline typename type_from_x_iterator<planar_pixel_iterator<IC,cmyk_t> >::view_t
planar_cmyk_view(std::size_t width, std::size_t height, IC c, IC m, IC y, IC k, std::ptrdiff_t rowsize_in_bytes)
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,cmyk_t> >::view_t;
    return view_t(width, height, typename view_t::locator(planar_pixel_iterator<IC,cmyk_t>(c,m,y,k), rowsize_in_bytes));
}

} }  // namespace gil

#endif

/* cmyk.hpp
pQWLcwrRyPBnJvMz0kmZKGH4l0HLzS8pC+FYFxpf4Vo110iozM0rOngRcxS39qpbyIqs9uvjdErkln7aTTsRWiM0kwFiI3Q1lsijjOt6cW5ZfhlWKSkoWmzyZ2jXWvXFyYvziyhVaNFdlZ8K35qT4nwMyvgywHoc2eGweK6z6rInz1xVZOxn2OIy3gxPST62zwsV5lyYXxKQ3r9x6V2UszRfpRzd7oCuWTt/RSgvpyzHKrfDKhdvryC4JL/Ekcqy1yUJuVdZE6WhWbp3u21Jp6G9bC422fx++Gyl4E/SZzw0j8Lxvn3UXOci1qYflgaO49pHqY88+KvcuInXu9dVtnBJaElO6ZJFy4py4+WfhcZ1NC3Kt230vKuv5PGOLEafQZcN8eyCRReGgjklOUu9+hwwdRfnnp+Tl1cSv0Oaszg/tCKY5EMYoix/caJ/Cicn2i67MJjv1Cn65yd7ZUtwGN1LoQeXXYCFLP4VfvzqOKP/F6HbMgY0vr7MNaOce7xUcs3WubC4+PxlwYRNjE9+08dvHQbVO5XPwmI8NYh0slGNq15HEY2ZVpfs8vEyE5QcDTQeLp+cNB4844q25RPLnMa5lmSrUK4tz3fNNTMNFObnFKHk4pLiZUFoxrZXQCsoChlTxW1y9Yi+UpOSv380+W3DqN7IBNrMXZJTIn2esMqZ52aY4VipV/KKgVO5bwxIDgEad09N9vdTscl+ybFpWdmieR4DWmNisiduePrg7156PlPDhWpJvnkKvGtZEjcxLs3vQ5SJBwXZoW+yNRbZwffr11w/ud5ytZtbUphoUPHsbdOG7eAMtrmS96gpfnXLBeXTx07x7QexWPVPgSeZAV2k6wVEXz484z3nbKsta1x9ZIpnHnIp8Anjt1M0rsqCZCTFZQxgJlLzdVGBPMmxxTx4XRkMXbC8oATm5XMsnT/rq49dhSXPginefpa66qOcKcZXrQBjfKxQ/F4fUy+pHHYyPm7Gn+xRTLmkbtH1FVx3TRSO/b7A9cLgBaU5xbRSmBMMQjI6nUX/oszIndZQdYM9pkOWjGsaazWKXDGp3LRH+9aoxgbqK/dEXfCF/LyyArIa13hdU2HdmjE2qJriP86988HqOB/uXVi82EtrdPRm1i4Ixn0hIHmaodlzb/FSV+CVPOl8LrywLH+Ery0scLIQw9cS7zvTdbTp0wehCzLPLw3OidexHlr+8qAme0scY++25Hm+grQ+oYrG1jcSPkESUcYIw2VledvPvj3Fm09IK42rtjgdDRIjwvIjzSFqS33rjOOFhejjNOXtzyCmiPeMjCJ7fQ+d3BOXfX0SvoULOE995y60rv9QsmvudcbflSN0Elk6b3bZpaxkWalrKlbeghw4W6jMaudaxyfyChYjs63z9a56cspQZeGyMjmb5gdk9M0jxaHYsu3IscUWDl9h7kvqd3WJ5I5SH/uRZ2Uqrp/K7zwFvylu+8vsxhazjW6uYIWHmVVEbr58evIEE7eXFJfIFr+FXwErcnFLuCUsW1zt449JY1zy0JQWIVxTfG5B6DlzEVptbqYuqyKr7h0+vuWNh3fDQxlnzrrPr288c/duXx7ZVPn0w1PcubAq0Lz0mO/4kmDKd/bCw+4/ezpkwcpHBrjmuwbxzGlPm74h8SH9wRHK8pWXqLw3T1Bh+cnP3P3h8e/nKb9w2aLQUvJ0004av/NYyMUD1dKcoN0Pp04wsd7yIOMrL7r0ZcHHCjI5lix2xklBaekyhp3ZNSxlMsopjMv9sq/cyfnrq1P88pfk8f2GeJRruP1M41d+PzfLWt9aPs5MtjTIeLJdPV7XO666vHm8sc3Yqa4Yo2bMmB3Pdc88yKRg6o+PXTo=
*/