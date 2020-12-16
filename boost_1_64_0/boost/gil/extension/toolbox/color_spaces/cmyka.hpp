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
pvRimSuja6oKYJk8+M0WidFbOpluQHCm3xUUpJQQJC0nFVAZ5Jc8pFf03XWydL1YJst71UObfKTpIohum6qMKdnHS99Pa5x3vCjVyDNfoj55mbVk/Zw/FoMl3H2/uw1PhQndKR/OBmZJejnVXvbnMw+d8U0t8vjP5yt94r8MJ4Q1YxpT/6OdpWvFs/YT/6JUXsm26vmgWqWBmvqSQGXoX/h7pPtu/AXdUTgE39S8NVFc9cPVFZBZPLrIPDqSim2LHy8Cda++vtLSIfhh5pFvT+XnbNIitZNf4l0BhgQPX97QN56SwFL48bBWBTdUtD7Pu4wKkKLy9S5+UGKD+Qjvp5HjEsAaQBlgFWAnIAuQDshAmMcAy+A+CDCiOxqOuWyPEeZgjqy57qMJopUUBDcGwZP7oqLHzSzdr7TsDUJY9/zXkCpbHl4VtF7gXtSTXrSJU/SWZRPH2/DrcBunaAYlvyF8lrrn0p1ICjW4zRmucogjKfyrOlLD36sjPvyVOhLCnzhYz0lLw7vEgeNNuMKhDTc5jIZjW9zPVF+x/IvCz8FlXv0SxbeMxo3bpRIf9wgt6c3FABqpppW+fwak+JAedM8ksY8DZ/hlp+T4fPg6R3WLh4dayU8M+yw0teSGc5jXsZ3SVDupUpIj4ES4PdGfA63G8xab5cnyMnteWEj8jeqjxraK6UUeDdOLiP1PTW9V+AB/LdVfSWEhRu/WX6nh9fw1U391pfE8Fvrp8Ity/63ozPBj+CVVoy66s8193XX9HWFTsOtYmou1NJz58xEgcrM5T+NXRq4zzdV5JDLMuHeqAaNBxqXIJZF+5uQORt4b6WmO7BBkeqSj+VqdGZE2KNNjkXPwd1nkLPM+0GoL6YMXqhjgoMnZp13zGogtnsMwC8ybBxQ3pAo4zA/SXIk4HCdCOxN0uy2B9l3q8Iby3TVUppQ5QUwJ9UF3tnpaFvR3w6A77vyT1atUVviZUFgpnX9KiDNmD0pBDy/0rMOk0btsOvwu8i4EPrAGTL8A9HYEEPszCji4oMwpgqNvAOeddziXVafvrL0IH3CJmrPuu9maD0KjvfnkWtSMAWLWvq4jImX+cn1zudMpNPmBbvhmY4K7FxwWSnIHJuC7F0JJrBpUKGVG5jjp4dhmn3KJprESwcxj3aqrF/KrQotrMZDZTlA2tirOn4jSfMrMaYDwgUfFYcwPiMdWa8DmwXeBpFOYRf0pnXkG9ZJ1cr9i1wB7gWAvJXamYsn3OUuwA4kdB2weiaTSIrWTwFsFfXfUWE6kXFtrnkjFYs3iBIpHg8IlB446pvlnjAf7FhRV94kXlQCXPSX1/bgTLQd3BUelqdwQzaoEqzX4ldPj9gSWehd8HcgVvVxoQpQY7Q5us+oq5HvRUtfziC5kOUId1OP5jQuqLbG+jbal1cnv9Lal932iXkK1qMXegI5hU/UDnWUbBStkHd6EQ1XiX9hVNtgx8gtKKtriNw8OSiwc6UnfQBPxxY5ZdZHsmLsjXUlqkQOmyi88lwjxpT+64Yed3Km+amkuH60R7hgv9m+fxMr1MBKC0sC57NAne1jhadkeXWJWXaSIyaaoW60Fbruoyfemcoh2wKxY1zGmR04rW61FrgDcKoR61EsFf5/LRCl8DArsoORveLpoMGv+fLU649uogz0KeuP3XjHLuK680IFI/wJyS5AHNBpzoIbhb/t1IGI8KogvTQiaDLhp/inF3C7tFtqb5/YcYKgViEaNKsdQM3ZZuqqWQyrmH13QpOWzz1MCZnkXqy14JnkZP5RSuauLtPt+beDZgq80f+qqM+EO/C7g2/HuUWZ2dRfp0l5qQGeInSI7da/pr3HV9OIes7APC8Y=
*/