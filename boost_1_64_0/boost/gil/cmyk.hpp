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
96U/eVR7lQkEMxihT9EPQkwVJZNcHV8TedMEwJn9ooA1yrhhhk122UK54lica+UchGQAUbEEmQXhGiDtKweB6FawSDJKfUX0l3DKdzpyDmWA7tilJIlAqOgwK3dSOnKM5SO/kXAnGFISw+mFpP7gCazgSGfxH0TGz6wapOJrGD6HABTPcRaOfBPwMbmML7q7wQss00sovht9ohVIgfoki1FmVmUoAwTulucQvl0kE/fmuSzo4TMMkm0Lct3s1rA8tObZQ+S7vClFbGH6+OFhls5ct9tCC84S3Fss+fWJ/hcR1xKq8Au8h9+AsJQf0wcm+aMS3UCEi4dCUKkY+7di57JnSHHXSwY5vhzbGbN8QLL8jx1KVySwbaV/6oNUG8BkfGwjC8DU9vi17NH0Zoj4fo8vOuWOAMdmjaQzlkxwb07nVUNjvgA/vEjGiizhnz1irKnV8iz6CP8Qvf04lwBytEtO5W4xqR2pwsAhKpQkyrpkAPHpmwpnFtOibJYLvBB2lh5KQItHQXMDToy2BD+3h/CEgfhy6i9H3VAe+7ZSl3PcVLBdEQnelkfR/A==
*/