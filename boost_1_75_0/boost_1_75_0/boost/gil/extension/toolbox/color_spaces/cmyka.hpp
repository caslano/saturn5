//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_CMYKA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_CMYKA_HPP

#include <boost/gil/cmyk.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// \ingroup ColorSpaceModel
using cmyka_t = mp11::mp_list<cyan_t, magenta_t, yellow_t, black_t, alpha_t>;

/// \ingroup LayoutModel
using cmyka_layout_t = layout<cmyka_t>;

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, cmyka)

///// \ingroup ColorConvert
///// \brief Converting CMYKA to any pixel type. Note: Supports homogeneous pixels only.
//template <typename C2>
//struct default_color_converter_impl<cmyka_t,C2> {
//    template <typename P1, typename P2>
//    void operator()(const P1& src, P2& dst) const {
//        using T1 = typename channel_type<P1>::type;
//        default_color_converter_impl<cmyk_t,C2>()(
//            pixel<T1,cmyk_layout_t>(channel_multiply(get_color(src,cyan_t()),  get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,magenta_t()),get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,yellow_t()), get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,black_t()), get_color(src,alpha_t())))
//            ,dst);
//    }
//};
template <>
struct default_color_converter_impl<cmyka_t,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T1 = typename channel_type<P1>::type;
        default_color_converter_impl<cmyk_t,rgba_t>()(
            pixel<T1,cmyk_layout_t>(get_color(src,cyan_t()),
                                    get_color(src,magenta_t()),
                                    get_color(src,yellow_t()),
                                    get_color(src,black_t()))
            ,dst);
    }
};

/// \ingroup ColorConvert
/// \brief Unfortunately CMYKA to CMYKA must be explicitly provided - otherwise we get ambiguous specialization error.
template <>
struct default_color_converter_impl<cmyka_t,cmyka_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        static_for_each(src,dst,default_channel_converter());
    }
};

} // namespace gil
} // namespace boost

#endif

/* cmyka.hpp
9q/XaDtGJ2lijLpsQ0GucQD6whWl3b9aU2lprSYiK0uDnyIxaYwGk8E4yJCmRV/nopz8tYFa3+BAnxAt50NRllKassy3h2nC0dPW5jaFoZq0LF2qj3/zqKhuiZ26x3WMiI3mAkMg3ajL0WeEAuIsg85k8PbVQqFEox499ReqyTCb80yh3t79Ms0Z+alafW62d1quOcdg9tbnGg3pg73NRoPBOyiQ80n3Tw/09Q3ggkPS01N9Q3zS9EFpAcG+IX76oNTU9AB9QJp/OvoCGXI/1QJCIQrYCGB9dRuFvjFGyfnHT9FTjcIkY76BQBOM6HnNuJzU3ME8FI0LHkCW5r9khwYoKrpN11j00S6qLXky0auxJjdHY//FEk1BJpBUl1WgKzRpzGiQNQA0WIddq+lqMmhattRk5sAA6xCx29BUS7v3nvzrKHHfKfQNMircvln/XnNCaSrgveb8vWbE0FTEx58K1jq8kqlppd+boXrQVBf0AKoJajRnaAz8WyY1RttDtRqd0aDJyTVrTNa3eEAHoE2ZJs0g4n7T5KZrCnPzjRo9/9yxlkYfkaPUDgvL/vMsaCIoh1hf7ebVuJlRVzAMfciOEuJXL6GpVc3qH6zwsRfKm6aaVNjf/bGPxVDNoSX4KYlQzRDr43hassl+GLALhRC9nJa1psActH478YqYok4efbgbDfg0+GVVfLzYFkL1G4z/Uc9kvfcrI8Ns
*/