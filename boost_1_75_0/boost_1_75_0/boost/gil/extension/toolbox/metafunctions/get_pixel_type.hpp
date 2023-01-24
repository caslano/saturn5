//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// get_pixel_type metafunction
/// \brief Depending on Image this function generates either
///        the pixel type or the reference type in case
///        the image is bit_aligned.
template<typename View>
struct get_pixel_type
{
    using type = mp11::mp_if
        <
            is_bit_aligned<typename View::value_type>,
            typename View::reference,
            typename View::value_type
        >;
};

template<typename Views>
struct get_pixel_type<any_image_view<Views>>
{
    using type = any_image_pixel_t;
};

}} // namespace boost::gil

#endif

/* get_pixel_type.hpp
p3PHDm14wcy1M+U2K/u9FfWYqaFz7RSf37k9BtdVMBuYXiU0j25YQF/EewvDvUj2aI9WYAwrhcTs0ZUMTxaSSjIblaKXOPsEnVAeDUUNC1XxSvQA6SX0nhNll5Rc63FrXeTp/mHcjCf2dxNM1nYT3qXOktpnu/NMLHaxLffvpaZmyrROT/AvBGDMY169/q8KM9uBg9tpbmZAy6pGBctMgPHpo+vFkKIxJb9ZyAOi5HK+AIMPul+QR3/yLF1dg/lh+0KSC8iggJ86v8vv0xQ7FvaCteJSyJxOleAD06WHxsiW3l4BwsVl5zFFoV35JF6Uqj+VpIW1anlwAGOropXXdhOlQw01/WitUCx/bC36LQYslhGyOkBGTWsT9egiEvVFrSYtmyfqUenhwcvxTyAN6ts7R1EYOvGNQ9cNCzFy+mswE9Fpr7ALEN5lcLr8qQ4o1SOBymxQ6jOCsS2DXBQvC+uzL1zwNGKNhR8LbmEyAriDfmZujk5tPliMIy9BRlccxsga6O7WDvpRx7EifDwmpxX1tKxG32mko3MS9H35DnVs8YZKKFMp84Sx3gueXoOLIW9huXglYQHgBcHrhaik6qys0bZbLlDEZ6PRSiY/68XGUc4L1kPaOkflvHnoX6bFHbVRP3J4lGXlJ+CEzglw9BB+XqOsxKx+4t3iNxgrCT8XMC+JHWSSNUEuLvsqNDPxDqderMoC1dKG1Gwh
*/